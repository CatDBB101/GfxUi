#include <Arduino.h>
#include <GfxUi.h>

GfxUi::GfxUi(Arduino_GFX *_gfx) {
  gfx = _gfx;
}

void GfxUi::begin() {
  Serial.println("Hello, World!");
  // gfx->setTextColor(0xFFFF);
  gfx->setTextSize(2);
  gfx->setCursor(20, 20);
  gfx->println(String("Hello, World!"));
}