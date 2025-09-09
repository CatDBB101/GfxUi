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

int GfxUi::calculateTextCanvaWidth(int fit_text_offset, const char* s) {
  return this->checkFitTextWidth(fit_text_offset, this->getStringWidth(s));
}

int GfxUi::calculateTextCanvaHeight(int fit_text_offset, const char* s) {
  return this->checkFitTextHeight(fit_text_offset, this->getStringHeight(s));
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

String GfxUi::b64BinString(const char* input) {
  String binaryResult = "";

  for (int i = 0; input[i] != '\0'; i++) {
    char c = input[i];

    // Skip newline characters
    if (c == '\n') {
      continue;
    }

    int value;

    // Convert base64 character to 6-bit value
    if (c >= 'A' && c <= 'Z') {
      value = c - 'A';  // A-Z: 0-25
    } else if (c >= 'a' && c <= 'z') {
      value = c - 'a' + 26;  // a-z: 26-51
    } else if (c >= '0' && c <= '9') {
      value = c - '0' + 52;  // 0-9: 52-61
    } else if (c == '+') {
      value = 62;
    } else if (c == '/') {
      value = 63;
    } else {
      // Skip invalid characters
      continue;
    }

    // Convert 6-bit value to binary string with leading zeros
    for (int bit = 5; bit >= 0; bit--) {
      if (value & (1 << bit)) {
        binaryResult += '1';
      } else {
        binaryResult += '0';
      }
    }
  }

  return binaryResult;
}

//* set up animation *//

void GfxUi::setAnimation(const char* _anim[], uint8_t _frameNumber) {
  for (int i = 0; i < _frameNumber; i++) {
    String bin = this->b64BinString(_anim[i]);
    this->anim[i] = strdup(bin.c_str());
  }
  // if (isColor) {
  //   this->initAnimColor(_anim, _frameNumber);
  // } else {
  //   this->initAnim(_anim, _frameNumber);
  // }
  this->stopAnimation = false;
  this->frameNumber = _frameNumber;

  this->frame = 0;
  this->lastTimer = 0;
}

void GfxUi::setAnimationDuration(int _duration) {
  this->duration = _duration;
}

//* black and white *//

void GfxUi::drawBitmap(int16_t x, int16_t y, const String bitmap, int16_t w, int16_t h, bool scaleX2) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  String binString = b64BinString(bitmap.c_str());

  // Serial.println(x);
  // Serial.println(y);
  // Serial.println(w);
  // Serial.println(h);
  // Serial.println(binString);

  int ix, iy;
  ix = 0;
  iy = 0;

  for (int i = 0; i < (w * h); i++) {
    // Serial.println(String(i) + " " + binString[i] + " " + (binString[i] == '1'));

    if (binString[i] == '1') {
      if (scaleX2) {
        int16_t dx = x + (ix * 2);
        int16_t dy = y + (iy * 2);

        gfx->fillRect(dx, dy, 2, 2, WHITE);
      } else {
        gfx->drawPixel(x + ix, y + iy, WHITE);
      }
    }

    ix++;
    if (ix >= w) {
      ix = 0;
      iy++;
    }
  }
}

void GfxUi::playSyncAnimation(int x, int y, int w, int h, bool scaleX2) {
  x = this->checkCenterWidth(x, scaleX2 ? w * 2 : w);
  y = this->checkCenterHeight(y, scaleX2 ? h * 2 : h);

  for (int f = 0; f < this->frameNumber; f++) {
    unsigned long frameStart = millis();
    // gfx->fillScreen(gfx->color565(0, 0, 0));
    const char* binString = this->anim[f];

    int ix, iy;
    ix = 0;
    iy = 0;

    for (int i = 0; i < (w * h); i++) {

      if (binString[i] == '1') {
        if (scaleX2) {
          int16_t dx = x + (ix * 2);
          int16_t dy = y + (iy * 2);

          gfx->fillRect(dx, dy, 2, 2, WHITE);
        } else {
          gfx->drawPixel(x + ix, y + iy, WHITE);
        }
      }

      ix++;
      if (ix >= w) {
        ix = 0;
        iy++;
      }
    }

    unsigned long frameTime = millis() - frameStart;
    if (frameTime < this->duration) {
      delay(this->duration - frameTime);
    }
  }
}

void GfxUi::playAsyncAnimation(int x, int y, int w, int h, bool scaleX2, bool clearScreen) {
  if (this->frame == -1) {
    // Serial.println("frame == -1");
    if (clearScreen) {
      gfx->fillScreen(gfx->color565(0, 0, 0));
    }
    this->frame++;
    return;
  }

  x = this->checkCenterWidth(x, scaleX2 ? w * 2 : w);
  y = this->checkCenterHeight(y, scaleX2 ? h * 2 : h);

  int ix, iy;
  ix = 0;
  iy = 0;

  // Serial.println("frame :" + String(this->frame));

  for (int i = 0; i < (w * h); i++) {

    if (this->anim[this->frame][i] == '1') {
      if (scaleX2) {
        int16_t dx = x + (ix * 2);
        int16_t dy = y + (iy * 2);

        gfx->fillRect(dx, dy, 2, 2, WHITE);
      } else {
        gfx->drawPixel(x + ix, y + iy, WHITE);
      }
    }

    ix++;
    if (ix >= w) {
      ix = 0;
      iy++;
    }
  }
  // this->drawBitmap(x, y, this->anim[this->frame], w, h, scaleX2);

  unsigned long past_time = millis() - this->lastTimer;

  // Serial.println("millis() : " + String(millis()));
  // Serial.println("past_time : " + String(past_time));
  // Serial.println("lastTimer : " + String(this->lastTimer));
  // Serial.println("duration : " + String(this->duration));
  // Serial.println("stop : " + String(this->stopAnimation));
  // Serial.println(past_time >= this->duration);
  // Serial.println("===============");

  if (past_time >= this->duration && !this->stopAnimation) {

    this->frame++;
    if (this->frame >= this->frameNumber) {
      this->frame = -1;
    }
    this->lastTimer = millis();
  }
}

