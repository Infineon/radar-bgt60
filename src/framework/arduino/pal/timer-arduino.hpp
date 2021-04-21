/** 
 * @file        timer-arduino.hpp
 * @brief       RADAR BGT60 Timer Arduino PAL Implementation 
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RADAR_BGT60_ARD_TIMER_HPP
#define RADAR_BGT60_ARD_TIMER_HPP

#include "../../../config/bgt60-conf.hpp"

#if (RADAR_BGT60_FRAMEWORK == RADAR_BGT60_FRMWK_ARDUINO)

#include "../../../pal/timer.hpp"

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

#endif /** RADAR_BGT60_FRAMEWORK **/
#endif /** RADAR_BGT60_ARD_TIMER_HPP **/