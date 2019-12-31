/*===========================================================
 * Dual Ring LED 
 * 
 * Porting to tiny!!!
 */

#include <Adafruit_NeoPixel.h>

// Which pin to use for DualRingLED control
#define LED_PIN    4
#define NUMPIXELS  40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB+NEO_KHZ800);

#define COLOR_RED     0xFF0000
#define COLOR_GREEN   0x00FF00
#define COLOR_BLUE    0x0000FF
#define COLOR_MAGENTA 0xFF00FF
#define COLOR_YELLOW  0xFFFF00
#define COLOR_CYAN    0x00FFFF
#define COLOR_BLACK   0
#define COLOR_WHITE   0xFFFFFF

/*================================================================================
 * LIBRARY FUNCITONS
 *===============================================================================*/
 
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

void fillGradient(Adafruit_NeoPixel *strip, int start_index, uint32_t start_color, int end_index, uint32_t end_color)
{
  int i;
  
  uint32_t start_red;
  uint32_t end_red;
  uint32_t start_green;
  uint32_t end_green;
  uint32_t start_blue;
  uint32_t end_blue;

  int red_step;
  int green_step;
  int blue_step;

  int num_steps = end_index - start_index;

  start_red = start_color & 0xFF0000;
  start_red = start_red >> 16;
  start_green = start_color & 0x00FF00;
  start_green = start_green >> 8;
  start_blue = start_color & 0x0000FF;

  end_red = end_color & 0xFF0000;
  end_red = end_red >> 16;
  end_green = end_color & 0x00FF00;
  end_green = end_green >> 8;
  end_blue = end_color & 0x0000FF;

  red_step = end_red - start_red;
  green_step = end_green - start_green;
  blue_step = end_blue - start_blue;

  #if 0
  Serial.print("Num steps: ");
  Serial.println(num_steps);
  Serial.print("r/g/b step: ");
  Serial.print(red_step);
  Serial.print(" ");
  Serial.print(green_step);
  Serial.print(" ");
  Serial.println(blue_step);
  #endif

  
  for (i = 0; i <= num_steps; i++)
  {
    #if 0
    Serial.print("i=");
    Serial.print(i);
    Serial.print(", r:");
    Serial.print(start_red+ ((i*red_step)/num_steps));
    Serial.print(" b:");
    Serial.println(start_blue + ((i*blue_step)/num_steps));
    #endif
    
    strip->setPixelColor(start_index + i, 
                         start_red + ((i*red_step)/num_steps),
                         start_green + ((i*green_step)/num_steps),
                         start_blue + ((i*blue_step)/num_steps));
  }

}

/*================================================================================
 * fillAll
 */
void fillAll( uint32_t color )
{
  int i;

  for (i=0; i<NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, color);
  }
}

/*================================================================================
 * fillInner
 */
void fillInner( uint32_t color )
{
  int i;

  for (i=0; i<16; i++)
  {
    pixels.setPixelColor(i, color);
  }
}

/*================================================================================
 * fillOuter
 */
void fillOuter( uint32_t color )
{
  int i;

  for (i=16; i<40; i++)
  {
    pixels.setPixelColor(i, color);
  }
}

/*================================================================================
 * rotateInnerClockwise
 */
 void rotateInnerClockwise( void )
 {
   rotateDownHelper(&pixels, 0, 16);
 }

/*================================================================================
 * rotateInnerCounterClockwise
 */
 void rotateInnerCounterClockwise( void )
 {
   rotateUpHelper(&pixels, 0, 16);
 }

 
/*================================================================================
 * rotateOuterClockwise
 */
 void rotateOuterClockwise( void )
 {
   rotateUpHelper(&pixels, 16, 24);
 }

/*================================================================================
 * rotateOuterCounterClockwise
 */
void rotateOuterCounterClockwise( void )
{
  rotateDownHelper(&pixels, 16, 24);
}

void makeInnerClockwiseStreak( int streakSize, uint32_t background, uint32_t head)
{
  if (streakSize > 16) streakSize = 16;
  fillInner(background);

  fillGradient(&pixels, 0, head, streakSize, background);
}
 
void makeInnerCounterClockwiseStreak( int streakSize, uint32_t background, uint32_t head)
{
  if (streakSize > 16) streakSize = 16;
  fillInner(background);

  fillGradient(&pixels, 0, background, streakSize, head);
}

void makeOuterClockwiseStreak( int streakSize, uint32_t background, uint32_t head)
{
  if (streakSize > 24) streakSize = 24;
  fillOuter(background);

  fillGradient(&pixels, 16, background, 16+streakSize, head);
}
 
void makeOuterCounterClockwiseStreak( int streakSize, uint32_t background, uint32_t head)
{
  if (streakSize > 24) streakSize = 24;
  fillOuter(background);

  fillGradient(&pixels, 16, head, 16+streakSize, background);
}

/*================================================================================
 * END LIBRARY FUNCITONS
 *===============================================================================*/

void setup()
{
    int i;
    uint32_t led_color=0xFF;

    //Serial.begin(9600);
    
    pixels.begin();

    for (i=0; i<NUMPIXELS; i++)
    {
      pixels.setPixelColor(i,led_color);
      delay(50);
      pixels.show();
    }
    delay(100);

    makeInnerCounterClockwiseStreak(5,COLOR_GREEN,COLOR_RED);
    makeOuterCounterClockwiseStreak(10,COLOR_BLUE,COLOR_RED);
    pixels.show();
    delay(1000);
}

void loop()
{
  int loop_delay_ms=100;

  rotateInnerCounterClockwise();
  rotateOuterCounterClockwise();
  pixels.show();
  delay(loop_delay_ms);
}
