#include <stdio.h>
#include <phidget21.h> 


int CCONV AttachHandler(CPhidgetHandle stepper, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (stepper, &name);
	CPhidget_getSerialNumber(stepper, &serialNo);
	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int CCONV DetachHandler(CPhidgetHandle stepper, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (stepper, &name);
	CPhidget_getSerialNumber(stepper, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle stepper, void *userptr, int ErrorCode, const char *Description)
{
	printf("Error handled. %d - %s\n", ErrorCode, Description);
	return 0;
}

int CCONV PositionChangeHandler(CPhidgetStepperHandle stepper, void *usrptr, int Index, __int64 Value)
{
	printf("Motor: %d > Current Position: %lld\n", Index, Value);
	return 0;
}

int stepperConnect(long accel, long speed,CPhidgetStepperHandle stepper){ 
	int result;
	const char *err;

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)stepper, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)stepper, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)stepper, ErrorHandler, NULL);
	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the Phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	//CPhidgetStepper_set_OnPositionChange_Handler(stepper, PositionChangeHandler, NULL);

	//open the device for connections
	CPhidget_open((CPhidgetHandle)stepper, -1);

	//get the program to wait for an stepper device to be attached
	printf("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)stepper, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}
	
	//Set up some initial acceleration and velocity values
	CPhidgetStepper_setAcceleration(stepper, 0, accel);
	CPhidgetStepper_setVelocityLimit(stepper, 0, speed);
	CPhidgetStepper_setCurrentLimit(stepper,0,1.7);

	//Set motor to position 0 
	CPhidgetStepper_setCurrentPosition(stepper, 0, 0);
	CPhidgetStepper_setEngaged(stepper, 0, 1);
	return 0; 
}

int stepperMove(int position, CPhidgetStepperHandle stepper){
	__int64 curr_pos;  
	CPhidgetStepper_getCurrentPosition(stepper, 0, &curr_pos); 
	CPhidgetStepper_setTargetPosition (stepper, 0, position);
	while(curr_pos!=position){
		CPhidgetStepper_getCurrentPosition(stepper, 0, &curr_pos); 
	}
	return 0; 
}

int stepperDisconnect(CPhidgetStepperHandle stepper){ 
	__int64 curr_pos;  
	int stopped;
	CPhidgetStepper_getCurrentPosition(stepper, 0, &curr_pos);
	CPhidgetStepper_setTargetPosition(stepper, 0, 0);
	//sleep(2);
	while(curr_pos!=curr_pos){
		CPhidgetStepper_getCurrentPosition(stepper, 0, &curr_pos); 
		if(curr_pos>curr_pos||curr_pos<curr_pos)
				CPhidgetStepper_setTargetPosition (stepper, 0, curr_pos);
	}
	stopped = PFALSE;
	while(!stopped)
	{
		CPhidgetStepper_getStopped(stepper, 0, &stopped);
		//usleep(100000);
	}

	CPhidgetStepper_setEngaged(stepper, 0, 0);
	CPhidget_close((CPhidgetHandle)stepper);
	CPhidget_delete((CPhidgetHandle)stepper);
	return 0; 
}
