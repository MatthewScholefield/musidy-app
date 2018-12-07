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
  explicit Renderer(SdlWindow &window) :
  renderer_(SDL_CreateRenderer(window.GetRaw(), -1, SDL_RENDERER_ACCELERATED)), window_(window) {
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
  }

  void Begin(Uint8 r, Uint8 g, Uint8 b);
  void End();
  void Rect(float x, float y, float width, float height, const Color &color);

  double GetDelta();

private:
  int tx(float x) {
    return int(x * window_.GetWidth());
  }

  int ty(float y) {
    return int(y * window_.GetHeight());
  }

  SDL_Renderer *renderer_;
  uint64_t last_tick_time_ = 0;
  double delta_ = 0.0;
  SdlWindow &window_;
};
