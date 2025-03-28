#include "Arduino_GFX.h"

#define CENTER 256
#define FIT_TEXT 256
#define TRANS 0x680c
#define TRANSPARENT 0x680c

class GfxUi {
public:
  GfxUi(Arduino_GFX* gfx);

  //* calculation function *//
  void getStringSize(const char* s, uint16_t* w, uint16_t* h);
  uint16_t getStringWidth(const char* s);
  uint16_t getStringHeight(const char* s);
  int centerOf(int container, int content);
  int checkCenterWidth(int offset, int w);
  int checkCenterHeight(int offset, int w);
  int checkFitTextWidth(int offset, int str_w);
  int checkFitTextHeight(int offset, int str_h);
  int calculateTextCanvaWidth(int fit_text_offset, const char* s);
  int calculateTextCanvaHeight(int fit_text_offset, const char* s);

  //* draw funciton *//
  void drawStringScope(int x, int y, const char* s);
  void drawCanva(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c);
  void drawTextCanva(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, const char* s, uint16_t tc, uint16_t bc);
  void drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h, float value, int16_t r, uint16_t c);
  void drawScrollBar(int16_t x, int16_t y, int16_t w, int16_t h, int stepNumber, int step, int16_t r, uint16_t c);
  void drawBitmap(int16_t x, int16_t y, const uint16_t* bitmap, int16_t w, int16_t h, uint16_t c);
  void drawBitmapX2(int16_t x, int16_t y, const uint16_t* bitmap, int16_t w, int16_t h, uint16_t c);
private:
  Arduino_GFX* gfx;
};