#include <SDL_timer.h>
#include "Renderer.hpp"

Renderer::Renderer(SdlWindow &window) :
    renderer_(SDL_CreateRenderer(window.GetRaw(), -1, SDL_RENDERER_ACCELERATED)),
    last_tick_time_(SDL_GetPerformanceCounter()), window_(window) {
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

void Renderer::Rect(float x, float y, float width, float height, const Color &color) {
  SDL_Rect rect{tx(x), ty(y), tx(width), ty(height)};
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer_, &rect);
}

void Renderer::Begin(Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
  SDL_RenderClear(renderer_);
}

void Renderer::End() {
  SDL_RenderPresent(renderer_);
  uint64_t tick_time = SDL_GetPerformanceCounter();
  delta_ = (tick_time - last_tick_time_) / float(SDL_GetPerformanceFrequency());
  last_tick_time_ = tick_time;
}

double Renderer::GetDelta() {
  return delta_;
}
