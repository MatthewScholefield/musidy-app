#pragma once

#include <SDL_video.h>

class SdlWindow {
public:
  SdlWindow();
  SdlWindow(const SdlWindow &other) = delete;

  ~SdlWindow();

  SDL_Window *GetRaw();
  bool Update();

private:
  SDL_Window *window_;
};
