/*  Written by Michael Benson on 7/12/2014.  This program reads data from two hydrophones,
    and then performs a biaural source localization algorithm that calculates the angle
    between SeaCat and the pinger.  This angle is then sent to SeaCat.    
*/

#include <math.h>
#include <String.h>

#define valueC .5207  //Distance between hydrophones in meters
#define pi 3.1415

int lhighthresh = 596; //840.  High threshold for hydrophone noise.
int llowthresh = 542;  //800.  Low threshold for hydrophone noise.
int rhighthresh = 607; //620.  High threshold for hydrophone noise.
int rlowthresh = 553;  //550.  Low threshold for hydrophone noise.
int lmean = 569;      //819.  Mean hydrophone bias value.
int rmean = 580;      //596.  Mean hydrophone bias value.

char buf[8];

void setup() {

  Serial1.begin(115200) ;

}

void loop() {
  int size1 = 1000;
  int l[size1];
  int r[size1];
  int j;
  
  int lfirst = analogRead(A0);  //initial hydrophone samples
  int rfirst = analogRead(A0);  //initial hydrophone samples
  
  //If both hydrophones are outside of the thresholds, begin the subroutine
  if ((lfirst <= llowthresh || lfirst >= lhighthresh) && (rfirst <= rlowthresh || rfirst >= rhighthresh))
  {
    //Sample both hydrophones, 1000 samples each
    for (int i = 0 ; i < size1 ; i++)
    {
      l[i] = analogRead(A0);
      r[i] = analogRead(A2);
    }
    //Remove bias from hydrophone signals
    for (int j = 0 ; j < size1 ; j++)
    {
      l[j] = l[j] - lmean;
      r[j] = r[j] - rmean;
    }
    
    double deltat = .000006;
    double fs = 1/deltat; // sampling frequency in Hz
    
    int fc = 1500;
    double wn = (2/fs)*fc;
    
    
    double p_coeffs[31] = {0.00986205705585001,0.0129419941869408,0.0162218286681249,0.0196456704747832,0.0231514315663839,0.0266723652406137,0.0301387786510383,0.0334798676337734,0.0366256183828982,0.0395087177222889,0.0420664128524640,0.0442422625476499,0.0459877248149020,0.0472635309102973,0.0480408021787587,0.0483018742264655,0.0480408021787587,0.0472635309102973,0.0459877248149020,0.0442422625476499,0.0420664128524640,0.0395087177222889,0.0366256183828982,0.0334798676337734,0.0301387786510383,0.0266723652406137,0.0231514315663839,0.0196456704747832,0.0162218286681249,0.0129419941869408,0.00986205705585001};
    int p_coeffs_n = 31;
    double l_out[size1];
    double r_out[size1];
    
    int i, j, k;
    double tmpl, tmpr;
    
    for (k = 0; k < size1; k++) // position in output
    {
      tmpl = 0;
      tmpr = 0;
      for (i = 0; i < p_coeffs_n; i++) //position in coefficients array
      {
        j = k - i;  //position in input
        
        if (j >= 0) //bounds check for input buffer
        {
          tmpl += p_coeffs[k] * l[j];
          tmpr += p_coeffs[k] * r[j];
        }
      }
      l_out[i] = tmpl;
      r_out[i] = tmpr;
    }
    
    double Tint = .01*fs; //Inegration constant in samples
    double Mdist = 2.0625*.3048; //Microphone distance in meters
    int soundspeed = 1497;  //Speed of sound in water, m/s
    int ITDmax = (int) (Mdist*fs/soundspeed); //Max interaural time difference, in samples
    int PsiSize = 2*ITDmax;
    double Psi[PsiSize]; //Array for the correlation function
    for (int z = 0; z < PsiSize; z++)
    {
      Psi[z] = 0;
    }
    
    //main loop
    for (int n = (1 + ITDmax); n < (size1 - ITDmax); n++) //Loop through signal samples
    {
      for (int Tau = -ITDmax; Tau < ITDmax; Tau++) //Loop through all possible ITD values
      {
        Psi[Tau+ITDmax+1] = exp(-1.0/Tint)*Psi[Tau+ITDmax+1] + l_out[n]*r_out[n-Tau];
      }
    }
    
    // Find the index of the largest value
    int runningmaxindex = 0; 
    for (int m = 1; m < PsiSize; m++)
    {
      if (Psi[m] > Psi[runningmaxindex])
      {
        runningmaxindex = m;
      }
    }
    int I = runningmaxindex - ITDmax - 1;  //compute corresponding ITD in samples
    double alpha = asin(soundspeed*I/(Mdist*fs))*180/pi; //compute the azimuth in degrees corresponding to ITD 'I'
    if (alpha > -90 && alpha < 90)
    {
      alpha = alpha;
    }
    else
    {
      alpha = 99.99;
    }
    Serial1.print("!");
    sprintf(buf, "%+05.2g", alpha);
    Serial1.print("A:");
    Serial1.print(buf);
    Serial1.print("\r\n");
  }
}
