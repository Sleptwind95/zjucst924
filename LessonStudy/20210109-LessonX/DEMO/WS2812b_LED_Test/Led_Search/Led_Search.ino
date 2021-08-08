#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        11
#define NUMPIXELS 7

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(5, 0 ,0,0));
  pixels.show();
  pixels.setPixelColor(1, pixels.Color(0, 5 ,0,0));
  pixels.show();
  pixels.setPixelColor(2, pixels.Color(0, 0 ,5,0));
  pixels.show();
  pixels.setPixelColor(3, pixels.Color(0, 0 ,0,5));
  pixels.show();
  pixels.setPixelColor(4, pixels.Color(5, 5 ,0,0));
  pixels.show();
  pixels.setPixelColor(5, pixels.Color(0, 5 ,5,0));
  pixels.show();
  pixels.setPixelColor(6, pixels.Color(0, 0 ,5,5));
  pixels.show();
}
