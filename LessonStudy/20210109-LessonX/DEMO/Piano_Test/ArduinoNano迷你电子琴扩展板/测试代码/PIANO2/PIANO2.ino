#include "pitches.h"
#include <Adafruit_NeoPixel.h>
#define PIN 11
#define NUM_LEDS 8
#define BRIGHTNESS 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop() {
  if (digitalRead(8) == 0) {
    colorWipe(strip.Color(255, 0, 0, 0), 0);
    do {
      tone(10, NOTE_C5, 10);
    }
    while (digitalRead(8) == 0);
  }

  if (digitalRead(7) == 0) {
    colorWipe(strip.Color(255, 60, 0, 0), 0);
    do {
      tone(10, NOTE_D5, 10);
    }
    while (digitalRead(7) == 0);
  }
  if (digitalRead(6) == 0) {
    colorWipe(strip.Color(255, 200, 0, 0), 0);
    do {
      tone(10, NOTE_E5, 10);
    }
    while (digitalRead(6) == 0);
  }

  if (digitalRead(5) == 0) {
    colorWipe(strip.Color(0, 255, 0, 0), 0);
    do {
      tone(10, NOTE_F5, 10);
    }
    while (digitalRead(5) == 0);
  }

  if (digitalRead(4) == 0) {
    colorWipe(strip.Color(0, 255, 255, 0), 0);
    do {
      tone(10, NOTE_G5, 10);
    }
    while (digitalRead(4) == 0);
  }
  if (digitalRead(3) == 0) {
    colorWipe(strip.Color(0, 0, 255, 0), 0);
    do {
      tone(10, NOTE_A5, 10);
    }
    while (digitalRead(3) == 0);
  }
  if (digitalRead(2) == 0) {
    colorWipe(strip.Color(255, 0, 255, 0), 0);
    do {
      tone(10, NOTE_B5, 10);
    }
    while (digitalRead(2) == 0);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
