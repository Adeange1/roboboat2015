% killModel Terminates old programs on the linux target.
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
function [status,result]= killModel(modelName,IP)

commsToolsPath=regexprep(which('putty.exe'), 'putty.exe','');

switch computer
    case {'PCWIN','PCWIN64'}     % Windows host computer
	[status,result]=system([commsToolsPath,'plink -ssh -pw password root@',IP,' killall ',modelName]); % Opens a ssh connection and kills all running executables with "modelName"

    case {'GLNX86','GLNXA64'}    % Linux host computer
	[status,result]= system(['ssh root@',IP,'  killall -9 ',modelName]);

end
