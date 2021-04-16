#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        4 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 500 // Popular NeoPixel wall size

// define the led  xwall size
#define WallWidth 25
#define WallHeight 20
int WallSize = WallWidth*WallHeight;

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 2000 // Time (in milliseconds) to pause between pixels


void myrow(int rownum, int g=0, int r=0, int b=255){
  // calculate starting point of the row
  int start;
  start = rownum*WallWidth;
    for(int n=start; n<start+WallWidth; n++){
      
      pixels.setPixelColor(n, pixels.Color(g, r, b));
      }
}

void mycolumn(int colnum, int g=0, int r=255, int b=0){
  // calculate starting point of the odd columns
    for(int k=0; k<=WallHeight; k+=2){
  int go,go2; 
    go = (colnum+(k*WallWidth));
    go2 = go-(2*colnum+1);
    pixels.setPixelColor(go, pixels.Color(g, r, b));
    if(go2>0){
      pixels.setPixelColor(go2, pixels.Color(g, r, b));
    }
    

      /*go = 0;
      go = ((WallWidth+(k*WallHeight))-(2*WallWidth+1));
      pixels.setPixelColor(k, pixels.Color(g, r, b)); */
      }
}

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'
/*
  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright purple color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));

    pixels.show();   // Send the updated pixel colors to the hardware.
    
    
 
  }
*/

pixels.clear(); // Set all pixel colors to 'off'

for(int a=0; a<WallHeight; a++){
  
  myrow(a);
    pixels.show();   // Send the updated pixel colors to the hardware.
    pixels.clear(); // Set all pixel colors to 'off'
  }

for(int b=0; b<WallWidth; b++){
  
  mycolumn(b);
    pixels.show();   // Send the updated pixel colors to the hardware.
    pixels.clear(); // Set all pixel colors to 'off'
  }
/*
for(int c=0; c<WallWidth; c++){
  
  mycolumn2(c);
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
  */
}
