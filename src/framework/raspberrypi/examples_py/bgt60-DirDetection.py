import bgt60_py as b
Pin_1 = 15
Pin_2 = 16

StartDirSensing = 1

# Create Radar object
radar = b.Bgt60Rpi(Pin_1,Pin_2)

def Detect_direction(DirDetectStatus,StartDirSensing):
    err = radar.getDirection(DirDetectStatus)
    print(DirDetectStatus)
    #Check if API execution is successful
    if err == radar.OK:
    
        # Variable "MotionDetectStatus" is set to MOTION when moving target is detected
        if radar.APPROACHING == DirDetectStatus:
            print(" Target is approaching! \n")
            #Stop sensing. If you want to continuously track the moving target set this value to 1
            StartDirSensing = 0
                
        # Variable "MotionDetectStatus" is set to NO_MOTION when moving target is not sensed
        elif radar.DEPARTING == DirDetectStatus:
            print(" Target is departing!\n")
            #Check until moving target is detected
            StartDirSensing = 1
        
        else:
            print(" Trying to detect motion \n")
            StartDirSensing = 1

                
    # API execution returned error
    else:
        print(" Error occured!")
        StartDirSensing = 0

    return StartDirSensing

print(" ***** Begin Direction Detection Example ***** \n")
# Initialize the sensor
init_status = radar.init()
if radar.OK != init_status:
    print(" Initialization failed! \n")
else:
    print(" Intialization successful! \n")
    DirDetectStatus = radar.NO_DIR
    while StartDirSensing:
        StartDirSensing = Detect_direction(DirDetectStatus,StartDirSensing)
  
    print(" ***** Example execution completed ***** \n")