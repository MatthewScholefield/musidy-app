#include <SDL_events.h>
#include <iostream>
#include "Renderer.hpp"
#include "SdlWindow.hpp"
#include "SoundSystem.hpp"
#include "Instrument.hpp"


int main(int argc, char **argv) {
  SdlWindow window;
  Renderer renderer(window.GetRaw());
  Instrument instrument(argv[1]);
  SoundSystem system([&](float *f, size_t n) {
    instrument.render(f, n);
    return 0;
  });

  int note = 60;
  double note_timer = 0.0;
  bool moving_up = true;

  while (window.Update()) {
    renderer.Begin();
    renderer.Rect(50, 50, 50, 50, {0, 0, 255, 255});
    renderer.End();

    if ((note_timer -= renderer.GetDelta()) < 0.0) {
      note_timer = 0.2;
      instrument.play(note);
      note += moving_up ? 1 : -1;
      if (note >= 60 + 12 || note <= 60) {
        moving_up = !moving_up;
      }
    }
  }
}
