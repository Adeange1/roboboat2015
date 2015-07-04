

import serial
from cmdsV2 import init

args = {'port':'/dev/ttyUSB0','baudrate':115200,'parity':serial.PARITY_NONE,'stopbits':serial.STOPBITS_ONE,'bytesize':serial.EIGHTBITS};
s = serial.Serial(**args);
s.open();

while 1:
	s.flushInput()
	message = s.readline();
	print message;
	if message[0:13] == 'MissionStart:':
		print 'Valid Message';
		if message[13] == '1':
			begun = init();
			print begun['Success'];
			if begun['Success'] == 'TRUE':
				s.write('MissionBegun:5\r\n');
			else:
				s.write('MissionBegun:0\r\n')
		else:
			s.write('MissionBegun:1\r\n');


