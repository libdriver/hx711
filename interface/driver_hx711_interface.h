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
 * @file      driver_hx711_interface.h
 * @brief     driver hx711 interface header file
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

#ifndef DRIVER_HX711_INTERFACE_H
#define DRIVER_HX711_INTERFACE_H

#include "driver_hx711.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hx711_interface_driver hx711 interface driver function
 * @brief    hx711 interface driver modules
 * @ingroup  hx711_driver
 * @{
 */

/**
 * @brief  interface bus init
 * @return status code
 *         - 0 success
 *         - 1 bus init failed
 * @note   none
 */
uint8_t hx711_interface_bus_init(void);

/**
 * @brief  interface bus deinit
 * @return status code
 *         - 0 success
 *         - 1 bus deinit failed
 * @note   none
 */
uint8_t hx711_interface_bus_deinit(void);

/**
 * @brief      interface bus read
 * @param[out] *value pointer to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hx711_interface_bus_read(uint8_t *value);

/**
 * @brief  interface clock init
 * @return status code
 *         - 0 success
 *         - 1 clock init failed
 * @note   none
 */
uint8_t hx711_interface_clock_init(void);

/**
 * @brief  interface clock deinit
 * @return status code
 *         - 0 success
 *         - 1 clock deinit failed
 * @note   none
 */
uint8_t hx711_interface_clock_deinit(void);

/**
 * @brief     interface clock write
 * @param[in] value written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t hx711_interface_clock_write(uint8_t value);

/**
 * @brief     interface delay us
 * @param[in] us time
 * @note      none
 */
void hx711_interface_delay_us(uint32_t us);

/**
 * @brief interface enable the interrupt
 * @note  none
 */
void hx711_interface_enable_irq(void);

/**
 * @brief interface disable the interrupt
 * @note  none
 */
void hx711_interface_disable_irq(void);

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void hx711_interface_debug_print(const char *const fmt, ...);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
