#include "Interface.hpp"

Interface::Interface(SongGenerator &generator, SdlWindow &window) : generator(generator) {
    window.onTouchInput([&](float x, float y) { onTouchInput(x, y); });
}

void Interface::render(Renderer &renderer) {
    renderer.rect(bx, by, 0.1f, 0.1f, {200, 200, 180});
}

void Interface::onTouchInput(float x, float y) {
    bx = x;
    by = y;
    generator.setDelta(x);
}
