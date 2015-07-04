/* Gin Siu Cheng
 * File: lidarCam_sfunct.c
 * Last Modified: July 11, 2014
 *
  *
  *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
  *
  *   This file is an S-function produced by the S-Function
  *   Builder which only recognizes certain fields.  Changes made
  *   outside these fields will be lost the next time the block is
  *   used to load, edit, and resave this file. This file will be overwritten
  *   by the S-function Builder block. If you want to edit this file by hand, 
  *   you must change it only in the area defined as:  
  *
  *        %%%-SFUNWIZ_defines_Changes_BEGIN
  *        #define NAME 'replacement text' 
  *        %%% SFUNWIZ_defines_Changes_END
  *
  *   DO NOT change NAME--Change the 'replacement text' only.
  *
  *   For better compatibility with the Real-Time Workshop, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Real-Time Workshop User's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *  -------------------------------------------------------------------------
  * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
  *  ------------------------------------------------------------------------- 
 * Created: Fri Jul 11 00:13:10 2014
 * 
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME lidarCam_sfunct
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS          5
/* Input Port  0 */
#define IN_PORT_0_NAME      potVal
#define INPUT_0_WIDTH       1
#define INPUT_DIMS_0_COL    1
#define INPUT_0_DTYPE       int32_T
#define INPUT_0_COMPLEX     COMPLEX_NO
#define IN_0_FRAME_BASED    FRAME_NO
#define IN_0_BUS_BASED      0
#define IN_0_BUS_NAME       
#define IN_0_DIMS           1-D
#define INPUT_0_FEEDTHROUGH 1
#define IN_0_ISSIGNED        0
#define IN_0_WORDLENGTH      8
#define IN_0_FIXPOINTSCALING 1
#define IN_0_FRACTIONLENGTH  9
#define IN_0_BIAS            0
#define IN_0_SLOPE           0.125
/* Input Port  1 */
#define IN_PORT_1_NAME      Speed
#define INPUT_1_WIDTH       1
#define INPUT_DIMS_1_COL    1
#define INPUT_1_DTYPE       real_T
#define INPUT_1_COMPLEX     COMPLEX_NO
#define IN_1_FRAME_BASED    FRAME_NO
#define IN_1_BUS_BASED      0
#define IN_1_BUS_NAME       
#define IN_1_DIMS           1-D
#define INPUT_1_FEEDTHROUGH 1
#define IN_1_ISSIGNED        0
#define IN_1_WORDLENGTH      8
#define IN_1_FIXPOINTSCALING 1
#define IN_1_FRACTIONLENGTH  9
#define IN_1_BIAS            0
#define IN_1_SLOPE           0.125
/* Input Port  2 */
#define IN_PORT_2_NAME      Upos
#define INPUT_2_WIDTH       1
#define INPUT_DIMS_2_COL    1
#define INPUT_2_DTYPE       real_T
#define INPUT_2_COMPLEX     COMPLEX_NO
#define IN_2_FRAME_BASED    FRAME_NO
#define IN_2_BUS_BASED      0
#define IN_2_BUS_NAME       
#define IN_2_DIMS           1-D
#define INPUT_2_FEEDTHROUGH 1
#define IN_2_ISSIGNED        0
#define IN_2_WORDLENGTH      8
#define IN_2_FIXPOINTSCALING 1
#define IN_2_FRACTIONLENGTH  9
#define IN_2_BIAS            0
#define IN_2_SLOPE           0.125
/* Input Port  3 */
#define IN_PORT_3_NAME      Dpos
#define INPUT_3_WIDTH       1
#define INPUT_DIMS_3_COL    1
#define INPUT_3_DTYPE       real_T
#define INPUT_3_COMPLEX     COMPLEX_NO
#define IN_3_FRAME_BASED    FRAME_NO
#define IN_3_BUS_BASED      0
#define IN_3_BUS_NAME       
#define IN_3_DIMS           1-D
#define INPUT_3_FEEDTHROUGH 1
#define IN_3_ISSIGNED        0
#define IN_3_WORDLENGTH      8
#define IN_3_FIXPOINTSCALING 1
#define IN_3_FRACTIONLENGTH  9
#define IN_3_BIAS            0
#define IN_3_SLOPE           0.125
/* Input Port  4 */
#define IN_PORT_4_NAME      ScanNumber
#define INPUT_4_WIDTH       1
#define INPUT_DIMS_4_COL    1
#define INPUT_4_DTYPE       real_T
#define INPUT_4_COMPLEX     COMPLEX_NO
#define IN_4_FRAME_BASED    FRAME_NO
#define IN_4_BUS_BASED      0
#define IN_4_BUS_NAME       
#define IN_4_DIMS           1-D
#define INPUT_4_FEEDTHROUGH 1
#define IN_4_ISSIGNED        0
#define IN_4_WORDLENGTH      8
#define IN_4_FIXPOINTSCALING 1
#define IN_4_FRACTIONLENGTH  9
#define IN_4_BIAS            0
#define IN_4_SLOPE           0.125

