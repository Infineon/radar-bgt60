import bgt60_py as b
import time, sys 
Td = 15
Pd = 16

interruptFlag = 0
# Create Radar object
radarShield = b.Bgt60Rpi(Td,Pd)

def bgt60_assert(err):
    """ 
    Assert return codes from BGT60 API functions

    args:
    - err : Return code from bgt60_py module lib
    """
    if radarShield.OK != err :
        print("Exiting with error", err)
        sys.exit(0)

def cback():
    """
    Callback for bgt60_py interrupt
    """
    global interruptFlag
    interruptFlag = 1

# Main
print(" ***** Begin Motion Detection Example ***** \n")

err = radarShield.init()
bgt60_assert(err)

print("Initialization successful")
err = radarShield.enableInterrupt(cback)
bgt60_assert(err)

print("Interrupt enable")

motion = radarShield.NO_MOTION
direction = radarShield.NO_DIR

# Super-loop
while True:

    # Wait for hardware interrupt
    while interruptFlag == 0:
        pass
    
    # Clear interrupt flag
    interruptFlag = 0

    err = radarShield.getMotion(motion)
    bgt60_assert(err)

    if radarShield.MOTION == motion:
        print(" Target in motion Detected! \n")
        err = radarShield.getDirection(direction)
        bgt60_assert(err)

        if radarShield.APPROACHING == direction:
            print("The target is approaching! \n")
        if radarShield.DEPARTING == direction:
            print("The target is departing! \n")
            
    elif radarShield.NO_MOTION == motion:
        print(" No one's there!\n")      
    else:
        print(" Sorry! Data unavailable. Check configuration \n")

print(" ***** Example execution completed ***** \n")
