/**
 * @file        bgt60-rpi.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 RaspberryPi API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_RPI_HPP_
#define BGT60_RPI_HPP_

#include "../../../config/bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)
#include <functional>
#include <stdint.h>

#include "bgt60.hpp"
#include "../pal/bgt60-pal-gpio-rpi.hpp"

/**
 * \addtogroup rpiAPi
 * @{
 */

class Bgt60Rpi : public Bgt60
{
    public:
            Bgt60Rpi(uint8_t targetDet, uint8_t phaseDet);
            ~Bgt60Rpi();

            using Bgt60::enableInterrupt;
            Error_t enableInterrupt(std::function<void(void)> &cback);

    private:
            GPIORpi * tDetPin;
            GPIORpi * pDetPin;
};

/** @}  */

#endif /**BGT60_FRAMEWORK*/
#endif /**BGT60_RPI_HPP_*/
