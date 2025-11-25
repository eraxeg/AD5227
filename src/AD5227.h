/*
  AD5227.h - Arduino library for controlling the AD5227 digital potentiometer
  Created by Erik Axel Eggeling, 2025.
  License: MIT

  This library allows software SPI control of the AD5227:
    - Step the wiper up or down
    - Set wiper to an absolute position (0-63)
  
  Hardware SPI support to be added.
*/


#ifndef AD5227_H
#define AD5227_H

#include <Arduino.h>

class AD5227 {
public:
    AD5227(uint8_t slaveSelect, uint8_t udPin, uint8_t clkPin) 
        : _ss(slaveSelect), _ud(udPin), _clk(clkPin) {
        pinMode(_ss, OUTPUT);
        pinMode(_clk, OUTPUT);
        pinMode(_ud, OUTPUT);

        digitalWrite(_ss, HIGH);   // CS inactive
        digitalWrite(_clk, LOW);   // CLK idle low
        digitalWrite(_ud, LOW);    // default direction
    }

/**
 * @brief Steps the wiper up (increases Rwb)
 */
    void stepUp() {
        setUD(HIGH);   // U/D HIGH = step up
        pulseClock();
    }

/**
 * @brief Steps the wiper down (decreases Rwb)
 */
    void stepDown() {
        setUD(LOW);    // U/D LOW = step down
        pulseClock();
    }

/**
 * @brief Sets the wiper to an absolute step (0-63)
 * @param targetStep Desired wiper position
 */
    void setWiper(uint8_t targetStep) {
        if(targetStep > 63) targetStep = 63; // clamp
        int8_t diff = targetStep - 32; // AD5227 powers up at midscale
        if(diff > 0) {
            setUD(HIGH);
            for(int i = 0; i < diff; i++) pulseClock();
        } else if(diff < 0) {
            setUD(LOW);
            for(int i = 0; i < -diff; i++) pulseClock();
        }
    }

private:
    uint8_t _ss;
    uint8_t _ud;
    uint8_t _clk;

    void setUD(uint8_t value) {
        digitalWrite(_ud, value);
    }

    void pulseClock() {
        digitalWrite(_ss, LOW);      // enable device
        digitalWrite(_clk, HIGH);    
        delayMicroseconds(1);        // min pulse width 10 ns
        digitalWrite(_clk, LOW);
        delayMicroseconds(1);
        digitalWrite(_ss, HIGH);     // disable device
    }
};

#endif
