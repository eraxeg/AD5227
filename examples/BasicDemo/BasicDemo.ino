#include "AD5227.h"

AD5227 pot(25, 27, 26); // CS=10, U/D=9, CLK=8

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Wiper to max");
  pot.setWiper(63);
  delay(500);
  Serial.println("Wiper to min");
  pot.setWiper(0);
  delay(500);
}
