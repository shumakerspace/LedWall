#include "BluetoothSerial.h"

// pixels headers and such
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 23 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 2000 // Popular NeoPixel wall size

// define the led  xwall size
#define WallWidth 40
#define WallHeight 50
int WallSize = WallWidth*WallHeight;
int BarSize = WallHeight/5;

// positioning info
int leftPos;
int rightPos;
int ballPosCol;
int ballPosRow;
bool ballDirLR; //ball direction left/right, 0 = left and 1 = right
bool ballDirUD; //ball direction up/down, 0 = up and 1 = down

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 2000 // Time (in milliseconds) to pause between pixels

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void gameOver(){
   
   for (int j=0; j<4; j++){
     for(int i=0; i<2000; i++){
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      }
      pixels.show();
      delay(500);
      pixels.clear();
      delay(500);
     }
  }

void updateBallPos(){
  int newRow = 0; 
  int newCol = 0;
  // calculating the new position of the ball
  if (ballDirLR == 0){newCol=ballPosCol-1;} else {newCol=ballPosCol+1;}
  if (ballDirUD == 0){newRow=ballPosRow+1;} else {newRow=ballPosRow-1;}

  //testing if we are bouncing off the top or bottom
  if (newRow < 0){ ballDirUD = 0; newRow=ballPosRow+1; }
  if (newRow > WallHeight){ ballDirUD = 1; newRow=ballPosRow-1;}
  
  //testing if we are bouncing off the left or right
  /* BOUNCING MODE - NO GAME OVER
  if (newCol < 0){ ballDirLR = 1; newCol=ballPosCol+1; }
  if (newCol > WallWidth){ ballDirLR = 0; newCol=ballPosCol-1;}
  */
  if (newCol < 0){ 
    gameOver();
    ballPosRow = WallHeight/2;
    ballPosCol = WallWidth/2;
  } else if (newCol >= WallWidth){ 
      gameOver();
      ballPosRow = WallHeight/2;
      ballPosCol = WallWidth/2;
  } else {
    ballPosCol = newCol;
    ballPosRow = newRow;
  }

}
  

void drawBall(int col, int row){
  int start;
  int i = 0;
  int ballArray[WallHeight];
  start = col*WallHeight;
  for(int n=start; n<start+WallHeight; n++){
    ballArray[i]=n; 
    i++;
  }

  if(col % 2 == 0){
    pixels.setPixelColor(ballArray[row], pixels.Color(0, 0, 255));
  } else {
    pixels.setPixelColor(ballArray[WallHeight-row], pixels.Color(0, 0, 255));
  }
}

void myNewCol(int colnum, int g=0, int r=0, int b=255){
  // calculate starting point of the column
  int start;
  start = colnum*WallHeight;
    for(int n=start; n<start+WallHeight; n++){
      pixels.setPixelColor(n, pixels.Color(g, r, b));
    }
}

void myNewRow(int rownum, int g=0, int r=255, int b=0){
  // calculate starting point of the odd columns
    for(int k=0; k<=WallHeight; k+=2){
  int go,go2; 
    go = (rownum+(k*WallHeight));
    go2 = go-(2*rownum+1);
    pixels.setPixelColor(go, pixels.Color(g, r, b));
    if(go2>0){
      pixels.setPixelColor(go2, pixels.Color(g, r, b));
    }
  }
}


/*
// What this does + maybe descr of inputs
void ballStart(int i=237, int g=0, int r=0, int b=255){
  
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(g, r, b));

    pixels.show();   // Send the updated pixel colors to the hardware.

  int ColArray[WallHeight];
  int colnum = WallWidth/2; // column number of the bar's location
  
    // Storing all the led addresses in an array
    for(int k=0; k<=WallHeight; k+=2){
      ColArray[k+1] = (colnum+(k*WallWidth));
      ColArray[k] = ColArray[k+1]-(2*colnum+1);
      }
  
  // Turning the bar on
  for (int h=top; h=WallHeight/2){
    pixels.setPixelColor(ColArray[h], pixels.Color(g, r, b));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
}
*/

// What this does + maybe descr of inputs
void rightBar(int top, int g=0, int r=255, int b=0){
  int rightArray[WallHeight];
  int col = WallWidth - 1;
  int start = col*WallHeight;
  int i= 0;
  for(int n=start; n<start+WallHeight; n++){
    rightArray[i]=n; 
    i++;
  }

  if(col % 2 == 0){
  // Turning the bar on
    for (int h=top; h>top-BarSize; h--){
      pixels.setPixelColor(rightArray[h], pixels.Color(g, r, b));
    }
  } else {
    for (int h=top; h>top-BarSize; h--){
      pixels.setPixelColor(rightArray[WallHeight-h], pixels.Color(g, r, b));
    }
  }

/*
  int rightArray[WallHeight];
  int colnum = WallWidth - 1; // column number of the bar's location
  
  // Storing all the led addresses in an array
  for(int k=0; k<=WallHeight; k+=2){
    rightArray[k+1] = (colnum+(k*WallWidth));
    rightArray[k] = rightArray[k+1]-(2*colnum+1);
  }
*/

}

// What this does + maybe descr of inputs
void leftBar(int top, int g=0, int r=255, int b=0){
  int leftArray[WallHeight];
  int col = 0;
  int start = col*WallHeight;
  int i= 0;
  for(int n=start; n<start+WallHeight; n++){
    leftArray[i]=n; 
    i++;
  }

  if(col % 2 == 0){
  // Turning the bar on
    for (int h=top; h>top-BarSize; h--){
      pixels.setPixelColor(leftArray[h], pixels.Color(g, r, b));
    }
  } else {
    for (int h=top; h>top-BarSize; h--){
      pixels.setPixelColor(leftArray[WallHeight-h], pixels.Color(g, r, b));
    }
   }
}

void setup() {
pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

Serial.begin(115200);
SerialBT.begin("ESP32test2"); //Bluetooth device name
Serial.print("The device started, now you can pair it with bluetooth!");

// Start positions
leftPos = (WallHeight/2)+2;
rightPos = (WallHeight/2)+2;
ballPosCol = WallHeight/2;
ballPosRow = WallWidth/2;

} // end setup

// Update the bar position based on BT user input via ArduinoBlueControl
void updateBarPos(){
  // inititalize button input var.
  char Choice;
  
  if (SerialBT.available()) {
      Choice = SerialBT.read();
  } else {
    return;
  }

  switch(Choice){
      case '1': // up left
        if (leftPos < WallHeight) { leftPos++; }
        break;
      case '2': // down right
        if (rightPos > BarSize) { rightPos--; }
        break;
      case '3': // up right
        if (rightPos < WallHeight) { rightPos++; }
        break;
      case '4': // down left
        if (leftPos > BarSize) { leftPos--; }
        break;
  }
} // end updatePos

void loop() { 

//ledCycle();

pixels.clear(); // clears the whole screen
updateBarPos(); // updates bar positions based on BT user input
updateBallPos();
leftBar(leftPos); // draws left bar
rightBar(rightPos); // draws right bar
drawBall(ballPosCol, ballPosRow);
pixels.show();   // Send the updated pixel colors to the hardware.    
delay(500);
}
