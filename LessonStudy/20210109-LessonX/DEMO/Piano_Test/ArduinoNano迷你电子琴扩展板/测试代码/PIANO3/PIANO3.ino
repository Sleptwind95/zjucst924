#include "pitches.h"
#include "U8glib.h"
#include <Adafruit_NeoPixel.h>
#define PIN 11
#define NUM_LEDS 8
#define BRIGHTNESS 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

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
  u8g.setFont(u8g_font_osb18);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  u8g.firstPage();
  do {
    u8g.setPrintPos(0, 0);
    u8g.print("Paino");
  } while ( u8g.nextPage() );
}

void loop() {
  if (digitalRead(8) == 1) {
    colorWipe(strip.Color(255, 0, 0, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(0, 45);
      u8g.print("C");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_C5, 50);
    }
    while (digitalRead(8) == 1);
  }

  if (digitalRead(7) == 1) {
    colorWipe(strip.Color(255, 60, 0, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(18, 45);
      u8g.print("D");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_D5, 50);
    }
    while (digitalRead(7) == 1);
  }
  if (digitalRead(6) == 1) {
    colorWipe(strip.Color(255, 200, 0, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(36, 45);
      u8g.print("E");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_E5, 50);
    }
    while (digitalRead(6) == 1);
  }

  if (digitalRead(5) == 1) {
    colorWipe(strip.Color(0, 255, 0, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(54, 45);
      u8g.print("F");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_F5, 50);
    }
    while (digitalRead(5) == 1);
  }

  if (digitalRead(4) == 1) {
    colorWipe(strip.Color(0, 255, 255, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(72, 45);
      u8g.print("G");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_G5, 50);
    }
    while (digitalRead(4) == 1);
  }
  if (digitalRead(3) == 1) {
    colorWipe(strip.Color(0, 0, 255, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(90, 45);
      u8g.print("A");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_A5, 50);
    }
    while (digitalRead(3) == 1);
  }
  if (digitalRead(2) == 1) {
    colorWipe(strip.Color(255, 0, 255, 0), 0);
    u8g.firstPage();
    do {
      u8g.setPrintPos(108, 45);
      u8g.print("B");
    } while ( u8g.nextPage() );
    do {
      tone(10, NOTE_B5, 50);
    }
    while (digitalRead(2) == 1);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
