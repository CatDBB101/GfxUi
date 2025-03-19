#include "Arduino_GFX.h"

class GfxUi {
public:
  GfxUi(Arduino_GFX* gfx);
  void getStringSize(const char* s, uint16_t* w, uint16_t* h);
  uint16_t getStringWidth(const char* s);
  uint16_t getStringHeight(const char* s);
  int centerOf(int container, int content, int offset);
  void drawStringScope(int x, int y, const char* s);
  void drawCanva(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c);
private:
  Arduino_GFX* gfx;
};