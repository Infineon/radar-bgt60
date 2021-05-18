import bgt60_py as b
import time 
Td = 15
Pd = 16

interruptFlag = 0
status= 0
# Create Radar object
radarShield = b.Bgt60Rpi(Td,Pd)

def cback():
    #print("Indicates interrupt initialization success") #Remove this line --> Only for testing
    interruptFlag = 1
    return interruptFlag

def Start_sensing():
    motion = radarShield.NO_MOTION
    direction = radarShield.NO_DIR
    err = radarShield.getMotion(motion)
    if err == radarShield.OK:
        if radarShield.MOTION == motion:
            print(" Target in motion Detected! \n")
            err_dir = radarShield.getDirection(direction)
            if radarShield.OK == err_dir:
                if radarShield.APPROACHING == direction:
                    print("The target is approaching! \n")
                if radarShield.DEPARTING == direction:
                    print("The target is departing! \n")
            else:
                print("Error occured! \n")
                
        elif radarShield.NO_MOTION == motion:
            print(" No one's there!\n")      
        else:
            print(" Sorry! Data unavailable. Check configuration \n")
     
    else:
        print(" Error occured!")     
    return
    
    
# Main
print(" ***** Begin Motion Detection Example ***** \n")
# Initialize the sensor
init_status = radarShield.init()
if radarShield.OK != init_status:
    print(" Initialization failed! \n")
else:
    print(" Intialization successful! \n")   
    init_status = b.setInterrupt(radarShield)
    while True:
        status = b.checkIntStats(cback)
        if status==1:
            Start_sensing()
  
    print(" ***** Example execution completed ***** \n")
