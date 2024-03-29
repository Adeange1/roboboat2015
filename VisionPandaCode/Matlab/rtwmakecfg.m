% RTWMAKECFG adds include and source directories to rtw make files. 
% makeInfo=RTWMAKECFG returns a structured array containing build info. 
% Please refer to the rtwmakecfg API section in the Real-Time Workshop 
% Documentation for details on the format of this structure. 

% Dan D. V. Bhanderi, 2006
% $Id: rtwmakecfg.m,v 1.1 2007/03/26 14:27:07 danji Exp $

% Get hold of the fullpath to this file, without the filename itself
% Edited by James Tripiciano, July 2011
function makeInfo=rtwmakecfg()

rootpath = rtw_alt_pathname(fileparts(mfilename('fullpath')));
disp('rootpath=');
makeInfo.includePath = { ...
    %fullfile(matlabroot,'rtw','c','rlnx','rlnx_source'), ...
    '$(MATLAB_ROOT)\rtw\c\rlnx\rlnx_source'};
makeInfo.sourcePath = {};

%makeInfo.includePath = strrep(makeInfo.includePath,'\','/')
disp(makeInfo.includePath);
% Block source path for C S-Function source file
makeInfo.precompile = 0;

return;
