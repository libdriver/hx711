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
 * @file      driver_hx711_basic.c
 * @brief     driver hx711 basic source file
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
  
#include "driver_hx711_basic.h"

static hx711_handle_t gs_handle;        /**< hx711 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hx711_basic_init(void)
{
    uint8_t res;
   
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
   
    /* hx711 init */
    res = hx711_init(&gs_handle);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: init failed.\n");
        
        return 1;
    }
    
    /* set default mode */
    res = hx711_set_mode(&gs_handle, HX711_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *raw_voltage points to a raw adc buffer
 * @param[out] *voltage_v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hx711_basic_read(int32_t *raw_voltage, double *voltage_v)
{
    /* read data */
    if (hx711_read(&gs_handle, raw_voltage, voltage_v) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hx711_basic_deinit(void)
{
    /* deinit hx711 */
    if (hx711_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
