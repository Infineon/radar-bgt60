/*!
 * \name        interruptMode
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example shows how to use the interrupt functionality
 * \details     This example demonstrates how to detect motion and the direction
 *              of a moving object with the help of interrupts while the shield is
 *              connected to Arduino form-factored boards.
 *
 *              ▶ Connection details:
 *              --------------------------------------------------
 *              Pin on shield   Connected to pin on Arduino MKR1000
 *              --------------------------------------------------
 *              TD                  16 (A1)
 *              PD                  17 (A2)
 *              GND                 GND
 *              Vin                 VCC
 *              --------------------------------------------------
 *
 *              ▶ Decoding on-board Red LED output
 *              - Red LED indicates the output of direction of motion once target is detected
 *              ---------------------------------------------
 *              LED    State    Output explanation
 *              ---------------------------------------------
 *              Red     ON       Departing target
 *                      OFF      Approaching target
 *              ---------------------------------------------
 *
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

/* Create radar object and specify GPIO pins as the two parameters */
Bgt60Ino radarShield(TD, PD);

/* Definition and initialization of the interrupt flag */
volatile static bool intFlag = false;

/* User defined callback function */
void cBackFunct(void *)
{
    intFlag = true;
}

/* Begin setup function - take care of initializations and executes only once post reset */
void setup()
{
    /* Set the baud rate for sending messages to the serial monitor */
    Serial.begin(115200);
    /* Configures the GPIO pins */
    Error_t init_status = radarShield.init();
    /* Enable the interrupts */
    init_status = radarShield.enableInterrupt(cBackFunct);
    /* Check if the initialization was successful */
    if (OK != init_status)
        Serial.println("Init failed");
    else
        Serial.println("Init successful");
}

/* Beginn loop function - this part of code is executed continuously until external termination */
void loop()
{
    /* Create variables to store the state of the motion as well as the direction */
    Bgt60::Motion_t motion = Bgt60::NO_MOTION;
    Bgt60::Direction_t direction = Bgt60::NO_DIR;

    /* Wait for the flag to be true, which means an event has occurred */
    if(true == intFlag)
    {
        /* Now check what happend, first check if a motion was detected or is
           not detected anymore */
        Error_t err = radarShield.getMotion(motion);
        /* Check if API execution is successful */
        if(OK == err)
        {
            /* In case motion is detected */
            if(Bgt60::MOTION == motion){
                Serial.println("Target in motion was detected!");

                /* Check the direction of the detected motion */
                err = radarShield.getDirection(direction);
                if(OK == err)
                {
                    /* In case the target is approaching */
                    if(Bgt60::APPROACHING == direction){
                        Serial.println("The target is approaching!");
                    }
                    /* In case the target is departing */
                    else{
                        Serial.println("The target is departing!");
                    }
                }
                /* API execution returned error */
                else{
                    Serial.println("Error has occurred during the determination of the direction!");
                }
                intFlag = false;
            }
            /* No motion is detected */
            else{
                Serial.println("No target in motion detected!");
                intFlag = false;
            }
        }
        /* API execution returned errord */
        else{
            Serial.println("Error has occurred during the determination of the direction!");
            intFlag = false;
        }
    }
}

#endif /** BGT60_FRAMEWORK **/