/*!
 * \name        bgt60-DirDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the direction of motion of an object using interrupt method
 * \details
 * This example demonstrates how to detect the direction of a moving object while the 
 * shield is connected to Arduino form-factored boards using interrupts.
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
 * - MODE_INTERRUPT : In this mode, an interrupt is generated in case a moving target and 
 *                    its motion is detected. Once the ISR in library is served, the callback 
 *                    function will be executed that sets variables to identify motion direction.
 * 
 * ▶ Decoding on-board Red LED output
 * - Red LED indicates the output of direction of motion once target is detected
 * ---------------------------------------------
 *    LED    State    Output explanation
 * ---------------------------------------------   
 *    Red     ON       Departing target
 *            OFF      Approaching target 
 * ---------------------------------------------
 * 
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
*  by mode of acquiring sensor data as MODE_INTERRUPT */
Bgt60ltr11aip radarBgt60(Pin_1, Pin_2, MODE_INTERRUPT);

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

     Serial.println("*** Begin sensing in interrupt mode ***");

    // Initialize the variable to NOT_AVAILABLE to record new events
    Direction_t detect_direction = NOT_AVAILABLE;

    /* The getDirection() API does two things: 
        1. Returns the success or failure to detect direction of object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "detect_direction" variable. Events can be: APPROACHING, DEPARTING or NOT_AVAILABLE 
       In case of interrupt method, the value set in detect_presence can be overlooked since these values will also be set
       in variables in ISR */
    Error_t err = radarBgt60.getDirection(detect_direction);
}

// Begin loop function - this part of code is executed continuously until external termination
void loop()
{
    // Check if API execution is successful
    if(err == OK)
    {
        // pDetFallingEdgeEvent (i.e high to low) set to true indicates the target is approaching
        if (pDetFallingEdgeEvent == true){
            Serial.println("Target is approaching!");
        }
        // pDetRisingEdgeEvent (i.e low to high) set to true indicates the target is departing 
        else if(pDetRisingEdgeEvent == true){
            Serial.println("Target is departing!");
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
