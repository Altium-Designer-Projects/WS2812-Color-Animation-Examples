/* fill_grad
 *
 * By: Andrew Tuline
 *
 * Date: August, 2015
 *
 * Here's a simple method to blend between a couple of colours across a strand of LED's.
 *
 * It uses FastLED's:
 *
 * - fill_gradient() function to blend between two colours.
 * - beatsin8() to provide a time based smooth varying input to blend().
 *
 * An issue when using the fill_gradient is which way you want the gradient to sweep around the colour wheel. Options are:
 *
 * FORWARD_HUES: hue always goes clockwise
 * BACKWARD_HUES: hue always goes counter-clockwise
 * SHORTEST_HUES: hue goes whichever way is shortest and is the DEFAULT
 * LONGEST_HUES: hue goes whichever way is longest
 *
 * When the start and end colours are animated, the sweep will flip in the other direction at certain points, thus causing a disruption of the smooth gradient.
 * 
 * This routine demonstrates one method to animate the start/end hues and to ensure the fill_gradient remains consistently smooth.
 *
 */

#include "FastLED.h"                              
#define DATA_PIN   8
#define NUM_LEDS   64 

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

void setup(){
 Serial.begin(9600);                               
 FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
 FastLED.setMaxPowerInVoltsAndMilliamps(5,500);               // This is used by the power management functionality and is currently set at 5V, 500mA.
 FastLED.setBrightness(255);
} 

void loop(){
  
  Gradient();
  
}

void Gradient(){
 uint8_t starthue = beatsin8(5, 0, 255);
 uint8_t endhue = beatsin8(7, 0, 255);
 if(starthue < endhue){
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the colour fill will flip around. 
 }else{
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
 }
 FastLED.show();  
}
