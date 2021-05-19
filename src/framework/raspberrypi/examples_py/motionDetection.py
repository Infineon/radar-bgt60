import bgt60_py as b
Pin_1 = 15
Pin_2 = 16

StartMotionSensing = 1

# Create Radar object
radar = b.Bgt60Rpi(Pin_1,Pin_2)

def Detect_motion(MotionDetectStatus,StartMotionSensing):
    err = radar.getMotion(MotionDetectStatus)
    #Check if API execution is successful
    if err == radar.OK:
        # Variable "MotionDetectStatus" is set to MOTION when moving target is detected
        if radar.MOTION == MotionDetectStatus:
            print(" Target in motion Detected! \n")
            #Stop sensing. If you want to continuously track the moving target set this value to 1
            StartMotionSensing = 0
            return StartMotionSensing
                
        # Variable "MotionDetectStatus" is set to NO_MOTION when moving target is not sensed
        elif MotionDetectStatus == radar.NO_MOTION:
            print(" No one's there!\n")
            #Check until moving target is detected
            StartMotionSensing = 1

        else:
            print(" Sorry! Data unavailable. Check configuration \n")
            StartMotionSensing = 0
                
    # API execution returned error
    else:
        print(" Error occured!")
        StartMotionSensing = 0
    return

print(" ***** Begin Motion Detection Example ***** \n")

# Initialize the sensor
init_status = radar.init()
if radar.OK != init_status:
    print(" Initialization failed! \n")
else:
    print(" Intialization successful! \n")
    MotionDetectStatus = radar.NO_MOTION
    while StartMotionSensing!=0:
        StartMotionSensing = Detect_motion(MotionDetectStatus,StartMotionSensing)
  
    print(" ***** Example execution completed ***** \n")