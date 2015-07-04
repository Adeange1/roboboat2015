% compLnxTarget compiles the source code previously downloaded to the linux 
% target by dlLnxTarget to create an executable.
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
function compLnxTarget(modelName,IP)

commsToolsPath='C:\RTtools\VU-RLNX\Comms_Tools\PuTTY\';%regexprep(which('putty.exe'), 'putty.exe','')

switch computer
    case {'PCWIN','PCWIN64'}     % Windows host computer
	system([commsToolsPath,'plink -ssh -pw password root@',IP,...          % Opens plink for ssh communication with lnx target
			' cd /matlab_code/',modelName,'_rlnx_rtw/updatedFiles;'...     % Navigates to model folder on lnx target
			' chmod +x selCP;./selCP ;'...                                 % Executes selCP after giving it executive permissions
			' cd ..; rm updatedFiles -r;'...                               % Deletes all of the old files from the lnx target
			' make -f ',modelName,'.mk']);                                 % Creates an executable for the model

    case {'GLNX86','GLNXA64'}    % Linux host computer
	system(['ssh -q  root@',IP,...
			' "cd /matlab_code/',modelName,'_rlnx_rtw/updatedFiles;'... 
			' chmod +x selCP;./selCP ;'...
			' cd ..;rm updatedFiles -r;'...
			' make -f ',modelName,'.mk"']);

end

