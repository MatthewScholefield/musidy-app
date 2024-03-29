#include "Interface.hpp"

Interface::Interface(ScorePlayer &generator, SdlWindow &window, Instrument &instrument) :
generator(generator), instrument(instrument) {
    window.onTouchInput([&](float x, float y) { onTouchInput(x, y); });
    onTouchInput(bx, by);
}

void Interface::render(Renderer &renderer) {
    renderer.rect(bx - 0.05f, by - 0.05f, 0.1f, 0.1f, {200, 200, 180});
}

void Interface::onTouchInput(float x, float y) {
    bx = std::max(0.f, std::min(1.f, x));
    by = std::max(0.f, std::min(1.f, y));
    generator.setNoteInterval(0.1f + 1.f - bx);
    instrument.setVolumeMultiplier(1.2f - 1.2f * by);
}
