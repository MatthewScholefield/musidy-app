#pragma once

#include <iostream>
#include "SongGenerator.hpp"
#include "SdlWindow.hpp"
#include "Renderer.hpp"

class Interface {
public:
  explicit Interface(SongGenerator &generator, SdlWindow &window) : generator_(generator) {
    window.OnTouchInput([&](float x, float y){OnTouchInput(x, y);});
  }
  void Render(Renderer &renderer) {
    renderer.Rect(bx, by, 0.1f, 0.1f, {200, 200, 180});
  }
  void OnTouchInput(float x, float y) {
    bx = x;
    by = y;
    generator_.SetDelta(x);
  }

private:
  float bx = 0.5f, by = 0.5f;
  SongGenerator &generator_;
};
