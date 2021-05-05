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

// What this does + maybe descr of inputs
void myLeftBar(int top, int g=0, int r=255, int b=0){
  int go,go2;
  int colValues[5];
  int colnum = 0; // Left bar is always at column 0
  
  // For each duple of a column, we calculate the ledNumber
  for(int k=0; k<=WallHeight; k+=2){
    go = (colnum+(k*WallWidth));
    go2 = go-(2*colnum+1);

    // FIFO storage of the led values to keep the last five (the bar itself)    
    colValues[4] = colValues[2];
    colValues[3] = colValues[1];
    colValues[2] = colValues[0];
    colValues[1] = go2;
    colValues[0] = go;

    // DEBUG: Dsiplaying the current led Numbers stored (last 5 normally)
    Serial.print("Print Array: [");
    for (int s=0; s<=4; s++){
     Serial.print(colValues[s]);
     Serial.print(", ");
    }
    Serial.println("]");

    // If we have reached the "top", then we stop searching
    if(go2 == top or go == top){ break; }
    
  }// End for each led until reached "top" 

  //adding an array to keep track of all the values of go and go2
  // int allValues[] = {};
  //adding an array to keep track of the 5 leds that will light up
  // int lineValues[5] = {};
  //hard coding the point 250 as the start point
  //extract the next 4 values after 250 from the allValues array to light up utilizing the lineValues array

  // Displaying the ledNumbers of the last 5 leds, that should correspond to the bar itself
  for (int h=0; h<=4; h++){
    pixels.setPixelColor(colValues[h], pixels.Color(g, r, b));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
    
}

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);
}

void loop() {
/*
// SNAKE
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright purple color:
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
  pixels.clear(); // Set all pixel colors to 'off'
*/

/*
// ROW Animation
for(int a=0; a<WallHeight; a++){
  myrow(a);
    pixels.show();   // Send the updated pixel colors to the hardware.
    pixels.clear(); // Set all pixel colors to 'off'
  }
*/

/*
// COLUMNS Animation
for(int b=0; b<WallWidth;){
    mycolumn(b);
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
*/

// Draws a bar topped at the value in parameter
myLeftBar(250);
delay(5000);
}
