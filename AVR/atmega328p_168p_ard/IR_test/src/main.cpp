
#include <Arduino.h>

// #define CLK 2
// #define LATCH 3
// #define CS 4
// #define MOSI 5
// #define MISO 6

// uint16_t b = 0xffff;
// uint16_t res_old = 0;

// void setup() {
//   pinMode(CLK, OUTPUT);
//   pinMode(LATCH, OUTPUT);
//   pinMode(CS, OUTPUT);
//   pinMode(MOSI, OUTPUT);
//   pinMode(MISO, INPUT);
  
//   Serial.begin(9600);

//   digitalWrite(CS, LOW);
// }

// void loop() {
//   // uint16_t res = b;
//   // // uint16_t read_res = 0;
//   // for(uint8_t i = 0; i < 16; i++){
//   //   digitalWrite(MOSI, res & 0x0001);
//   //   digitalWrite(CLK, HIGH);
//   //   digitalWrite(CLK, LOW);
//   //   res = res >> 1;
//   //   delay(10);
//   // }
//   // digitalWrite(LATCH, HIGH);
//   // digitalWrite(LATCH, LOW);
//   // delay(1000);
//   // b = b >> 1;

//   // uint16_t res = 0;
//   // digitalWrite(LATCH, LOW);
//   // delay(10);
//   // digitalWrite(LATCH, HIGH);
//   // for(uint8_t i = 0; i < 16; i++){
//   //   res += digitalRead(MISO);
//   //   digitalWrite(CLK, HIGH);
//   //   digitalWrite(CLK, LOW);
//   //   res = i < 15 ? res << 1 : res;
//   //   delay(5);
//   // }
//   // // if (res_old != res)  
//   //   Serial.println(res, BIN);
//   // delay(200);
//   // // res_old = res;
// }


void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(10);
}