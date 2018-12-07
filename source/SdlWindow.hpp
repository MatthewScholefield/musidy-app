#pragma once

#include <SDL_video.h>
#include <vector>
#include <functional>

class SdlWindow {
public:
    using TouchInputHandler = std::function<void(float, float)>;

    SdlWindow();
    SdlWindow(const SdlWindow &other) = delete;
    ~SdlWindow();

    void onTouchInput(const TouchInputHandler &inputHandler);
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
