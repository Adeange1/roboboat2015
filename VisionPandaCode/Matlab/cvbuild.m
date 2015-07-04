function cvbuild(name,inc,cpp,lib)
% To build cvLink C-MEX S-Function
%
% Use cvbuildall to rebuild the entire library

if (nargin<=3),
	inc='';
	cpp='';
	lib='';
end

inc=[inc ' -IC:\cvlink\cvlink\include -IC:\OpenCV2.2\include\opencv2 -IC:\cvlink\easylink\include '];

cpp=[cpp ' C:\cvlink\easylink\src\easylink.cpp C:\cvlink\cvlink\src\cvinterface.cpp'];

lib=[lib ' C:\OpenCV-2.2.0\build\lib\Release\opencv_core220.lib C:\OpenCV-2.2.0\build\lib\Release\opencv_highgui220.lib C:\OpenCV-2.2.0\build\lib\Release\opencv_imgproc220.lib'];

%lib=[lib ' C:\OpenCV2.2\lib\opencv_core220.lib C:\OpenCV2.2\lib\opencv_highgui220.lib C:\OpenCV2.2\lib\opencv_imgproc220.lib'];
%C:\OpenCV-2.2.0\build\lib

P=['mex ' inc ' C:\cvlink\cvlink\src\' name ' ' cpp ' ' lib]
disp(['Building ' name '...']);
eval(P);

% inc=[inc ' -I./include -IC:/OpenCV2.2/include -I../easylink/include'];
% 
% cpp=[cpp ' ../easylink/src/easylink.cpp ./src/cvinterface.cpp'];
% 
% lib=[lib ' C:/OpenCV2.2/lib/opencv_core220.lib C:/OpenCV2.2/lib/opencv_highgui220.lib C:/OpenCV2.2/lib/opencv_imgproc220.lib '];
% 
% P=['mex ' inc ' ./src/' name ' ' cpp ' ' lib];
% disp(['Building ' name '...']);
% eval(P);