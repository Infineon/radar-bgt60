'''
 Name:        interruptMode
 Author:      Infineon Technologies AG
 Copyright:   2021 Infineon Technologies AG
 Description: This example demonstrates how to detect motion and the direction
              of a moving object with the help of interrupts while the BGT60LTR11AIP
              shield is connected to a Raspberry Pi board using interrupts.
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
import sys 

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
    print("Init failed.")
else:
    print("Init successful.")

# Definition and initialization of the interrupt active flag
intActive = False

def cbackFunct():
    global intActive

    if not intActive:

        # Set the interrupt active flag to avoid parallel execution of this function multiple times.
        intActive = True

        # Create variables to store the state of the motion as well as the direction.
        motion = radarShield.NO_MOTION
        direction = radarShield.NO_DIR

        # Now check what happend, first check if a motion was detected.
        err = radarShield.getMotion(motion)

        # Check if API execution is successful.
        if err == radarShield.OK:
            # In case motion is detected.
            if motion == radarShield.MOTION:
                print("Target in motion was detected!")

                # Check the direction of the detected motion.
                err = radarShield.getDirection(direction)

                if err == radarShield.OK:
                    # In case the target is approaching
                    if direction == radarShield.APPROACHING:
                        print("The target is approaching!")

                    # In case the target is departing
                    else:
                        print("The target is departing!")
                # API execution returned error
                else:
                    print("Error has occurred during the determination of the direction!")
            # No motion is detected
            else:
                print("No target in motion detected!")
        # API execution returned error
        else:
            print("Error has occurred during the determination of the direction!")

        print("\n--------------------------------------\n")

        # Release the interrupt active flag to allow a new call of this callback function.
        intActive = False

print("Initialization successful")
int_status = radarShield.enableInterrupt(cbackFunct)

if radarShield.OK != int_status:
    print("Interrupt init failed.")
else:
    print("Interrupt init successful.")

while True:
    # Here you can do something else in parallel while waiting for an interrupt.
    sleep(1000)
