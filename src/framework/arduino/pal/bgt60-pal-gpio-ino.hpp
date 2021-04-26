/** 
<<<<<<< HEAD:src/framework/arduino/pal/bgt60-pal-gpio-ino.hpp
 * @file        bgt60-pal-gpio-ino.hpp
 * @brief       Radar BGT 60GHz Arduino PAL Implementation  
=======
 * @file        gpio-arduino.hpp
 * @brief       Radar BGT 60GHz GPIO Arduino PAL Implementation  
>>>>>>> e7c4459b961e5f0115b2f1eefbd5f59f0a1d3f55:src/framework/arduino/pal/gpio-arduino.hpp
 * @date        April 2021
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_GPIO_INO_HPP_
#define BGT60_PAL_GPIO_INO_HPP_
#include <stdint.h>
#include "bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include "bgt60-pal-gpio.hpp"

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

<<<<<<< HEAD:src/framework/arduino/pal/bgt60-pal-gpio-ino.hpp
#endif /** RADAR_BGT60_FRAMEWORK **/
=======
#endif /** BGT60_FRAMEWORK **/
>>>>>>> e7c4459b961e5f0115b2f1eefbd5f59f0a1d3f55:src/framework/arduino/pal/gpio-arduino.hpp
#endif /** BGT60_PAL_GPIO_INO_HPP_ **/
