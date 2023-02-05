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
 * @file      driver_hx711.c
 * @brief     driver hx711 source file
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
  
#include "driver_hx711.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Aviaic HX711"        /**< chip name */
#define MANUFACTURER_NAME         "Aviaic"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.6f                  /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                  /**< chip max supply voltage */
#define MAX_CURRENT               1.5f                  /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            2000                  /**< driver version */

/**
 * @brief      read the raw ad
 * @param[in]  *handle points to an hx711 handle structure
 * @param[in]  len is the read bits
 * @param[out] *value points to a raw ad buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_hx711_read_ad(hx711_handle_t *handle, uint8_t len, int32_t *value)
{
    uint32_t val = 0;
    uint32_t cnt = 0;
    uint8_t i;
    uint8_t v;
    
    if (handle->clock_write(0) != 0)                                      /* write clock 0 */
    {
        handle->debug_print("hx711: clock write 0 failed.\n");            /* clock write failed */
        
        return 1;                                                         /* return error */
    }
    
    while (1)                                                             /* loop */
    {
        handle->delay_us(100);                                            /* wait 100 us */
        if (handle->bus_read((uint8_t *)&v) != 0)                         /* bus read failed */
        {
            handle->debug_print("hx711: bus read failed.\n");             /* bus read failed */
            
            return 1;                                                     /* return error */
        }
        cnt++;                                                            /* increase timeout cnt */
        if (v == 1)                                                       /* if v==1 */
        {
            if (cnt >= 50000)                                             /* check timeout */
            {
                handle->debug_print("hx711: bus no response.\n");         /* bus no response */
                
                return 1;                                                 /* return error */
            }
        }
        else
        {
            break;                                                        /* break */
        }
    }
    handle->disable_irq();                                                /* disable interrupt */
    handle->delay_us(1);                                                  /* wait 1 us */
    for (i = 0; i < 24; i++)                                              /* read 24 bits */
    {
        if (handle->clock_write(1) != 0)                                  /* write clock 1 */
        {
            handle->enable_irq();                                         /* enable interrupt */
            handle->debug_print("hx711: clock write 1 failed.\n");        /* clock write failed */
            
            return 1;                                                     /* return error */
        }
        val = val << 1;                                                   /* left shift 1 */
        handle->delay_us(1);                                              /* wait 1 us */
        if (handle->clock_write(0) != 0)                                  /* write clock 0 */
        {
            handle->enable_irq();                                         /* enable interrupt */
            handle->debug_print("hx711: clock write 0 failed.\n");        /* clock write failed */
            
            return 1;                                                     /* return error */
        }
        if (handle->bus_read((uint8_t *)&v) != 0)                         /* read 1 bit */
        {
            handle->enable_irq();                                         /* enable interrupt */
            handle->debug_print("hx711: bus read failed.\n");             /* bus read failed */
            
            return 1;                                                     /* return error */
        }
        if (v != 0)                                                       /* check v */
        {
            val++;                                                        /* value++ */
        }
        handle->delay_us(1);                                              /* wait 1 us */
    }
    while (len != 0)                                                      /* send pulses */
    {
        if (handle->clock_write(1) != 0)                                  /* write clock 1 */
        {
            handle->enable_irq();                                         /* enable interrupt */
            handle->debug_print("hx711: clock write 1 failed.\n");        /* clock write failed */
            
            return 1;                                                     /* return error */
        }
        handle->delay_us(1);                                              /* wait 1 us */
        if (handle->clock_write(0) != 0)                                  /* write clock 0 */
        {
            handle->enable_irq();                                         /* enable interrupt */
            handle->debug_print("hx711: clock write 0 failed.\n");        /* clock write failed */
            
            return 1;                                                     /* return error */
        }
        handle->delay_us(1);                                              /* wait 1 us */
        len--;                                                            /* length-- */
    }
    handle->enable_irq();                                                 /* enable interrupt */
    if ((val & 0x800000) != 0)                                            /* check negative bit */
    {
        union 
        {
            int32_t i_f;
            uint32_t u_f;
        } u;
        val = 0xFF000000U | val;                                          /* set negative value */
        u.u_f = val;                                                      /* set negative value */
        *value = (int32_t)u.i_f;                                          /* set negative value */
    }
    else
    {
        *value = (int32_t)val;                                            /* set positive value */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t hx711_init(hx711_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->bus_init == NULL)                                    /* check bus_init */
    {
        handle->debug_print("hx711: bus_init is null.\n");           /* bus_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_deinit == NULL)                                  /* check bus_deinit */
    {
        handle->debug_print("hx711: bus_deinit is null.\n");         /* bus_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_read == NULL)                                    /* check bus_read */
    {
        handle->debug_print("hx711: bus_read is null.\n");           /* bus_read is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->clock_init == NULL)                                  /* check clock_init */
    {
        handle->debug_print("hx711: clock_init is null.\n");         /* clock_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->clock_deinit == NULL)                                /* check clock_deinit */
    {
        handle->debug_print("hx711: clock_deinit is null.\n");       /* clock_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->clock_write == NULL)                                 /* check clock_write */
    {
        handle->debug_print("hx711: clock_write is null.\n");        /* clock_write is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_us == NULL)                                    /* check delay_us */
    {
        handle->debug_print("hx711: delay_us is null.\n");           /* delay_us is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->enable_irq == NULL)                                  /* check enable_irq */
    {
        handle->debug_print("hx711: enable_irq is null.\n");         /* enable_irq is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->disable_irq == NULL)                                 /* check disable_irq */
    {
        handle->debug_print("hx711: disable_irq is null.\n");        /* disable_irq is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->clock_init() != 0)                                   /* initialize clock */
    {
        handle->debug_print("hx711: clock init failed.\n");          /* clock init failed */
        
        return 1;                                                    /* return error */
    }
    if (handle->bus_init() != 0)                                     /* initialize bus */
    {
        handle->debug_print("hx711: bus init failed.\n");            /* bus init failed */
        (void)handle->clock_deinit();                                /* deinit clock */
        
        return 1;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag finish initialization */
    handle->mode = 1;                                                /* set mode */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t hx711_deinit(hx711_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->bus_deinit() != 0)                                   /* deinit bus */
    {
        handle->debug_print("hx711: bus deinit failed.\n");          /* bus deinit failed */
        
        return 1;                                                    /* return error */
    }   
    if (handle->clock_deinit() != 0)                                 /* deinit clock */
    {
        handle->debug_print("hx711: clock deinit failed.\n");        /* clock deinit failed */

        return 1;                                                    /* return error */
    } 
    handle->inited = 0;                                              /* flag close */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t hx711_set_mode(hx711_handle_t *handle, hx711_mode_t mode)
{
    int32_t value; 
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    handle->mode = (uint8_t)mode;                                             /* set mode */
    if (a_hx711_read_ad(handle, handle->mode, (int32_t *)&value) != 0)        /* make mode valid */
    {
        handle->debug_print("hx711: read ad failed.\n");                      /* read ad failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t hx711_get_mode(hx711_handle_t *handle, hx711_mode_t *mode)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    if (handle->inited != 1)                     /* check handle initialization */
    {
        return 3;                                /* return error */
    }
    
    *mode = (hx711_mode_t)(handle->mode);        /* get mode */
    
    return 0;                                    /* success return 0 */
}

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
uint8_t hx711_read(hx711_handle_t *handle, int32_t *raw, double *voltage_v)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    if (a_hx711_read_ad(handle, handle->mode, (int32_t *)raw) != 0)          /* read ad */
    {
        handle->debug_print("hx711: read voltage failed.\n");                /* read voltage failed */
        
        return 1;                                                            /* return error */
    }
    if (handle->mode == (uint8_t)HX711_MODE_CHANNEL_A_GAIN_128)              /* if gain 128 */
    {
        *voltage_v = (double)(*raw) * (20.0 / (pow(2.0, 24.0))) / 1000.0;    /* calculate gain 128 */
        
        return 0;                                                            /* success return 0 */
    }
    else if (handle->mode == (uint8_t)HX711_MODE_CHANNEL_B_GAIN_32)          /* if gain 32 */
    {
        *voltage_v = (double)(*raw) * (80.0 / (pow(2.0, 24.0))) / 1000.0;    /* calculate gain 32 */
        
        return 0;                                                            /* success return 0 */
    }
    else if (handle->mode == (uint8_t)HX711_MODE_CHANNEL_A_GAIN_64)          /* if gain 64 */
    {
        *voltage_v = (double)(*raw) * (40.0 / (pow(2.0, 24.0))) / 1000.0;    /* calculate gain 64 */
        
        return 0;                                                            /* success return 0 */
    }
    else
    {
        handle->debug_print("hx711: mode error.\n");                         /* mode error */
        
        return 4;                                                            /* return error */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an hx711 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hx711_info(hx711_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(hx711_info_t));                          /* initialize hx711 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
