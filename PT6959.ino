#include "Arduino.h"
#include <stdint.h>
#include <stdbool.h>
#include <SPI.h>

const char DISP[16] {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
const int slaveSelectPin = 20;

void setup() {
  pinMode (slaveSelectPin, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE2);

  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0x02);
  digitalWrite(slaveSelectPin, HIGH);

  //set to writing mode, auto incrament address after data write
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0x40);
  digitalWrite(slaveSelectPin, HIGH);

  //first clear 8 bytes of the display RAM
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0xC0);
  for (int i = 0; i < 8; i++) {
    SPI.transfer(0x00);
  }
  digitalWrite(slaveSelectPin, HIGH);

  //display on, max brightness
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0x8F);
  digitalWrite(slaveSelectPin, HIGH);

}

void loop() {

  //count through 0-9,a-f
  for (int i = 0; i < 16; i++) {
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(0xC0);
    SPI.transfer(DISP[i]);
    digitalWrite(slaveSelectPin, HIGH);
    delay(500);
  }

  for (int i = 0; i < 16; i++) {
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(0xC2);
    SPI.transfer(DISP[i] | 0x80);
    digitalWrite(slaveSelectPin, HIGH);
    delay(500);
  }

  for (int i = 0; i < 16; i++) {
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(0xC4);
    SPI.transfer(DISP[i]);
    digitalWrite(slaveSelectPin, HIGH);
    delay(500);
  }

  for (int i = 0; i < 16; i++) {
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(0xC6);
    SPI.transfer(DISP[i]);
    digitalWrite(slaveSelectPin, HIGH);
    delay(500);
  }

}
