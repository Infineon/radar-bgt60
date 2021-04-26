/**
 * @file        bgt60-pal-gpio-arduino.hpp
 * @author 		Infineon Technologies AG
 * @brief       Radar BGT60 GPIO Arduino PAL Implementation
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_GPIO_INO_HPP_
#define BGT60_PAL_GPIO_INO_HPP_

#include "bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
#include <stdint.h>
#include "bgt60-pal-gpio.hpp"

using namespace bgt60;

/**
 * @addtogroup bgtinopal
 * @{
 */
class GPIOIno: virtual public GPIO
{
private:
	#define     UNUSED_PIN    0xFF  /**< Unused pin */
	uint8_t     pin;
	uint8_t     mode;
	VLogic_t    logic;

public:
				GPIOIno();
				GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
				~GPIOIno();
	Error_t     init();
	Error_t     deinit();
	VLevel_t    read();
	Error_t     write(VLevel_t level);
	Error_t     enable();
	Error_t     disable();
	Error_t     enableInt(void (*cback) (void *), IntEvent_t mode);
	Error_t   	disableInt();
	IntEvent_t  intEvent();
};

/** @} */

#endif /** BGT60_FRAMEWORK **/
#endif /** BGT60_PAL_GPIO_INO_HPP_ **/
