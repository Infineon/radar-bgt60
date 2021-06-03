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
            Error_t enableInterrupt(std::function<void(void)> & cback);

    private:
            GPIORpi * tDetPin;
            GPIORpi * pDetPin;
        
            /**
             * Adapter of lambda functions to C pointers
             */

            typedef std::function<void(void)> StdFnCBack_t;
            
            static           uint8_t        idxNext;                   /**< Callback array allocation index*/
            static constexpr uint8_t        maxCBacks = 5;             /**< Maximum number of callbacks (thus class instances) that can register an interrupt */
            static           StdFnCBack_t   lambdaFnVector[maxCBacks]; /**< Lambda function vector */
            static           void         * fnPtrVector [maxCBacks];   /**< Callbacks function handlers vector */

            static void   wrappedCBackLambda0();
            static void   wrappedCBackLambda1();
            static void   wrappedCBackLambda2();
            static void   wrappedCBackLambda3();
            static void   wrappedCBackLambda4();

            static void * registerCBack(StdFnCBack_t cback);
};

/** @}  */

#endif /**BGT60_FRAMEWORK*/
#endif /**BGT60_RPI_HPP_*/
