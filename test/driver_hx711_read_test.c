/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
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
 * @file      driver_hx711_read_test.c
 * @brief     driver hx711 read test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-27
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/27  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/08  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_hx711_read_test.h"

static hx711_handle_t gs_handle;        /**< hx711 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t hx711_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    int32_t raw;
    double voltage_v;
    hx711_info_t info;
    
    /* link interface function */
    DRIVER_HX711_LINK_INIT(&gs_handle, hx711_handle_t);
    DRIVER_HX711_LINK_BUS_INIT(&gs_handle, hx711_interface_bus_init);
    DRIVER_HX711_LINK_BUS_DEINIT(&gs_handle, hx711_interface_bus_deinit);
    DRIVER_HX711_LINK_BUS_READ(&gs_handle, hx711_interface_bus_read);
    DRIVER_HX711_LINK_CLOCK_INIT(&gs_handle, hx711_interface_clock_init);
    DRIVER_HX711_LINK_CLOCK_DEINIT(&gs_handle, hx711_interface_clock_deinit);
    DRIVER_HX711_LINK_CLOCK_WRITE(&gs_handle, hx711_interface_clock_write);
    DRIVER_HX711_LINK_DELAY_US(&gs_handle, hx711_interface_delay_us);
    DRIVER_HX711_LINK_ENABLE_IRQ(&gs_handle, hx711_interface_enable_irq);
    DRIVER_HX711_LINK_DISABLE_IRQ(&gs_handle, hx711_interface_disable_irq);
    DRIVER_HX711_LINK_DEBUG_PRINT(&gs_handle, hx711_interface_debug_print);
    
    /* get hx711 info */
    res = hx711_info(&info);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip information */
        hx711_interface_debug_print("hx711: chip is %s.\n", info.chip_name);
        hx711_interface_debug_print("hx711: manufacturer is %s.\n", info.manufacturer_name);
        hx711_interface_debug_print("hx711: interface is %s.\n", info.interface);
        hx711_interface_debug_print("hx711: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        hx711_interface_debug_print("hx711: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        hx711_interface_debug_print("hx711: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        hx711_interface_debug_print("hx711: max current is %0.2fmA.\n", info.max_current_ma);
        hx711_interface_debug_print("hx711: max temperature is %0.1fC.\n", info.temperature_max);
        hx711_interface_debug_print("hx711: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    hx711_interface_debug_print("hx711: start read test.\n");
    res = hx711_init(&gs_handle);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: init failed.\n");
       
        return 1;
    }
    
    /* start channel A 128 gain mode test */
    hx711_interface_debug_print("hx711: channel A 128 gain mode test.\n");
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_A_GAIN_128);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = hx711_read(&gs_handle, (int32_t *)&raw, (double *)&voltage_v);
        if (res != 0)
        {
            hx711_interface_debug_print("hx711: read failed.\n");
            (void)hx711_deinit(&gs_handle);
            
            return 1;
        }
        hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v * 1000.0);
        hx711_interface_delay_us(1000L * 2000L);
    }
    
    /* start channel B 32 gain mode test */
    hx711_interface_debug_print("hx711: channel B 32 gain mode test.\n");
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_B_GAIN_32);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }    
    for (i = 0; i < times; i++)
    {
        res = hx711_read(&gs_handle, (int32_t *)&raw, (double *)&voltage_v);
        if (res != 0)
        {
            hx711_interface_debug_print("hx711: read failed.\n");
            (void)hx711_deinit(&gs_handle);
            
            return 1;
        }
        hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v * 1000.0);
        hx711_interface_delay_us(1000L * 2000L);
    }
    
    /* start channel A 64 gain mode test */
    hx711_interface_debug_print("hx711: channel A 64 gain mode test.\n");
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_A_GAIN_64);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        res = hx711_read(&gs_handle, (int32_t *)&raw, (double *)&voltage_v);
        if (res != 0)
        {
            hx711_interface_debug_print("hx711: read failed.\n");
            (void)hx711_deinit(&gs_handle);
            
            return 1;
        }
        hx711_interface_debug_print("hx711: voltage is %fmV.\n", voltage_v * 1000.0);
        hx711_interface_delay_us(1000L * 2000L);
    }
    
    /* finish read test */
    hx711_interface_debug_print("hx711: finish read test.\n");
    (void)hx711_deinit(&gs_handle);
    
    return 0;
}
