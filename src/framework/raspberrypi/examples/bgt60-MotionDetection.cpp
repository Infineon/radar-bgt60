/*!
 * \name        bgt60-MotionDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object using polling mode
 * \details
 * This example demonstrates how to detect a moving object while the shield is connected to
 * RaspberryPi using polling method. As soon as a moving target is detected, the code execution ends.
 * 
 * \note: You can always control the execution by setting StartMotionSensing flag value correctly
 *        as described in the code section.
 * 
 * ▶ Connection details:
 * -----------------------------------------------------
 *  Pin on shield   Connected to pin on RaspberryPi 4B  
 * -----------------------------------------------------
 *      TD                       15                          
 *      PD                       16
 *      GND                      GND
 *      Vin                      3V3               
 * -----------------------------------------------------
 * 
 * ▶ Polling mode of acquiring Radar data:
 * - MODE_POLLING   : In this mode, the GPIO pins are continuously monitored to detect the 
 *                    moving target.
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

#include "../../../config/bgt60-conf.hpp"

/* This library works with multiple frameworks and hence these guards are 
 *  necessary to avoid compiling this example for other frameworks. */
#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

// Include library header
#include "bgt60-rpi.hpp"
#include <stdio.h>
#include <stdint.h>

//  Define GPIO pins that will be connected to shield
#define Pin_1  15
#define Pin_2  16

// Function declaration for motion detection
void Detect_motion();

// Flag to control the motion sensing
bool StartMotionSensing = 1;

/* Create radar object with following arguements:
 *  Pin_1 : Target Detect Pin (TD)
 *  Pin_2 : Phase Detect Pin  (PD) 
 *  Mode  : Set mode of acquiring sensor data as MODE_POLLING */
Bgt60Rpi bgt60rpi(Pin_1, Pin_2, Bgt60Rpi::MODE_POLLING);

// Begin main
int main(int argc, char const *argv[])
{
    printf(" ***** Begin Motion Detection example ***** \n");
    // Configures the GPIO pins to input mode
    Error_t init_status = bgt60rpi.init();
    // Check if init was successful
    if (OK != init_status)
    {
        printf(" Initialization failed! \n");
        return 0;
    }
    else
    {
        printf(" Initialization successful! \n");
        // If all initializations have been successful, then start motion sensing
        while(StartMotionSensing)
            Detect_motion();
        printf(" ***** Example execution completed ***** \n");
    }
}

/**
 * @brief           Motion Detection Function
 * @details         This function handles the logic to detect a moving target. 
 *                  It can display results in case of three types of event:
 *                      1. When it detects a moving target
 *                      2. When there is no moving target 
 *                      3. When there is a configuration error
 */
void Detect_motion()
{
    // Initialize the variable to NOT_AVAILABLE to record new events
    Bgt60::Motion_t MotionDetectStatus = Bgt60Rpi::NOT_AVAILABLE;
    /* The getMotion() API does two things: 
        1. Returns  success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "MotionDetectStatus" variable. Events can be: MOTION, NO_MOTION or NOT_AVAILABLE */
    Error_t err = bgt60rpi.getMotion(MotionDetectStatus);
    // Check if API execution is successful
    if(err == OK)
    {
        // Cases based on value set in MotionDetectStatus variable
        switch (MotionDetectStatus)
        {
            //  Variable "MotionDetectStatus" is set to MOTION when moving target is detected
            case Bgt60Rpi::MOTION:
                printf(" Target in motion Detected! \n");
                // Stop sensing. If you want to continuously track the moving target set this value to 1
                StartMotionSensing = 0;
                break;
            //  Variable "MotionDetectStatus" is set to NO_MOTION when moving target is not sensed
            case Bgt60Rpi::NO_MOTION:
                printf(" No one's there!\n");
                // Check until moving target is detected
                StartMotionSensing = 1;
                break;
            //  Variable "MotionDetectStatus" is set to NOT_AVAILABLE when no data is available
            case Bgt60Rpi::NOT_AVAILABLE:
                printf(" Sorry! Data unavailable. Check configuration \n");
                // Cannot detect further without fixing the config issue
                StartMotionSensing = 0;
                break;
            default:
                printf(" Waiting for sensor to detect target movement...\n");
        }
    }
    // API execution returned error
    else
    {
        printf(" Error occured!");
        StartMotionSensing = 0;
        return;
    }
}

#endif /** BGT60_FRAMEWORK **/