/**
 * @file        bgt60.cpp
 * @author      Infineon Technologies AG
 * @brief       BGT60LTRAIP API
 * @version     0.0.1
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60.hpp"

/**
 * @brief 
 * 
 */
BGT60::BGT60(GPIO *pDet, GPIO *tDet, MeasMode_t mode) : pDet(pDet), tDet(tDet), mode(mode)
{

}

/**
 * @brief 
 * 
 */
BGT60::~BGT60()
{
    // TODO: How to properly destroy the instances
}

/**
 * @brief 
 * 
 */
Error_t BGT60::init()
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
 * @brief 
 * 
 */
Error_t BGT60::deinit()
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
 * @brief 
 * 
 * @return true 
 * @return false 
 */
Error_t BGT60::getMotion(Motion_t &motion)
{
    Error_t err = OK;

    do
    {
        if(MODE_INTERRUPT == mode)
        {
            err = tDet->enableInt((cback_t)isrRegister(this));      //TODO: Create a mechanism to avoid calling the ISR regestration more than once
            if(OK != err)
                break;
        }
        else
        {
            GPIO::VLevel_t level = tDet->read();                    //TODO: Why no error handling here?
            
            if(GPIO::VLevel_t::GPIO_LOW == level)
            {
                motion = MOTION;
            }
            else if(GPIO::VLevel_t::GPIO_HIGH == level)
            {
                motion = NO_MOTION;
            }
        }
    } while (0);
    return err;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
Error_t BGT60::getDirection(Direction_t &direction)
{
    Error_t err = OK;

    do
    {
        if(MODE_INTERRUPT == mode)
        {
            err = ->enableInt((cback_t)isrRegister(this));          //TODO: Create a mechanism to avoid calling the ISR regestration more than once
            if(OK != err)
                break;
        }
        else
        {
            GPIO::VLevel_t level = pDet->read();                    //TODO: Why no error handling here?
            
            if(GPIO::VLevel_t::GPIO_LOW == level)
            {
                direction = DEPARTING;
            }
            else if(GPIO::VLevel_t::GPIO_HIGH == level)
            {
                direction = APPROACHING;
            }
        }
    } while (0);
    return err;
}

/**
 * @brief 
 * 
 */
void BGT60::callbackPresence()
{
    GPIO::Intevent_t event = tDet->intEvent();

    if(GPIO::IntEvent_t::INT_FALLING_EDGE == event)
    {
        tDetFallingEdgeEvent = true;
    }
    else if(GPIO::IntEvent_t::INT_RISING_EDGE == event)
    {
        tDetRisingEdgeEvent = true;
    }
}

/**
 * @brief 
 * 
 */
void BGT60::callbackDirection()
{
    GPIO::Intevent_t event = pDet->intEvent();

    if(GPIO::IntEvent_t::INT_FALLING_EDGE == event)
    {
        pDetFallingEdgeEvent = true;
    }
    else if(GPIO::IntEvent_t::INT_RISING_EDGE == event)
    {
        pDetRisingEdgeEvent = true;
    }
}

BGT60 * BGT60::objPtrVector[maxGPIOObjs] = {nullptr};
uint8_t BGT60::idNext  = 0;

void BGT60::int0Handler()
{
    objPtrVector[0]->callback();
}

void BGT60::int1Handler()
{
    objPtrVector[1]->callback();
}

void BGT60::int2Handler()
{
    objPtrVector[2]->callback();
}

void BGT60::int3Handler()
{
    objPtrVector[3]->callback();
}

void BGT60::int4Handler()
{
    objPtrVector[4]->callback();
}

void BGT60::int5Handler()
{
    objPtrVector[5]->callback();
}

void BGT60::int6Handler()
{
    objPtrVector[6]->callback();
}

void BGT60::int7Handler()
{
    objPtrVector[7]->callback();
}

void BGT60::int8Handler()
{
    objPtrVector[8]->callback();
}

void BGT60::int9Handler()
{
    objPtrVector[9]->callback();
}

void * BGT60::fnPtrVector[maxGPIOObjs] =   {(void *)int0Handler,
                                            (void *)int1Handler,
                                            (void *)int2Handler,
                                            (void *)int3Handler,
                                            (void *)int4Handler,
                                            (void *)int5Handler,
                                            (void *)int6Handler,
                                            (void *)int7Handler,
                                            (void *)int8Handler,
                                            (void *)int9Handler};


void * BGT60::isrRegister(BGT60 *objPtr)
{
    void *fPtr = nullptr;

    if(idNext < 4)
    {
        objPtrVector[idNext] = objPtr;
        fPtr = fnPtrVector[idNext++];
    }

    return fPtr;
}
