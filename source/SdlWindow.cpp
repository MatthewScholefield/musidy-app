#include <SDL_events.h>
#include "SdlWindow.hpp"

SdlWindow::SdlWindow() : window_(SDL_CreateWindow(
    "Musidy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    640, 480, SDL_WINDOW_SHOWN
)) {}

SdlWindow::~SdlWindow() {
  SDL_DestroyWindow(window_);
}

SDL_Window *SdlWindow::GetRaw() {
  return window_;
}

bool SdlWindow::Update() {
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
