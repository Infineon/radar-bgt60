/**
 * @file        bgt60.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BGT60_HPP_
#define BGT60_HPP_

#include "bgt60-conf.hpp"
#include "bgt60-pal-gpio.hpp"
#include <stdint.h>

using namespace bgt60;

class Bgt60
{
    public:

        /**
         * @brief Modes for acquiring the data of the radar
         */
        enum MeasMode_t
        {
            MODE_POLLING = 0,               /**< Polling mode */
            MODE_INTERRUPT = 1              /**< Interrupt mode */
        };

        /**
         * @brief States of motion
         */
        enum Motion_t
        {
            NOT_AVAILABLE   = 0,        /**< No information available */
            NO_MOTION       = 1,        /**< No presence */
            MOTION          = 2         /**< Presence */
        };

        /**
         * @brief States of direction
         */
        enum Direction_t
        {
            NO_INFORMATION  = 0,        /**< No information available */
            APPROACHING     = 1,        /**< Target approaching */
            DEPARTING       = 2         /**< Target departing */
        };

        /**
         * @brief Resulting states of the interrupt flags
         */
        enum InterruptStatus_t
        {
            NOTHING_OCCURRED    = 0,    /**< No valid status or no flag set */
            MOTION_APPROACHING  = 1,    /**< Motion detected, target approaching */
            MOTION_DEPARTING    = 2,    /**< Motion detected, target departing */
            MOTION_OCCURRED     = 3,    /**< Motion detected */
            NO_MOTION_OCCURRED  = 4     /**< No motion detected> */
        } motion,direction;

        /**
         * @brief Data availability indicator flag for interrupt
         */
        bool available;

                    Bgt60(GPIO *tDet, GPIO *pDet, MeasMode_t mode);
                    ~Bgt60();
        Error_t     init();
        Error_t     deinit();
        Error_t     getMotion(Motion_t &motion);
        Error_t     getDirection(Direction_t &direction);
        void        getInterruptStatus(InterruptStatus_t &intStatus);
        

    private:

        GPIO       * tDet;
        GPIO       * pDet;
        // Timer      * timer;
        MeasMode_t   mode;

        volatile bool motionDetected;

        volatile bool tDetRisingEdgeEvent;      /**< Target detect pin rising edge event flag */
        volatile bool tDetFallingEdgeEvent;     /**< Target detect pin falling edge event flag */

        volatile bool pDetRisingEdgeEvent;      /**< Phase detect pin rising edge event flag */
        volatile bool pDetFallingEdgeEvent;     /**< Phase detect pin falling edge event flag */

        typedef void (* cback_t)(void *);

        static constexpr uint8_t    maxGPIOObjsTarget = 5;                              /**< Maximum number of isntances which can register hardware interrupt */
        static           uint8_t    idNextTarget;                                       /**< Interrupt array allocation index */
        static           Bgt60    * objPtrVectorTarget[maxGPIOObjsTarget];              /**< Bgt60 object pointer vector */
        static void               * fnPtrVectorTarget[maxGPIOObjsTarget];               /**< Bgt60 interrupt function handlers vector */

        static constexpr uint8_t    maxGPIOObjsDirection = 5;                           /**< Maximum number of isntances which can register hardware interrupt */
        static           uint8_t    idNextDirection;                                    /**< Interrupt array allocation index */
        static           Bgt60    * objPtrVectorDirection[maxGPIOObjsDirection];        /**< Bgt60 object pointer vector */
        static void               * fnPtrVectorDirection[maxGPIOObjsDirection];         /**< Bgt60 interrupt function handlers vector */

    protected:

               void     callbackMotion();
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

        static void   * isrRegister(Bgt60 *objPtr);
        static void   * isr2Register(Bgt60 *objPtr);
};

#endif /** BGT60_HPP_ **/