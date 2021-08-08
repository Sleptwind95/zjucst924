#include "pitches.h"
#include "U8glib.h"
#include <Adafruit_NeoPixel.h>
#include "LinkedList.h"
#define PIN_PIANO 11
#define BRIGHTNESS 6
#define NUM_LEDS 7
#define PIN_PIXELS 13
#define NUMPIXELS 56
#define DELAYVAL 10

#define WIDTH 7
#define HEIGHT 8



Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_PIANO, NEO_GRBW + NEO_KHZ800);
// Adafruit_NeoPixel strip(NUM_LEDS, PIN_PIANO, NEO_GRB + NEO_KHZ800);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

const int notations[] = {
  1, 1, 5, 5, 6, 6, 5,
  4, 4, 3, 3, 2, 2, 1,
  5, 5, 4, 4, 3, 3, 2,
  5, 5, 4, 4, 3, 3, 2,
  1, 1, 5, 5, 6, 6, 5,
  4, 4, 3, 3, 2, 2, 1
};
LinkedList<int> tasks = LinkedList<int>();

bool isPracticing = false;

//const int lineColors[HEIGHT][3] = {
//  {46, 68, 243},
//  {71, 148, 255},
//  {91, 255, 253},
//  {210, 173, 255},
//  {245, 45, 255},
//  {255, 61, 97},
//  {255, 179, 90},
//  {255, 235, 74}
//};

//const int lineColors[HEIGHT][3] = {
//  {11, 17, 61},
//  {18, 37, 64},
//  {23, 64, 63},
//  {52, 43, 64},
//  {61, 11, 64},
//  {64, 15, 24},
//  {64, 45, 22},
//  {64, 59, 18}
//};

const int lineColors[HEIGHT][3] = {
  {64, 79, 8},
  {64, 55, 12},
  {74, 15, 24},
  {99, 11, 54},
  {90, 43, 54},
  {23, 74, 63},
  {18, 37, 64},
  {11, 17, 91}
};

  const int pianoColors[7][3] = {
    {255, 0, 0},
    {255, 60, 0},
    {255, 200, 0},
    {0, 255, 0},
    {0, 255, 255},
    {0, 0, 255},
    {255, 0, 255}
  };

LinkedList<int> records = LinkedList<int>();
int lastIndex = -1;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
  pixels.setBrightness(36);

  for(int i = 0; i < 8; i++){
    records.add(-1);
  }

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
  // pinMode(12, INPUT);
  u8g.setFont(u8g_font_osb18);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();
  u8g.firstPage();
  do {
    u8g.setPrintPos(0, 0);
    u8g.print("Piano");
  } while ( u8g.nextPage() );

  Serial.begin(9600);

  if(isPracticing){
    initializeTasks();
  }
}

void loop() {

  const String pitches[] = {
    "C", "D", "E", "F", "G" , "A", "B"
  };

  const int pitchValues[] = {
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5
  };

  if(digitalRead(9)==1){
    isPracticing = !isPracticing;
    pixels.clear();
    strip.clear();
    if(isPracticing){
      initializeTasks();
    }else{
      records = LinkedList<int>();
      for(int i = 0; i < 8; i++){
        records.add(-1);
      }
    }
  }

  int index = -1;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(8 - i) == 1) {
      index = i;
    }
  }

  if(index >= 0){
    // Serial.println(index);
    // colorWipe(strip.Color(pianoColors[index][0], pianoColors[index][1], pianoColors[index][2], 0), 0);
    u8g.firstPage();
    do {
       u8g.setPrintPos(18*index, 45);
       u8g.print(pitches[index]);
    } while ( u8g.nextPage() );
    do {
      tone(10, pitchValues[index], 50);
    }
    while (digitalRead(8 - index) == 1);

    if(isPracticing){
      updateTasks(index);
    }else{
      update(index);
    }
  }
  
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void update(int index) {
  strip.clear();
  strip.setPixelColor(index, strip.Color(pianoColors[index][0], pianoColors[index][1], pianoColors[index][2]));
  strip.show();
  pixels.clear();
  records.add(index);
  if (records.size() > 8) {
    records.shift();
  }
  for (int i = 0; i < records.size(); i++) {
    int value = records.get(i);
    if(value >= 0){
      pixels.setPixelColor(value * HEIGHT + (WIDTH - i), pixels.Color(lineColors[7 - i][0], lineColors[7 - i][1], lineColors[7 - i][2]));
    }
  }
  pixels.show();

}

void initializeTasks(){
  tasks = LinkedList<int>();
  for(int i = 0; i < 8; i++){
    tasks.add(0); 
  }
  for(int i = 0; i < sizeof(notations)/2; i++){
    tasks.add(notations[i]);
  }
  updateTasks(-1);
  for(int i = 0; i < 7; i++){
    updateTasks(-1);
    delay(500);
  }
}

void updateTasks(int index){
    if(tasks.size() > 0 && index == tasks.get(0)-1){
      tasks.shift();
      
      int nextIndex = tasks.get(0)-1;
      strip.clear();
      strip.setPixelColor(nextIndex, strip.Color(pianoColors[nextIndex][0], pianoColors[nextIndex][1], pianoColors[nextIndex][2]));
      strip.show();
      
      pixels.clear();
      for (int i = 0; i < 8; i++) {
        int value = tasks.get(i)-1;

        if(value >= 0){
          pixels.setPixelColor(value * HEIGHT + i, pixels.Color(lineColors[i][0], lineColors[i][1], lineColors[i][2]));
        }
      }
      pixels.show();
     
    } 
    if(tasks.size()==0){
      showHeart();  
    }
}

void showHeart(){
  int Rnum=40;
  int Gnum=0;
  int Bnum=20;
  pixels.setPixelColor(15, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(23, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(39, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(47, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(6, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(14, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(22, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(30, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(38, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(46, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(54, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(5, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(13, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(21, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(29, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(37, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(45, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(53, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(4, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(12, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(20, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(28, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(36, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(44, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(52, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(11, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(19, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(27, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(35, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(43, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(10, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(18, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(26, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(34, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(42, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(17, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(25, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(33, pixels.Color(Rnum, Gnum, Bnum));
  pixels.setPixelColor(24, pixels.Color(Rnum, Gnum, Bnum));
  pixels.show();
}
