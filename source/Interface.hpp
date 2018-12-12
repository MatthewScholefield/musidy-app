#pragma once

#include <iostream>
#include "songCreation/ScorePlayer.hpp"
#include "SdlWindow.hpp"
#include "Renderer.hpp"

/**
 * User interface for app
 */
class Interface {
public:
    /**
     * Create new user interface object
     * @param generator Song generator object
     * @param window SDL window
     */
    explicit Interface(ScorePlayer &generator, SdlWindow &window);

    /**
     * Render the interface
     * @param renderer Renderer
     */
    void render(Renderer &renderer);

private:
    /**
     * Update based on new touch input
     * @param x X coordinate
     * @param y Y coordinate
     */
    void onTouchInput(float x, float y);

    float bx = 0.5f, by = 0.5f; // Box x and y of input knob
    ScorePlayer &generator;  // Song generator reference to set parameters
};
