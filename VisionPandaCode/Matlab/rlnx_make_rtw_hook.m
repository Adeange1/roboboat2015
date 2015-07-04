function rlnx_make_rtw_hook(hookMethod, modelName, rtwroot, templateMakefile, buildOpts, buildArgs, buildInfo) %#ok<INUSL>
% AUTOSAR_MAKE_RTW_HOOK - This is the standard ERT hook file for the RTW build
% process (make_rtw).
%
% This hook file (i.e., file that implements various RTW callbacks) is
% called by RTW for system target file ert.tlc.  The file leverages
% strategic points of the RTW process.  A brief synopsis of the callback
% API is as follows:
%
% autosar_make_rtw_hook(hookMethod, modelName, rtwroot, templateMakefile,
%                   buildOpts, buildArgs)
%
% hookMethod:
%   Specifies the stage of the RTW build process.  Possible values are
%   entry, before_tlc, after_tlc, before_make, after_make and exit, etc.
%
% modelName:
%   Name of model.  Valid for all stages.
%
% rtwroot:
%   Reserved.
%
% templateMakefile:
%   Name of template makefile.  Valid for stages 'before_make' and 'exit'.
%
% buildOpts:
%   Valid for stages 'before_make' and 'exit', a MATLAB structure
%   containing fields
%
%   modules:
%     Char array specifying list of generated C files: model.c, model_data.c,
%     etc.
%
%   codeFormat:
%     Char array containing code format: 'RealTime', 'RealTimeMalloc',
%     'Embedded-C', and 'S-Function'
%
%   noninlinedSFcns:
%     Cell array specifying list of non-inlined S-Functions.
%
%   compilerEnvVal:
%     String specifying compiler environment variable value, e.g.,
%     D:\Applications\Microsoft Visual
%
% buildArgs:
%   Char array containing the argument to make_rtw.  When pressing the build
%   button through the Configuration Parameter Dialog, buildArgs is taken
%   verbatim from whatever follows make_rtw in the make command edit field.
%   From MATLAB, it's whatever is passed into make_rtw.  For example, itsmodelName= deblank(s(5:end));
%   'optimized_fixed_point=1' for make_rtw('optimized_fixed_point=1').
%
%   This file implements these buildArgs:
%     optimized_fixed_point=1
%     optimized_floating_point=1
%
% You are encouraged to add other configuration options, and extend the
% various callbacks to fully integrate ERT into your environment.
%
% Edited by James Tripiciano, July 2011
% 
% Copyright 2007 The MathWorks, Inc.
% $Revision: 1.1.6.3 $ $Date: 2008/01/15 18:56:12 $
targetArch=get_param(modelName, 'TargetArch');
cs = getActiveConfigSet(modelName);
hostArch=grt_default_tmf;	
folderPath=regexprep(which(modelName), '.mdl', '_rlnx_rtw');	
commsToolsPath=regexprep(which('putty.exe'), 'putty.exe','');	
exePath=which(regexprep('extTest.mdl', '.mdl', '.exe'));

switch hookMethod
   case 'error'
    % Called if an error occurs anywhere during the build.  If no error occurs
    % during the build, then this hook will not be called.  Valid arguments
    % at this stage are hookMethod and modelName. This enables cleaning up
    % any static or global data used by this hook file.
    disp(['### Real-Time Workshop build procedure for model: ''' modelName...
          ''' aborted due to an error.']);
    
	case 'entry'
	% Called at start of code generation process (before anything happens.)
	% Valid arguments at this stage are hookMethod, modelName, and buildArgs.
	clc;
	disp(sprintf(['\n### Starting Real-Time Workshop build procedure for ', ...
		  'model: %s'],modelName));
	set_param(cs,'GenerateComments','off');
	if targetArch(1)=='L'
		set_param(cs,'TemplateMakefile','rlnx_ubuntu.tmf');
		set_param( modelName, 'GenCodeOnly', 'on' )

	else
		set_param(cs,'TemplateMakefile',strcat('rlnx',strtok(grt_default_tmf,'grt'),'tmf'));
		set_param( modelName, 'GenCodeOnly', 'off' )
        disp(['del "',exePath ,'"']);
        if length(exePath)~=0
            [status,result]=system(['del "',exePath ,'"'])
        end
        %disp(exePath);
        %delete(exePath);
	end
	if hostArch(5)=='u'
        	[status,result]=system(['rm  -r ',folderPath]);
	else 
		[status,result]=system(['del ',folderPath,' /Q /S']);
    end    

   

    
   case 'before_tlc'
    % Called just prior to invoking TLC Compiler (actual code generation.)
    % Valid arguments at this disp('Not In External Mode');stage are hookMethod, modelName, and
    % buildArgs

   case 'after_tlc'
    % Called just after to invoking TLC Compiler (actual code generation.)
    % Valid arguments at this stage are hookMethod, modelName, and
    % buildArgs
    

   case 'before_make'
    % Called after code generation is complete, and just prior to kicking
    % off make process (assuming code generation only is not selected.)  All
    % arguments are valid at this stage.


   case 'after_make'
       
   case 'exit'
	% Called at the end of the RTW build process.  All arguments are valid
	%at this stage.
	runT=get_param(modelName, 'runTarget');
	IP=get_param(modelName, 'TIP');

	if targetArch(1)=='L'
		download=get_param(modelName, 'Download');
		if isempty(IP)==1
			disp('Ip not Found: Enter Ip in configuration panel');	
		end
		if download(2)~='f'%If downloading to target
			disp(['### Terminating old programs on target']);		
			[X,result]=killModel(modelName,IP);	
			disp(['### Downloading code folder to target']);		
			[X,result]=dlLnxTarget(modelName,IP);
			disp(['### Compiling for target']);
			compLnxTarget(modelName,IP);

			if runT(2)~='f'	%If chose to run on target
				disp(['### Starting program on target']);
				if strcmp(get_param(gcs, 'SimulationMode'),'external')
					runExtTarget(modelName,IP);
					disp(['### Finished, Ready to connect']);
				else
					runTarget(modelName,IP);
					disp(['### Finished']);
				end
			else	
				disp(['### Finished']);
			end
		end%%end download

	else %Compiling for PC
   
		if runT(2)~='f'	%if running on target
			disp(['### Starting program on PC']);

			if hostArch(5)=='u'            
				path=regexprep(folderPath, '_rlnx_rtw','');
			else
				p = which(strcat(modelName,'.exe'),'-all');
				path =cat(2,p{:});
			end

			if strcmp(get_param(gcs, 'SimulationMode'),'external')
				if hostArch(5)=='u'            
					system(['xterm -e ',path,' -w -tf inf" &']);
				else
					system(horzcat('start cmd /k ',path,' -w -tf inf'));
				end
					disp(['### Finished, Ready to connect']);
			else

				if hostArch(5)=='u'            
					system(['xterm -e ',path]);
				else
			    		system(horzcat('start cmd /k ',path));
				end
				disp(['### Finished']);
			end
		else %Not running on target
			disp(['### Finished']);
		end
	end

    
    
end%end Switch
