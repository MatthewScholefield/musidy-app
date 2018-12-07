#pragma once

#include <SDL_video.h>
#include <vector>
#include <functional>

class SdlWindow {
public:
  SdlWindow();
  SdlWindow(const SdlWindow &other) = delete;

  using TouchInputHandler = std::function<void(float, float)>;

  void OnTouchInput(const TouchInputHandler &input_handler) {
    touch_input_handlers_.push_back(input_handler);
  }

  ~SdlWindow();

  SDL_Window *GetRaw();
  bool Update();

  int GetWidth();

  int GetHeight();

private:
  void OnMouse(int x, int y);

  std::vector<TouchInputHandler> touch_input_handlers_;
  int width_ = 640, height_ = 480;
  SDL_Window *window_;
};
