/*!
 * \name        bgt60-DirDetection-Int
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the direction of motion of an object using interrupt method
 * \details
 * This example demonstrates how to detect the direction of a moving object while the 
 * Shield is connected a Raspberry Pi board using interrupts.
 * 
 * ▶ Connection details:
 * ----------------------------------------------------
 *  Pin on shield   Connected to pin on Raspberry Pi
 * ----------------------------------------------------
 *      TD                      15                          
 *      PD                      16
 *      GND                     GND
 *      Vin                     3V3               
 * ----------------------------------------------------
 * 
 * ▶ Interrupt mode of acquiring Radar data:
 * - MODE_INTERRUPT : In this mode, an interrupt is generated in case the direction of moving target
 *                    is detected. Once the ISR in library is served, the callback function will be 
 *                    executed that sets variables to identify motion direction.
 * 
 * SPDX-License-Identifier: MIT
 */

/* This library works with multiple frameworks and hence these guards are 
 *  necessary to avoid compiling this example for other frameworks. */
#include "bgt60-conf.hpp"
#if (BGT60_FRAMEWORK == BGT60_FRMWK_RPI)

// Include library header
#include "bgt60-rpi.hpp"
#include <stdio.h>
#include <stdint.h>

//  Define GPIO pins that will be connected to Shield
#define Pin_1  15
#define Pin_2  16

// Function declaration to get motion status
void GetDirectionStatus(Error_t);

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

    printf(" ***** Begin Direction Detection example ***** \n");
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
                GetDirectionStatus(err);
        }
            
        printf(" ***** Example execution completed ***** \n");
    }
}

/**
 * @brief           Direction Detection Status Function
 * @details         This function handles the logic to detect the direction of a moving target.
 *                  It first waits for the interrupt routine to record motion detection events
 *                  followed by direction detection. Both motion and direction is sensed by interrupt method
 *                  Following permutations of events are possible : 
 *                  -----------------------------------------------------------------------------
 *                  Motion Detected     Detected Direction             Expected behavior
 *                  -----------------------------------------------------------------------------
 *                      Yes                 Approaching               Prints approaching
 *                                           Departing                 Prints departing
 *                                            No data           Direction detection config failed    
 *                  -----------------------------------------------------------------------------          
 *                      No                      x               Waits infinitely to detect motion
 *                  -----------------------------------------------------------------------------
 *                    No data                   x               Motion detection config failed
 *                  -----------------------------------------------------------------------------
 * @param           err      Success or Failure message   
 */
void GetDirectionStatus(Error_t err)
{
    if(err == OK)
    {
        // tDetFallingEdgeEvent (i.e high to low) set to true indicates that a moving object is detected
        if (bgt60rpi.motion == Bgt60Rpi::MOTION_OCCURRED)
        {
            printf("Target in motion Detected! \n");
            // Initialize the variable to NO_INFORMATION to record new events
            Bgt60::Direction_t DirectionDetectStatus = Bgt60Rpi::NO_INFORMATION;
             /* The getDirection() API does two things: 
                1. Returns  success or failure to detect direction of object as a message of type Error_t.
                    Any value other than OK indicates failure
                2. Sets recent event in "DirectionDetectStatus" variable. Events can be: APPROACHING or DEPARTING */
            Error_t err_dir = bgt60rpi.getDirection(DirectionDetectStatus);
            if(err_dir == OK)
            {
                // pDetFallingEdgeEvent (i.e high to low) set to true indicates the target is approaching
                if (bgt60rpi.direction = Bgt60Rpi::MOTION_APPROACHING)
                    printf("Target is approaching! \n");     
                // pDetRisingEdgeEvent (i.e low to high) set to true indicates the target is departing 
                else if(bgt60rpi.direction = Bgt60Rpi::MOTION_DEPARTING)
                    printf("Target is departing! \n");
            }
            // Any other combination means there is an issue with configuration
            else
                printf("Sorry! Data unavailable for direction detection. Check configuration \n");
        }
    
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