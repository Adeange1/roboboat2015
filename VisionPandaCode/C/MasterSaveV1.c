/*
 * File: MasterSaveV1.c
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
 * Created: Tue Jul 22 09:13:09 2014
 * 
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME MasterSaveV1
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS          13
/* Input Port  0 */
#define IN_PORT_0_NAME      Pose
#define INPUT_0_WIDTH       1
#define INPUT_DIMS_0_COL    3
#define INPUT_0_DTYPE       real_T
#define INPUT_0_COMPLEX     COMPLEX_NO
#define IN_0_FRAME_BASED    FRAME_NO
#define IN_0_BUS_BASED      0
#define IN_0_BUS_NAME       
#define IN_0_DIMS           2-D
#define INPUT_0_FEEDTHROUGH 1
#define IN_0_ISSIGNED        0
#define IN_0_WORDLENGTH      8
#define IN_0_FIXPOINTSCALING 1
#define IN_0_FRACTIONLENGTH  9
#define IN_0_BIAS            0
#define IN_0_SLOPE           0.125
/* Input Port  1 */
#define IN_PORT_1_NAME      Vel
#define INPUT_1_WIDTH       1
#define INPUT_DIMS_1_COL    2
#define INPUT_1_DTYPE       real_T
#define INPUT_1_COMPLEX     COMPLEX_NO
#define IN_1_FRAME_BASED    FRAME_NO
#define IN_1_BUS_BASED      0
#define IN_1_BUS_NAME       
#define IN_1_DIMS           2-D
#define INPUT_1_FEEDTHROUGH 1
#define IN_1_ISSIGNED        0
#define IN_1_WORDLENGTH      8
#define IN_1_FIXPOINTSCALING 1
#define IN_1_FRACTIONLENGTH  9
#define IN_1_BIAS            0
#define IN_1_SLOPE           0.125
/* Input Port  2 */
#define IN_PORT_2_NAME      Euler
#define INPUT_2_WIDTH       1
#define INPUT_DIMS_2_COL    3
#define INPUT_2_DTYPE       real_T
#define INPUT_2_COMPLEX     COMPLEX_NO
#define IN_2_FRAME_BASED    FRAME_NO
#define IN_2_BUS_BASED      0
#define IN_2_BUS_NAME       
#define IN_2_DIMS           2-D
#define INPUT_2_FEEDTHROUGH 1
#define IN_2_ISSIGNED        0
#define IN_2_WORDLENGTH      8
#define IN_2_FIXPOINTSCALING 1
#define IN_2_FRACTIONLENGTH  9
#define IN_2_BIAS            0
#define IN_2_SLOPE           0.125
/* Input Port  3 */
#define IN_PORT_3_NAME      PortState
#define INPUT_3_WIDTH       1
#define INPUT_DIMS_3_COL    2
#define INPUT_3_DTYPE       real_T
#define INPUT_3_COMPLEX     COMPLEX_NO
#define IN_3_FRAME_BASED    FRAME_NO
#define IN_3_BUS_BASED      0
#define IN_3_BUS_NAME       
#define IN_3_DIMS           2-D
#define INPUT_3_FEEDTHROUGH 1
#define IN_3_ISSIGNED        0
#define IN_3_WORDLENGTH      8
#define IN_3_FIXPOINTSCALING 1
#define IN_3_FRACTIONLENGTH  9
#define IN_3_BIAS            0
#define IN_3_SLOPE           0.125
/* Input Port  4 */
#define IN_PORT_4_NAME      StbdState
#define INPUT_4_WIDTH       1
#define INPUT_DIMS_4_COL    2
#define INPUT_4_DTYPE       real_T
#define INPUT_4_COMPLEX     COMPLEX_NO
#define IN_4_FRAME_BASED    FRAME_NO
#define IN_4_BUS_BASED      0
#define IN_4_BUS_NAME       
#define IN_4_DIMS           2-D
#define INPUT_4_FEEDTHROUGH 1
#define IN_4_ISSIGNED        0
#define IN_4_WORDLENGTH      8
#define IN_4_FIXPOINTSCALING 1
#define IN_4_FRACTIONLENGTH  9
#define IN_4_BIAS            0
#define IN_4_SLOPE           0.125
/* Input Port  5 */
#define IN_PORT_5_NAME      StartTime
#define INPUT_5_WIDTH       1
#define INPUT_DIMS_5_COL    1
#define INPUT_5_DTYPE       real_T
#define INPUT_5_COMPLEX     COMPLEX_NO
#define IN_5_FRAME_BASED    FRAME_NO
#define IN_5_BUS_BASED      0
#define IN_5_BUS_NAME       
#define IN_5_DIMS           1-D
#define INPUT_5_FEEDTHROUGH 1
#define IN_5_ISSIGNED        0
#define IN_5_WORDLENGTH      8
#define IN_5_FIXPOINTSCALING 1
#define IN_5_FRACTIONLENGTH  9
#define IN_5_BIAS            0
#define IN_5_SLOPE           0.125
/* Input Port  6 */
#define IN_PORT_6_NAME      ElapsedTime
#define INPUT_6_WIDTH       1
#define INPUT_DIMS_6_COL    1
#define INPUT_6_DTYPE       real_T
#define INPUT_6_COMPLEX     COMPLEX_NO
#define IN_6_FRAME_BASED    FRAME_NO
#define IN_6_BUS_BASED      0
#define IN_6_BUS_NAME       
#define IN_6_DIMS           1-D
#define INPUT_6_FEEDTHROUGH 1
#define IN_6_ISSIGNED        0
#define IN_6_WORDLENGTH      8
#define IN_6_FIXPOINTSCALING 1
#define IN_6_FRACTIONLENGTH  9
#define IN_6_BIAS            0
#define IN_6_SLOPE           0.125
/* Input Port  7 */
#define IN_PORT_7_NAME      UV_data
#define INPUT_7_WIDTH       120
#define INPUT_DIMS_7_COL    160
#define INPUT_7_DTYPE       real_T
#define INPUT_7_COMPLEX     COMPLEX_NO
#define IN_7_FRAME_BASED    FRAME_NO
#define IN_7_BUS_BASED      0
#define IN_7_BUS_NAME       
#define IN_7_DIMS           2-D
#define INPUT_7_FEEDTHROUGH 1
#define IN_7_ISSIGNED        0
#define IN_7_WORDLENGTH      8
#define IN_7_FIXPOINTSCALING 1
#define IN_7_FRACTIONLENGTH  9
#define IN_7_BIAS            0
#define IN_7_SLOPE           0.125
/* Input Port  8 */
#define IN_PORT_8_NAME      Dist_Image
#define INPUT_8_WIDTH       65
#define INPUT_DIMS_8_COL    540
#define INPUT_8_DTYPE       real_T
#define INPUT_8_COMPLEX     COMPLEX_NO
#define IN_8_FRAME_BASED    FRAME_NO
#define IN_8_BUS_BASED      0
#define IN_8_BUS_NAME       
#define IN_8_DIMS           2-D
#define INPUT_8_FEEDTHROUGH 1
#define IN_8_ISSIGNED        0
#define IN_8_WORDLENGTH      8
#define IN_8_FIXPOINTSCALING 1
#define IN_8_FRACTIONLENGTH  9
#define IN_8_BIAS            0
#define IN_8_SLOPE           0.125
/* Input Port  9 */
#define IN_PORT_9_NAME      Traject
#define INPUT_9_WIDTH       3
#define INPUT_DIMS_9_COL    3
#define INPUT_9_DTYPE       real_T
#define INPUT_9_COMPLEX     COMPLEX_NO
#define IN_9_FRAME_BASED    FRAME_NO
#define IN_9_BUS_BASED      0
#define IN_9_BUS_NAME       
#define IN_9_DIMS           2-D
#define INPUT_9_FEEDTHROUGH 1
#define IN_9_ISSIGNED        0
#define IN_9_WORDLENGTH      8
#define IN_9_FIXPOINTSCALING 1
#define IN_9_FRACTIONLENGTH  9
#define IN_9_BIAS            0
#define IN_9_SLOPE           0.125
/* Input Port  10 */
#define IN_PORT_10_NAME      Hue
#define INPUT_10_WIDTH       480
#define INPUT_DIMS_10_COL    640
#define INPUT_10_DTYPE       uint8_T
#define INPUT_10_COMPLEX     COMPLEX_NO
#define IN_10_FRAME_BASED    FRAME_NO
#define IN_10_BUS_BASED      0
#define IN_10_BUS_NAME       
#define IN_10_DIMS           2-D
#define INPUT_10_FEEDTHROUGH 1
#define IN_10_ISSIGNED        0
#define IN_10_WORDLENGTH      8
#define IN_10_FIXPOINTSCALING 1
#define IN_10_FRACTIONLENGTH  9
#define IN_10_BIAS            0
#define IN_10_SLOPE           0.125
/* Input Port  11 */
#define IN_PORT_11_NAME      Sat
#define INPUT_11_WIDTH       480
#define INPUT_DIMS_11_COL    640
#define INPUT_11_DTYPE       uint8_T
#define INPUT_11_COMPLEX     COMPLEX_NO
#define IN_11_FRAME_BASED    FRAME_NO
#define IN_11_BUS_BASED      0
#define IN_11_BUS_NAME       
#define IN_11_DIMS           2-D
#define INPUT_11_FEEDTHROUGH 1
#define IN_11_ISSIGNED        0
#define IN_11_WORDLENGTH      8
#define IN_11_FIXPOINTSCALING 1
#define IN_11_FRACTIONLENGTH  9
#define IN_11_BIAS            0
#define IN_11_SLOPE           0.125
/* Input Port  12 */
#define IN_PORT_12_NAME      Val
#define INPUT_12_WIDTH       480
#define INPUT_DIMS_12_COL    640
#define INPUT_12_DTYPE       uint8_T
#define INPUT_12_COMPLEX     COMPLEX_NO
#define IN_12_FRAME_BASED    FRAME_NO
#define IN_12_BUS_BASED      0
#define IN_12_BUS_NAME       
#define IN_12_DIMS           2-D
#define INPUT_12_FEEDTHROUGH 1
#define IN_12_ISSIGNED        0
#define IN_12_WORDLENGTH      8
#define IN_12_FIXPOINTSCALING 1
#define IN_12_FRACTIONLENGTH  9
#define IN_12_BIAS            0
#define IN_12_SLOPE           0.125

