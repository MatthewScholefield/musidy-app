#include <SDL_events.h>
#include <iostream>
#include "SdlWindow.hpp"

SdlWindow::SdlWindow() : window(SDL_CreateWindow(
        "Musidy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
)) {
    resize(640, 480);
}

SdlWindow::~SdlWindow() {
    SDL_DestroyWindow(window);
}

void SdlWindow::onTouchInput(const SdlWindow::TouchInputHandler &inputHandler) {
    touchInputHandlers.push_back(inputHandler);
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
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        resize(event.window.data1, event.window.data2);
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

int SdlWindow::getXOffset() {
    return xOffset;
}

int SdlWindow::getYOffset() {
    return yOffset;
}

int SdlWindow::getScale() {
    return scale;
}

void SdlWindow::resize(int sx, int sy) {
    scale = std::min(sx, sy);
    xOffset = (sx - scale) / 2;
    yOffset = (sy - scale) / 2;
}

void SdlWindow::onMouse(int x, int y) {
    for (const auto &i : touchInputHandlers) {
        i((x - xOffset)/ float(scale), (y - yOffset) / float(scale));
    }
}
