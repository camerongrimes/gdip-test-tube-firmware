#include <Arduino.h>

//Pin connected to ST_CP of 74HC595
#define STCP_pin 13
//Pin connected to SH_CP of 74HC595
#define SHCP_pin 14
////Pin connected to DS of 74HC595
#define DS_pin 10

#define CLEAR 0b11111111

// Define the patterns for each digit (0-9)
const byte digitPatterns[] = {
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};


// Define the patterns for each letter (A-R, excluding Q)
const byte letterPatterns[] = {
  0b10001000,  // A
  0b10000011,  // B
  0b11000110,  // C
  0b10100001,  // D
  0b10000110,  // E
  0b10001110,  // F
  0b10010000,  // G
  0b10001001,  // H
  0b11111001,  // I
  0b11110001,  // J
  0b10001001,  // K
  0b11000111,  // L
  0b10010001,  // M
  0b10010011,  // N
  0b11000000,  // O
  0b10001100,  // P
  0b10010100   // R
  // Patterns for S to Z can be added if needed
};



void sevenseg_initialise(void)
{
  pinMode(DS_pin,  OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
}


void shiftOutMSBF(byte data) {
  for (int i = 7; i >= 0; --i) {
    digitalWrite(DS_pin, (data >> i) & 1);
    digitalWrite(SHCP_pin, LOW);
    delayMicroseconds(1);  // Adjust delay if needed
    digitalWrite(SHCP_pin, HIGH);
    delayMicroseconds(1);  // Adjust delay if needed
  }
}

void sevenseg_display_number(int number) {
  if (number >= 0 && number <= 9) {
    byte pattern = digitPatterns[number];

    digitalWrite(STCP_pin, LOW);
    shiftOutMSBF(pattern);
    digitalWrite(STCP_pin, HIGH);
  }
}


void sevenseg_display_char(char character)
{
  if (character >= 'A' && character <= 'R') {
    byte pattern = letterPatterns[character - 'A'];

    digitalWrite(STCP_pin, LOW);
    shiftOutMSBF(pattern);
    digitalWrite(STCP_pin, HIGH);
  }
}

void sevenseg_clear(void)
{
    digitalWrite(STCP_pin, LOW);
    shiftOutMSBF(CLEAR);
    digitalWrite(STCP_pin, HIGH);
}




