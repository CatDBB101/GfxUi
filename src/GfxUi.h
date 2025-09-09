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

  String b64BinString(const char* input);

  //* animation setup *//
  void setAnimation(const char* _anim[], uint8_t _frameNumber);
  void setAnimationDuration(int _duration);

  //* black and white *//
  void drawBitmap(int16_t x, int16_t y, const String bitmap, int16_t w, int16_t h, bool scaleX2);
  void playSyncAnimation(int x, int y, int w, int h, bool scaleX2);
  void playAsyncAnimation(int x, int y, int w, int h, bool scaleX2, bool clearScreen);

  //* color *//
  void drawBitmapColor(int16_t x, int16_t y, const String bitmap, int16_t paletteIndex, int16_t w, int16_t h, bool scaleX2);
  void playSyncAnimationColor(int x, int y, int w, int h, int16_t paletteIndex, bool scaleX2);
  void playAsyncAnimationColor(int x, int y, int w, int h, int16_t paletteIndex, bool scaleX2, bool clearScreen);

  const char* anim[10];
  uint8_t frameNumber;
  int pixelNumber;
  int duration;
  int frame;
  bool stopAnimation = false;

  const uint16_t COLOR_PALETTE[6][4] = {
    // Palette 0: Grayscale
    {
      57083,
      40179,
      25356,
      8452,
    },

    // Palette 1: Blues/Teals
    { 331, 753, 1495, 40892 },

    // Palette 2: Greens
    { 46643, 36079, 25482, 12740 },

    // Palette 3: Browns
    { 52525, 39751, 25158, 12612 },

    // Palette 4: Muted colors
    { 56985, 42484, 31858, 21326 },

    // Palette 5: Red with grays
    { 63752, 46551, 29647, 12743 }
  };
private:
  Arduino_GFX* gfx;
  unsigned long lastTimer;
};