/**
 * @file        bgt60-ino.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Arduino API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_INO_HPP_
#define BGT60_INO_HPP_

#include "bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
#include <stdint.h>

#include "bgt60.hpp"
#include "bgt60-pal-gpio-ino.hpp"

class Bgt60Ino : public Bgt60
{
    public:
                    Bgt60Ino(uint8_t targetDet, uint8_t phaseDet);
                    ~Bgt60Ino();
        Error_t     begin();
        Error_t     end();

    private:

        GPIOIno * tDetPin;
        GPIOIno * pDetPin;
};

#endif /** BGT60_FRMWK_ARDUINO */
#endif /** BGT60_INO_HPP_ */