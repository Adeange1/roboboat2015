% dlLnxTarget downloads the source code of the model onto the linux target
% 
% rlnxPath:
%      The location of the rlnx folder
%
% modelPath:
%      The location of the model
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
function [status,result]= dlLnxTarget(modelName,IP)

rlnxPath=regexprep(which('rlnx.tlc'), 'rlnx.tlc','');
modelPath=regexprep(which(modelName), '.mdl', '_rlnx_rtw');
commsToolsPath='C:\RTtools\VU-RLNX\Comms_Tools\PuTTY\';%regexprep(which('putty.exe'), 'putty.exe','')

switch computer
    case {'PCWIN','PCWIN64'}     % Windows host computer
	[status,result]=system(['cd "',modelPath,'" && mkdir updatedFiles&& move * updatedFiles']);
	[status,result]=system(['cd "',modelPath,'" && move * updatedFiles']);
	[status,result]=system(['cd "',modelPath,'\updatedFiles" && copy *_targ_data_map.m ..']);
	[status,result]=system(['copy /Y "',rlnxPath,'selCP" "',modelPath,'\updatedFiles"']);
	[status,result]=system(['cd ',modelPath,'\.. && ',commsToolsPath,'pscp -pw password -q -r ',modelName,'_rlnx_rtw root@',IP,':/matlab_code']);

    case {'GLNX86','GLNXA64'}    % Linux host computer
	[status,result]=system(['cd "',modelPath,'"; mkdir updatedFiles; mv * updatedFiles']);
	[status,result]=system(['cd "',modelPath,'/updatedFiles"; cp *_targ_data_map.m ..']);
	[status,result]=system(['cp "',rlnxPath,'selCP" "',modelPath,'/updatedFiles"']);
	[status,result]=system(['scp -r ',modelPath,' root@',IP,':/matlab_code']);

end

