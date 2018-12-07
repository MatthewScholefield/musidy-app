#pragma once

#include <SDL_video.h>
#include <vector>
#include <functional>

class SdlWindow {
public:
  SdlWindow();
  SdlWindow(const SdlWindow &other) = delete;

  using TouchInputHandler = std::function<void(float, float)>;

  void onTouchInput(const TouchInputHandler &inputHandler) {
    touchInputHandlers.push_back(inputHandler);
  }

  ~SdlWindow();

  SDL_Window *getRaw();
  bool update();

  int getWidth();

  int getHeight();

private:
  void onMouse(int x, int y);

  std::vector<TouchInputHandler> touchInputHandlers;
  int width = 640, height = 480;
  SDL_Window *window;
};