//* color *//

void GfxUi::drawBitmapColor(int16_t x, int16_t y, const String bitmap, int16_t paletteIndex, int16_t w, int16_t h, bool scaleX2) {
  x = this->checkCenterWidth(x, w);
  y = this->checkCenterHeight(y, h);

  String binString = b64BinString(bitmap.c_str());

  int ix, iy;
  ix = 0;
  iy = 0;

  for (int i = 0; i < (w * (h * 2)); i += 2) {
    uint8_t colorIndex = ((binString[i] == '1') << 1) | (binString[i + 1] == '1');

    uint16_t color =
      this->COLOR_PALETTE[paletteIndex][colorIndex];

    if (scaleX2) {
      int16_t dx = x + (ix * 2);
      int16_t dy = y + (iy * 2);

      gfx->drawPixel(dx, dy, color);
      gfx->drawPixel(dx + 1, dy, color);
      gfx->drawPixel(dx, dy + 1, color);
      gfx->drawPixel(dx + 1, dy + 1, color);
    } else {
      gfx->drawPixel(x + ix, y + iy, color);
    }


    ix++;
    if (ix >= w) {
      ix = 0;
      iy++;
    }
  }
}

void GfxUi::playSyncAnimationColor(int x, int y, int w, int h, int16_t paletteIndex, bool scaleX2) {
  x = this->checkCenterWidth(x, scaleX2 ? w * 2 : w);
  y = this->checkCenterHeight(y, scaleX2 ? h * 2 : h);

  for (int f = 0; f < this->frameNumber; f++) {
    unsigned long frameStart = millis();

    // gfx->fillScreen(gfx->color565(0, 0, 0));

    int ix, iy;
    ix = 0;
    iy = 0;

    const char* binString = this->anim[f];

    for (int i = 0; i < (w * (h * 2)); i += 2) {
      uint8_t colorIndex = ((binString[i] == '1') << 1) | (binString[i + 1] == '1');

      // Serial.println(String(binString[i]) + " " + String(binString[i + 1]));

      uint16_t color =
        this->COLOR_PALETTE[paletteIndex][colorIndex];

      // Serial.println(color);

      if (scaleX2) {
        int16_t dx = x + (ix * 2);
        int16_t dy = y + (iy * 2);

        gfx->fillRect(dx, dy, 2, 2, color);
        // gfx->drawPixel(dx, dy, color);
        // gfx->drawPixel(dx + 1, dy, color);
        // gfx->drawPixel(dx, dy + 1, color);
        // gfx->drawPixel(dx + 1, dy + 1, color);
      } else {
        gfx->drawPixel(x + ix, y + iy, color);
      }


      ix++;
      if (ix >= w) {
        ix = 0;
        iy++;
      }
    }

    // this->drawBitmapColor(x, y, String(this->anim[i]), paletteIndex, w, h, scaleX2);
    unsigned long frameTime = millis() - frameStart;
    if (frameTime < this->duration) {
      delay(this->duration - frameTime);
    }
  }
}

void GfxUi::playAsyncAnimationColor(int x, int y, int w, int h, int16_t paletteIndex, bool scaleX2, bool clearScreen) {
  if (this->frame == -1) {
    // Serial.println("frame == -1");
    if (clearScreen) {
      gfx->fillScreen(gfx->color565(0, 0, 0));
    }
    this->frame++;
    return;
  }

  x = this->checkCenterWidth(x, scaleX2 ? w * 2 : w);
  y = this->checkCenterHeight(y, scaleX2 ? h * 2 : h);

  int ix, iy;
  ix = 0;
  iy = 0;

  // Serial.println("frame :" + String(this->frame));

  const char* binString = this->anim[this->frame];

  for (int i = 0; i < (w * (h * 2)); i += 2) {
    uint8_t colorIndex = ((binString[i] == '1') << 1) | (binString[i + 1] == '1');

    // Serial.println(String(binString[i]) + " " + String(binString[i + 1]));

    uint16_t color =
      this->COLOR_PALETTE[paletteIndex][colorIndex];

    // Serial.println(color);

    if (scaleX2) {
      int16_t dx = x + (ix * 2);
      int16_t dy = y + (iy * 2);

      gfx->fillRect(dx, dy, 2, 2, color);
      // gfx->drawPixel(dx, dy, color);
      // gfx->drawPixel(dx + 1, dy, color);
      // gfx->drawPixel(dx, dy + 1, color);
      // gfx->drawPixel(dx + 1, dy + 1, color);
    } else {
      gfx->drawPixel(x + ix, y + iy, color);
    }


    ix++;
    if (ix >= w) {
      ix = 0;
      iy++;
    }
  }

  unsigned long past_time = millis() - this->lastTimer;

  // Serial.println("millis() : " + String(millis()));
  // Serial.println("past_time : " + String(past_time));
  // Serial.println("lastTimer : " + String(this->lastTimer));
  // Serial.println("duration : " + String(this->duration));
  // Serial.println("stop : " + String(this->stopAnimation));
  // Serial.println("frame : " + String(this->frame));
  // Serial.println(past_time >= this->duration);
  // Serial.println("===============");

  if (past_time >= this->duration && !this->stopAnimation) {

    this->frame++;
    if (this->frame >= this->frameNumber) {
      this->frame = -1;
    }
    this->lastTimer = millis();
  }
}
