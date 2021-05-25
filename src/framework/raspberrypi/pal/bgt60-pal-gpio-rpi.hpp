/** 
 * @file        bgt60-pal-gpio.hpp
 * @brief       Radar BGT 60GHz GPIO RaspberryPi PAL
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_GPIO_RPI_HPP_ 
#define BGT60_PAL_GPIO_RPI_HPP_

#include "../../../config/bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

#include "bgt60-pal-gpio.hpp"
#include <wiringPi.h>
#include <stdint.h>
using namespace bgt60;

/**
 * @addtogroup bgt60rpipal
 * @{
 */

class GPIORpi : virtual public GPIO 
{
    private:
        #define     UNUSED_PIN    0xFF  /**< Unused pin */
        uint8_t     pin;                /**< Pin number*/
        uint8_t     mode;               /**< Pin mode*/
        VLogic_t    logic;              /**< Pin logic */

    public:

        			GPIORpi    ();
				    GPIORpi     (uint8_t pin, uint8_t mode, VLogic_t logic);
				    ~GPIORpi    ();
	    Error_t     init        ();
	    Error_t     deinit      ();
	    VLevel_t    read        ();
	    Error_t     write       (VLevel_t level);
	    Error_t     enable      ();
	    Error_t     disable     ();
	    Error_t     enableInt   (void (*cback) (void), IntEvent_t mode);
	    Error_t   	disableInt  ();
	    IntEvent_t  intEvent    ();

};

/** @} */

#endif /** BGT60_FRAMEWORK **/
#endif /** BGT60_PAL_GPIO_RPI_HPP_ **/