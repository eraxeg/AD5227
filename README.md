# AD5227 Arduino Library

An Arduino library for controlling the Analog Devices AD5227 64-step digital potentiometer using software SPI.  

Note that hardware SPI support is not implemented yet.

---

## Usage example

```
#include <AD5227.h>

// CS = 10, U/D = 9, CLK = 8
AD5227 pot(10, 9, 8);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Step up
  pot.stepUp();
  delay(500);

  // Step down
  pot.stepDown();
  delay(500);

  // Set to absolute wiper position (0-63)
  pot.setWiper(48);
  delay(1000);
}
```