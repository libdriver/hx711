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
 * @file      driver_hx711.h
 * @brief     driver hx711 header file
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

#ifndef DRIVER_HX711_H
#define DRIVER_HX711_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hx711_driver hx711 driver function
 * @brief    hx711 driver modules
 * @{
 */

/**
 * @addtogroup hx711_base_driver
 * @{
 */

/**
 * @brief hx711 mode enumeration definition
 */
typedef enum
{
    HX711_MODE_CHANNEL_A_GAIN_128 = 0x01,        /**< channel A 128 gain */
    HX711_MODE_CHANNEL_B_GAIN_32  = 0x02,        /**< channel B 32 gain */
    HX711_MODE_CHANNEL_A_GAIN_64  = 0x03,        /**< channel A 64 gain */
} hx711_mode_t;

/**
 * @brief hx711 handle structure definition
 */
typedef struct hx711_handle_s
{
    uint8_t (*bus_init)(void);                              /**< point to a bus_init function address */
    uint8_t (*bus_deinit)(void);                            /**< point to a bus_deinit function address */
    uint8_t (*bus_read)(uint8_t *value);                    /**< point to a bus_read function address */
    uint8_t (*clock_init)(void);                            /**< point to a clock_init function address */
    uint8_t (*clock_deinit)(void);                          /**< point to a clock_deinit function address */
    uint8_t (*clock_write)(uint8_t value);                  /**< point to a clock_write function address */
    void (*delay_us)(uint32_t us);                          /**< point to a delay_us function address */
    void (*enable_irq)(void);                               /**< point to an enable_irq function address */
    void (*disable_irq)(void);                              /**< point to a disable_irq function address */
    void (*debug_print)(const char *const fmt, ...);        /**< point to a debug_print function address */
    uint8_t inited;                                         /**< inited flag */
    uint8_t mode;                                           /**< chip mode */
} hx711_handle_t;

/**
 * @brief hx711 info structure definition
 */
typedef struct hx711_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} hx711_info_t;

/**
 * @}
 */

/**
 * @defgroup hx711_link_driver hx711 link driver function
 * @brief    hx711 link driver modules
 * @ingroup  hx711_driver
 * @{
 */

/**
 * @brief     initialize hx711_handle_t structure
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] STRUCTURE is hx711_handle_t
 * @note      none
 */
#define DRIVER_HX711_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link bus_init function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a bus_init function address
 * @note      none
 */
#define DRIVER_HX711_LINK_BUS_INIT(HANDLE, FUC)    (HANDLE)->bus_init = FUC

/**
 * @brief     link bus_deinit function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a bus_deinit function address
 * @note      none
 */
#define DRIVER_HX711_LINK_BUS_DEINIT(HANDLE, FUC)  (HANDLE)->bus_deinit = FUC

/**
 * @brief     link bus_read function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a bus_read function address
 * @note      none
 */
#define DRIVER_HX711_LINK_BUS_READ(HANDLE, FUC)    (HANDLE)->bus_read = FUC

/**
 * @brief     link clock_init function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a clock_init function address
 * @note      none
 */
#define DRIVER_HX711_LINK_CLOCK_INIT(HANDLE, FUC)  (HANDLE)->clock_init = FUC

/**
 * @brief     link clock_deinit function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a clock_deinit function address
 * @note      none
 */
#define DRIVER_HX711_LINK_CLOCK_DEINIT(HANDLE, FUC)(HANDLE)->clock_deinit = FUC

/**
 * @brief     link clock_write function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a clock_write function address
 * @note      none
 */
#define DRIVER_HX711_LINK_CLOCK_WRITE(HANDLE, FUC) (HANDLE)->clock_write = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a delay_us function address
 * @note      none
 */
#define DRIVER_HX711_LINK_DELAY_US(HANDLE, FUC)    (HANDLE)->delay_us = FUC

/**
 * @brief     link enable_irq function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to an enable_irq function address
 * @note      none
 */
#define DRIVER_HX711_LINK_ENABLE_IRQ(HANDLE, FUC)  (HANDLE)->enable_irq = FUC

/**
 * @brief     link disable_irq function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a disable_irq function address
 * @note      none
 */
#define DRIVER_HX711_LINK_DISABLE_IRQ(HANDLE, FUC) (HANDLE)->disable_irq = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an hx711 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_HX711_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup hx711_base_driver hx711 base driver function
 * @brief    hx711 base driver modules
 * @ingroup  hx711_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an hx711 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hx711_info(hx711_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an hx711 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus or clock initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t hx711_init(hx711_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an hx711 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus or clock deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hx711_deinit(hx711_handle_t *handle);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an hx711 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hx711_set_mode(hx711_handle_t *handle, hx711_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an hx711 handle structure
 * @param[out] *mode points to a chip mode
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hx711_get_mode(hx711_handle_t *handle, hx711_mode_t *mode);

/**
 * @brief      read the 24 bits raw ad from the chip
 * @param[in]  *handle points to an hx711 handle structure
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *voltage_v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 mode error
 * @note       none
 */
uint8_t hx711_read(hx711_handle_t *handle, int32_t *raw, double *voltage_v);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
