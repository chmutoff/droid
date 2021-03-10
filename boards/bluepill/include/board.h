/*
 * Copyright (C) 2015 TriaGnoSys GmbH
 *               2017 Alexander Kurth, Sören Tempel, Tristan Bruns
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_bluepill
 *
 * This board can be bought very cheaply on sides like eBay or
 * AliExpress. Although the MCU nominally has 64 KiB ROM, most of them
 * have 128 KiB ROM. For more information see:
 * https://web.archive.org/web/20190527040051/http://wiki.stm32duino.com/index.php?title=Blue_Pill
 *
 * @{
 *
 * @file
 * @brief       Peripheral MCU configuration for the bluepill board
 *
 * @author      Víctor Ariño <victor.arino@triagnosys.com>
 * @author      Sören Tempel <tempel@uni-bremen.de>
 * @author      Tristan Bruns <tbruns@uni-bremen.de>
 * @author      Alexander Kurth <kurth1@uni-bremen.de>
 */

#ifndef BOARD_H
#define BOARD_H

#include "board_common.h"
#include "motor_driver.h"

/**
 * @name Describe DC motors with PWM channel and GPIOs
 * @{
 */
static const motor_driver_config_t motor_driver_config[] = {
    {
        .pwm_dev         = 0,
        .mode            = MOTOR_DRIVER_2_DIRS,
        .mode_brake      = MOTOR_BRAKE_HIGH,
        .pwm_mode        = PWM_LEFT,
        .pwm_frequency   = 1000U,
        .pwm_resolution  = 256U,
        .nb_motors       = 2,
        .motors          = {
            {
                .pwm_channel            = 0,
                .gpio_enable            = GPIO_UNDEF,
                .gpio_dir0              = GPIO_PIN(PORT_B, 12),
                .gpio_dir1_or_brake     = GPIO_PIN(PORT_B, 13),
                .gpio_dir_reverse       = 0,
                .gpio_enable_invert     = 0,
                .gpio_brake_invert      = 0,
            },
            {
                .pwm_channel            = 1,
                .gpio_enable            = GPIO_UNDEF,
                .gpio_dir0              = GPIO_PIN(PORT_B, 14),
                .gpio_dir1_or_brake     = GPIO_PIN(PORT_B, 15),
                .gpio_dir_reverse       = 0,
                .gpio_enable_invert     = 0,
                .gpio_brake_invert      = 0,
            },
        },
        .cb = NULL,
    },
};

#define MOTOR_DRIVER_NUMOF           ARRAY_SIZE(motor_driver_config)
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
