#include <SDL_events.h>
#include "SdlWindow.hpp"

SdlWindow::SdlWindow() : window(SDL_CreateWindow(
    "Musidy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height, SDL_WINDOW_SHOWN
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
      case SDL_MOUSEBUTTONDOWN:
        onMouse(event.button.x, event.button.y);
        break;
      case SDL_MOUSEMOTION:
        if (event.motion.state & SDL_BUTTON_LMASK) {
          onMouse(event.motion.x, event.motion.y);
        }
        break;
      case SDL_WINDOWEVENT:
        switch(event.window.type) {
          case SDL_WINDOWEVENT_RESIZED:
            width = event.window.data1;
            height = event.window.data2;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  return true;
}

int SdlWindow::getWidth() {
  return width;
}

int SdlWindow::getHeight() {
  return height;
}

void SdlWindow::onMouse(int x, int y) {
  for (const auto &i : touchInputHandlers) {
    i(x / float(width), y / float(height));
  }
}
