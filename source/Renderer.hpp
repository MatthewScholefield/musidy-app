#pragma once

#include <SDL_video.h>
#include <SDL_render.h>

struct Color {
  Color(int r, int g, int b, int a = 255) :
      r(uint8_t(r)), g(uint8_t(g)), b(uint8_t(b)), a(uint8_t(a)) {}

  uint8_t r, g, b, a = 255;
};

class Renderer {
public:
  explicit Renderer(SDL_Window *window) : renderer_(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) {}

  void Begin();
  void End();
  void Rect(int x, int y, int width, int height, const Color &color);

private:
  SDL_Renderer *renderer_;
};
