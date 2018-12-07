#pragma once

#include <iostream>
#include "SongGenerator.hpp"
#include "SdlWindow.hpp"
#include "Renderer.hpp"

class Interface {
public:
  explicit Interface(SongGenerator &generator, SdlWindow &window) : generator(generator) {
    window.onTouchInput([&](float x, float y) { onTouchInput(x, y); });
  }
  void render(Renderer &renderer) {
    renderer.rect(bx, by, 0.1f, 0.1f, {200, 200, 180});
  }
  void onTouchInput(float x, float y) {
    bx = x;
    by = y;
    generator.setDelta(x);
  }

private:
  float bx = 0.5f, by = 0.5f;
  SongGenerator &generator;
};
