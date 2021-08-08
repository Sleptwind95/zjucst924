#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN        6
#define NUMPIXELS 40
int Rnum=0;
int Gnum=0;
int Bnum=0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 100

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();

   for(int i=39;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(Rnum, Gnum, Bnum));
    //pixels.setPixelColor(6, pixels.Color(Rnum, Gnum, Bnum));
    pixels.show();
    delay(DELAYVAL);
    Rnum=Rnum+1;
    Gnum=Gnum+1;
    Bnum=Bnum+1;
    
    if(i==NUMPIXELS-1)
    {
    i=-1;
    Rnum=0;
    Gnum=0;
    Bnum=0;
    pixels.clear();
    }
    
  }

}
