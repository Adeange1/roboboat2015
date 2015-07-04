// This program uses code from the .ino file "Binaural_Source_Localization_V03" to test the communication between the Arduino Due and the Speedgoat.
// Created by Samantha Tropeano on 6/30/15

double alpha = 123.45; //arbitrary value to output

char buf[8];

void setup() {
  
  Serial3.begin(115200);
    
  Serial3.print("!");
  sprintf(buf, "%+08.3g", alpha);
  Serial3.print("A:");
  Serial3.print(buf);
  Serial3.print("\r\n");
  }
