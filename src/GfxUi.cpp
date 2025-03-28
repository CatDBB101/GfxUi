#include <Arduino.h>
#include <GfxUi.h>

GfxUi::GfxUi(Arduino_GFX* _gfx) {
  gfx = _gfx;
}

//* calculation function *//

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

int GfxUi::checkCenterWidth(int offset, int w) {
  if (offset == CENTER) {
    return this->centerOf(gfx->width(), w);
  } else {
    return offset;
  }
}

int GfxUi::checkCenterHeight(int offset, int w) {
  if (offset == CENTER) {
    return this->centerOf(gfx->height(), w);
  } else {
    return offset;
  }
}

int GfxUi::checkFitTextWidth(int offset, int str_w) {
  if (offset == FIT_TEXT) {
    return str_w + (5 * 2);
  } else {
    return offset;
  }
}

int GfxUi::checkFitTextHeight(int offset, int str_h) {
  if (offset == FIT_TEXT) {
    return str_h + (5 * 2);
  } else {
    return offset;
  }
}

//* draw function  *//

void GfxUi::drawCanva(
  int16_t x, int16_t y,
  int16_t w, int16_t h,
  int16_t r, uint16_t c) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);
  gfx->drawRoundRect(x, y, w, h, r, c);
}

void GfxUi::drawStringScope(int x, int y, const char* s) {
  int w = getStringWidth(s);
  int h = getStringHeight(s);

  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  gfx->fillRect(x, y - h, w, h, GREEN);

  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(x, y);
  gfx->println(s);

  gfx->drawLine(x, y, x + w, y, RED);
  gfx->drawLine(x, y, x, y - h, RED);
}

void GfxUi::drawTextCanva(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const char* s, uint16_t tc, uint16_t bc) {
  int sw = getStringWidth(s);
  int sh = getStringHeight(s);

  w = this->checkFitTextWidth(w, sw);
  h = this->checkFitTextHeight(h, sh);

  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  gfx->drawRoundRect(x, y, w, h, r, bc);

  int tx = x + centerOf(w, sw);
  int ty = y + centerOf(h, sh) + sh;

  gfx->setTextSize(1);
  gfx->setTextColor(tc);
  gfx->setCursor(tx - 1, ty - 1);
  gfx->println(s);
}

void GfxUi::drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h, float value, int16_t r, uint16_t c) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  gfx->drawRoundRect(x, y, w, h, r, c);

  int w2 = (value / 100) * (w - (2 * 2));
  int h2 = h - (2 * 2);

  gfx->fillRect(x + 2, y + 2, w2, h2, c);
}

void GfxUi::drawScrollBar(int16_t x, int16_t y, int16_t w, int16_t h, int stepNumber, int step, int16_t r, uint16_t c) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  gfx->drawRoundRect(x, y, w, h, r, c);

  int w2 = w - (2 * 2);
  int h2 = (h - (2 * 2)) / stepNumber;
  int x2 = x + 2;
  int y2 = (y + 2) + (h2 * step);

  gfx->fillRect(x2, y2, w2, h2, c);
}

void GfxUi::drawBitmap(int16_t x, int16_t y, const uint16_t* bitmap, int16_t w, int16_t h, uint16_t c) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  int16_t i, j;
  uint16_t pixel;

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      pixel = bitmap[i + j * w];
      if (pixel != c) {
        gfx->drawPixel(x + i, y + j, pixel);
      }
    }
  }
}

void GfxUi::drawBitmapX2(int16_t x, int16_t y, const uint16_t* bitmap, int16_t w, int16_t h, uint16_t c) {
  x = this->checkCenterWidth(x, w * 2);
  y = this->checkCenterHeight(y, h * 2);

  uint16_t pixel;

  for (int16_t j = 0; j < h; j++) {
    for (int16_t i = 0; i < w; i++) {
      pixel = bitmap[i + j * w];
      if (pixel != c) {
        // Draw each pixel as 2x2 block
        int16_t dx = x + (i * 2);
        int16_t dy = y + (j * 2);
        gfx->drawPixel(dx, dy, pixel);
        gfx->drawPixel(dx + 1, dy, pixel);
        gfx->drawPixel(dx, dy + 1, pixel);
        gfx->drawPixel(dx + 1, dy + 1, pixel);
      }
    }
  }
}