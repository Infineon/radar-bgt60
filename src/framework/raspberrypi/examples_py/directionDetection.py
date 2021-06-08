'''
 Name:        directionDetection
 Author:      Infineon Technologies AG
 Copyright:   2021 Infineon Technologies AG
 Description: This example demonstrates how to detect the direction of a moving object while the
              BGT60LTR11AIP shield is connected to a Raspberry Pi using polling method.
              The code is programmed to first detect a moving object followed by its direction of motion.
              Press CTRL+C to end this example.
 
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

# Initialize the variable to radarShield.NO_DIR to be able to record new events
direction = radarShield.NO_DIR

while True:
    # The getDirection() API does two things:
    ## 1. Returns the success or failure to detect direction of object as a message of type Error_t.
    ## Any value other than OK indicates failure
    ## 2. Sets recent event in "direction" variable. Events can be: APPROACHING, DEPARTING or NO_DIR */
    err = radarShield.getDirection(direction)
    
    # Check if API execution is successful
    if err == radarShield.OK:
        # Variable "direction" is set to radarShield.APPROACHING when target is moving closer to sensor
        if direction == radarShield.APPROACHING:
            print("Target is approaching!")

        # Variable "direction" is set to radarShield.DEPARTING when target is moving away from sensor
        elif direction == radarShield.DEPARTING:
            print("Target is departing!")

        # Variable "direction" is set to NO_DIR when no motion was detected
        elif direction == radarShield.NO_DIR:
            print("Direction cannot be determined since no motion was detected.")
                
    # API execution returned error
    else:
        print("Error occured!")

    # Wait 0.5 second
    sleep(0.5)
