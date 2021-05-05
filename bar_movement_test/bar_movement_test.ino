#include "BluetoothSerial.h"

// pixels headers and such
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
int BarSize = WallHeight/4;

// inititalize button input var.
char Choice;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 2000 // Time (in milliseconds) to pause between pixels

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// What this does + maybe descr of inputs
void rightBar(int top, int g=0, int r=255, int b=0){
  int ColArray[WallHeight];
  int colnum = WallWidth - 1; // column number of the bar's location
  
  // Storing all the led addresses in an array
  for(int k=0; k<=WallHeight; k+=2){
    ColArray[k+1] = (colnum+(k*WallWidth));
    ColArray[k] = ColArray[k+1]-(2*colnum+1);
  }
  
  // Turning the bar on
  for (int h=top; h>top-BarSize; h--){
    pixels.setPixelColor(ColArray[h], pixels.Color(g, r, b));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
}

// What this does + maybe descr of inputs
void leftBar(int top, int g=0, int r=255, int b=0){
  int ColArray[WallHeight];
  int colnum = 0; // Left bar is always at column 0
  
  // Storing all the led addresses in an array
  for(int k=0; k<=WallHeight; k+=2){
    ColArray[k+1] = (colnum+(k*WallWidth));
    ColArray[k] = ColArray[k+1]-(2*colnum+1);
  }
  
  // Turning the bar on
  for (int h=top; h>top-BarSize; h--){
    pixels.setPixelColor(ColArray[h], pixels.Color(g, r, b));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.    
}

void setup() {
pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

Serial.begin(115200);
SerialBT.begin("ESP32test2"); //Bluetooth device name
Serial.print("The device started, now you can pair it with bluetooth!");

// setup pixels 
} // end function


void loop() { 
  if (Serial.available()) { 
    Serial.read();
    }
  if (SerialBT.available()) {
    Choice = SerialBT.read();
    if (Choice == '1') {
      for (int up=((WallHeight/2)+2); up<=WallHeight; up++){
        leftBar(up);
      } 
    }
    if (Choice == '2') {
      for (int down=((WallHeight/2)+2); down>=0; down--){
        leftBar(down);
        } 
      }
   
    if (Choice == '3') {
      for (int upr=((WallHeight/2)+2); upr<=WallHeight; upr++){
        rightBar(upr);
      } 
    }
    
    if (Choice == '4') {
      for (int downr=((WallHeight/2)+2); downr>=0; downr--){
        rightBar(downr);
        } 
      }
  }
}
