% runTarget executes the compiled source code on the linux target.
%
% commsToolsPath:
%      The location of the putty tools C:\RTtools\VU-RLNX\Comms_Tools\PuTTY
%
% modelName:
%      Name of model.
%
% IP:
%      IP address of target specified in the configuration parameters under 
%      Target IP Address.
%
% Edited by James Tripiciano, July 2011
%
function [status,result]= runTarget(modelName,IP)

commsToolsPath=regexprep(which('putty.exe'), 'putty.exe','');

switch computer
    case {'PCWIN','PCWIN64'}     % Windows host computer
	[status,result]=system([commsToolsPath,'plink -ssh -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							' "cd /matlab_code; chmod 777 *'...                   % Navigates to model folder on lnx target and changes folder permissions
							'; nohup ./',modelName,' > /dev/null &"']);           % Executes the make file

    case {'GLNX86','GLNXA64'}    % Linux host computer
	[status,result]=   system(['ssh root@',IP,' "run-standalone.sh /usr/bin/maemo-summoner /usr/bin/osso-xterm.launch -e ''/matlab_code/',modelName,' -tf inf -w'' " &']);
	end