#define NUM_OUTPUTS          5
/* Output Port  0 */
#define OUT_PORT_0_NAME      lidarData
#define OUTPUT_0_WIDTH       70200
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       real_T
#define OUTPUT_0_COMPLEX     COMPLEX_NO
#define OUT_0_FRAME_BASED    FRAME_NO
#define OUT_0_BUS_BASED      0
#define OUT_0_BUS_NAME       
#define OUT_0_DIMS           2-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125
/* Output Port  1 */
#define OUT_PORT_1_NAME      Red
#define OUTPUT_1_WIDTH       480
#define OUTPUT_DIMS_1_COL    640
#define OUTPUT_1_DTYPE       uint8_T
#define OUTPUT_1_COMPLEX     COMPLEX_NO
#define OUT_1_FRAME_BASED    FRAME_NO
#define OUT_1_BUS_BASED      0
#define OUT_1_BUS_NAME       
#define OUT_1_DIMS           2-D
#define OUT_1_ISSIGNED        1
#define OUT_1_WORDLENGTH      8
#define OUT_1_FIXPOINTSCALING 1
#define OUT_1_FRACTIONLENGTH  3
#define OUT_1_BIAS            0
#define OUT_1_SLOPE           0.125
/* Output Port  2 */
#define OUT_PORT_2_NAME      Green
#define OUTPUT_2_WIDTH       480
#define OUTPUT_DIMS_2_COL    640
#define OUTPUT_2_DTYPE       uint8_T
#define OUTPUT_2_COMPLEX     COMPLEX_NO
#define OUT_2_FRAME_BASED    FRAME_NO
#define OUT_2_BUS_BASED      0
#define OUT_2_BUS_NAME       
#define OUT_2_DIMS           2-D
#define OUT_2_ISSIGNED        1
#define OUT_2_WORDLENGTH      8
#define OUT_2_FIXPOINTSCALING 1
#define OUT_2_FRACTIONLENGTH  3
#define OUT_2_BIAS            0
#define OUT_2_SLOPE           0.125
/* Output Port  3 */
#define OUT_PORT_3_NAME      Blue
#define OUTPUT_3_WIDTH       480
#define OUTPUT_DIMS_3_COL    640
#define OUTPUT_3_DTYPE       uint8_T
#define OUTPUT_3_COMPLEX     COMPLEX_NO
#define OUT_3_FRAME_BASED    FRAME_NO
#define OUT_3_BUS_BASED      0
#define OUT_3_BUS_NAME       
#define OUT_3_DIMS           2-D
#define OUT_3_ISSIGNED        1
#define OUT_3_WORDLENGTH      8
#define OUT_3_FIXPOINTSCALING 1
#define OUT_3_FRACTIONLENGTH  3
#define OUT_3_BIAS            0
#define OUT_3_SLOPE           0.125
/* Output Port  4 */
#define OUT_PORT_4_NAME      udOut
#define OUTPUT_4_WIDTH       1
#define OUTPUT_DIMS_4_COL    1
#define OUTPUT_4_DTYPE       real_T
#define OUTPUT_4_COMPLEX     COMPLEX_NO
#define OUT_4_FRAME_BASED    FRAME_NO
#define OUT_4_BUS_BASED      0
#define OUT_4_BUS_NAME       
#define OUT_4_DIMS           1-D
#define OUT_4_ISSIGNED        1
#define OUT_4_WORDLENGTH      8
#define OUT_4_FIXPOINTSCALING 1
#define OUT_4_FRACTIONLENGTH  3
#define OUT_4_BIAS            0
#define OUT_4_SLOPE           0.125

