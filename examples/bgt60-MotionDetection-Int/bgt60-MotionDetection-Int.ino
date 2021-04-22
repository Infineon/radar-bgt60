/*!
 * \name        bgt60-MotionDetection-Int
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object using interrupt mode
 * \details
 * This example demonstrates how to detect a moving object while the shield is connected to
 * Arduino form-factored boards using interrupts.
 * 
 * ▶ Connection details:
 * --------------------------------------------------
 *  Pin on shield   Connected to pin on Arduino Makr  
 * --------------------------------------------------
 *      TD                       1                          
 *      PD                       2
 *      GND                     GND
 *      Vin                     VCC               
 * --------------------------------------------------
 * 
 * ▶ Interrupt mode of acquiring Radar data:
 * - MODE_INTERRUPT : In this mode, an interrupt is generated in case a moving target is detected.
 *                    Once the ISR in library is served, the callback function will be executed that
 *                    sets variables to identify motion detection.
 * 
 * ▶ Decoding Green LED outputs
 * - Green LED indicates the output of target in motion detection
 * ---------------------------------------------
 *    LED    State    Output explanation
 * ---------------------------------------------
 *   Green    ON       Moving target detected
 *            OFF      No target detected 
 * ---------------------------------------------
 * 
 * SPDX-License-Identifier: MIT
 */

// Include library main header
#include "bgt60.hpp"

/* This library works with multiple frameworks and hence these guards are 
*  necessary to avoid compiling this example for other frameworks. */
#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
//  Define GPIO pins that will be connected to shield
#define Pin_1  1
#define Pin_2  2

/* Create radar object and specify GPIO pins as first two parameters followed
*  by mode of acquiring sensor data as MODE_INTERRUPT */
BGT60 bgt60(Pin_1, Pin_2, MODE_INTERRUPT);

// Begin setup function - takes care of initialization and executes only once post reset
void setup()
{
    // Set baud rate for sending messages to serial monitor
    Serial.begin(115200);
    // Configures the GPIO pins to specified mode
    Error_t init_status = bgt60.init();
    // Check if init was successful
    if (OK != init_status)
        Serial.println("Init failed");
    else
        Serial.println("Init successful");

    Serial.println("*** Begin sensing in interrupt mode ***");

    // Initialize the variable to detect to NOT_AVAILABLE to record new events
    Presence_t detect_presence = NOT_AVAILABLE;

  /* The getPresence() API does two things: 
        1. Returns the success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "detect_presence" variable. Events can be: PRESENCE, NO_PRESENCE or NOT_AVAILABLE 
        In case of interrupt method, the value set in detect_presence can be overlooked since these values will also be set
        in variables in ISR */
    Error_t err = bgt60.getPresence(detect_presence);
}

// Begin loop function - this part of code is executed continuously until external termination
void loop()
{   
    // Check if API execution is successful
    if(err == OK)
    {
        // tDetFallingEdgeEvent (i.e high to low) set to true indicates that a moving object is detected
        if (tDetFallingEdgeEvent == true){
            Serial.println("Target in motion Detected!");
        }
        // tDetRisingEdgeEvent (i.e low to high) set to true indicates that no object is detected
        else if(tDetRisingEdgeEvent == true){
            Serial.println("No one's there!");
        }
        // Any other combination means there is an issue with configuration
        else{
            Serial.println("Sorry! Data unavailable. Check configuration");
        }
    }
    // API execution returned error
    else
        Serial.println("Error occured!");
}
#endif /** BGT60_FRAMEWORK **/
