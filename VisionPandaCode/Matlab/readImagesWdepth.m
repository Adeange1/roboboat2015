function [ distI,phiI,thetaI,depth,scan ] = readImagesWdepth( filename )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

load([filename '\Dist_im']);
load([filename '\Phi_im']);
load([filename '\Theta_im']);
load([filename '\ImageData']);
load([filename '\UVData']);
% load([filename '\DistBW']);

numScanCols = 1080;
numScanRows = 65;
numVidCols = 640;
numVidRows = 480;
numDepthCols = 160;
numDepthRows = 120;
numCols = 540;
numRows = 65;
numFrames = floor(length(Dist_im)/(numCols*numRows));

Red = zeros(numVidRows,numVidCols,numFrames);
Green = zeros(numVidRows,numVidCols,numFrames);
Blue = zeros(numVidRows,numVidCols,numFrames);
depth = zeros(numDepthRows,numDepthCols,numFrames);
BW = zeros(numRows,numCols,numFrames);
distI = zeros(numRows,numCols,numFrames);
phiI = zeros(numRows,numCols,numFrames);
thetaI = zeros(numRows,numCols,numFrames);
scan = zeros(numScanRows,numScanCols,numFrames);

for k=1:numFrames
%     for j=1:numVidCols
%         for i=1:numVidRows
%             Red(i,j,k) = RedData(int32(i+numVidRows*(j-1)+numVidRows*numVidCols*(k-1)));
%             Green(i,j,k) = GreenData(int32(i+numVidRows*(j-1)+numVidRows*numVidCols*(k-1)));
%             Blue(i,j,k) = BlueData(int32(i+numVidRows*(j-1)+numVidRows*numVidCols*(k-1)));
%         end
%     end
    for j=1:numCols
        for i=1:numRows
            distI(i,j,k) = Dist_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
            phiI(i,j,k) = Phi_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
            thetaI(i,j,k) = Theta_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
%             BW(i,j,k) = DistBW(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
        end
    end
    for j2=1:numScanCols
        for i2=1:numScanRows
            scan(i2,j2,k)=ImageData(int32(j2+numScanCols*(i2-1)+numScanRows*numScanCols*(k-1)));
        end
    end
    for j3=1:numDepthCols
        for i3=1:numDepthRows
            depth(i3,j3,k) = UVData(int32(i3+numDepthRows*(j3-1)+numDepthRows*numDepthCols*(k-1)));
        end
    end
end

end

