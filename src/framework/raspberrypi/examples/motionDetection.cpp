/*!
 * \name        motionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object using polling mode
 * \details     This example demonstrates how to detect a moving object while the shield is
 *              connected to RaspberryPi using polling method. As soon as a moving target is
 *              detected, the code execution ends.
 * 
 *              ▶ Connection details:
 *              -----------------------------------------------------
 *              Pin on shield   Connected to pin on Raspberry Pi 4B
 *              -----------------------------------------------------
 *              TD                       GPIO 22    (board 15)
 *              PD                       GPIO 23    (board 16)
 *              GND                      GND        (e.g. board 6)
 *              Vin                      3.3V       (board 1)
 *              -----------------------------------------------------
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

// Include library header
#include "bgt60-rpi.hpp"
#include <stdio.h>
#include <stdint.h>

//  Define GPIO pins that will be connected to shield
#define TD  15
#define PD  16

/* Create radar object with following arguments:
 *  TD : Target Detect Pin
 *  PD : Phase Detect Pin */
Bgt60Rpi radarShield(TD, PD);

int main(int argc, char const *argv[])
{
    // Configures the GPIO pins to input mode
    Error_t init_status = radarShield.init();
    /* Check if the initialization was successful */
    if (OK != init_status) {
        printf("Init failed.\n");
        return 1;
    }
    else {
        printf("Init successful.\n");
    }

    while(1) {

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
                    printf("Target in motion detected!\n");
                    break;
                /*  Variable "motion" is set to NO_MOTION when moving target is not present */
                case Bgt60::NO_MOTION:
                    printf("No target in motion detected.\n");
                    break;
            }
        }
        /*  API execution returned error */
        else {
            printf("Error occurred!\n");
        }

        /* Reducing the frequency of the measurements */
        delay(500);
    }
}