#include <SDL_events.h>
#include "SdlWindow.hpp"

SdlWindow::SdlWindow() : window_(SDL_CreateWindow(
    "Musidy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width_, height_, SDL_WINDOW_SHOWN
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
      case SDL_MOUSEBUTTONDOWN:
        OnMouse(event.button.x, event.button.y);
        break;
      case SDL_MOUSEMOTION:
        if (event.motion.state & SDL_BUTTON_LMASK) {
          OnMouse(event.motion.x, event.motion.y);
        }
        break;
      case SDL_WINDOWEVENT:
        switch(event.window.type) {
          case SDL_WINDOWEVENT_RESIZED:
            width_ = event.window.data1;
            height_ = event.window.data2;
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

int SdlWindow::GetWidth() {
  return width_;
}

int SdlWindow::GetHeight() {
  return height_;
}

void SdlWindow::OnMouse(int x, int y) {
  for (const auto &i : touch_input_handlers_) {
    i(x / float(width_), y / float(height_));
  }
}
