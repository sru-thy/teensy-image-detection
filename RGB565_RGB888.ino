void RGB565_to_RGB888(byte R5, byte G6, byte B5, byte *R8, byte *G8, byte *B8)
{
  *R8 = ( R5 * 527 + 23 ) >> 6;
  *G8 = ( G6 * 259 + 33 ) >> 6;
  *B8 = ( B5 * 527 + 23 ) >> 6;
}
