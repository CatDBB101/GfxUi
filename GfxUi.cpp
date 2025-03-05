#include <Arduino.h>
#include <GfxUi.h>

GfxUi::GfxUi(Arduino_GFX* _gfx, int _fontWidth, int _fontHeight) {
  gfx = _gfx;
  fontWidth = _fontWidth;
  fontHeight = _fontHeight;
}

void GfxUi::drawCanva(
  int16_t x, int16_t y,
  int16_t w, int16_t h,
  int16_t r, uint16_t c) {
  gfx->drawRoundRect(x, y, w, h, r, c);
}

int GfxUi::strWidth(const char* s) {
  return strlen(s) * fontWidth;
}

int GfxUi::strHeight(const char* s) {
  return strlen(s) * fontHeight;
}