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
#include <stdint.h>

#include "bgt60.hpp"
#include "bgt60-pal-gpio-rpi.hpp"

class Bgt60Rpi : public Bgt60
{
    public:
            Bgt60Rpi(uint8_t targetDet, uint8_t phaseDet, MeasMode_t pinMode);
            ~Bgt60Rpi();

    private:
            GPIORpi * tDetPin;
            GPIORpi * pDetPin;
};
#endif /**BGT60_FRAMEWORK*/
#endif /**BGT60_RPI_HPP_*/