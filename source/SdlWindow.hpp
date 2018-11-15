#pragma once

#include <SDL_video.h>

class SdlWindow {
public:
  SdlWindow();
  SdlWindow(const SdlWindow &other) = delete;

  ~SdlWindow();

  SDL_Window *getRaw();
  bool update();

private:
  SDL_Window *window;
};
