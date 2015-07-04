function blkStruct = nxtblocks

% slblocks
%   defines the Simulink library block representation
%   for the Lego nxtOSEK blockset.
%
%   Copyright 2010 The MathWorks, Inc.
%
% Edited by James Tripiciano, July 2011

blkStruct.Name    = ['Panda/Arduino Blockset'];
blkStruct.OpenFcn = '';
blkStruct.MaskInitialization = '';
blkStruct.MaskDisplay = '';

% Define the library list for the Simulink Library browser.
% Return the name of the library model and the name for it
%
Browser(1).Library = 'Panda_Arduino_Blocks';
Browser(1).Name    = 'Panda/Arduino Blockset';
Browser(1).IsFlat  = 0;% Is this library "flat" (i.e. no subsystems)?

blkStruct.Browser = Browser;

% define information for model updater
% What's this?, in R2010a, this is needed to avoid an error when opening
% the library browser.
%blkStruct.ModelUpdaterMethods.fhDetermineBrokenLinks = @sl3dBrokenLinksMapping;
blkStruct.ModelUpdaterMethods.fhDetermineBrokenLinks = [];

% End of slblocks.m
