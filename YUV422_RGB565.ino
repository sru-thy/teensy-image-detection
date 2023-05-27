
// 5.6.1 RGB to YUV conversion matrix
// The color conversion matrix can be derived from the standard equations below:
// Y = 0.59G + 0.31R + 0.11B
// U = B - Y
// V = R - Y
// Cr = 0.713 (R - Y)
// Cb = 0.563 (B - Y)

uint16_t RGB888_RGB565(unsigned char R8, unsigned char G8, unsigned char B8) {
  uint16_t W16 = 0;
  // RGB 8:8:8 to RGB 5:6:5

  W16 = (R8 >> 3) << 11;  // top 5 bits of R into top 5 bits of W16
  W16 |= (G8 >> 2) << 5;  // top 6 bits of G into middle 6 bits of W16
  W16 |= (B8 >> 3);       // top 5 bits of B into lower 5 bits of W16
  return W16;
}

uint32_t convert_yuv_to_rgb_pixel(int y, int u, int v) {
  uint32_t pixel32 = 0;
  unsigned char *pixel = (unsigned char *)&pixel32;
  int r, g, b;
  r = y + (1.370705 * (v - 128));
  g = y - (0.698001 * (v - 128)) - (0.337633 * (u - 128));
  b = y + (1.732446 * (u - 128));
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;
  if (r < 0) r = 0;
  if (g < 0) g = 0;
  if (b < 0) b = 0;
  pixel[0] = r;
  pixel[1] = g;
  pixel[2] = b;
  return pixel32;
}
uint16_t getRGB565_from_YUV422(byte yuv)
{

}