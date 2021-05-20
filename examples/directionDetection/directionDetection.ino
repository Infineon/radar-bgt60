/*!
 * \name        directionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the direction of motion of an object
 * \details     This example demonstrates how to detect the direction of a moving object while the
 *              BGT60LTR11AIP shield is connected to Arduino MKR form-factored boards.
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
 *              ▶ Decoding on-board LED output of BGT60LTR11AIP shield:
 * 
 *              - Red LED indicates the output of direction of motion once target is detected (PD)
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

#include <Arduino.h>
/* Include library main header */
#include <bgt60-ino.hpp>
/* Include Arduino platform header */
#include <bgt60-platf-ino.hpp>

/* Create radar object with following arguments:
 *  TD : Target Detect Pin
 *  PD : Phase Detect Pin */
Bgt60Ino radarShield(TD, PD);

/* Begin setup function - takes care of initialization and executes only once post reset */
void setup()
{
    /* Set the baud rate for sending messages to the serial monitor */
    Serial.begin(9600);
    // Configures the GPIO pins to input mode
    Error_t init_status = radarShield.init();
    /* Check if the initialization was successful */
    if (OK != init_status) {
        Serial.println("Init failed.");
    }
    else {
        Serial.println("Init successful.");
    }
}

/* Begin loop function - this part of code is executed continuously until external termination */
void loop()
{
    /* Initialize the variable to NO_DIR to be able to record new events */
    Bgt60::Direction_t direction = Bgt60::NO_DIR;

    /* The getDirection() API does two things:
        1. Returns the success or failure to detect direction of object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "direction" variable. Events can be: APPROACHING, DEPARTING or NO_DIR */
    Error_t err = radarShield.getDirection(direction);

    /* Check if API execution is successful */
    if (err == OK)
    {
        /* Cases based on value set in direction variable */
        switch (direction)
        {
            /* Variable "direction" is set to APPROACHING when target is moving closer to sensor */
            case Bgt60::APPROACHING:
                Serial.println("Target is approaching!");
                break;
            /* Variable "direction" is set to DEPARTING when target is moving away from sensor */
            case Bgt60::DEPARTING:
                Serial.println("Target is departing!");
                break;
            /* Variable "direction" is set to NO_DIR when no motion was detected */
            case Bgt60::NO_DIR:
                Serial.println("Direction cannot be determined since no motion was detected!");
                break;
        }
    }
    /* API execution returned error */
    else{
        Serial.println("Error occurred!");
    }

    /* Reducing the frequency of the measurements */
    delay(500);
}
#endif /** BGT60_FRAMEWORK **/
