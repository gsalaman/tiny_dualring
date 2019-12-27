/*===========================================================
 * Dual Ring LED Client 
 * 
 * Excercise 1:  your first fill!
 * Tweaked for Tiny
 */

#include <Adafruit_NeoPixel.h>

// Which pin to use for DualRingLED control
#define LED_PIN    0
#define NUMPIXELS 40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB+NEO_KHZ800);

void setup()
{
  int i;
  
    pixels.begin();

    for (i=0; i<NUMPIXELS; i++)
    {
      pixels.setPixelColor(i,pixels.Color(0,0,128));
      delay(500);
      pixels.show();
    }
    
}

void loop()
{
    
}
