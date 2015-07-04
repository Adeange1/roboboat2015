function [ distI ] = readScans( filename )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

load([filename '\Dist_im']);
% load([filename '\Phi_im']);
% load([filename '\Theta_im']);
% load([filename '\ImageData']);

% numScanCols = 1080;
numCols = 540;
numRows = 65;
numFrames = floor(length(Dist_im)/(numCols*numRows));

distI = zeros(numRows,numCols,numFrames);
% phiI = zeros(numRows,numCols,numFrames);
% thetaI = zeros(numRows,numCols,numFrames);
% scan = zeros(numRows,numScanCols,numFrames);

for k=1:numFrames
    for j=1:numCols
        for i=1:numRows
            distI(i,j,k) = Dist_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
%             phiI(i,j,k) = Phi_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
%             thetaI(i,j,k) = Theta_im(int32(i+numRows*(j-1)+numRows*numCols*(k-1)));
        end
    end
end

% for k2=1:numFrames
%     for j2=1:numScanCols
%         for i2=1:numRows
%             scan(i2,j2,k2)=ImageData(int32(j2+numScanCols*(i2-1)+numRows*numScanCols*(k2-1)));
%         end
%     end
% end

end

