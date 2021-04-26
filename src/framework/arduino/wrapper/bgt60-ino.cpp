/**
 * @file        bgt60-ino.cpp
 * @author      Infineon Technologies AG
 * @brief       Radar BGT60 Arduino API
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-ino.hpp"

#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

using namespace bgt60;

/**
 * @brief       Constructor of the Arduino Bgt60 object
 *
 * @param[in]   targetDet Pin number of the target detect pin
 * @param[in]   phaseDet Pin number of the phase detect pin
 * @param[in]   pinMode Desired mode of the board, polling or interrupt driven
 */
Bgt60Ino::Bgt60Ino(uint8_t targetDet, uint8_t phaseDet, MeasMode_t pinMode)
:
Bgt60((tDetPin = new GPIOIno(targetDet, INPUT, GPIO::VLogic_t::NEGATIVE)), (pDetPin = new GPIOIno(phaseDet, INPUT, GPIO::VLogic_t::NEGATIVE)), pinMode)
{

}

/**
 * @brief       Destructor of the Arduino Bgt60 object
 */
Bgt60Ino::~Bgt60Ino()
{

}

/**
 * @brief       Begin the radar board
 *
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
Error_t Bgt60Ino::begin()
{
    Error_t err = OK;

    err  = init();

    return err;
}

/**
 * @brief       Ends the radar board
 *
 * @return      Bgt60 error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
Error_t Bgt60Ino::end()
{
    Error_t err = OK;

    err = deinit();

    return err;
}

/**
 * @brief       Check the internal interrupt flags
 *
 * @details     This function is checking the internal interrupt flags of the object.
 *              Depending on the status of the flags it is printing the actual status
 *              of the chip.
 *
 * @note        Call this function in the loop to constantly get the current status
 *              of the radar board.
 *
 * @pre         Interrupt mode has to be selected, otherwise the function will print
 *              always an invalid status.
 */
void Bgt60Ino::checkIntFlags()
{
    Bgt60::InterruptStatus_t intstatus = Bgt60::InterruptStatus_t::NOTHING_OCCURRED;

    getInterruptStatus(intstatus);

    if(Bgt60::InterruptStatus_t::MOTION_APPROACHING == intstatus)
    {
        Serial.println("Approaching Motion detected");
    }
    else if(Bgt60::InterruptStatus_t::MOTION_DEPARTING == intstatus)
    {
        Serial.println("Departing Motion detected");
    }
    else
    {
        Serial.println("No Motion detected");
    }
}

#endif /** BGT60_FRAMEWORK */