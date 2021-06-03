/** 
 * @file        bgt60-rpi.hpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Raspberry Pi API
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-rpi.hpp"


#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)
using namespace bgt60;

/**
 * @brief       Constructor of the RaspberryPi Bgt60 object
 * @details     This function is the instance constructor. It accepts the Raspberry Pi GPIO pins utilized
 *              for target and phase detect from the user. These pins are initialized by creating instances 
 *              to GPIORpi and then mapped to main Bgt60 class.           
 * @param[in]   targetDet   Pin number of the target detect pin
 * @param[in]   phaseDet    Pin number of the phase detect pin
 * @param[in]   pinMode     Desired mode of the board, polling or interrupt driven
 */
 
Bgt60Rpi::Bgt60Rpi(uint8_t targetDet, uint8_t phaseDet)
:
Bgt60((tDetPin = new GPIORpi(targetDet, INPUT, GPIO::VLogic_t::NEGATIVE)), (pDetPin = new GPIORpi(phaseDet, INPUT, GPIO::VLogic_t::NEGATIVE)))
{

}

/**
 * @brief       Destructor of the RaspberryPi Bgt60 object
 */
Bgt60Rpi::~Bgt60Rpi()
{

}

/**
 * @brief       Enable interrupt
 * @param[in]   cback   Pointer to the interrupt callback function 
 * 
 * @note        Convenience function to ease pybind11 wrapping of void pointer
 *              argument functions
 * 
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 * @retval      CONF_ERROR if callback resource allocation not avaiable     
 */
Error_t Bgt60Rpi::enableInterrupt(std::function<void(void)> & cback)
{   
    typedef void (*CCBackPtr_t)(void);

    CCBackPtr_t cCback = (CCBackPtr_t)registerCBack(cback);

    if (nullptr != cCback)
    {
        return Bgt60::enableInterrupt(cCback);
    }
    else
    {
        return CONF_ERROR;
    }
}

Bgt60Rpi::StdFnCBack_t Bgt60Rpi::lambdaFnVector[maxCBacks] = { nullptr };
uint8_t Bgt60Rpi::idxNext = 0;

/**
 * @brief   Callback Lambda Wrapper Handler
 */
void Bgt60Rpi::wrappedCBackLambda0() 
{
    lambdaFnVector[0]();
}

/**
 * @brief   Callback Lambda Wrapper Handler
 */
void Bgt60Rpi::wrappedCBackLambda1() 
{
    lambdaFnVector[1]();
}

/**
 * @brief   Callback Lambda Wrapper Handler
 */
void Bgt60Rpi::wrappedCBackLambda2() 
{
    lambdaFnVector[2]();
}

/**
 * @brief   Callback Lambda Wrapper Handler
 */
void Bgt60Rpi::wrappedCBackLambda3() 
{
    lambdaFnVector[3]();
}

/**
 * @brief   Callback Lambda Wrapper Handler
 */
void Bgt60Rpi::wrappedCBackLambda4() 
{
    lambdaFnVector[4]();
}

void * Bgt60Rpi::fnPtrVector[maxCBacks] = {(void *)wrappedCBackLambda0,
                                           (void *)wrappedCBackLambda1,
                                           (void *)wrappedCBackLambda2,
                                           (void *)wrappedCBackLambda3,
                                           (void *)wrappedCBackLambda4};

/**
 * @brief       Register a lambda function and allocated its to one of the 
 *              available static wrappers. Up to the maximum available.
 * @param[in]   stdFuncBack Lambda callback
 * @return      Pointer to the allocated C callback wrapper
 */
void * Bgt60Rpi::registerCBack(StdFnCBack_t   cback)
{
    void * fPtr = nullptr;

    if(idxNext < maxCBacks)
    {
        lambdaFnVector[idxNext] = cback;
        fPtr =  fnPtrVector[idxNext++];
    }

    return fPtr;
}

#endif /** BGT60_FRAMEWORK */