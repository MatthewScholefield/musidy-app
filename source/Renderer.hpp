#pragma once

#include <SDL_video.h>
#include <SDL_render.h>
#include "SdlWindow.hpp"

struct Color {
    int r = 0, g = 0, b = 0, a = 255;
};

class Renderer {
public:
    explicit Renderer(SdlWindow &window);

    void begin(Uint8 r, Uint8 g, Uint8 b);
    void finish();
    void rect(float x, float y, float width, float height, const Color &color);

    float getXMargin() {
        return window.getXOffset() / float(window.getScale());
    }

    float getYMargin() {
        return window.getYOffset() / float(window.getScale());
    }

    double getDelta();

private:
    int tx(float x);
    int ty(float y);

    SDL_Renderer *renderer;
    uint64_t lastTickTime;
    double delta = 0.0;
    SdlWindow &window;
};
