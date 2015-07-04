IPath = ' -IC:\opencv\build\include\opencv -IC:\opencv\build\include';
LPath = ' C:\opencv\build\x86\vc10\lib';
lib1 = fullfile(LPath,'opencv_core240.lib');
lib2 = fullfile(LPath,'opencv_imgproc240.lib'); 
lib3 = fullfile(LPath,'opencv_calib3d240.lib'); 
lib4 = fullfile(LPath,'opencv_video240.lib'); 
lib5 = fullfile(LPath,'opencv_features2d240.lib'); 
lib6 = fullfile(LPath,'opencv_ml240.lib'); 
lib7 = fullfile(LPath,'opencv_highgui240.lib'); 
lib8 = fullfile(LPath,'opencv_objdetect240.lib'); 
lib9 = fullfile(LPath,'opencv_contrib240.lib'); 
lib10 = fullfile(LPath,'opencv_legacy240.lib');

comm = ['mex WebcamTest.c', IPath, lib1, lib2, lib3, lib4, lib5, lib6, lib7, lib8, lib9, lib10];
eval(comm)