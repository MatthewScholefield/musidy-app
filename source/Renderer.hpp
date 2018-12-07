#pragma once

#include <SDL_video.h>
#include <SDL_render.h>
#include "SdlWindow.hpp"

struct Color {
  Color(int r, int g, int b, int a = 255) :
      r(uint8_t(r)), g(uint8_t(g)), b(uint8_t(b)), a(uint8_t(a)) {}

  uint8_t r, g, b, a = 255;
};

class Renderer {
public:
  explicit Renderer(SdlWindow &window);

  void begin(Uint8 r, Uint8 g, Uint8 b);
  void finish();
  void rect(float x, float y, float width, float height, const Color &color);

  double getDelta();

private:
  int tx(float x) {
    return int(x * window.getWidth());
  }

  int ty(float y) {
    return int(y * window.getHeight());
  }

  SDL_Renderer *renderer;
  uint64_t lastTickTime;
  double delta = 0.0;
  SdlWindow &window;
};
