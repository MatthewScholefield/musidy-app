#include <SDL_events.h>
#include <iostream>
#include "Renderer.hpp"
#include "SdlWindow.hpp"
#include "SoundSystem.hpp"
#include "Instrument.hpp"
#include "CLI11.hpp"


struct Arguments {
  Arguments(int argc, char **argv) : app("Dynamic Music Generation App") {
    app.ignore_case();
    app.add_option("soundfont_file", instrument_file, "Soundfont file (.sf2) to play song with")->required();
    app.add_option("-g,--gain", gain, "Volume gain of instrument (negative or positive decimal)");
  }

  CLI::App app;
  std::string instrument_file;
  float gain = 0.f;
};


int main(int argc, char **argv) {
  Arguments args(argc, argv);
  CLI11_PARSE(args.app, argc, argv);

  std::cout << "Loading instrument..." << std::endl;
  Instrument instrument(args.instrument_file, args.gain);
  std::cout << "Starting app..." << std::endl;

  SdlWindow window;
  Renderer renderer(window.GetRaw());
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