#define NUM_OUTPUTS           0

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

extern void MasterSaveV1_Outputs_wrapper(const real_T *Pose,
                          const real_T *Vel,
                          const real_T *Euler,
                          const real_T *PortState,
                          const real_T *StbdState,
                          const real_T *StartTime,
                          const real_T *ElapsedTime,
                          const real_T *UV_data,
                          const real_T *Dist_Image,
                          const real_T *Traject,
                          const uint8_T *Hue,
                          const uint8_T *Sat,
                          const uint8_T *Val);

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
    inputDimsInfo.width = INPUT_0_WIDTH;
    ssSetInputPortDimensionInfo(S,  0, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 0, INPUT_0_WIDTH, INPUT_DIMS_0_COL);
    ssSetInputPortFrameData(S,  0, IN_0_FRAME_BASED);

    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /*Input Port 1 */
    inputDimsInfo.width = INPUT_1_WIDTH;
    ssSetInputPortDimensionInfo(S,  1, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 1, INPUT_1_WIDTH, INPUT_DIMS_1_COL);
    ssSetInputPortFrameData(S,  1, IN_1_FRAME_BASED);

    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/

    /*Input Port 2 */
    inputDimsInfo.width = INPUT_2_WIDTH;
    ssSetInputPortDimensionInfo(S,  2, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 2, INPUT_2_WIDTH, INPUT_DIMS_2_COL);
    ssSetInputPortFrameData(S,  2, IN_2_FRAME_BASED);

    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  2, INPUT_2_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 2, INPUT_2_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/

    /*Input Port 3 */
    inputDimsInfo.width = INPUT_3_WIDTH;
    ssSetInputPortDimensionInfo(S,  3, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 3, INPUT_3_WIDTH, INPUT_DIMS_3_COL);
    ssSetInputPortFrameData(S,  3, IN_3_FRAME_BASED);

    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  3, INPUT_3_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 3, INPUT_3_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/

    /*Input Port 4 */
    inputDimsInfo.width = INPUT_4_WIDTH;
    ssSetInputPortDimensionInfo(S,  4, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S , 4, INPUT_4_WIDTH, INPUT_DIMS_4_COL);
    ssSetInputPortFrameData(S,  4, IN_4_FRAME_BASED);

    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  4, INPUT_4_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 4, INPUT_4_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/

    /*Input Port 5 */
    ssSetInputPortWidth(S,  5, INPUT_5_WIDTH); /* */
    ssSetInputPortDataType(S, 5, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  5, INPUT_5_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 5, INPUT_5_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 5, 1); /*direct input signal access*/

    /*Input Port 6 */
    ssSetInputPortWidth(S,  6, INPUT_6_WIDTH); /* */
    ssSetInputPortDataType(S, 6, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  6, INPUT_6_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 6, INPUT_6_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 6, 1); /*direct input signal access*/

    /*Input Port 7 */
    inputDimsInfo.width = INPUT_7_WIDTH;
    ssSetInputPortDimensionInfo(S, 7, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,7, INPUT_7_WIDTH, INPUT_DIMS_7_COL);
    ssSetInputPortFrameData(S, 7, IN_7_FRAME_BASED);
    ssSetInputPortDataType(S, 7, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 7, INPUT_7_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 7, INPUT_7_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 7, 1); /*direct input signal access*/

    /*Input Port 8 */
    inputDimsInfo.width = INPUT_8_WIDTH;
    ssSetInputPortDimensionInfo(S, 8, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,8, INPUT_8_WIDTH, INPUT_DIMS_8_COL);
    ssSetInputPortFrameData(S, 8, IN_8_FRAME_BASED);
    ssSetInputPortDataType(S, 8, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 8, INPUT_8_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 8, INPUT_8_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 8, 1); /*direct input signal access*/

    /*Input Port 9 */
    inputDimsInfo.width = INPUT_9_WIDTH;
    ssSetInputPortDimensionInfo(S, 9, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,9, INPUT_9_WIDTH, INPUT_DIMS_9_COL);
    ssSetInputPortFrameData(S, 9, IN_9_FRAME_BASED);
    ssSetInputPortDataType(S, 9, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 9, INPUT_9_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 9, INPUT_9_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 9, 1); /*direct input signal access*/

    /*Input Port 10 */
    inputDimsInfo.width = INPUT_10_WIDTH;
    ssSetInputPortDimensionInfo(S, 10, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,10, INPUT_10_WIDTH, INPUT_DIMS_10_COL);
    ssSetInputPortFrameData(S, 10, IN_10_FRAME_BASED);
    ssSetInputPortDataType(S, 10, SS_UINT8);
    ssSetInputPortComplexSignal(S, 10, INPUT_10_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 10, INPUT_10_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 10, 1); /*direct input signal access*/

    /*Input Port 11 */
    inputDimsInfo.width = INPUT_11_WIDTH;
    ssSetInputPortDimensionInfo(S, 11, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,11, INPUT_11_WIDTH, INPUT_DIMS_11_COL);
    ssSetInputPortFrameData(S, 11, IN_11_FRAME_BASED);
    ssSetInputPortDataType(S, 11, SS_UINT8);
    ssSetInputPortComplexSignal(S, 11, INPUT_11_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 11, INPUT_11_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 11, 1); /*direct input signal access*/

    /*Input Port 12 */
    inputDimsInfo.width = INPUT_12_WIDTH;
    ssSetInputPortDimensionInfo(S, 12, &inputDimsInfo);
    ssSetInputPortMatrixDimensions(  S ,12, INPUT_12_WIDTH, INPUT_DIMS_12_COL);
    ssSetInputPortFrameData(S, 12, IN_12_FRAME_BASED);
    ssSetInputPortDataType(S, 12, SS_UINT8);
    ssSetInputPortComplexSignal(S, 12, INPUT_12_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 12, INPUT_12_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 12, 1); /*direct input signal access*/


    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;

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

