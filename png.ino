//
// PNG encoder test sketch
// written by Larry Bank
//
// Creates a 128x128x8-bpp image 'on-the-fly' and
// compresses it as a PNG file. The image is a green square with an X in the middle
// on a transparent background
//
// This program can run as either a memory-to-memory test for measuring
// performance or can write the PNG file to a micro-SD card
// Disable the macro below (WRITE_TO_SD) to use only memory
//

#include "PNGenc.h"
PNG png;  // static instance of the PNG encoder lass

#define WIDTH 320
#define HEIGHT 240

// Memory to hold the output file
uint16_t pngOut[48000];

void pngEn(uint16_t *imgData) {
  int rc, iDataSize, x, y;
  //uint16_t imgLine[WIDTH];
  unsigned char pTempLine[WIDTH * 4];
  long l;
  char replyBuff[1024];
  int readCount = 0;

  l = micros();

  rc = png.open((uint8_t *)pngOut, sizeof(pngOut));

  if (rc == PNG_SUCCESS) {
    rc = png.encodeBegin(WIDTH, HEIGHT, PNG_PIXEL_TRUECOLOR, 24, NULL, 3);
    if (rc == PNG_SUCCESS) {
      for (int y = 0; y < HEIGHT && rc == PNG_SUCCESS; y++) {
        //imgData[y*width to y*width+width-1]
        //for (int x = 0; x < HEIGHT; x++)
        // *(imgLine + x) = *(imgData + x * HEIGHT + y);
        rc = png.addRGB565Line(imgData + y * WIDTH, pTempLine);
      }  // for y
      iDataSize = png.close();
      l = micros() - l;
      tft.printf("%d bytes  in %d us\n", iDataSize, (int)l);
      //PNG VERIFICATION
      //for (int x = 0; x < iDataSize; x++)
      //  Serial.write(*((unsigned char *)pngOut + x));
      size_t out_length;
      char *base64_data = base64_encode((unsigned char *)pngOut, iDataSize, &out_length);
      tft.printf("base64 length %d\n", out_length);
      delay(3000);
      tft.setCursor(10, 260);
      tft.fillRect(0, 260, 480, 80, ILI9488_BLACK);
      if (out_length != 0) {
        for (int x = 0; x < out_length; x++)

          Serial1.write(*(base64_data + x));

        while (1) {
          if (Serial1.available()) {
            replyBuff[readCount] = Serial1.read();
            if (replyBuff[readCount] == '\n') {
              break;
            }
            readCount++;
          }
        }

        for (int x = 0; x < readCount; x++)
          tft.print(replyBuff[x]);
      } else {
        tft.print("Encoding error");
      }
    }
    delay(3000);
    while (digitalRead(BUTTON_IN_PIN) == HIGH)
      ;
    delay(100);
    while (digitalRead(BUTTON_IN_PIN) == LOW)
      ;
    delay(100);
  } else {
    Serial.println("Failed to create the file on the SD card!");
  }
}