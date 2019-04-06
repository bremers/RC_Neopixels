/* Used on 24/11/2015 on the Adafruit Trinket
ATTiny85 based mini microcontroller and a PNA4602 or TSOP38238 to
read an IR code and perform a function.  

This program includes five modes that are IR controlled for a NeoPixel ring. The individual modes are explained in the code.
Based on Adafruit tutorial http://learn.adafruit.com/ir-sensor/using-an-ir-sensor
and http://learn.adafruit.com/trinket-gemma-mini-theramin-music-maker
*/

#include <Adafruit_NeoPixel.h>
 
// We need to use the 'raw' pin reading methods because timing is very important here 
// and the digitalRead() procedure is slower!
#define IRpin_PIN  PINB // ATTiny85 had Port B pins
#define IRpin      2    // IR sensor - TSOP38238 on Pin GPIO #2 / D2
#define RingPin    1    // DConnects to Adafruit Neopixel Ring

#define MAXPULSE    5000  // the maximum pulse we'll listen for - 5 milliseconds 
#define NUMPULSES    100  // max IR pulse pairs to sample
#define RESOLUTION     2  // time between IR measurements
#define NumPixels      24 // number of pixels 
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, 1, NEO_GRB + NEO_KHZ800);
 
// we will store up to 40 pulse pairs (reduce if needed)
uint16_t pulses[40][2];    // pair is high and low pulse
uint16_t currentpulse = 0; // index for pulses we're storing
uint32_t irCode = 0;
uint16_t n;
 
void setup() {
  pinMode(IRpin, INPUT);       // Listen to IR receiver on Trinket pin D2
  pinMode(RingPin, OUTPUT);    // Output on Trinket pin D1
  strip.begin();
    cli();  // disables interrupts
    strip.show();  // generates the NeoPixel control signals
    sei();  // re-enables interrupts; // Initialize all pixels to 'off'
}
 
void loop() {
  
  irCode=listenForIR(); // Wait for an IR Code
 
  // Process the pulses to get our code
  for (int i = 0; i < 32; i++) {
    irCode=irCode<<1;
    if((pulses[i][0] * RESOLUTION)>0&&(pulses[i][0] * RESOLUTION)<500) {
      irCode|=0; 
    } else {
      irCode|=1;
    }
  

  }
  //ACTION ONE: TURNING WHITE TWICE ROUND THE CIRCLE, "STARTING ANIMATION"
  //PRESS BUTTON "1" *Note: white color updated to softer
  if(irCode==0xC03F403F)  {      // "1" on my remote
   colorWipe(strip.Color(56.25, 56.25, 45), 60); // White
   colorWipe(strip.Color(225, 250, 180), 60); // White
   colorWipe(strip.Color(56.25, 56.25, 45), 60); // White
   colorWipe(strip.Color(225, 250, 180), 60); // White
   strip.show();
  } 
 
   //ACTION TWO: LIGHT BEIGE, THIS ONE SHOULD REPEAT "INFINITELY" UNTIL OTHER BUTTON IS PRESSED
   //PRESS BUTTON "2"
   //IMPORTANT: to change speed, change max int i value in code since i increases at constant rate
  if(irCode==0xC03F601F)  {      // "2" on my remote
    for (int i = 0 ; i < 51; i++)  {    
      colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1); // Skin Color
     }
    for (int i = 51 ; i >-1; i--)  {
      colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1);
     }
         delay(30);
    for (int i = 0 ; i < 51; i++)  {    
      colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1); // Skin Color
     }
    for (int i = 51 ; i >-1; i--)  {
      colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1);
     } 
   }
  
      
   //ACTION THREE: FADING RED, THIS ONE SHOULD REPEAT "INFINITELY" UNTIL OTHER BUTTON IS PRESSED
   //PRESS BUTTON "3"
   //IMPORTANT: to change speed, change max int i value in code since i increases at constant rate
  if(irCode==0xC03F502F)  {      // "3" on my remote
    for (int i = 0 ; i < 51; i++)  {    
      colorWipe(strip.Color((5*i), (0.1*i), (0)), 1); // Full red
     }
    for (int i = 51 ; i >-1; i--)  {
      colorWipe(strip.Color((5*i), (0.1*i), (0)), 1);
     }
         delay(30);
    for (int i = 0 ; i < 51; i++)  {    
      colorWipe(strip.Color((5*i), (0.1*i), (0)), 1); // Full red
     }
    for (int i = 51 ; i >-1; i--)  {
      colorWipe(strip.Color((5*i), (0.1*i), (0)), 1);
     }
  } 
    
 
   //ACTION FOUR: WIPE TO FULL WHITE AND STAY WHITE
   //PRESS BUTTON "4"
  if(irCode==0xC03F4837)  {      // "4" on my remote
    for (int i = 0 ; i < 51; i++)  {    
      colorWipe(strip.Color((5*i), (4.65*i), (3.8*i)), 1); // White
       strip.show();
     }
    } 
    
    
   //ACTION FIVE: ALL LEDS OFF
   //PRESS BUTTON "5"
  if(irCode==0xC03F6817)  {      // "5" on my remote
      colorWipe(strip.Color(0,0,0), 1); // BLACK
       strip.show();
    }

   //ACTION SIX: LIGHT BEIGE INFINITELY FOR EXHIBITION PURPOSES
   //PRESS BUTTON "6"
   //IMPORTANT: to change speed, change max int i value in code since i increases at constant rate
  if(irCode==0xC03F5827)  {      // "6" on my remote
    while(irCode==0xC03F5827) {
      for (int i = 0 ; i < 51; i++)  {    
      	colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1); // Skin Color
      }
      for (int i = 51 ; i >-1; i--)  {
      	colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1);
      }
      delay(30);
      for (int i = 0 ; i < 51; i++)  {    
        colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1); // Skin Color
      }
      for (int i = 51 ; i >-1; i--)  {
        colorWipe(strip.Color((5*i), (1.96078431*i), (0.39215686*i)), 1);
      } 
    }
  }
 
  
   //ACTION SEVEN: RAINBOW MODE "INFINITELY" FOR EXHIBITION PURPOSES
   //PRESS BUTTON "7"
  if(irCode==0xC03F443B)  {      // "4" on my remote
    rainbowCycle(15); // White
  } 
}

uint16_t listenForIR() {  // IR receive code
  currentpulse = 0;
  while (1) {
   unsigned int highpulse, lowpulse;  // temporary storage timing
   highpulse = lowpulse = 0; // start out with no pulse length 
  
   while (IRpin_PIN & _BV(IRpin)) { // got a high pulse
      highpulse++; 
      delayMicroseconds(RESOLUTION);
      if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
        return currentpulse; 
      }
   }
   pulses[currentpulse][0] = highpulse;
 
   while (! (IRpin_PIN & _BV(IRpin))) { // got a low pulse
      lowpulse++; 
      delayMicroseconds(RESOLUTION);
      if (((lowpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
        return currentpulse; 
      }
   }
   pulses[currentpulse][1] = lowpulse;
   currentpulse++;
  }
}


//FUNCTIONS DEFINED BELOW HERE
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
