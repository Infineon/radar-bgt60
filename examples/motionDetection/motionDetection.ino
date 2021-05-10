/*!
 * \name        motionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object
 * \details     This example demonstrates how to detect a moving object while the shield is connected to
 *              Arduino form-factored boards using polling method.
 *
 *              ▶ Connection details:
 *              --------------------------------------------------
 *              Pin on shield   Connected to pin on Arduino Makr
 *              --------------------------------------------------
 *              TD                  16 (A1)
 *              PD                  17 (A2)
 *              GND                 GND
 *              Vin                 VCC
 *              --------------------------------------------------
 *
 *              ▶ Decoding on-board Green LED output
 *              - Green LED indicates the output of target in motion detection (TD)
 *              ---------------------------------------------
 *              LED    State    Output explanation
 *              ---------------------------------------------
 *              Green    ON       Moving target detected
 *                       OFF      No target detected
 *              ---------------------------------------------
 *
 * SPDX-License-Identifier: MIT
 */

/* This library works with multiple frameworks and hence these guards are
   necessary to avoid compiling this example for other frameworks */
#if (BGT60_FRAMEWORK == BGT60_FRMWK_ARDUINO)

#include <Arduino.h>
/* Include library main header */
#include <bgt60-ino.hpp>
/* Include Arduino platform header */
#include <bgt60-platf-ino.hpp>

/* Definition of a delay to reduce the measurement frequency */
#define MEASDELAY 500

/* Create radar object and specify GPIO pins as the two parameters */
Bgt60Ino radarShield(TD, PD);

/* Begin setup function - takes care of initializations and executes only once post reset */
void setup()
{
    /* Set the baud rate for sending messages to the serial monitor */
    Serial.begin(115200);
    /* Configures the GPIO pins */
    Error_t init_status = radarShield.init();
    /* Check if the initialization was successful */
    if (OK != init_status)
        Serial.println("Init failed");
    else
        Serial.println("Init successful");
}

/* Begin loop function - this part of code is executed continuously until external termination */
void loop()
{
    /* Initialize the variable to NO_MOTION to be able to record new events */
    Bgt60::Motion_t motion = Bgt60::NO_MOTION;

   /* The getMotion() API does two things:
        1. Returns the success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "motion" variable. Events can be: NO_MOTION or MOTION */
    Error_t err = radarShield.getMotion(motion);
    /* Check if API execution is successful */
    if(err == OK)
    {
        /* Cases based on value set in motion variable */
        switch (motion)
        {
            /* Variable "motion" is set to MOTION when moving target is detected */
            case Bgt60::MOTION:
                Serial.println("Target in motion detected!");
                break;
            /*  Variable "motion" is set to NO_MOTION when moving target is not present */
            case Bgt60::NO_MOTION:
                Serial.println("No target in motion detected!");
                break;
        }
    }
    /*  API execution returned error */
    else{
        Serial.println("Error occurred!");
    }

    /* Reducing the frequency of the measurements */
    delay(MEASDELAY);
}
#endif /** BGT60_FRAMEWORK **/
