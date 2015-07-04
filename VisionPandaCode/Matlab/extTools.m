% extTools
% Allows for simple and quick changing of TCP/IPv4 configuration 
%      Static IP address for connecting to an ad-hoc network
%      DHCP for a home/school network
% Opens VNC remote desktop viewer
% Edited by James Tripiciano, July 2011

function extTools()
	clear, clc
	%netsh wlan show profiles 
	while 1
		clear
		disp('External Tools:')
		disp(' ');
		disp('   1. Change TCP/IPv4 settings for static IP on Ad-Hoc network');
		disp('   2. Change TCP/IPv4 settings for DHCP on home/public network');
		disp('   3. List available wireless connections');
		disp('   4. Open VNC remote desktop viewer');
		disp('   5. Exit');
		disp(' ');
		disp('###Note### to connect to a network click on network button located');
		disp('in the notification area on the taskbar');
		disp(' ');
		
		menuControl= input('Enter choice: ');
		
		switch menuControl
			case 1
				[status,result]=system(['netsh wlan disconnect']);
				disp('Enter desired IP address in form of 10.0.0.XX');
				disp('Note: IP must be a unique address different from the target IP address.')
				disp('Example: 10.0.0.54');
				disp(' ');
				IP= input('Enter IP: ','s');
				[status,result]=system(['netsh interface ip set address name="Wireless Network Connection" source=static addr=',IP,' mask=255.0.0.0']);
				if status==0
					clc
					disp(' ');
					disp(' ');
					disp('#####Settings Saved#####');
					disp(' ');
					disp(' ');
				end
		
			case 2	
				[status,result]=system(['netsh wlan disconnect']);
				[status,result]=system(['netsh interface ip set address name="Wireless Network Connection" source=dhcp']);
				if status==0
					clc
					disp(' ');
					disp(' ');
					disp('#####Settings Saved#####');
					disp(' ');
					disp(' ');
				end
		
			case 3
				system(['netsh wlan show profiles']);
					disp(' ');
					disp(' ');
				
			case 4
				commsToolsPath=regexprep(which('vncviewer.exe'), 'vncviewer.exe','');
				system([,commsToolsPath,'vncviewer &']);
			
			otherwise
				clear
				break;
		end;%switch
	end;%while
end %function