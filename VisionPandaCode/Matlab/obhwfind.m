function [dis,ob_h,ob_w]=obhwfind(height1,height2,width1,width2)

ratio1=height2/height1;
dis=(fwd_d*ratio1)/(ratio1-1);
ob_h=2*tan(44.443*pi/360)*dis*height1/size1(1,1);
ob_w=2*tan(57.154*pi/360)*dis*width1/size1(1,2);