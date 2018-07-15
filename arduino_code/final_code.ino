#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

const int buttonPin1 = 4; // the number of the pushbutton pin
int buttonState1 = 0; // variable for reading the pushbutton status
boolean buttonOne = 0;

const int buttonPin2 = 5; // the number of the pushbutton pin
int buttonState2 = 0; // variable for reading the pushbutton status
boolean buttonTwo = 0;

const int buttonPin3 = 7; // the number of the pushbutton pin
int buttonState3 = 0; // variable for reading the pushbutton status
boolean buttonThree = 0;

const int buttonPin4 = 8; // the number of the pushbutton pin
int buttonState4 = 0; // variable for reading the pushbutton status
boolean buttonFour = 0;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);

  pinMode(buttonPin1, INPUT);     
  digitalWrite(buttonPin1, HIGH); // initiate the internal pull up resistor
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 == LOW) 
  {
   Serial.println("button 1 pressed") ;
   buttonOne = 1;
  }

  pinMode(buttonPin2, INPUT);     
  digitalWrite(buttonPin2, HIGH); // initiate the internal pull up resistor
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 == LOW) 
  {
   Serial.println("button 2 pressed") ;
   buttonTwo = 1;
  }

  pinMode(buttonPin3, INPUT);     
  digitalWrite(buttonPin3, HIGH); // initiate the internal pull up resistor
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState3 == LOW) 
  {
   Serial.println("button 3 pressed") ;
   buttonThree = 1;
  }

  pinMode(buttonPin4, INPUT);     
  digitalWrite(buttonPin4, HIGH); // initiate the internal pull up resistor
  buttonState4 = digitalRead(buttonPin4);
  if (buttonState4 == LOW) 
  {
   Serial.println("button 4 pressed") ;
   buttonFour = 1;
  }

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Slightly different, this makes the rainbow equally distributed throughout
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

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void loop() {
  if (buttonOne == 1)
  {
    theaterChaseRainbow(50);
    Serial.println("buttonOne is 1");
  }
  if (buttonTwo == 1)
  {
    rainbow(20);
    Serial.println("buttonTwo is 1");
  }
    
  if (buttonThree == 1)
  {
    colorWipe(strip.Color(0, 0, 255), 20); // Blue
    Serial.println("buttonThree is 1");
  }

  if (buttonFour == 1)
  {
    rainbowCycle(20);
    Serial.println("buttonFour is 1");
  }

}
