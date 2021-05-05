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

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 2000 // Time (in milliseconds) to pause between pixels

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char Choice;
// inititalize button input var.

void setup() {
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
      pixels.setPixelColor(237, pixels.Color(255, 0, 0));
      pixels.show();
    }
    if (Choice == '2') {
      pixels.setPixelColor(212, pixels.Color(255, 0, 0));
      pixels.show();
    }
    } 
  delay(20); 
}
