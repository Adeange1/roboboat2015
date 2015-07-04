/*  Lidar_zero_tester_v3.c
 *  Wesley Anderson, Villanova University
 *  June 2014
 *
 *  This code is to be used in an S-Function with the lidar gimble system
 *  with the three turn pot attached, in place of 10 turn used in v2
 *
 *  Ensure that the zero position of the pot is 500 before using this code
 *
 *  This code is edited from v3 to include input for scan number and
 *  output for whether the gimbal is moving up or down
 *
 */

/*
 * File: lidar_zero_test_v4.c
 *
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
 * Created: Sun Jun 29 16:11:09 2014
 *
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME TT_lidar_zero_test_Lebbad3
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

#define NUM_OUTPUTS          2
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
#define OUT_PORT_1_NAME      udOut
#define OUTPUT_1_WIDTH       1
#define OUTPUT_DIMS_1_COL    1
#define OUTPUT_1_DTYPE       real_T
#define OUTPUT_1_COMPLEX     COMPLEX_NO
#define OUT_1_FRAME_BASED    FRAME_NO
#define OUT_1_BUS_BASED      0
#define OUT_1_BUS_NAME
#define OUT_1_DIMS           1-D
#define OUT_1_ISSIGNED        1
#define OUT_1_WORDLENGTH      8
#define OUT_1_FIXPOINTSCALING 1
#define OUT_1_FRACTIONLENGTH  3
#define OUT_1_BIAS            0
#define OUT_1_SLOPE           0.125

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

extern void lidar_zero_test_v4_Outputs_wrapper(const int32_T *potVal,
        const real_T *Speed,
        const real_T *Upos,
        const real_T *Dpos,
        const real_T *ScanNumber,
        real_T *lidarData,
        real_T *udOut);

/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S) {
    
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
    ssSetOutputPortMatrixDimensions( S , 0, OUTPUT_0_WIDTH, OUTPUT_DIMS_0_COL);
    ssSetOutputPortFrameData(S, 0, OUT_0_FRAME_BASED);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    /* Output Port 1 */
    ssSetOutputPortWidth(S, 1, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);
    
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
        Frame_T    frameData) {
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S) {
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

void urg_exit(urg_t *urg, const char *message){
    printf("%s: %s\n", message, urg_error(urg));
    urg_disconnect(urg);
    
    #ifdef MSC
            getchar();
    #endif
}

//Define Global variables
//For Lidar
int i, j, k, l;  // for loop vars
int n, ret; // check var
int timestamp = -1; // Time Stamp for Each Image
int counter;
const char device[] = "/dev/ttyUSB.LID";
urg_t urg; // urg struct for lidar
long data[1080];
//For Stepper
CPhidgetStepperHandle stepper = 0;
//Variable for zeroing
counter = 0;


#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S) {
    //Lidar setup
    ret = urg_connect(&urg, device, 115200);
    if (ret < 0) {
        urg_exit(&urg, "urg_connect()");
    }
    else
        urg_setCaptureTimes(&urg, UrgInfinityTimes);
    
    //Stepper Setup
    CPhidgetStepper_create(&stepper);
    stepperConnect(600000, 1214, stepper);
    
    //Zero prameters
    counter = 0;
    
}
#endif /*  MDL_START */

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType) {
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType) {
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S) {
    ssSetInputPortDataType( S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}
/* Function: mdlOutputs =======================================================
 *
 */
static void mdlOutputs(SimStruct *S, int_T tid) {
    const int32_T   *potVal  = (const int32_T*) ssGetInputPortSignal(S, 0);
    const real_T   *Speed  = (const real_T*) ssGetInputPortSignal(S, 1);
    const real_T   *Upos  = (const real_T*) ssGetInputPortSignal(S, 2);
    const real_T   *Dpos  = (const real_T*) ssGetInputPortSignal(S, 3);
    const real_T   *ScanNumber  = (const real_T*) ssGetInputPortSignal(S, 4);
    real_T        *lidarData  = (real_T *)ssGetOutputPortRealSignal(S, 0);
    real_T        *udOut  = (real_T *)ssGetOutputPortRealSignal(S, 1);
    
    //Read number of scans
    int ScanNum = *ScanNumber;
    
    CPhidgetStepper_setVelocityLimit(stepper, 0, *Speed);
    
    //Variables required for zeroing
    //Calibrated for three turn pot
    int zeroPos = 517;
    int dpot;
    int dstep;
    
    //Pot reader may take a minute to initialize and will send zero
    //If this is the case do nothing
    if (*potVal != 0){
        
        //Zero stepper on first run
        //Account for differnces coming from different directions
        if (counter == 0) {
            
            if (zeroPos > *potVal) {
                zeroPos = 515;
            }
            if (zeroPos < *potVal) {
                zeroPos = 519;
            }
            
            //Find required steps and move to zero position
            printf("potVal:%d\n", *potVal);
            dpot = zeroPos - *potVal;
            printf("Dpot:%d\n", dpot);
            dstep = -1036/125*dpot;
            //If error occurs dstep may be very large
            //Limit dstep value to prevent damage to system
            if (dstep > 1600) {
                dstep = 1600;
            }
            if (dstep < -1600) {
                dstep = -1600;
            }
            printf("Dstep:%d\n", dstep);
            //stepperMove(dstep, stepper);
            CPhidgetStepper_setTargetPosition(stepper, 0, dstep);
            
            //Set current position to zero
            //CPhidgetStepper_setCurrentPosition(stepper, 0, 0);
            //Move to Up position to begin scanning process
            stepperMove(*Upos, stepper);
            //CPhidgetStepper_setTargetPosition(stepper, 0, *Upos);
            counter = 1;
            printf("Poops all over the world\n");
        }
        else {
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
        }
        
        //stepperMove(*Upos, stepper);
        
    }
    
    //lidar_zero_test_v4_Outputs_wrapper(potVal, Speed, Upos, Dpos, ScanNumber, lidarData, udOut);
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S) {
    //Move stepper to zero, disconnect lidar and stepper
    stepperMove(0, stepper);
    urg_disconnect(&urg);
    stepperDisconnect(stepper);
}
#endif

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


