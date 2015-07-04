function installer(cmd,rootInstallDir,downloadDir)

%INSTALLER Installs the Pandaboard associated third party tools
%
%   INSTALLER (with no arguments) displays a menu of installation options.
%   The tools are installed underneath the default root: C:\RTtargets
%
%   INSTALLER(n) directly executes the nth option of the installation menu:
%       1. Download and Install tools, Compile Mex files, and Download Includes Folder to Pandaboard;
%       2. Download tools (only);
%       3. Install tools (only);
%       4. Compile Mex files (only);
%		5. Download Include Directory to Pandaboard (only);
%       6. Exit;
%
%   INSTALLER(n,rootInstallDir,downloadDir) enables the default download
%   and installation root directories to be overridden with pathnames
%   specified by the user.  However, these pathnames must NOT CONTAIN SPACES
%
% Signature
%   Author: James Peyton Jones
%   Date: 28 Dec 2010
%   Copyright: 2010 Villanova University
%
% Edited by James Tripiciano, July 2011
%
% Configuration Section
if nargin<2, rootInstallDir= 'C:\RTtools\VU-RLNX'; end;     % No spaces allowed in path!!!
if nargin<3, downloadDir= fullfile(rootInstallDir,'Downloads'); end;

config(1) = struct('name','PuTTY',...
                   'url','http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe',...
                   'downloadFile',fullfile(downloadDir,'putty.exe'),...
                   'destDir',fullfile(rootInstallDir,'Comms_Tools/PuTTY'),...
                   'fileName','\putty.exe');
               
config(2) = struct('name','PSFTP',...
                   'url','http://the.earth.li/~sgtatham/putty/latest/x86/psftp.exe',...
                   'downloadFile',fullfile(downloadDir,'psftp.exe'),...
                   'destDir',fullfile(rootInstallDir,'Comms_Tools/PuTTY'),...
                   'fileName','\psftp.exe');    
               
config(3) = struct('name','PSCP',...
                   'url','http://the.earth.li/~sgtatham/putty/latest/x86/pscp.exe',...
                   'downloadFile',fullfile(downloadDir,'pscp.exe'),...
                   'destDir',fullfile(rootInstallDir,'Comms_Tools/PuTTY'),...
                   'fileName','\pscp.exe');   
	
config(4) = struct('name','Plink',...
                   'url','http://the.earth.li/~sgtatham/putty/latest/x86/plink.exe',...
                   'downloadFile',fullfile(downloadDir,'plink.exe'),...
                   'destDir',fullfile(rootInstallDir,'Comms_Tools/PuTTY'),...
                   'fileName','\plink.exe');   
               
config(5) = struct('name','TightVNC',...
                   'url','http://www.tightvnc.com/download/2.0.2/tightvnc-2.0.2-setup.exe',...
                   'downloadFile',fullfile(downloadDir,'tightvnc-2.0.2-setup.exe'),...
                   'destDir',fullfile(rootInstallDir,'Comms_Tools/VNC'),...
                   'fileName','\vncviewer.exe');   
            
% Menu / Action Section               
if (nargin<1), 
    disp(' ');
    disp('*****************************************************');
    disp('*                                                   *');
    disp('*  Villanova University Pandaboard Real Time Target *');
    disp('*  Installer, ver 1.0                               *');
    disp('*                                                   *');
    disp('*****************************************************');
    cmd = getCmd(config); 
end;
while 1, %loop until terminating 'break'
    switch cmd
		case 1, downloadTools(config); installTools(config); mexAll; downloadIncludes(config);
		case 2, downloadTools(config);
		case 3, installTools(config);
		case 4, mexAll;
		case 5, downloadIncludes(config);
		case 6, ;
		otherwise, 
			disp(['Unrecognized option:' cmd]);
	end; %switch
	if (nargin>=1) || (cmd==6),  break; 
	else cmd = getCmd(config);
	end; %if
end; %while


