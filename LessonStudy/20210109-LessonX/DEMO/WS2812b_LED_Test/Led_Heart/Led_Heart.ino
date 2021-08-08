#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        12
#define NUMPIXELS 55
int Rnum=0;
int Gnum=100;
int Bnum=200;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 10

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.setPixelColor(15, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(23, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(39, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(47, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(6, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(14, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(22, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(30, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(38, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(46, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(54, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(5, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(13, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(21, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(29, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(37, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(45, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(53, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(4, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(12, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(20, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(28, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(36, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(44, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(52, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(11, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(19, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(27, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(35, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(43, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(10, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(18, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(26, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(34, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(42, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(17, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(25, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(33, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(24, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
  delay(DELAYVAL);
  ChangeLED();
}
void ChangeLED()
{
  Rnum=Rnum+45;
  Gnum=Gnum+105;
  Bnum=Bnum-55;
}
