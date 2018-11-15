#include <SDL_events.h>
#include "SdlWindow.hpp"

SdlWindow::SdlWindow() : window(SDL_CreateWindow(
    "Jeu de la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480, SDL_WINDOW_SHOWN
)) {}

SdlWindow::~SdlWindow() {
  SDL_DestroyWindow(window);
}

SDL_Window *SdlWindow::getRaw() {
  return window;
}

bool SdlWindow::update() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return false;
      default:
        return true;
    }
  }
  return true;
}
