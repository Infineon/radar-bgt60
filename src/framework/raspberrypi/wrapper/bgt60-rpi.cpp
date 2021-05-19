/** 
 * @file        bgt60-rpi.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Raspberry Pi API
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-rpi.hpp"


#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)
using namespace bgt60;

/**
 * @brief       Constructor of the RaspberryPi Bgt60 object
 * @details     This function is the instance constructor. It accepts the Raspberry Pi GPIO pins utilized
 *              for target and phase detect from the user. These pins are initialized by creating instances 
 *              to GPIORpi and then mapped to main Bgt60 class.           
 * @param[in]   targetDet   Pin number of the target detect pin
 * @param[in]   phaseDet    Pin number of the phase detect pin
 * @param[in]   pinMode     Desired mode of the board, polling or interrupt driven
 */
 
Bgt60Rpi::Bgt60Rpi(uint8_t targetDet, uint8_t phaseDet)
:
Bgt60((tDetPin = new GPIORpi(targetDet, INPUT, GPIO::VLogic_t::NEGATIVE)), (pDetPin = new GPIORpi(phaseDet, INPUT, GPIO::VLogic_t::NEGATIVE)))
{

}

/**
 * @brief       Destructor of the RaspberryPi Bgt60 object
 */
Bgt60Rpi::~Bgt60Rpi()
{

}

#endif /** BGT60_FRAMEWORK */