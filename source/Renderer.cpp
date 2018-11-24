#include "Renderer.hpp"

void Renderer::Rect(int x, int y, int width, int height, const Color &color) {
  SDL_Rect rect{x, y, width, height};
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer_, &rect);
}

void Renderer::Begin() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}

void Renderer::End() {
  SDL_RenderPresent(renderer_);
}
