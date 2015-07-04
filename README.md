The project runs on several different processors, and there is a folder containing code for each individual processor.

The main processor running high level decision making is the speedgoat, a real-time target machine that uses simulink's xpctarget turnkey for development - using matlab version r2014a. All other processors are linked to the speedgoat via serial connections.

The vision system is run on a pandaboard ES rev b2. The pandaboard runs the VU-RLNX package for simulink - using matlab version r2009a.
 
The IMU is run by a raspberry pi, and the code is written in c.

# roboboat2015
