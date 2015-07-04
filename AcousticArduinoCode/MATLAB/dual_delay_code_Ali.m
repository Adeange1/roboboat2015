clear all

% fs = 16000; % sampling frequency (in Hz)

% First, generate the input signals.
% We need two signals, one for the right
% and one for the left channels.
% These are stored in the 'l' and 'r' arrays
%
% As an example, 3 signal types are provided:
% click, sine and noise (uncomment the commands
% for the signal you wish to use and comment out
% the others)
%
% In order to use signals from real microphones,
% the samples would need to somehow be recorded
% from the hardware audio device and then stored
% in the 'l' and 'r' arrays. The rest of the
% program would not need to be changed.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% click (all samples set to zero except one)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc
clear all

filename_p1='18_1.csv';
filename_p2='18_11.csv';

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
deltat=time(2)-time(1);
fs = 1/deltat; % sampling frequency (in Hz)

fc=1500;
wn=(2/fs)*fc;
b=fir1(30,wn,'low',kaiser(31,3));
fvtool(b,1,'Fs',fs)

y=filter(b,1,r);
y1=filter(b,1,l);

plot(r)
hold on
plot(y,'r')


l=y1;
r=y;




% l = zeros( 1, 512);
% r = zeros( 1, 512);
% l( 256 ) = 1;
% r( 262 ) = 1; % ITD of 6 samples

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a sinusoidal signal of frequency 'sinfrq'
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% sinfrq = 1984.5; % sine frequency (in Hz)
% l = sin( 2 * pi * sinfrq * ( 1 : 1000 ) / fs );
% r = sin( 2 * pi * sinfrq * ( ( 1 : 1000 ) / fs + 300e-6 ) ); % ITD of 300 microseconds

%%%%%%%%%%%%%%
% random noise
%%%%%%%%%%%%%%

% l = rand( 1, 1000 );
% r( 1, 26 : 1000 ) = l( 1, 1 : ( 1000 -25 ) );

ft_to_m=0.3048;
Mdist = 2.0625*ft_to_m;
% Mdist = 0.20; % m microphone distance
soundspeed = 1497; % speed of sound (340 m/s)
ITDmax = Mdist / soundspeed; % maximal possible interaural time difference in seconds
I = 361; % number of coincidence detectors

fftr = fft( r ); % Fourier transform of the left microphone channel
fftl = fft( l ); % Fourier transform of the right microphone channel
M = length( l ); % number of points in the Fourier transform

% main loop

for m = 1 : ( M / 2 ) % loop through frequencies

  fm = ( m - 1 ) * fs / M; % frequency (in Hz) corresponding to frequency index 'm'

    for i = 1 : I % loop through coincidence detectors

      % compute the delay value for coincidence detector 'i'
      Taui = ( ITDmax / 2 ) * sin( ( i - 1 ) / ( I - 1 ) * pi - pi / 2 );

      % adjust phase of left signal
      Xl = fftl( m ) * exp( -j * 2 * pi * fm * Taui );

      % adjust phase of right signal
      Xr = fftr( m ) * exp( j * 2 * pi * fm * Taui );

      % magnitude of the difference of the left and right phase-delayed signals
      Delta( i, m ) = abs( Xl - Xr );

    end

end

% uncomment if you want to plot the 3D coincidence map Delta (azimuth
% vs. frequency vs. dissimilarity)
% NOTE: This could take a looooong time under Octave

% mesh( 90 - ( ( 1 : I ) - 1 ) / ( I - 1 ) * 180, ( 0 : ( M / 2 - 1 ) ) * fs / M, Delta' );

% Sum up Delta over frequency, which results in the dissimilarity
% function, which shows the similarity between the delayed signals at a
% specific coincidence detector (the higher the value, the less similar
% the signals).
D=sum(Delta');

% plot dissimilarity vs. coincidence detector index
plot(1:I,D);

% find the index 'i' at which the dissimilarity function has a minimum
% (this is the place of coincidence)
[ C, i ] = min( D );

% compute the azimuth corresponding to coincidence detector 'i'
alphai = 90 - ( i - 1 ) / ( I - 1 ) * 180