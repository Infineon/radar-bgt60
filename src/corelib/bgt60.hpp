/**
 * @file        bgt60.hpp
 * @author      Infineon Technologies AG
 * @brief       BGT60LTRAIP
 * @version     0.0.1
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_HPP_
#define BGT60_HPP_

#include "bgt60-conf.hpp"
#include "bgt60-pal-gpio.hpp"
#include "bgt60-pal-timer.hpp"


class BGT60
{
    public:

        /**
         * @brief Modes for acquiring the data of the Radar
         * 
         */
        enum MeasMode_t
        {
            MODE_POLLING,       /**< Polling Mode */
            MODE_INTERRUPT      /**< Interrupt Mode */
        };

        enum Motion_t
        {
            NOT_AVAILABLE = 0,  /**< No information available */
            NO_MOTION = 1,    /**< No presence */
            MOTION = 2        /**< Presence */
        };

        enum Direction_t
        {
            NOT_AVAILABLE = 0,
            APPROACHING = 1,
            DEPARTING = 2
        };

                    BGT60(GPIO *pDet, GPIO *tDet, MeasMode_t mode);
                    ~BGT60();
        Error_t     init();
        Error_t     deinit();
        Error_t     getMotion(Motion_t &motion);
        Error_t     getDirection(Direction_t &direction);

    private:

        GPIO       * pDet;
        GPIO       * tDet;
        Timer      * timer;
        MeasMode_t   mode;

        volatile bool pDetRisingEdgeEvent;
        volatile bool pDetFallingEdgeEvent;

        volatile bool tDetRisingEdgeEvent;
        volatile bool tDetFallingEdgeEvent;

        typedef void (* cback_t)(void *);

        static constexpr uint8_t    maxGPIOObjs = 10;                /**< Maximum number of isntances which can register hardware interrupt */
        static           uint8_t    idNext;                          /**< Interrupt array allocation index */
        static           BGT60    * objPtrVector[maxGPIOObjs];       /**< BGT60 object pointer vector */
        static void               * fnPtrVector[maxGPIOObjs];        /**< BGT60 interrupt function handlers vector */

    protected:

               void     callbackPresence();
               void     callbackDirection();
        static void     int0Handler();
        static void     int1Handler();
        static void     int2Handler();
        static void     int3Handler();
        static void     int4Handler();
        static void     int5Handler();
        static void     int6Handler();
        static void     int7Handler();
        static void     int8Handler();
        static void     int9Handler();

        static void   * isrRegister(BGT60 *objPtr);
};

#endif /** BGT60_HPP_ **/