clc
clear all

filename_p1='20_1.csv';
filename_p2='20_11.csv';

M1 = csvread(filename_p1,2,0);
M2 = csvread(filename_p2,2,0);


[maxsamp col] = size(M1);
time = zeros(maxsamp,1);
left = zeros(maxsamp,1);
right = zeros(maxsamp,1);

[maxsamp1 col1] = size(M2);
time1 = zeros(maxsamp1,1);
left1 = zeros(maxsamp1,1);
right1 = zeros(maxsamp1,1);

% This loop populates the matrices for time and the two hydrophones
for i = 1:maxsamp,
    time(i,1) = M1(i,1);
    left(i,1) = M1(i,2);
    right(i,1) = M1(i,3);
end

for i = 1:maxsamp1,
    time1(i,1) = M2(i,1);
    left1(i,1) = M2(i,2);
    right1(i,1) = M2(i,3);
end
clear i

time=[time;time1];
left=[left;left1];
right=[right;right1];
maxsamp=maxsamp+maxsamp1;

l=left;
r=right;



clear time1 left1 right1

deltat=time(2)-time(1);
fs = 1/deltat; % sampling frequency (in Hz)

fc=1500;
wn=(2/fs)*fc;
b=fir1(30,wn,'low',kaiser(31,3));
fvtool(b,1,'Fs',fs)

y=filter(b,1,r);
y1=filter(b,1,l);

% plot(r)
% hold on
% plot(y,'r')


l=y1;
r=y;

right=l;
left=r;


ft_to_m=0.3048; % conversion to SI
Tint = 10e-3; % integration constant in seconds
Tint = Tint * fs; % convert to samples
Mdist = 2.0625*ft_to_m; % m microphone distance
soundspeed = 1497; % speed of sound in water (m/s)
ITDmax = Mdist / soundspeed; % maximal possible interaural time difference in seconds
ITDmax = floor(ITDmax * fs); % convert to samples
Psi = zeros(1, 2*ITDmax+1); % create an array for the correlation function

% main loop
% not sure if the next line is right (changed 1000 to maxsamp) - this loop
% isn't running currently
for n = (1 + ITDmax) : (maxsamp - ITDmax) % loop through the signal samples
    for Tau = -ITDmax : ITDmax % loop through all possible ITD values
        Psi(Tau+ITDmax+1) = exp(-1 / Tint) * Psi(Tau+ITDmax+1) + left(n) * right(n - Tau);
    end
end

% plots and computations
plot( - ITDmax : ITDmax, Psi ); % plot ITD (in samples) vs. correlation
[C, I ] = max( Psi ); % find the index 'I' at which the correlation function has a maximum
I = I - ITDmax - 1; % compute the corresponding ITD in samples
alpha=asin(soundspeed * I / (Mdist * fs)) * 180 / pi % compute the azimuth (in degrees) corresponding to ITD 'I'
