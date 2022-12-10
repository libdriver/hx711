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
 * @file      driver_hx711_register_test.c
 * @brief     driver hx711 register test source file
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

#include "driver_hx711_register_test.h"

static hx711_handle_t gs_handle;        /**< hx711 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t hx711_register_test(void)
{
    uint8_t res;
    hx711_mode_t mode;
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
    
    /* get chip information */
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
    
    /* start register test */
    hx711_interface_debug_print("hx711: start register test.\n");
    
    /* hx711 init */
    res = hx711_init(&gs_handle);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: init failed.\n");
        
        return 1;
    }
    
    /* hx711_set_mode/hx711_get_mode test */
    hx711_interface_debug_print("hx711: hx711_set_mode/hx711_get_mode test.\n");
    
    /* set CHANNEL_A_GAIN_128 */
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_A_GAIN_128);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }        
    hx711_interface_debug_print("hx711: set channel a gain 128 mode.\n");
    res = hx711_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: get mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    hx711_interface_debug_print("hx711: check mode %s.\n", mode==HX711_MODE_CHANNEL_A_GAIN_128?"ok":"error");
    
    /* set CHANNEL_B_GAIN_32 */
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_B_GAIN_32);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    hx711_interface_debug_print("hx711: set channel b gain 32 mode.\n");
    res = hx711_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: get mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    hx711_interface_debug_print("hx711: check mode %s.\n", mode==HX711_MODE_CHANNEL_B_GAIN_32?"ok":"error");
    
    /* set CHANNEL_A_GAIN_64 */
    res = hx711_set_mode(&gs_handle, HX711_MODE_CHANNEL_A_GAIN_64);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: set mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    hx711_interface_debug_print("hx711: set channel a gain 64 mode.\n");
    res = hx711_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hx711_interface_debug_print("hx711: get mode failed.\n");
        (void)hx711_deinit(&gs_handle);
        
        return 1;
    }
    hx711_interface_debug_print("hx711: check mode %s.\n", mode==HX711_MODE_CHANNEL_A_GAIN_64?"ok":"error");
    
    /* finish register test */
    hx711_interface_debug_print("hx711: finish register test.\n");
    (void)hx711_deinit(&gs_handle);
    
    return 0;
}
