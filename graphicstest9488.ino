/***************************************************
  This is our GFX example for the Adafruit ILI9488 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include "SPI.h"
#include "ILI9488_t3.h"

#define TFT_RST A17
#define TFT_LED 8
#define TFT_DC 31
#define TFT_CS 36
#define BUTTON_OUT_PIN 8
#define BUTTON_IN_PIN 7

bool captureImage = false;

int camAddr = -1;

ILI9488_t3 tft = ILI9488_t3(&SPI, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  //SPISettings settingsA(16000000, MSBFIRST, SPI_MODE1);
  pinMode(BUTTON_IN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_OUT_PIN, OUTPUT);
  digitalWrite(BUTTON_OUT_PIN, LOW);
  //pinMode(TFT_LED, OUTPUT);
  //digitalWrite(TFT_LED, HIGH);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9488_BLACK);
  tft.setCursor(30, 10);
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_RED);
  tft.println("INITIALISING....");

  tft.println("AI Learning tool");
  delay(1000);
  tft.setTextColor(ILI9488_GREEN);

  tft.println("initialising camera....");
  initcam();
  delay(100);

  do {
    camAddr = detectcam();
    tft.setCursor(30, 130);
    if (camAddr != -1) {
      tft.print("camera found at ");
      tft.print("0X");
      tft.println(camAddr, HEX);
    } else {
      tft.println("camera not found");
    }

  } while (camAddr == -1);
  camcapture();
  delay(3000);
  tft.useFrameBuffer(true);
}

void loop(void) {
  if (digitalRead(BUTTON_IN_PIN) == LOW) {
    // Button is pressed, capture an image
    captureImage = true;
    delay(100);  // Delay for button debouncing
    tft.setCursor(10, 260);
    tft.useFrameBuffer(false);
    tft.print("Capturing..");
    delay(1000);
    tft.useFrameBuffer(true);
  }
  camcapture_loop();
}
