#include "Arduino.h"
void setup() {

  S5020B_INIT();
}

void loop() {

  speaker_wirte_cmd(6);//5
  while (!digitalRead(34));
  speaker_wirte_cmd(0xfe);
  speaker_wirte_cmd(5);//4
  while (!digitalRead(34));
  speaker_wirte_cmd(0xfe);
  speaker_wirte_cmd(2);//1
  while (!digitalRead(34));
  speaker_wirte_cmd(0xfe);
  speaker_wirte_cmd(7);//6
  while (!digitalRead(34));
  speaker_wirte_cmd(0xfe);
  speaker_wirte_cmd(9);//8
  while (!digitalRead(34));
  speaker_wirte_cmd(0xfe);
  delay(3000);

}

void S5020B_INIT() {
  pinMode(35, OUTPUT);
  pinMode(34, INPUT);
  digitalWrite(35, HIGH);
}

void send_cmd(byte data) {
  byte i;
  digitalWrite(35, LOW);
  delay(5);
  for (i = 0; i < 8; i++) {
    digitalWrite(35, HIGH);
    if (data & 0x01) {
      delayMicroseconds(1500);
      digitalWrite(35, LOW);
      delayMicroseconds(500);
    } else {
      delayMicroseconds(500);
      digitalWrite(35, LOW);
      delayMicroseconds(1500);
    }
    data >>= 1;
  }
  digitalWrite(35, HIGH);
  delay(50);
}
