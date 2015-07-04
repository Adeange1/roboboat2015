// This program tests the communication between the Arduino Due and the Speedgoat.
// Created by Samantha Tropeano and Anderson Lebbad on 6/30/15

double alpha = 123.45; //arbitrary value to output
int inByte = 0;
int message = 0;

char buf[8], buf1[8];

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

}

void loop() {
  Serial.println("hello world");
  Serial1.println("hello world");
  delay(1000);

}
