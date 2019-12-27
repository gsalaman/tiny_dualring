/*===========================================================
 * Dual Ring LED Client 
 * 
 * Excercise 1:  your first fill!
 * Tweaked for Tiny
 */

#include <Adafruit_NeoPixel.h>

// Which pin to use for DualRingLED control
#define LED_PIN    4
#define NUMPIXELS 40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB+NEO_KHZ800);

/*===============================================================================
 * Function:  rotateDownHelper
 *
 * Since the LEDs can be wired arbitrarily (is increasing the index going clockwise
 * or counter-clockwise), I'm gonna make these helpers just go "up" for increasing array
 * and "down" for decreasing array.  We can then map to clockwise and counter-clockwise
 * with the real rotate functions.
 */
void rotateDownHelper( Adafruit_NeoPixel *strip, int start_index, int num )
{
    uint32_t roll_over_value;
    int i;
    
    // this is basically just gonna be a big shift with roll-over.
    
    // remember the "0th" value...it's gonna go into the "last" array value.
    roll_over_value = strip->getPixelColor(start_index);
    
    // now copy everything one slot "down"
    for (i=0; i< num -1; i++)
    {
        //start_led[i] = start_led[i+1];
        strip->setPixelColor(i+start_index, (strip->getPixelColor(i+start_index+1)));
    }
    
    // Finally, store the last LED with that roll-over value.
    //start_led[num - 1] = roll_over_value;
    strip->setPixelColor(start_index + num-1, roll_over_value);
    
}  // end of rotateDownHelper

/*===============================================================================
 * Function:  rotateUpHelper
 *
 * Since the LEDs can be wired arbitrarily (is increasing the index going clockwise
 * or counter-clockwise), I'm gonna make these helpers just go "up" for increasing array
 * and "down" for decreasing array.  We can then map to clockwise and counter-clockwise
 * with the real rotate functions.
 */
void rotateUpHelper( Adafruit_NeoPixel *strip, int start_led, int num )
{
    uint32_t roll_over_value;
    int i;
    
    // this is basically just gonna be a big shift with roll-over.
    
    // remember the "last" value...it's gonna go into the "first" array value.
    //roll_over_value = start_led[num - 1];
    roll_over_value = strip->getPixelColor(start_led + num - 1);
    
    // now copy everything one slot "up"
    for (i = num - 1; i > 0; i--)
    {
        //start_led[i] = start_led[i-1];
        strip->setPixelColor(start_led + i, strip->getPixelColor(start_led + i - 1));
    }
    
    // Finally, store the first LED with that roll-over value.
    //start_led[0] = roll_over_value;
    strip->setPixelColor(start_led, roll_over_value);
    
}  // end of rotate_down_helper


void setup()
{
    int i;
    uint32_t led_color=0xFF;
    
    pixels.begin();

    for (i=0; i<NUMPIXELS; i++)
    {
      pixels.setPixelColor(i,led_color);
      delay(500);
      pixels.show();
    }

    delay(1000);
    pixels.setPixelColor(0,0xFF0000);
    pixels.setPixelColor(16,0x00FF00);
}

void loop()
{
  int loop_delay_ms=100;

  rotateUpHelper(&pixels, 0, 16);
  rotateDownHelper(&pixels, 16, 24);
  pixels.show();
  delay(loop_delay_ms);
}
