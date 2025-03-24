#include <Arduino.h>
#include <GfxUi.h>

GfxUi::GfxUi(Arduino_GFX* _gfx) {
  gfx = _gfx;
}

void GfxUi::drawCanva(
  int16_t x, int16_t y,
  int16_t w, int16_t h,
  int16_t r, uint16_t c) {
  gfx->drawRoundRect(x, y, w, h, r, c);
}

void GfxUi::getStringSize(const char* s, uint16_t* w, uint16_t* h) {
  int16_t x1, y1;
  gfx->getTextBounds(s, 0, 0, &x1, &y1, w, h);
}

uint16_t GfxUi::getStringWidth(const char* s) {
  int16_t x1, y1;
  uint16_t w, h;
  gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
  return w - 1;
}

uint16_t GfxUi::getStringHeight(const char* s) {
  int16_t x1, y1;
  uint16_t w, h;
  gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
  return h - 1;
}

int GfxUi::centerOf(int container, int content) {
  return (container / 2) - (content / 2);
}

void GfxUi::drawStringScope(int x, int y, const char* s) {
  int w = getStringWidth(s);
  int h = getStringHeight(s);

  gfx->fillRect(x, y - h, w, h, GREEN);

  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(x, y);
  gfx->println(s);

  gfx->drawLine(x, y, x + w, y, RED);
  gfx->drawLine(x, y, x, y - h, RED);
}

void GfxUi::drawTextCanva(int16_t x, int16_t y, int16_t r, const char* s, uint16_t tc, uint16_t bc) {
  int sw = getStringWidth(s);
  int sh = getStringHeight(s);

  int w = sw + (5 * 2);
  int h = sh + (5 * 2);

  gfx->drawRoundRect(x, y, w, h, r, bc);

  int tx = x + centerOf(w, sw);
  int ty = y + centerOf(h, sh) + sh;

  gfx->setTextSize(1);
  gfx->setTextColor(tc);
  gfx->setCursor(tx, ty);
  gfx->println(s);
}