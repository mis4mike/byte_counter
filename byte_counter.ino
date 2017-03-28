// Program to drive a dotstar LED array based on accelerometer readings

//Debugging memory library
#include <MemoryFree.h>

#define  DEBUG  0    

// Libraries for Dotstar
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 8 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    3
#define CLOCKPIN   4

// Here are the colors:
#define DARK 0x000000
#define RED 0x00FF00
#define ORANGE 0x00FF91
#define YELLOW 0x00FFFB
#define GREEN 0x0000FF
#define BLUE 0xFF0000
#define TEAL 0xFF00FF
#define VIOLET 0xFFAA00
#define WHITE 0xFFFFFF
#define DIM_WHITE 0x010101

#define NUMCOLORS 8

uint32_t colors[NUMCOLORS]={RED,ORANGE,YELLOW,GREEN,TEAL, BLUE,VIOLET,WHITE};
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);


uint32_t color = 0x888888;      // 'On' color

uint8_t counter = 0;
int colorCounter = 0;

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  setStripColor(ORANGE);
  color = BLUE;

  //rainbowsForever();
  
}

void loop() {
  
  //setThisManyLEDs(int(NUMPIXELS * (freeMemory() / 2048.0)));
  //if(colorCounter >= NUMCOLORS) {
  //  colorCounter = 0;
  //}
  color = colors[colorCounter];
  setStripBinary(counter);
  delay(1000);
  counter++;
  colorCounter++;
}

void setStripBinary (uint8_t number) {
 for (int i = 0; i <= NUMPIXELS; i++) {
  if(bitRead(number, i) == 1) {
   strip.setPixelColor(i, colors[i]);
  } else {
    strip.setPixelColor(i, DARK);
  }
 } 
 strip.show();
}

void setStripColor (uint32_t setColor) {
    for(int i = 0; i < 30; i++) {
      strip.setPixelColor(i, setColor);
    }  
    strip.show();
}

void setThisManyLEDs(int numLEDs) {
  if(numLEDs >= NUMPIXELS) {
    numLEDs = 5;
  }
  
  setStripColor(DARK);
  for(int i = 0; i < numLEDs; i++) {
    strip.setPixelColor(i, color);
  }  
  strip.show();
}

uint32_t pickRainbowColor (float num) {
  if(num < 0.25) {
    return DIM_WHITE; 
  }
  if(num < 0.375) {
    return RED;
  }
  if(num < 0.50) {
    return ORANGE;
  }
  if(num < 0.625) {
    return YELLOW;
  }
  if(num < 0.75) {
    return GREEN;
  }
  if(num < 0.875) {
    return BLUE;
  }
  return VIOLET;  
}
void rainbowCycle () {
  setStripColor(RED);
  delay(200);
  setStripColor(ORANGE);
  delay(200);
  setStripColor(YELLOW);
  delay(200);
  setStripColor(GREEN);
  delay(200);
  setStripColor(BLUE);
  delay(200);
  setStripColor(VIOLET);
  delay(200);
  
}

void rainbowsForever() {
  while(1) {
    rainbowCycle();
  }
}