#define NPARAMS              0

#define SAMPLE_TIME_0        INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 0
#define SOURCEFILES "__SFB__"
#define PANELINDEX           6
#define USE_SIMSTRUCT        0
#define SHOW_COMPILE_STEPS   0                   
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"

extern void lidarCam_sfunct_Outputs_wrapper(const int32_T *potVal,
                          const real_T *Speed,
                          const real_T *Upos,
                          const real_T *Dpos,
                          const real_T *ScanNumber,
                          real_T *lidarData,
                          uint8_T *Red,
                          uint8_T *Green,
                          uint8_T *Blue,
                          real_T *udOut);

/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);
     if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
	 return; /* Parameter mismatch will be reported by Simulink */
     }

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;
    /*Input Port 0 */
    ssSetInputPortWidth(S,  0, INPUT_0_WIDTH); /* */
    ssSetInputPortDataType(S, 0, SS_INT32);
    ssSetInputPortComplexSignal(S,  0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /*Input Port 1 */
    ssSetInputPortWidth(S,  1, INPUT_1_WIDTH); /* */
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/

    /*Input Port 2 */
    ssSetInputPortWidth(S,  2, INPUT_2_WIDTH); /* */
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  2, INPUT_2_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 2, INPUT_2_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/

    /*Input Port 3 */
    ssSetInputPortWidth(S,  3, INPUT_3_WIDTH); /* */
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  3, INPUT_3_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 3, INPUT_3_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/

    /*Input Port 4 */
    ssSetInputPortWidth(S,  4, INPUT_4_WIDTH); /* */
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  4, INPUT_4_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 4, INPUT_4_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/


    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    /* Output Port 0 */
    outputDimsInfo.width = OUTPUT_0_WIDTH;
    ssSetOutputPortDimensionInfo(S, 0, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,0, OUTPUT_0_WIDTH, OUTPUT_DIMS_0_COL);
    ssSetOutputPortFrameData(S, 0, OUT_0_FRAME_BASED);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    /* Output Port 1 */
    outputDimsInfo.width = OUTPUT_1_WIDTH;
    ssSetOutputPortDimensionInfo(S, 1, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,1, OUTPUT_1_WIDTH, OUTPUT_DIMS_1_COL);
    ssSetOutputPortFrameData(S, 1, OUT_1_FRAME_BASED);
    ssSetOutputPortDataType(S, 1, SS_UINT8);
    ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);
    /* Output Port 2 */
    outputDimsInfo.width = OUTPUT_2_WIDTH;
    ssSetOutputPortDimensionInfo(S, 2, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,2, OUTPUT_2_WIDTH, OUTPUT_DIMS_2_COL);
    ssSetOutputPortFrameData(S, 2, OUT_2_FRAME_BASED);
    ssSetOutputPortDataType(S, 2, SS_UINT8);
    ssSetOutputPortComplexSignal(S, 2, OUTPUT_2_COMPLEX);
    /* Output Port 3 */
    outputDimsInfo.width = OUTPUT_3_WIDTH;
    ssSetOutputPortDimensionInfo(S, 3, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,3, OUTPUT_3_WIDTH, OUTPUT_DIMS_3_COL);
    ssSetOutputPortFrameData(S, 3, OUT_3_FRAME_BASED);
    ssSetOutputPortDataType(S, 3, SS_UINT8);
    ssSetOutputPortComplexSignal(S, 3, OUTPUT_3_COMPLEX);
    /* Output Port 4 */
    ssSetOutputPortWidth(S, 4, OUTPUT_4_WIDTH);
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 4, OUTPUT_4_COMPLEX);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
}

# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetOffsetTime(S, 0, 0.0);
}


/* ******************************************************************
 * This is where the matlab setup code stops*************************
 *******************************************************************/

#ifdef _WIN32 || _WIN64/*If run for windows, do nothing (linux only)*/

static void mdlOutputs(SimStruct *S, int_T tid){}
static void mdlTerminate(SimStruct *S){}
#define MDL_START      
static void mdlStart(SimStruct *S){}
#else /*Running for linux*/

#include <stdlib.h>

//Stepper includes
#include <phidget21.h>
#include <time.h> 
#include <signal.h>
#include <sys/types.h>
#include "stepperFunct.h"

//Lidar includes
#include <stdio.h>
#include <malloc.h>
#include "math_utils.h"
#include "ring_buffer.h"
#include "scip_handler.h"
#include "serial_ctrl.h"
#include "serial_errno.h"
#include "serial_t.h"
#include "serial_utils.h"
#include "urg_ctrl.h"
#include "urg_delay.h"
#include "urg_errno.h"
#include "urg_parameter_t.h"
#include "urg_t.h"
#include "urg_ticks.h"

// OpenCV Includes
#include "cv.h" 
#include "highgui.h" 

void urg_exit(urg_t *urg, const char *message){
  printf("%s: %s\n", message, urg_error(urg));
  urg_disconnect(urg);
}

//Define Global variables
//For Lidar
int i,j,k,l;  // for loop vars 
int n, ret; // check var 
int timestamp = -1; // Time Stamp for Each Image
CvCapture *capture1;
const char device[] = "/dev/ttyUSB.LID"; 
urg_t urg; // urg struct for lidar 
long data[1080]; 
//For Stepper
CPhidgetStepperHandle stepper = 0;
//Variable for zeroing
int counter = 0;

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
        //Lidar setup
    ret = urg_connect(&urg, device, 115200);
    if (ret < 0) {
        urg_exit(&urg, "urg_connect()");
    }
    else
        urg_setCaptureTimes(&urg, UrgInfinityTimes);
    
    //Stepper Setup
    CPhidgetStepper_create(&stepper);
    stepperConnect(600000, 1214,stepper);
    
    //Zero prameters
    counter = 0;
    
    // Webcam SetUp
    capture1  = cvCaptureFromCAM( -1 ); //Sets up Camera Object
    if ( !capture1 ) 
        fprintf( stderr, "ERROR: capture is NULL \n" );
  }
#endif /*  MDL_START */


#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
  ssSetInputPortDataType( S, 0, SS_DOUBLE);
 ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}
