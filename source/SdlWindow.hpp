#pragma once

#include <SDL_video.h>
#include <vector>
#include <functional>

/**
 * Wrapper for SDL window
 */
class SdlWindow {
public:
    /**
     * Type of functions that handle touch input
     */
    using TouchInputHandler = std::function<void(float, float)>;

    /**
     * Create a new SDL window
     */
    SdlWindow();

    /**
     * Cannot be copied since it would mess up destruction
     * @param other Other window
     */
    SdlWindow(const SdlWindow &other) = delete;

    /**
     * Destroy the window
     */
    ~SdlWindow();

    /**
     * Set function to be called anytime a mouse is clicking the screen
     * @param inputHandler
     */
    void onTouchInput(const TouchInputHandler &inputHandler);

    /**
     * @return raw SDL window pointer
     */
    SDL_Window *getRaw();

    /**
     * Update window events
     * @return
     */
    bool update();

    /**
     * @return Horizontal pixels to the 0 coordinate
     */
    int getXOffset();

    /**
     * @return Vertical pixels to the 0 coordinate
     */
    int getYOffset();

    /**
     * @return Number of pixels mapped as one centered unit (0.0 to 1.0)
     */
    int getScale();

private:
    /**
     * Update this window to a new size
     * @param sx New horizontal pixels
     * @param sy New vertical pixels
     */
    void resize(int sx, int sy);

    /**
     * Called whenever the mouse is updated
     * @param x New mouse X
     * @param y New mouse Y
     */
    void onMouse(int x, int y);

    std::vector<TouchInputHandler> touchInputHandlers;
    int xOffset, yOffset, scale;
    SDL_Window *window;
};
