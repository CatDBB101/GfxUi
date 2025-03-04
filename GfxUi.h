#include "Arduino_GFX.h"

class GfxUi {
public:
  GfxUi(Arduino_GFX *gfx);
  void begin();
private:
  Arduino_GFX *gfx;
};