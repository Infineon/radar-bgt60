/*!
 * \name        bgt60-MotionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object using polling mode
 * \details
 * This example demonstrates how to detect a moving object while the shield is connected to
 * Arduino form-factored boards using polling method.
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
 * ▶ Polling mode of acquiring Radar data:
 * - MODE_POLLING   : In this mode, the GPIO pins are continuously monitored to detect the 
 *                    moving target and its direction
 * 
 * ▶ Decoding on-board Green LED output
 * - Green LED indicates the output of target in motion detection (TD)
 * ---------------------------------------------
 *    LED    State    Output explanation
 * ---------------------------------------------
 *   Green    ON       Moving target detected
 *            OFF      No target detected 
 * ---------------------------------------------
 * SPDX-License-Identifier: MIT
 */

// Include library main header
#include "../../../corelib/bgt60ltr11aip.hpp"

/* This library works with multiple frameworks and hence these guards are 
*  necessary to avoid compiling this example for other frameworks. */
#if (RADAR_BGT60_FRAMEWORK == RADAR_BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
//  Define GPIO pins that will be connected to shield
#define Pin_1  1
#define Pin_2  2

/* Create radar object and specify GPIO pins as first two parameters followed
*  by mode of acquiring sensor data as MODE_POLLING */
Bgt60ltr11aip radarBgt60(Pin_1, Pin_2, MODE_POLLING);

// Begin setup function - takes care of initialization and executes only once post reset
void setup()
{
    // Set the baud rate for sending messages to serial monitor
    Serial.begin(115200);
    // Configures the GPIO pins to specified mode
    Error_t init_status = radarBgt60.init();
    // Check if init was successful
    if (OK != init_status)
        Serial.println("Init failed");
    else
        Serial.println("Init successful");
}

// Begin loop function - this part of code is executed continuously until external termination
void loop()
{
    // Initialize the variable to NOT_AVAILABLE to record new events
    Presence_t detect_presence = NOT_AVAILABLE;

   /* The getPresence() API does two things: 
        1. Returns the success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "detect_presence" variable. Events can be: PRESENCE, NO_PRESENCE or NOT_AVAILABLE */
    Error_t err = radarBgt60.getPresence(detect_presence);
    // Check if API execution is successful
    if(err == OK)
    {
        // Cases based on value set in detect_presence variable
        switch (detect_presence)
        {
            //  Variable "detect_presence" is set to PRESENCE when moving target is detected
            case PRESENCE:
                Serial.println("Target in motion Detected!");
                break;
            //  Variable "detect_presence" is set to NO_PRESENCE when moving target is not present
            case NO_PRESENCE:
                Serial.println("No one's there!");
                break;
            //  Variable "detect_presence" is set to NOT_AVAILABLE when no data is available
            case NOT_AVAILABLE:
                Serial.println("Sorry! Data unavailable. Check configuration");
                break;
            default:
                Serial.println("Waiting for sensor to detect target...");
        }
       
    }
    // API execution returned error
    else
        Serial.println("Error occured!");
}
