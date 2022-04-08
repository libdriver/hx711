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
 * @file      driver_hx711_basic.h
 * @brief     driver hx711 basic header file
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

#ifndef DRIVER_HX711_BASIC_H
#define DRIVER_HX711_BASIC_H

#include "driver_hx711_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hx711_example_driver hx711 example driver function
 * @brief    hx711 example driver modules
 * @ingroup  hx711_driver
 * @{
 */

/**
 * @brief hx711 basic example default definition
 */
#define HX711_BASIC_DEFAULT_MODE HX711_MODE_CHANNEL_A_GAIN_128        /**< 128 gain */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hx711_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hx711_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *raw_voltage points to a raw adc buffer
 * @param[out] *voltage_v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hx711_basic_read(int32_t *raw_voltage, double *voltage_v);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
