/*!
 * \name        directionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the direction of motion of an object using polling method
 * \details     This example demonstrates how to detect the direction of a moving object while the
 *              BGT60LTR11AIP shield is connected to a Raspberry Pi using polling method.
 *              The code is programmed to first detect a moving object followed by its direction of motion.
 *              Press CTRL+C to end this example.
 *
 *              Connection details:
 *              -----------------------------------------------------
 *              Pin on shield   Connected to pin on Raspberry Pi 4B
 *              -----------------------------------------------------
 *              TD                      WiringPi 15 (header 8)
 *              PD                      WiringPi 16 (header 10)
 *              GND                     GND         (e.g. header 6)
 *              Vin                     3.3V        (e.g. header 1)
 *              -----------------------------------------------------
 *
 *              Decoding on-board LED output of BGT60LTR11AIP shield:
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

//  Define GPIO pins that will be connected to the shield
#define TD  15
#define PD  16

/* Create radar object with following arguments:
 *  TD : Target Detect Pin
 *  PD : Phase Detect Pin */
Bgt60Rpi radarShield(TD, PD);

int main(int argc, char const *argv[])
{
    // Configures the GPIO pins as input mode
    Error_t init_status = radarShield.init();
    // Check if the initialization was successful
    if (OK != init_status)
    {
        printf("Init failed.\n");
        return 1;
    }
    else
    {
        printf("Init successful.\n");
    }

    while(1) {

        // Initialize the variable to NO_INFORMATION to record new events
        Bgt60Rpi::Direction_t direction = Bgt60Rpi::NO_DIR;

        /* The getDirection() API does two things:
            1. Returns the success or failure to detect direction of object as a message of type Error_t.
            Any value other than OK indicates failure
            2. Sets recent event in "direction" variable. Events can be: APPROACHING, DEPARTING or NO_DIR */
        Error_t err = radarShield.getDirection(direction);
        
        // Check if API execution is successful
        if (err == OK)
        {
            /* Cases based on value set in direction variable */
            switch (direction)
            {
                /* Variable "direction" is set to APPROACHING when target is moving closer to sensor */
                case Bgt60::APPROACHING:
                    printf("Target is approaching!\n");
                    break;
                /* Variable "direction" is set to DEPARTING when target is moving away from sensor */
                case Bgt60::DEPARTING:
                    printf("Target is departing!\n");
                    break;
                /* Variable "direction" is set to NO_DIR when no motion was detected */
                case Bgt60::NO_DIR:
                    printf("Direction cannot be determined since no motion was detected.\n");
                    break;
            }
        }
        /* API execution returned error */
        else{
            printf("Error occurred!\n");
        }

        /* Reducing the frequency of the measurements */
        delay(500);

    }
}