/*
 * File: lidarOnly.c
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
  *   For better compatibility with the Simulink Coder, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Simulink Coder's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *  -------------------------------------------------------------------------
  * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
  *  ------------------------------------------------------------------------- 
* Created: Thu Jun 12 13:53:14 2014
*/
#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME lidarOnly2
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS           0

#define NUM_OUTPUTS          1
/* Output Port  0 */
#define OUT_PORT_0_NAME      y0
#define OUTPUT_0_WIDTH       70200
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       int32_T
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

#define NPARAMS              0

#define SAMPLE_TIME_0        100
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 1
#define SOURCEFILES
#define PANELINDEX           6
#define USE_SIMSTRUCT        0
#define SHOW_COMPILE_STEPS   1                  
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0
/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> 
//#include <windows.h> //Uncomment for testing on windows machines
#include "math_utils.h"
#include "ring_buffer.h"
#include "scip_handler.h"
#include "serial_ctrl.h"
#include "serial_errno.h"
#include "serial_t.h"
//#include "serial_t_win.h" //Uncomment for testing on windows machines
#include "serial_utils.h"
#include "urg_ctrl.h"
#include "urg_delay.h"
#include "urg_errno.h"
#include "urg_parameter_t.h"
#include "urg_t.h"
#include "urg_ticks.h"

//mex lidarOnly2.c urg_ctrl.c ring_buffer.c scip_handler.c serial_ctrl.c serial_utils.c urg_delay.c urg_errno.c urg_ticks.c


void urg_exit(urg_t *urg, const char *message){
  printf("%s: %s\n", message, urg_error(urg));
  urg_disconnect(urg);

  #ifdef MSC
      getchar();
  #endif
}

extern void lidarOnly_Outputs_wrapper(int32_T *y0);

int i,j,k,l;  // for loop vars 
int n, ret; // check var 
int timestamp = -1; // Time Stamp for Each Image 
const char device[] = "/dev/ttyACM0"; 
urg_t urg; // urg struct for lidar 
long data[1080]; 

    
/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);
     if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
	 return; /* Parameter mismatch will be reported by Simulink */
     }

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;

    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    /* Output Port 0 */
    outputDimsInfo.width = OUTPUT_0_WIDTH;
    ssSetOutputPortDimensionInfo(S, 0, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,0, OUTPUT_0_WIDTH, OUTPUT_DIMS_0_COL);
    ssSetOutputPortFrameData(S, 0, OUT_0_FRAME_BASED);
    ssSetOutputPortDataType(S, 0, SS_INT32);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    //ssSetSimulinkVersionGeneratedIn(S, "8.3");

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR | 
		     SS_OPTION_WORKS_WITH_CODE_REUSE));
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

          ret = urg_connect(&urg, device, 115200);
          if (ret < 0) {
             urg_exit(&urg, "urg_connect()");

            }
          else
             urg_setCaptureTimes(&urg, UrgInfinityTimes);

}
#endif /*  MDL_START */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
   ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}
/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    int32_T        *y0  = (int32_T *)ssGetOutputPortRealSignal(S,0);
    
    for (j=0;j<65;j++) { 
      // Request Data 
      ret = urg_requestData(&urg, URG_GD, 0, 1080);
      if (ret < 0) {
        urg_exit(&urg, "urg_requestData()");
      }

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
            	y0[(i*1080)+k] = data[k];  
          	}
        }
    }
    //lidarOnly_Outputs_wrapper(y0);
      
      //printf(data);


}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{

     urg_disconnect(&urg);

}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


