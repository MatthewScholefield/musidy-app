#pragma once

#include <iostream>
#include "SongGenerator.hpp"
#include "SdlWindow.hpp"
#include "Renderer.hpp"

class Interface {
public:
    explicit Interface(SongGenerator &generator, SdlWindow &window);
    void render(Renderer &renderer);

private:
    void onTouchInput(float x, float y);

    float bx = 0.5f, by = 0.5f;
    SongGenerator &generator;
};
