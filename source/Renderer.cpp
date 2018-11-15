#include "Renderer.hpp"

void Renderer::rect(int x, int y, int width, int height, const Color &color) {
  SDL_Rect rect{x, y, width, height};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::begin() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::end() {
  SDL_RenderPresent(renderer);
}
