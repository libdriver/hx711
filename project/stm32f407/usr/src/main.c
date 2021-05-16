/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-27
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/27  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_hx711_basic.h"
#include "driver_hx711_register_test.h"
#include "driver_hx711_read_test.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "wire.h"
#include "shell.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     hx711 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t hx711(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            hx711_info_t info;
            
            /* print hx711 information */
            hx711_info(&info);
            hx711_interface_debug_print("hx711: chip is %s.\n", info.chip_name);
            hx711_interface_debug_print("hx711: manufacturer is %s.\n", info.manufacturer_name);
            hx711_interface_debug_print("hx711: interface is %s.\n", info.interface);
            hx711_interface_debug_print("hx711: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            hx711_interface_debug_print("hx711: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            hx711_interface_debug_print("hx711: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            hx711_interface_debug_print("hx711: max current is %0.2fmA.\n", info.max_current_ma);
            hx711_interface_debug_print("hx711: max temperature is %0.1fC.\n", info.temperature_max);
            hx711_interface_debug_print("hx711: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            hx711_interface_debug_print("hx711: SCK pin connected to GPIOA PIN7.\n");
            hx711_interface_debug_print("hx711: DT pin connected to GPIOA PIN8.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            
            help:
            
            hx711_interface_debug_print("hx711 -h\n\tshow hx711 help.\n");
            hx711_interface_debug_print("hx711 -i\n\tshow hx711 chip and driver information.\n");
            hx711_interface_debug_print("hx711 -p\n\tshow hx711 pin connections of the current board.\n");
            hx711_interface_debug_print("hx711 -t reg\n\trun hx711 register test.\n");
            hx711_interface_debug_print("hx711 -t read <times>\n\trun hx711 read times.times means test times.\n");
            hx711_interface_debug_print("hx711 -c read <times>\n\trun hx711 read function.times means read times.\n");
            
            return 0;
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* register test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run register test */
                if (hx711_register_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (hx711_read_test(atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run common function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* function read */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile int32_t raw_voltage;
                volatile double voltage_v;
                
                res = hx711_basic_init();
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    res = hx711_basic_read((int32_t *)&raw_voltage, (double *)&voltage_v);
                    if (res)
                    {
                        hx711_basic_deinit();
                        
                        return 1;
                    }
                    delay_ms(1000);
                    hx711_interface_debug_print("hx711: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    hx711_interface_debug_print("hx711: raw voltage is %d.\n", raw_voltage);
                    hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v); 
                }
                hx711_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register hx711 fuction */
    shell_init();
    shell_register("hx711", hx711);
    uart1_print("hx711: welcome to libdriver hx711.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("hx711: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("hx711: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("hx711: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("hx711: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("hx711: param is invalid.\n");
            }
            else
            {
                uart1_print("hx711: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
