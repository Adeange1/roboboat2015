/*
 * File: pot_reader.c
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
 * Created: Thu Jun 19 20:43:25 2014
 * 
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME pot_reader2
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS           0

#define NUM_OUTPUTS          1
/* Output Port  0 */
#define OUT_PORT_0_NAME      potVal
#define OUTPUT_0_WIDTH       1
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       int32_T
#define OUTPUT_0_COMPLEX     COMPLEX_NO
#define OUT_0_FRAME_BASED    FRAME_NO
#define OUT_0_BUS_BASED      0
#define OUT_0_BUS_NAME       
#define OUT_0_DIMS           1-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125

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

extern void pot_reader_Outputs_wrapper(int32_T *potVal);

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
    ssSetOutputPortWidth(S, 0, OUTPUT_0_WIDTH);
    ssSetOutputPortDataType(S, 0, SS_INT32);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
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

#include <stdio.h> 		/* Standard I/O definitions */
#include <stdlib.h> 	
#include <unistd.h> 	/* UNIX standard function definitions */ 
#include <termios.h> 	/* POSIX terminal control definitions */ 
#include <errno.h> 		/* Error number definitions */ 
#include <fcntl.h> 		/* File control definitions */ 

int fd, i; // file descriptor for usb port and 
char readBuffer[8];
struct termios options;


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
    
    fd = open("/dev/ttyO3",O_RDWR | O_NOCTTY | O_NDELAY);
				
	if (fd == -1){ // file pter for serial not established
		printf("Can't Open Serial Port.Exiting Program...\n"); 
		//return 0; 
	} 	
	else{ // file pter for usb port established
		  
		if(tcgetattr(fd,&options)<0){ // can't get current options for usb port
			printf("Cant get term attributes. Exiting Program...\n"); 
			//return 0; 
		}
		else{ // got current options for usb port 
			cfsetispeed(&options,B9600); // Set IO baud rates to 115200
			cfsetospeed(&options,B9600); 
			
		    // 8N1
			//options.c_cflag &= ~PARENB; // Enable Parity
			options.c_cflag &= ~CSTOPB; // Stop Bit
			options.c_cflag &= ~CSIZE; // Character size
			options.c_cflag |= CS8; // 8 bits
		      
	
	      // Local Mode and Serial Data Receive
			options.c_cflag |= CREAD | CLOCAL; // turn on read and ignore ctrl lines 
		
			if(tcsetattr(fd,TCSANOW,&options)<0){ // if can't set attributes 
				printf("Can't set term attributes. Exiting Program...\n");
				//return 0; 
			}
			
			fcntl(fd,F_SETFL,0);
		}
	}
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
    int32_T        *potVal  = (int32_T *)ssGetOutputPortRealSignal(S,0);
    char value[4];
	//while(1){
		read(fd,readBuffer,sizeof(readBuffer));
		    if(readBuffer[0] == 'P' && readBuffer[1] == 'o' &&
		       readBuffer[2] == 't' && readBuffer[3] == ':'){
               value[0]=readBuffer[4]; 
               value[1]=readBuffer[5]; 
               value[2]=readBuffer[6]; 
               value[3]=readBuffer[7]; 
               *potVal = atoi(value);
               //printf("PotValue:%d\n",*potVal);
			} 
		//}
    
    //*potVal = potHolder;
		

    //pot_reader_Outputs_wrapper(potVal);
}



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    close(fd);
}

#endif

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


