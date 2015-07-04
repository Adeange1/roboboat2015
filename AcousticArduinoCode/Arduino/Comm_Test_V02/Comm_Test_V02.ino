// This program tests the communication between the Arduino Due and the Speedgoat.
// Created by Samantha Tropeano and Anderson Lebbad on 6/30/15

double alpha = 123.45; //arbitrary value to output
int inByte = 0;
int message = 0;

char buf[8];

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200,SERIAL_7E1);

}

void loop() {
  inByte = Serial1.read();
  if (inByte != -1) {
      //Serial1.print("!A:+123.450\r\n");
      if (inByte == 65) {
        message = 1;
      }
      if (inByte == 13) {
        message = 0;
      }
      if (message == 1) {
        Serial.println(inByte);
      }
  }

}