function userCmd=getCmd(config)
	disp(' ');
	disp('Options:')
	disp('   1. Download and Install tools, Compile Mex files, and Download Includes Folder to Pandaboard');
	disp('   2. Download tools (only)');
	disp('   3. Install tools (only)');
	disp('   4. Compile Mex files (only)');
	disp('   5. Download Include Directory to Pandaboard (only)');
	disp('   6. Exit');  
	disp(' ');
	userCmd= input('Enter choice: ');
	if isempty(userCmd), userCmd = 0; end;
end; %getCmd


function downloadTools(config)
	for i=1:length(config),
		disp(['Downloading ' config(i).name]);
		filename = config(i).downloadFile;
		if ~isdir(fileparts(filename)), mkdir(fileparts(filename)); 
		end; %if
		if exist(filename, 'file')==2,
			disp(['...Downloaded file already exists.']);
		else % do download...
			try 
				urlwrite(config(i).url, filename);
				disp('...Done');
			catch
				disp(['Problem downloading ' config(i).name ' from ' config(i).url]);
				disp(lasterror);
			end; %try/catch
		end; %if
	end; %for
end %downloadTools


function installTools(config)
	response = lower(deblank(input(['\nHave you read and accepted all the licenses associated' ...
									'\nwith each third party tool listed in the documentation? [y/n]: '],'s')));
	if response(1)~='y', return; end;
	for i=1:length(config),
		disp(['Installing ' config(i).name]);
		setupFile= config(i).downloadFile;
		destDir= config(i).destDir;
		if ~isdir(destDir), mkdir(destDir); end;
		switch config(i).name
			case {'PuTTY','PSFTP','PSCP','Plink'}
				cmdstr = ['move ' setupFile ' ' fullfile(destDir, config(i).fileName)];
			case 'TightVNC'
				system([setupFile ' /S /D=' destDir]);
				system(' taskkill /F /im tvnserver.exe');
				cmdstr = [' del ' destDir '\tvnserver.exe'];
		end; %switch
		[status,result] = system(cmdstr);
		if status==0, disp('...Done'),
		else disp('...Did not appear to install correctly.');
		end; %if
	end; %for
	
	disp('Setting Matlab search path');
	addpath(pwd);               % Path to VU-PRT
	addpath(config(1).destDir); % Path to putty.exe
	addpath(config(5).destDir); % Path to VNC.exe
	status = savepath;
	if status==0,
		disp('...Done');
	else,
		disp('Could not save the Matlab search path for future sessions');
		disp('This may require administrator privileges.  On Windows 7 platforms');
		disp('it may also be necessary to be running Matlab in Administrator mode.');
		disp('See http://www.mathworks.com/support/solutions/en/data/1-9574H9/index.html?solution=1-9574H9');
	end; %if
end %installTools

function downloadIncludes(config)
	rlnxPath=regexprep(which('rlnx.tlc'), 'rlnx.tlc','');
	commsToolsPath=regexprep(which('putty.exe'), 'putty.exe','');
	
	disp(' '); disp('Make sure Pandaboard is powered and connected to a network.')
	disp(' '); 
	IP= input('Enter IP of Pandaboard: ','s');
	
	disp(' ');
	disp('Downloading matlab_includes to target...');
	[status,result]=system(['cd ',rlnxPath,' && ',commsToolsPath,'pscp -pw password -q -r matlab_includes root@',IP,':/']);
	if status==0, disp('...Done'),
	else disp('...Did not download matlab_includes correctly.');
	end;
	
	disp(' ');
	disp('Creating matlab_code directory on target...');
	system(['cd ',rlnxPath,' && mkdir matlab_code']);
	[status,result]=system(['cd ',rlnxPath,' && ',commsToolsPath,'pscp -pw password -q -r matlab_code root@',IP,':/']);
	system(['cd ',rlnxPath,' && rmdir matlab_code']);
	if status==0, disp('...Done'),
	else disp('...Did  not download matlab_code correctly.');
	end;
	
end %downloadFirmware

end %installer