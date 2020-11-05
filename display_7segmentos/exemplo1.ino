#include "LedControl.h"

const int PIN_DIN = 5;
const int PIN_CS = 6;
const int PIN_CLK = 7;

LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, 1);

void setup() {
  lc.shutdown(0, false); // desativar a economia de energia, ativa o display
  lc.setIntensity(0, 8); // define o nível de brilho (0 até 15)
  lc.clearDisplay(0);    // limpa a tela
}

void loop() {
  lc.setChar(0, 7, 'a', false);  // A
  lc.setChar(0, 6, 'b', false);  // b
  lc.setChar(0, 5, 'c', false);  // c
  lc.setChar(0, 4, 'd', false);  // d
  lc.setChar(0, 3, 'e', false);  // E
  lc.setChar(0, 2, 'f', false);  // F
  lc.setChar(0, 1, 'h', false);  // H
  lc.setChar(0, 0, 'l', false);  // L
  delay(2000);
  lc.clearDisplay(0);
  lc.setChar(0, 7, 'p', false);  // P
  lc.setChar(0, 6, '-', false);  // -
  lc.setChar(0, 5, '_', false);  // _
  lc.setChar(0, 4, '.', false);  // .
  lc.setChar(0, 3, '0', false);  // 0
  lc.setChar(0, 2, '1', false);  // 1
  lc.setChar(0, 1, '2', false);  // 2
  lc.setChar(0, 0, '3', false);  // 3
  delay(2000);
  lc.clearDisplay(0);
  lc.setChar(0, 7, '4', false);  // 4
  lc.setChar(0, 6, '5', false);  // 5
  lc.setChar(0, 5, '6', false);  // 6
  lc.setChar(0, 4, '7', false);  // 7
  lc.setChar(0, 3, '8', false);  // 8
  lc.setChar(0, 2, '9', false);  // 9
  lc.setRow(0, 1, 0x4E);         // C
  lc.setRow(0, 0, 0x5E);         // G
  delay(2000);
  lc.clearDisplay(0);
  lc.setRow(0, 7, 0x17);         // h
  lc.setRow(0, 6, 0x06);         // I
  lc.setRow(0, 5, 0x3C);         // J
  lc.setRow(0, 4, 0x15);         // n
  lc.setRow(0, 3, 0x1D);         // o
  lc.setRow(0, 2, 0x05);         // r
  lc.setRow(0, 1, 0x5B);         // S
  lc.setRow(0, 0, 0x0F);         // t
  delay(2000);
  lc.clearDisplay(0);
  lc.setRow(0, 7, 0x3E);         // U
  lc.setRow(0, 6, 0x1C);         // u
  lc.setRow(0, 5, 0x3B);         // y
  delay(2000);
  lc.clearDisplay(0);
}