#ifdef _WIN32 || _WIN64/*If run for windows, do nothing (linux only)*/

static void mdlOutputs(SimStruct *S, int_T tid){}
static void mdlTerminate(SimStruct *S){}
#define MDL_START      
static void mdlStart(SimStruct *S){}
#else /*Running for linux*/

#include <stdio.h> 		/* Standard I/O definitions */
#include <stdlib.h> 	

FILE *posefd, *velfd, *eulerfd, *portstatefd, *stbdstatefd, *timefd, *uvdatafd, *distimagefd, *trajectfd, *huefd, *satfd, *valfd; 

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
    system("mkdir TestingTime:$(date '+%m_%d_%Y_%H_%M') && cd TestingTime:$(date '+%m_%d_%Y_%H_%M')"); 
    
    posefd = fopen("pose_data","w");
    if(posefd == NULL){ 
        printf("Pose File Not Opened\n"); 
        exit(1); 
    }
    
    velfd = fopen("vel_data","w");
     if(velfd == NULL){ 
        printf("Vel File Not Opened\n"); 
        exit(1); 
    }
    
    eulerfd = fopen("euler_data","w");
     if(eulerfd == NULL){ 
        printf("Euler File Not Opened\n"); 
        exit(1); 
    }
    
    portstatefd = fopen("port_data","w");
     if(portstatefd == NULL){ 
        printf("PortState File Not Opened\n"); 
        exit(1); 
    }
    
    stbdstatefd = fopen("stbd_data","w");
     if(stbdstatefd == NULL){ 
        printf("Stbd File Not Opened\n"); 
        exit(1); 
    }
    
    timefd = fopen("timestamp_data","w");
     if(timefd == NULL){ 
        printf("Time File Not Opened\n"); 
        exit(1); 
    }
    
    uvdatafd = fopen("uvdata_data","w");
     if(uvdatafd == NULL){ 
        printf("uvdata File Not Opened\n"); 
        exit(1); 
    }
    
    distimagefd = fopen("distimage_data","w");
     if(distimagefd == NULL){ 
        printf("distimage File Not Opened\n"); 
        exit(1); 
    }
    
    trajectfd = fopen("traject_data","w");
     if(trajectfd == NULL){ 
        printf("traject File Not Opened\n"); 
        exit(1); 
    }
    
    huefd = fopen("hue_data","w"); 
     if(huefd == NULL){ 
        printf("Hue File Not Opened\n"); 
        exit(1); 
    }
    
    satfd = fopen("sat_data","w");
     if(satfd == NULL){ 
        printf("Sat File Not Opened\n"); 
        exit(1); 
    }
    
    valfd = fopen("val_data","w");
     if(valfd == NULL){ 
        printf("Val File Not Opened\n"); 
        exit(1); 
    }
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
    const real_T   *Pose  = (const real_T*) ssGetInputPortSignal(S,0);
    const real_T   *Vel  = (const real_T*) ssGetInputPortSignal(S,1);
    const real_T   *Euler  = (const real_T*) ssGetInputPortSignal(S,2);
    const real_T   *PortState  = (const real_T*) ssGetInputPortSignal(S,3);
    const real_T   *StbdState  = (const real_T*) ssGetInputPortSignal(S,4);
    const real_T   *StartTime  = (const real_T*) ssGetInputPortSignal(S,5);
    const real_T   *ElapsedTime  = (const real_T*) ssGetInputPortSignal(S,6);
    const real_T   *UV_data  = (const real_T*) ssGetInputPortSignal(S,7);
    const real_T   *Dist_Image  = (const real_T*) ssGetInputPortSignal(S,8);
    const real_T   *Traject  = (const real_T*) ssGetInputPortSignal(S,9);
    const uint8_T   *Hue  = (const uint8_T*) ssGetInputPortSignal(S,10);
    const uint8_T   *Sat  = (const uint8_T*) ssGetInputPortSignal(S,11);
    const uint8_T   *Val  = (const uint8_T*) ssGetInputPortSignal(S,12);

    int i; 
    
    // Pose, Euler 
    for(i=0;i<3;i++){ 
        fprintf(eulerfd,"%g\n",Euler[i]);
        fprintf(posefd,"%g\n",Pose[i]); 
    }
    
    // Vel, Port, Stbd
    for(i=0;i<2;i++){ 
        fprintf(velfd,"%g\n",Vel[i]); 
        fprintf(portstatefd,"%g\n",PortState[i]); 
        fprintf(stbdstatefd,"%g\n",StbdState[i]); 
    }
    
    // Start/Elapsed Time 
    fprintf(timefd,"%g %g\n",*StartTime,*ElapsedTime); 
    
    // UV Data
    for(i=0;i<19200;i++){ 
        fprintf(uvdatafd,"%g\n",UV_data[i]); 
    }
    
    // Dist Data
    for(i=0;i<35100;i++){
        fprintf(distimagefd,"%g\n",Dist_Image[i]); 
    }
    
    // Traject Data
    for(i=0;i<9;i++){ 
        fprintf(trajectfd,"%g\n",Traject[i]); 
    }
    //  HSV Data
    for(i=0;i<307200;i++){ 
        fprintf(huefd,"%ud\n",Hue[i]); 
        fprintf(valfd,"%ud\n",Val[i]); 
        fprintf(satfd,"%ud\n",Sat[i]); 
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
    fclose(posefd); 
    fclose(velfd); 
    fclose(eulerfd); 
    fclose(portstatefd); 
    fclose(stbdstatefd); 
    fclose(timefd); 
    fclose(uvdatafd); 
    fclose(distimagefd);
    fclose(trajectfd); 
    fclose(huefd);
    fclose(satfd); 
    fclose(valfd);
}
#endif
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

