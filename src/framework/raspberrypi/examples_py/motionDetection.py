'''
 Name:        motionDetection
 Author:      Infineon Technologies AG
 Copyright:   2021 Infineon Technologies AG
 Description: This example demonstrates how to detect a moving object while the shield is
              connected to Raspberry Pi using polling method. Press CTRL+C to end this example.
 
              Connection details:
              -----------------------------------------------------
              Pin on shield   Connected to pin on Raspberry Pi 4B
              -----------------------------------------------------
              TD                      WiringPi 15 (header 8)
              PD                      WiringPi 16 (header 10)
              GND                     GND         (e.g. header 6)
              Vin                     3.3V        (e.g. header 1)
              -----------------------------------------------------

              Decoding on-board LED output of BGT60LTR11AIP shield:
 
              - Red LED indicates the output of direction of motion once target is detected (PD)
              ---------------------------------------------
              LED    State    Output explanation
              ---------------------------------------------
              Red     ON       Departing target
                      OFF      Approaching target
              ---------------------------------------------

              - Green LED indicates the output of target in motion detection (TD)
              ---------------------------------------------
              LED    State    Output explanation
              ---------------------------------------------
              Green    ON       Moving target detected
                       OFF      No target detected
              ---------------------------------------------

 SPDX-License-Identifier: MIT
'''

import bgt60_py as bgt60
from time import sleep

# Define GPIO pins that will be connected to the shield
TD = 15
PD = 16

# Create radarShield object with following arguments:
# TD : Target Detect Pin
# PD : Phase Detect Pin
radarShield = bgt60.Bgt60Rpi(TD, PD)

# Configures the GPIO pins to input mode
init_status = radarShield.init()

# Check if the initialization was successful
if radarShield.OK != init_status:
    print("Initialization failed!")
else:
    print("Intialization successful!")

# Initialize the variable to radarShield.NO_MOTION to be able to record new events
motion = radarShield.NO_MOTION

while True:
    # The getMotion() API does two things:
    ## 1. Returns the success or failure to detect moving object as a message of type Error_t.
    ## Any value other than OK indicates failure
    ## 2. Sets recent event in "motion" variable. Events can be: NO_MOTION or MOTION
    err = radarShield.getMotion(motion)
    
    # Check if API execution is successful
    if err == radarShield.OK:
        # Variable "motion" is set to radarShield.MOTION when moving target is detected
        if motion == radarShield.MOTION:
            print("Target in motion detected!")

        # Variable "motion" is set to radarShield.NO_MOTION when moving target is not present
        elif motion == radarShield.NO_MOTION:
            print("No target in motion detected.")
                
    # API execution returned error
    else:
        print("Error occured!")

    # Wait 0.5 second
    sleep(0.5)
