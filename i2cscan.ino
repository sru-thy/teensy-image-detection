#include <Wire.h>
// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 2000000;
const int ledChannel = 0;
const int resolution = 8;


int detectcam() {

  for (byte i = 0; i < 255; i++) {

    tft.fillRect(30, 100, 100, 22, 0);
    tft.setCursor(30, 100);
    tft.print("0X");
    tft.print(i, HEX);
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      return i;
    }
    // delay (1);
  }
  return -1;
}
