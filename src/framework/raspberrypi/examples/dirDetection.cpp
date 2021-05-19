/*!
 * \name        bgt60-DirDetection
 * \author      Infineon Technologies AG
 * \copyright   2021 Infineon Technologies AG
 * \brief       This example detects the direction of motion of an object using polling method
 * \details     This example demonstrates how to detect the direction of a moving object while the
 *              shield is connected to RaspberryPi using polling method. The code is programmed to first detect
 *              a moving object followed by its direction of motion.
 *
 * \note        You can always control the execution loop by setting StartMotionSensing and
 *              StartDirectionSensing flag value correctly as described in the code section.
 *
 *              ▶ Connection details:
 *              -----------------------------------------------------
 *              Pin on shield   Connected to pin on RaspberryPi 4B
 *              -----------------------------------------------------
 *              TD                       15
 *              PD                       16
 *              GND                      GND
 *              Vin                      VCC
 *              -----------------------------------------------------
 *
 *              ▶ Decoding on-board Green LED output:
 *              - Green LED indicates the output of target in motion detection (TD)
 *              ---------------------------------------------
 *              LED    State    Output explanation
 *              ---------------------------------------------
 *              Green    ON       Moving target detected
 *              OFF      No target detected
 *              ---------------------------------------------
 *
 * SPDX-License-Identifier: MIT
 */

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

// Function declaration for direction detection
void Detect_direction();

// Flag to control the motion and direction sensing
bool StartDirectionSensing = 1;
bool StartMotionSensing = 1;

/* Create radar object with following arguments:
 *  Pin_1 : Target Detect Pin (TD)
 *  Pin_2 : Phase Detect Pin  (PD) */
Bgt60Rpi bgt60rpi(Pin_1, Pin_2);

// Begin main
int main(int argc, char const *argv[])
{
    printf(" ***** Begin Direction Detection example ***** \n");
    // Configures the GPIO pins as input mode
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
        // Function call to start sensing
        while(StartMotionSensing)
            Detect_direction();
        printf("***** Example execution completed \n*****");
    }
}
/**
 * @brief           Direction Detection Function
 * @details         This function handles the logic to detect the direction of a moving target.
 *                  It first waits for a moving object to be identified and then checks for its
 *                  direction. Following permutations of events are possible :
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
 */
void Detect_direction()
{
    // Initialize the variable to NO_INFORMATION to record new events
    Bgt60Rpi::Direction_t DirectionDetectStatus = Bgt60Rpi::NO_INFORMATION;
    // Initialize the variable to NOT_AVAILABLE to record new events
    Bgt60Rpi::Motion_t MotionDetectStatus = Bgt60Rpi::NOT_AVAILABLE;
    /* The getMotion() API does two things:
        1. Returns  success or failure to detect moving object as a message of type Error_t.
           Any value other than OK indicates failure
        2. Sets recent event in "MotionDetectStatus" variable. Events can be: MOTION, NO_MOTION or NOT_AVAILABLE */
    Error_t err_motion = bgt60rpi.getMotion(MotionDetectStatus);
    // Check if API execution is successful
    if(err_motion == OK)
    {
        // Cases based on value set in MotionDetectStatus variable
        switch (MotionDetectStatus)
        {
            //  Variable "MotionDetectStatus" is set to MOTION when moving target is detected
            case Bgt60Rpi::MOTION:
                printf(" Moving target detected... \n");
                while(StartDirectionSensing)
                {
                    /* The getDirection() API does two things:
                    1. Returns  success or failure to detect direction of object as a message of type Error_t.
                       Any value other than OK indicates failure
                    2. Sets recent event in "DirectionDetectStatus" variable. Events can be: APPROACHING or DEPARTING */
                    Error_t err_dir = bgt60rpi.getDirection(DirectionDetectStatus);
                    if(err_dir == OK)
                    {
                        if(Bgt60Rpi::APPROACHING == DirectionDetectStatus)
                        {
                            printf(" Target is approaching! \n");
                            // Continuous sensing. If you want to stop direction sensing once target
                            // is found to be approaching, set this value to 0.
                            StartDirectionSensing = 1;
                            StartMotionSensing = 1;
                        }
                        else if(Bgt60Rpi::DEPARTING == DirectionDetectStatus)
                        {
                            printf(" Target is departing! \n");
                            // Continuous direction sensing. If you want to stop direction sensing once target
                            // is found to be departing, set this value to 0.
                            StartDirectionSensing = 1;
                            // Continuous motion sensing. If you want to stop sensing once motion is detected,
                            // set this value to 0.
                            StartMotionSensing = 1;
                        }
                        // API execution returned error
                        else
                        {
                            printf(" Sorry! Data unavailable. Check configuration! \n");
                            StartDirectionSensing = 0;
                            StartMotionSensing = 0;
                        }
                    }
                    // API execution returned error
                    else
                    {
                        printf(" Direction detection failed! Check configuration again! ");
                        StartDirectionSensing = 0;
                        StartMotionSensing = 0;
                    }
                }
                break;
            //  Variable "MotionDetectStatus" is set to NO_MOTION when moving target is not detected
            case Bgt60Rpi::NO_MOTION:
                printf(" No one's there!\n");
                // Check until moving target is detected
                StartMotionSensing = 1;
                StartDirectionSensing = 1;
                break;
            //  Variable "MotionDetectStatus" is set to NOT_AVAILABLE when no data is available
            case Bgt60Rpi::NOT_AVAILABLE:
                printf(" Sorry! Data unavailable. Check configuration \n");
                // Cannot detect further without fixing the config issue
                StartMotionSensing = 0;
                StartDirectionSensing = 0;
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