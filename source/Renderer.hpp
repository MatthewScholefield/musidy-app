#pragma once

#include <SDL_video.h>
#include <SDL_render.h>
#include "SdlWindow.hpp"

/**
 * Represents red, green, blue, and alpha values in color
 */
struct Color {
    int r = 0, g = 0, b = 0, a = 255;
};

/**
 * Class to render shapes to the screen
 */
class Renderer {
public:
    /**
     * Create a new renderer instance
     * @param window The SDL window to render to
     */
    explicit Renderer(SdlWindow &window);

    /**
     * Start rendering a new frame, clearing screen first
     * @param r Red component [0..255]
     * @param g Green component [0..255]
     * @param b Blue component [0..255]
     */
    void begin(Uint8 r, Uint8 g, Uint8 b);

    /**
     * End the rendering for this frame
     */
    void finish();

    /**
     * Draw a rectangle at the given position
     * @param x X position (0.5 = center)
     * @param y Y position (0.5 = center)
     * @param width Horizontal size
     * @param height Vertical size
     * @param color Color of rectangle
     */
    void rect(float x, float y, float width, float height, const Color &color);

    /**
     * @return Ratio of x margin between left edge and coordinate x=0
     */
    float getXMargin() {
        return window.getXOffset() / float(window.getScale());
    }

    /**
     * @return Ratio of y margin between top edge and coordinate y=0
     */
    float getYMargin() {
        return window.getYOffset() / float(window.getScale());
    }

    /**
     * @return Delta time between this frame and the last from
     */
    double getDelta();

private:
    /**
     * Transform the coordinate to screen coordinates
     * @param x Input coordinate
     * @return Screen pixels
     */
    int tx(float x);

    /**
     * Transform the coordinate to screen coordinates
     * @param x Input coordinate
     * @return Screen pixels
     */
    int ty(float y);

    SDL_Renderer *renderer;
    uint64_t lastTickTime;
    double delta = 0.0;
    SdlWindow &window;
};
