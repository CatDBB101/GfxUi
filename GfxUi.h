#include "Arduino_GFX.h"

class GfxUi {
public:
  GfxUi(Arduino_GFX* gfx, int fontWidth, int fontHeight);
  void drawCanva(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c);
  int strWidth(const char* s);
  int strHeight(const char* s);
private:
  Arduino_GFX* gfx;
  int fontWidth;
  int fontHeight;
};