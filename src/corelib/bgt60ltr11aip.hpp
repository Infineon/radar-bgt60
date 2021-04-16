/**
 * @file        bgt60ltr11aip.hpp
 * @author      Infineon Technologies AG
 * @brief       BGT60LTRAIP
 * @version     0.0.1
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60LRT11AIP_HPP_
#define BGT60LRT11AIP_HPP_

#include "bgt60ltr11aip-conf.hpp"
#include "bgt60ltr11aip-pal-gpio.hpp"
#include "bgt60ltr11aip-pal-timer.hpp"


class Bgt60ltr11aip
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

        enum Presence_t
        {
            NOT_AVAILABLE = 0,  /**< No information available */
            NO_PRESENCE = 1,    /**< No presence */
            PRESENCE = 2        /**< Presence */
        };

        enum Direction_t
        {
            NOT_AVAILABLE = 0,
            APPROACHING = 1,
            DEPARTING = 2
        };

        Bgt60ltr11aip(GPIO *pDet, GPIO *tDet, MeasMode_t mode);
        ~Bgt60ltr11aip();
        Error_t init();
        Errort_t deinit();
        Error_t getPresence(Presence_t &presence);
        Errort_t getDirection(Direction_t &direction);

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

        static constexpr uint8_t         maxGPIOObjs = 10;              /**< Maximum number of isntances which can register hardware interrupt */
        static           uint8_t         idNext;                        /**< Interrupt array allocation index */
        static           Bgt60ltr11aip * objPtrVector[maxGPIOObjs];     /**< Bgt60ltr11aip object pointer vector */
        static void                    * fnPtrVector[maxGPIOObjs];      /**< Bgt60ltr11aip interrupt function handlers vector */

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

        static void   * isrRegister(Bgt60ltr11aip *objPtr);

};

#endif /** BGT60LRT11AIP_HPP_ **/