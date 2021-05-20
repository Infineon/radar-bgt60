/**
 * @file        bgt60-pal-timer-ino.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Timer Arduino PAL Implementation
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_PAL_TIMER_INO_HPP_
#define BGT60_PAL_TIMER_INO_HPP_

#include "../../../config/bgt60-conf.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
#include "../../../pal/bgt60-pal-timer.hpp"

using namespace bgt60;

/**
 * @addtogroup bgtinopal
 * @{
 */

class TimerIno: virtual public Timer
{
    public:
                        TimerIno        ();
                        ~TimerIno       ();
        Error_t         init            ();
        Error_t         deinit          ();
        Error_t         start           ();
        Error_t         elapsed         (uint32_t & elapsed);
        Error_t         elapsedMicro    (uint32_t & elapsed);
        Error_t         stop            ();
        Error_t         delay           (const uint32_t timeout);

    private:
        uint32_t curTime;   /**< Current time */
};

/** @} */

#endif /** BGT60_FRAMEWORK **/
#endif /** BGT60_PAL_TIMER_INO_HPP_ **/