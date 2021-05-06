/**
 * @file        bgt60.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60.hpp"

using namespace bgt60;

/**
 * @brief           Radar Bgt60 constructor
 *
 * @details         This is the constructor of the Radar BGT60 board. The user has to pass the two
 *                  desired pins for reading out the radar data, as well as the mode in which the board
 *                  should acquire the data. The two available modes are polling and interrupt mode.
 *                  In the interrupt mode the board is constantly changing internal variables, which can
 *                  then be used to determine the status of board.
 *
 * @param[in]       *tDet           Instance of a GPIO to read the target-detect-pin
 * @param[in]       *pDet           Instance of a GPIO to read the phase-detect-pin
 * @param[in]        mode           Mode to acquire the data of the radar sensor
 */
Bgt60::Bgt60(GPIO *tDet, GPIO *pDet, MeasMode_t mode) : tDet(tDet), pDet(pDet), mode(mode)
{

}

/**
 * @brief           Radar Bgt60 destructor
 */
Bgt60::~Bgt60()
{

}

/**
 * @brief           Initialize the Bgt60 class object
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 */
Error_t Bgt60::init()
{
    Error_t err = OK;

    do
    {
        err = pDet->init();
        if(err != OK)
            break;

        err = tDet->init();
        if(err != OK)
            break;
    } while (0);

    return err;
}

/**
 * @brief           De-Initialize the Bgt60 class object
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 */
Error_t Bgt60::deinit()
{
    Error_t err = OK;

    do
    {
        err = pDet->deinit();
        if(err != OK)
            break;

        err = tDet->deinit();
        if(err != OK)
            break;
    } while (0);

    return err;
}

/**
 * @brief           Read out target-detect-pin
 *
 * @details         This function reads out the target-detect-pin. Depending on the choosen mode
 *                  of the board it is either actively polling the status of the pin or mapping
 *                  an interrupt to the corresponding pin.
 *
 * @note            If you're using the interrupt mode of the board just call this function once
 *                  in the setup(). For each object of the BGT60 this function can be called once.
 *                  Calling it more often can lead to undesired behavior of the radar board.
 *
 * @param[in,out]   motion This variable stores the actual state of the target-detect-pin
 *                  Possible Values:
 *                      - NOT_AVAILABLE
 *                      - NO_MOTION
 *                      - MOTION
 *
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 */
Error_t Bgt60::getMotion(Motion_t &motion)
{
    Error_t err = OK;

    do
    {
        if(MODE_INTERRUPT == mode)
        {
            err = tDet->enableInt((cback_t)isrRegister(this), GPIO::INT_CHANGE);
            if(OK != err)
                break;
        }
        else
        {
            GPIO::VLevel_t level = tDet->read();
            
            if(GPIO::VLevel_t::GPIO_LOW == level)
            {
                motion = MOTION;
                motionDetected = true;
            }
            else if(GPIO::VLevel_t::GPIO_HIGH == level)
            {
                motion = NO_MOTION;
                motionDetected = false;
            }
        }
    } while (0);
    return err;
}

/**
 * @brief           Read out phase-detect-pin
 *
 * @details         This function reads out the phase-detect-pin. Depending on the choosen mode
 *                  of the board it is either actively polling the status of the pin or mapping
 *                  an interrupt to the corresponding pin.
 *
 * @note            If you're using the interrupt mode of the board just call this function once
 *                  in the setup(). For each object of the BGT60 this function can be called once.
 *                  Calling it more often can lead to undesired behavior of the radar board.
 *
 * @param[in,out]   direction This variable stores the actual state of the phase-detect-pin
 *                  Possible Values:
 *                      - NO_INFORMATION
 *                      - APPROACHING
 *                      - DEPARTING
 *
 * @return          Bgt60 error code
 * @retval          OK if success
 * @retval          INTF_ERROR if error
 */
Error_t Bgt60::getDirection(Direction_t &direction)
{
    Error_t err = OK;

    do
    {
        if(MODE_INTERRUPT == mode)
        {
            err = pDet->enableInt((cback_t)isr2Register(this), GPIO::INT_CHANGE);          //TODO: Create a mechanism to avoid calling the ISR regestration more than once
            if(OK != err)
                break;
        }
        else
        {
            if(true == motionDetected)
            {
                GPIO::VLevel_t level = pDet->read();                                    //TODO: Why no error handling here?

                if(GPIO::VLevel_t::GPIO_LOW == level)
                {
                    direction = DEPARTING;
                }
                else if(GPIO::VLevel_t::GPIO_HIGH == level)
                {
                    direction = APPROACHING;
                }
            }
            else
            {
                direction = NO_INFORMATION;
            }
        }
    } while (0);
    return err;
}

/**
 * @brief           Check internal interrupt flags
 *
 * @details         This function is checking the four internal interrupt variables.
 *                  Depending on them it determines the status of the board and is
 *                  telling the user if a target is there and if so, if it is approaching
 *                  or departing.
 *
 * @pre             The mode has to be INTERRUPT_MODE, otherwise the status of the variable
 *                  will always be NOTING_OCCURRED.
 *
 * @param[in, out]  intStatus Shows the resulting status of the internal interrupt flags
 */
