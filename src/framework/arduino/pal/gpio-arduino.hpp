/** 
 * @file        gpio-arduino.hpp
 * @brief       Radar BGT 60GHz Arduino PAL Implementation  
 * @date        April 2021
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RADAR_BGT60_ARD_HPP_
#define RADAR_BGT60_ARD_HPP_
#include <stdint.h>
#include "../../../config/bgt60-conf.hpp"

#if (RADAR_BGT60_FRAMEWORK == RADAR_BGT60_FRMWK_ARDUINO)
#include "../../../pal/gpio.hpp"
/**
 * @addtogroup bgtinopal
 * @{
 */

using namespace bgt60;

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

#endif /** RADAR_BGT60_FRAMEWORK **/
#endif /** RADAR_BGT60_ARD_HPP_ **/
