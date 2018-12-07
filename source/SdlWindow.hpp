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
    int getXOffset();
    int getYOffset();
    int getScale();

private:
    void resize(int sx, int sy);
    void onMouse(int x, int y);

    std::vector<TouchInputHandler> touchInputHandlers;
    int xOffset, yOffset, scale;
    SDL_Window *window;
};
