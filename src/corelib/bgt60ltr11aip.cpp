/**
 * @file        bgt60ltr11aip.cpp
 * @author      Infineon Technologies AG
 * @brief       BGT60LTRAIP API
 * @version     0.0.1
 * @date        April 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60ltr11aip.hpp"

/**
 * @brief 
 * 
 */
Bgt60ltr11aip::Bgt60ltr11aip(GPIO *pDet, GPIO *tDet, MeasMode_t mode) : pDet(pDet), tDet(tDet), mode(mode)
{

}

/**
 * @brief 
 * 
 */
Bgt60ltr11aip::~Bgt60ltr11aip()
{
    // TODO: How to properly destroy the instances
}

/**
 * @brief 
 * 
 */
Error_t Bgt60ltr11aip::init()
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
Error_t Bgt60ltr11aip::deinit()
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
Error_t Bgt60ltr11aip::getPresence(Presence_t &presence)
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
                presence = PRESENCE;
            }
            else if(GPIO::VLevel_t::GPIO_HIGH == level)
            {
                presence = NO_PRESENCE;
            }
        }
    }
    return err;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
Error_t Bgt60ltr11aip::getDirection(Direction_t &direction)
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
    }
    return err;
}

/**
 * @brief 
 * 
 */
void Bgt60ltr11aip::callbackPresence()
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
void Bgt60ltr11aip::callbackDirection()
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

Bgt60ltr11aip * Bgt60ltr11aip::objPtrVector[maxGPIOObjs] = {nullptr};
uint8_t         Bgt60ltr11aip::idNext  = 0;

void Bgt60ltr11aip::int0Handler()
{
    objPtrVector[0]->callback();
}

void Bgt60ltr11aip::int1Handler()
{
    objPtrVector[1]->callback();
}

void Bgt60ltr11aip::int2Handler()
{
    objPtrVector[2]->callback();
}

void Bgt60ltr11aip::int3Handler()
{
    objPtrVector[3]->callback();
}

void Bgt60ltr11aip::int4Handler()
{
    objPtrVector[4]->callback();
}

void Bgt60ltr11aip::int5Handler()
{
    objPtrVector[5]->callback();
}

void Bgt60ltr11aip::int6Handler()
{
    objPtrVector[6]->callback();
}

void Bgt60ltr11aip::int7Handler()
{
    objPtrVector[7]->callback();
}

void Bgt60ltr11aip::int8Handler()
{
    objPtrVector[8]->callback();
}

void Bgt60ltr11aip::int9Handler()
{
    objPtrVector[9]->callback();
}

void * Bgt60ltr11aip::fnPtrVector[maxGPIOObjs] = {(void *)int0Handler,
                                                  (void *)int1Handler,
                                                  (void *)int2Handler,
                                                  (void *)int3Handler,
                                                  (void *)int4Handler,
                                                  (void *)int5Handler,
                                                  (void *)int6Handler,
                                                  (void *)int7Handler,
                                                  (void *)int8Handler,
                                                  (void *)int9Handler};


void * Bgt60ltr11aip::isrRegister(Bgt60ltr11aip *objPtr)
{
    void *fPtr = nullptr;

    if(idNext < 4)
    {
        objPtrVector[idNext] = objPtr;
        fPtr = fnPtrVector[idNext++];
    }

    return fPtr;
}