/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const int32_T   *potVal  = (const int32_T*) ssGetInputPortSignal(S,0);
    const real_T   *Speed  = (const real_T*) ssGetInputPortSignal(S,1);
    const real_T   *Upos  = (const real_T*) ssGetInputPortSignal(S,2);
    const real_T   *Dpos  = (const real_T*) ssGetInputPortSignal(S,3);
    const real_T   *ScanNumber  = (const real_T*) ssGetInputPortSignal(S,4);
    real_T        *lidarData  = (real_T *)ssGetOutputPortRealSignal(S,0);
    uint8_T        *Red  = (uint8_T *)ssGetOutputPortRealSignal(S,1);
    uint8_T        *Green  = (uint8_T *)ssGetOutputPortRealSignal(S,2);
    uint8_T        *Blue  = (uint8_T *)ssGetOutputPortRealSignal(S,3);
    real_T        *udOut  = (real_T *)ssGetOutputPortRealSignal(S,4);

      //Read number of scans
    int ScanNum = *ScanNumber;
    
    CPhidgetStepper_setVelocityLimit(stepper, 0, *Speed);
    
    //Parameters required for zeroing
    //Calibrated for three turn pot
    int zeroPos = 534; //Potentiometer reading at level position
    int stepRes = 3950; //Number of steps to move the stepper 180 degrees
    int potRes = 323; //Number of potValues that represent the rotation of the gimbal 180 degrees
    int potGive = 2; //Accounts for slack in gearing for pot
    
    //Variables required for zeroing
    int dpot; //difference to desired pot value from current
    int dstep; //number of steps the stepper must move to get to desired position
    
    //Pot reader may take a minute to initialize and will send zero
    //If this is the case do nothing
    if (*potVal != 0){
        //Zero stepper on first run
        //Account for differnces coming from different directions
        if (counter == 0) {
            
            //write pot value
            printf("potVal:%d\n", *potVal);
            
            //Find pot value difference to calculate steps needed to level
            if (zeroPos > *potVal) {
                dpot = zeroPos - potGive - *potVal;
            }
            if (zeroPos < *potVal) {
                dpot = zeroPos + potGive -*potVal;
            }
            //write difference
            printf("Dpot:%d\n", dpot);
            
            //Find required steps and move to level position
            dstep = -stepRes/potRes*dpot;
            
            //If error occurs dstep may be very large
            //Limit dstep value to prevent damage to system
            if (dstep > 1600) {
                dstep = 1600;
            }
            if (dstep < -1600) {
                dstep = -1600;
            }
            //write number of steps to zero
            printf("Dstep:%d\n", dstep);
            stepperMove(dstep, stepper);
            
            //Set current position to zero
            CPhidgetStepper_setCurrentPosition(stepper, 0, 0);
            //Move to Up position to begin scanning process
            stepperMove(*Upos, stepper);
            counter = 1;
        }
        
        //Request data
        urg_setCaptureTimes(&urg, ScanNum);
        ret = urg_requestData(&urg, URG_MD, 0, 1080);
        if (ret < 0) {
            urg_exit(&urg, "urg_requestData()");
        }
        
        //Tell stepper to move to new position
        if (counter == 1) {
            CPhidgetStepper_setTargetPosition(stepper, 0, *Dpos);
            counter = 2;
            *udOut = 0;
        }
        else if (counter == 2) {
            CPhidgetStepper_setTargetPosition(stepper, 0, *Upos);
            counter = 1;
            *udOut = 1;
        }
        
        for (j=0;j<ScanNum;j++) {
            
            // Receive Data
            n = urg_receiveData(&urg, data, 1080);
            // Error, can't receive negative data points
            if (n < 0) {
                urg_exit(&urg, "urg_receiveData()");
                // Disconnect Lidar
                urg_disconnect(&urg);
                
            }
            
            // Data Received, Construct Partial Image
            else{
                for(k=0;k<1080;k++){
                    lidarData[(j*1080)+k] = data[k];
                }
            }
        }
    }// END OF LIDAR DATA ACQ
    // START CAM ACQ
    // Grab a number of frames in order to flush the data buffer
    int flush1 = cvGrabFrame( capture1 );
    int flush2 = cvGrabFrame( capture1 );
    int flush3 = cvGrabFrame( capture1 );
    int flush4 = cvGrabFrame( capture1 );

    IplImage *frame1 = cvQueryFrame( capture1 ); //Gets Frame from Camera

    unsigned char *data1 = frame1->imageData;
    long iNew, jNew = 0, kNew = 0; 
    for(iNew = 0; iNew < 480*640*3; iNew+=3){
        //printf("data: %d, %d, %d \n",data[i],data[i+1], data[i+2]);
        Blue[jNew*480+kNew] = data1[iNew];
        Green[jNew*480+kNew] = data1[iNew+1];
        Red[jNew*480+kNew] = data1[iNew+2];
        jNew++;
        if(jNew==640){kNew++; jNew = 0;}
    }
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    //Move stepper to zero, disconnect lidar and stepper
    stepperMove(0, stepper);
    urg_disconnect(&urg);
    stepperDisconnect(stepper);
    //Disconnect From Target Camera
    cvReleaseCapture( &capture1 );
}
#endif 
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