void Bgt60::getInterruptStatus(InterruptStatus_t &intStatus)
{
    if(true == tDetFallingEdgeEvent && true == pDetFallingEdgeEvent)
    {
        intStatus = MOTION_DEPARTING;
    }
    else if(true == tDetFallingEdgeEvent && true == pDetRisingEdgeEvent)
    {
        intStatus = MOTION_APPROACHING;
    }
    else
    {
        intStatus = NOTHING_OCCURRED;
    }
}

/**
 * @brief           Callack of the target-detect-pin
 */
void Bgt60::callbackMotion()
{
    GPIO::IntEvent_t event = tDet->intEvent();

    if(GPIO::IntEvent_t::INT_FALLING_EDGE == event)
    {
        tDetFallingEdgeEvent = true;
        tDetRisingEdgeEvent = false;
        motion = MOTION_OCCURRED;
    }
    else if(GPIO::IntEvent_t::INT_RISING_EDGE == event)
    {
        tDetRisingEdgeEvent = true;
        tDetFallingEdgeEvent = false;
        motion = NO_MOTION_OCCURRED;
    }
    available = true;
}

/**
 * @brief           Callback of the phase-detect-pin
 */
void Bgt60::callbackDirection()
{
    GPIO::IntEvent_t event = pDet->intEvent();

    if(GPIO::IntEvent_t::INT_FALLING_EDGE == event)
    {
        pDetFallingEdgeEvent = true;
        pDetRisingEdgeEvent = false;
        direction = MOTION_APPROACHING;
    }
    else if(GPIO::IntEvent_t::INT_RISING_EDGE == event)
    {
        pDetRisingEdgeEvent = true;
        pDetFallingEdgeEvent = false;
        direction = MOTION_DEPARTING;
    }
}

Bgt60 * Bgt60::objPtrVectorTarget[maxGPIOObjsTarget] = {nullptr};
uint8_t Bgt60::idNextTarget  = 0;

Bgt60 * Bgt60::objPtrVectorDirection[maxGPIOObjsDirection] = {nullptr};
uint8_t Bgt60::idNextDirection  = 0;

/**
 * @brief           Interrupt 0 Handler
 */
void Bgt60::int0Handler()
{
    objPtrVectorTarget[0]->callbackMotion();
}

/**
 * @brief           Interrupt 1 Handler
 */
void Bgt60::int1Handler()
{
    objPtrVectorTarget[1]->callbackMotion();
}

/**
 * @brief           Interrupt 2 Handler
 */
void Bgt60::int2Handler()
{
    objPtrVectorTarget[2]->callbackMotion();
}

/**
 * @brief           Interrupt 3 Handler
 */
void Bgt60::int3Handler()
{
    objPtrVectorTarget[3]->callbackMotion();
}

/**
 * @brief           Interrupt 4 Handler
 */
void Bgt60::int4Handler()
{
    objPtrVectorTarget[4]->callbackMotion();
}

/**
 * @brief           Interrupt 5 Handler
 */
void Bgt60::int5Handler()
{
    objPtrVectorDirection[0]->callbackDirection();
}

/**
 * @brief           Interrupt 6 Handler
 */
void Bgt60::int6Handler()
{
    objPtrVectorDirection[1]->callbackDirection();
}

/**
 * @brief           Interrupt 7 Handler
 */
void Bgt60::int7Handler()
{
    objPtrVectorDirection[2]->callbackDirection();
}

/**
 * @brief           Interrupt 8 Handler
 */
void Bgt60::int8Handler()
{
    objPtrVectorDirection[3]->callbackDirection();
}

/**
 * @brief           Interrupt 9 Handler
 */
void Bgt60::int9Handler()
{
    objPtrVectorDirection[4]->callbackDirection();
}

void * Bgt60::fnPtrVectorTarget[maxGPIOObjsTarget] =        {(void *)int0Handler,
                                                             (void *)int1Handler,
                                                             (void *)int2Handler,
                                                             (void *)int3Handler,
                                                             (void *)int4Handler};

void * Bgt60::fnPtrVectorDirection[maxGPIOObjsDirection] =  {(void *)int5Handler,
                                                             (void *)int6Handler,
                                                             (void *)int7Handler,
                                                             (void *)int8Handler,
                                                             (void *)int9Handler};

/**
 * @brief           Register a hardware interrupt for the Bgt60 object passed by
 *                  argument
 * @param[in]       *objPtr Bgt60 object pointer
 * @return          Pointer to allocate the interrupt function handler
 */
void * Bgt60::isrRegister(Bgt60 *objPtr)
{
    void *fPtr = nullptr;

    if(idNextTarget < 5)
    {
        objPtrVectorTarget[idNextTarget] = objPtr;
        fPtr = fnPtrVectorTarget[idNextTarget++];
    }

    return fPtr;
}

/**
 * @brief           Register a second hardware interrupt for the Bgt60 object passed by
 *                  argument
 * @param[in]       *objPtr Bgt60 object pointer
 * @return          Pointer to allocate the interrupt function handler
 */
void * Bgt60::isr2Register(Bgt60 *objPtr)
{
    void *fPtr = nullptr;

    if(idNextDirection < 5)
    {
        objPtrVectorDirection[idNextDirection] = objPtr;
        fPtr = fnPtrVectorDirection[idNextDirection++];
    }

    return fPtr;
}
