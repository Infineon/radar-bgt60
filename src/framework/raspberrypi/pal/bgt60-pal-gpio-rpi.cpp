/** 
 * @file        bgt60-pal-gpio-rpi.cpp
 * @brief       Radar BGT60 Raspberry Pi PAL Implementation
 * @copyright   Copyright (c) 2020-2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bgt60-pal-gpio-rpi.hpp"
#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

/**
 * @brief       GPIO Rpi constructor
 * @details     This function sets the basics for a GPIO.
 */
GPIORpi::GPIORpi() 
: pin(4), mode(INPUT), logic(POSITIVE) 
{

}

/**
 * @brief       GPIO Rpi default constructor
 * @details     This function is setting the basics for a GPIO. It allows to set the pin number,
 *              mode of the pin and the logic level.
 * @param[in]   pin     Number of the desired pin
 * @param[in]   mode    Defines the mode of the pin (INPUT, OUTPUT, etc.)
 * @param[in]   logic   Defines the logic level of the pin
 */
GPIORpi::GPIORpi(   uint8_t     pin,
                    uint8_t     mode,
                    VLogic_t    logic)
: pin(pin), mode(mode), logic(logic)
{

}

/**
 * @brief       GPIO Rpi destructor
 * @details     This function does cleanup for class object and its class members when the 
 *              object is destroyed
 */
GPIORpi::~GPIORpi()
{

}

/**
 * @brief       Initializes the Raspberry Pi GPIO
 * @details     This function initializes the chosen pin.
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if initialization error
 */
Error_t GPIORpi::init()
{
    Error_t err = OK;
    if (wiringPiSetup() < 0)
        err = INTF_ERROR;

    pinMode(this->pin, this->mode);

    return err;
}

/**
 * @brief       Deinitializes the Raspberry Pi GPIO
 * @details     This function deinitializes the chosen pin
 * @return      GPIO error code
 * @retval      OK always
 */
Error_t GPIORpi::deinit()
{
    return OK;
}

/**
 * @brief       Enables the Raspberry Pi GPIO interrupt
 * @details     This function enables the interrupt on chosen pin. Depending on the mode,
 *              it triggers the interrupt.
 * @param[in]   *cback  	Function pointer of the interrupt callback
 * @param[in]   mode	  	Event at which the interrupt will occur
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
Error_t GPIORpi::enableInt(void (*cback) (void), IntEvent_t mode) 
{
    Error_t err = OK;
    switch(mode)
    {
        case INT_FALLING_EDGE:
            if (0 > wiringPiISR(this->pin, INT_EDGE_FALLING, (void (*)())cback))  
                err = INTF_ERROR;
            break;

        case INT_RISING_EDGE:
            if (0 > wiringPiISR(this->pin, INT_EDGE_RISING, (void (*)())cback))  
                err = INTF_ERROR;
            break;

        case INT_CHANGE:
            if (0 > wiringPiISR(this->pin, INT_EDGE_BOTH, (void (*)())cback))  
                err = INTF_ERROR;
            break;
        
        default:
            if (0 > wiringPiISR(this->pin, INT_EDGE_BOTH, (void (*)())cback))  
                err = INTF_ERROR;
    }
    return err;
}

/**
 * @brief       Disable Raspberry Pi GPIO interrupt
 * @details     This function disables the interrupt on chosen pin.
 * @note        Not supported by low level framework.
 * @return      GPIO error code
 * @retval      INTF Error always
 */
inline Error_t GPIORpi::disableInt()
{
    return INTF_ERROR;
}

/**
 * @brief       Gets the latest Raspberry Pi interrupt event
 * @details     This function gets the latest interrupt event on the earlier configured
 *              GPIO pin. 
 * @return      GPIO interrupt event
 * @retval      INT_FALLING_EDGE if falling edge event
 * @retval      INT_RISING_EDGE if rising edge event
 */
inline GPIORpi::IntEvent_t GPIORpi::intEvent()
{
    IntEvent_t edge = INT_FALLING_EDGE;
    
    int val = digitalRead(this->pin);
    if(val == LOW)
    {
        edge = INT_FALLING_EDGE;
    }
    else if(val == HIGH) 
    {
        edge = INT_RISING_EDGE;
    }

    return edge;
}

/**
 * @brief       Reads the Raspberry Pi GPIO voltage level
 * @details     This function reads the logic level of the chosen pin and
 *              returns the logic level value.
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIORpi::VLevel_t GPIORpi::read()
{
    return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief       Writes the Raspberry Pi GPIO output voltage level
 * @details     This functions sets the logic level of the chosen pin.
 * @param[in]   level    Voltage level
 * @return      GPIO error code
 * @retval      OK always
 */
inline Error_t GPIORpi::write(VLevel_t level)
{
    digitalWrite(this->pin, level);
    return OK;
}

/**
 * @brief       Enable the GPIO
 * @details     Enables the Raspberry Pi GPIO output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK always
 */
inline Error_t GPIORpi::enable()
{
    if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    return OK;
}

/**
 * @brief       Disable the GPIO
 * @details     Disables the Raspberry Pi GPIO output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK always
 */
inline Error_t GPIORpi::disable()
{
   if(this->logic == POSITIVE)
    {
        digitalWrite(this->pin, GPIO_LOW);
    }
    else if(this->logic == NEGATIVE)
    {
        digitalWrite(this->pin, GPIO_HIGH);
    }
    return OK;
}

#endif /** BGT60_FRAMEWORK **/