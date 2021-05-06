/*!
 * \name        bgt60-MotionDetection-Int
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the motion of an object using interrupt mode
 * \details
 * This example demonstrates how to detect a moving object while the shield is connected to
 * RaspberryPi using interrupts.
 * 
 * ▶ Connection details:
 * ----------------------------------------------------
 *  Pin on shield   Connected to pin on RaspberryPi 4B   
 * ----------------------------------------------------
 *      TD                      15                          
 *      PD                      16
 *      GND                     GND
 *      Vin                     3V3               
 * ----------------------------------------------------
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

// Include library header
#include "bgt60-rpi.hpp"
#include <stdio.h>
#include <stdint.h>

/* This library works with multiple frameworks and hence these guards are 
 *  necessary to avoid compiling this example for other frameworks. */
#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

//  Define GPIO pins that will be connected to shield
#define Pin_1  15
#define Pin_2  16

// Function declaration to get motion status
void GetMotionStatus(Error_t);

/* Create radar object with following arguements:
 *  Pin_1 : Target Detect Pin (TD)
 *  Pin_2 : Phase Detect Pin  (PD) 
 *  Mode  : Set mode of acquiring sensor data as MODE_INTERRUPT */
Bgt60Rpi bgt60rpi(Pin_1, Pin_2, Bgt60Rpi::MODE_INTERRUPT);

// Begin main
int main(int argc, char const *argv[])
{
    // Initialize the variable to NOT_AVAILABLE to record new events
    Bgt60Rpi::Motion_t MotionDetectStatus = Bgt60Rpi::NOT_AVAILABLE;

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
        /* The getMotion() API does two things: 
        1. Returns  success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "MotionDetectStatus" variable. Events can be: MOTION, NO_MOTION or NOT_AVAILABLE */
        Error_t err = bgt60rpi.getMotion(MotionDetectStatus);
        while(true)
        {
            // Wait for motion detection isr to complete recording motion events
            if(bgt60rpi.available)
                GetMotionStatus(err);
        }
            
        printf(" ***** Example execution completed ***** \n");
    }
}

/**
 * @brief           Motion Detection Status Function
 * @details         This function waits for the interrupt callback function to set events
 *                  based on which following outputs are possible:  
 *                      1. When a moving target is detected
 *                      2. When no motion is detected
 *                      3. When there is a configuration error
 * @param           err      Success or Failure message   
 */
void GetMotionStatus(Error_t err)
{
    if(err == OK)
    {
        // tDetFallingEdgeEvent (i.e high to low) set to true indicates that a moving object is detected
        if (bgt60rpi.motion == Bgt60Rpi::MOTION_OCCURRED)
            printf("Target in motion Detected! \n");
        // tDetRisingEdgeEvent (i.e low to high) set to true indicates that no object is detected
        else if(bgt60rpi.motion == Bgt60Rpi::NO_MOTION_OCCURRED)
            printf("No one's there! \n");
        // Any other combination means there is an issue with configuration
        else
            printf("Sorry! Data unavailable. Check configuration \n");
    }
    // API execution returned error
    else
        printf("Error occured! \n");
}

#endif /** BGT60_FRAMEWORK **/