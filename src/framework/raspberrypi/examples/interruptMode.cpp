/*!
 * \name        interruptMode
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example shows how to use the interrupt functionality
 * \details     This example demonstrates how to detect motion and the direction
 *              of a moving object with the help of interrupts while the BGT60LTR11AIP
 *              shield is connected to a Raspberry Pi board using interrupts.
 * 
 *              ▶ Connection details:
 *              ----------------------------------------------------
 *              Pin on shield   Connected to pin on Raspberry Pi
 *              ----------------------------------------------------
 *              TD                      15                          
 *              PD                      16
 *              GND                     GND
 *              Vin                     3V3               
 *              ----------------------------------------------------
 * 
 *              ▶ Interrupt mode of acquiring Radar data:
 *              - MODE_INTERRUPT : In this mode, an interrupt is generated in case the direction of
 *                  moving target is detected. Once the ISR in library is served, the callback function
 *                  will be executed that sets variables to identify motion direction.
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

/*
 * As this library works with multiple frameworks,
 * this part is needed to avoid trying to compile
 * this example from other frameworks.
 */
#include "../../../config/bgt60-conf.hpp"
#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

// Include library header
#include "bgt60-rpi.hpp"
#include <stdio.h>
#include <stdint.h>


/**
 * TODO: This example needs rework to adapt to new API. Not compiling!!!!
 */

//  Define GPIO pins that will be connected to shield
#define TD  15
#define PD  16

/* Create radar object with following arguments:
 *  TD : Target Detect Pin
 *  PD : Phase Detect Pin
 *  Mode  : Set mode of acquiring sensor data as MODE_INTERRUPT */
Bgt60Rpi radarShield(TD, PD);

// Begin main
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
        while(true)
        {
            // Wait for motion detection isr to complete recording motion events
            if(radarShield.available)
            {
                /* Now check what happend, first check if a motion was detected or is
                not detected anymore */
                Error_t err = radarShield.getMotion(motion);

                /* Check if API execution is successful */
                if(OK == err)
                {
                    /* In case motion is detected */
                    if(Bgt60::MOTION == motion){
                        printf("Target in motion was detected!\n");

                        /* Check the direction of the detected motion */
                        err = radarShield.getDirection(direction);
                        if(OK == err)
                        {
                            /* In case the target is approaching */
                            if(Bgt60::APPROACHING == direction){
                                printf("The target is approaching!\n");
                            }
                            /* In case the target is departing */
                            else{
                                printf("The target is departing!\n");
                            }
                        }
                        /* API execution returned error */
                        else{
                            printf("Error has occurred during the determination of the direction!\n");
                        }
                    }
                    /* No motion is detected */
                    else{
                        printf("No target in motion detected!\n");
                    }
                }
                /* API execution returned errord */
                else{
                    printf("Error has occurred during the determination of the direction!\n");
                }
            }
        }
    }
}

#endif /** BGT60_FRAMEWORK **/