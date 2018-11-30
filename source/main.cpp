#include <SDL_events.h>
#include <iostream>
#include "Renderer.hpp"
#include "SdlWindow.hpp"
#include "SoundSystem.hpp"
#include "Instrument.hpp"
#include "CLI11.hpp"
#include "SongGenerator.hpp"


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
  srand(time(nullptr));
  Arguments args(argc, argv);
  CLI11_PARSE(args.app, argc, argv);

  std::cout << "Loading instrument..." << std::endl;
  Instrument instrument(args.instrument_file, args.gain);
  std::cout << "Starting app..." << std::endl;

  SdlWindow window;
  Renderer renderer(window.GetRaw());
  SoundSystem system([&](float *f, size_t n) { instrument.Render(f, n); });
  SongGenerator generator(instrument);

  for (int chord : generator.GetProgression()) {
    std::cout << (chord % 7) + 1 << " ";
  }
  std::cout << std::endl;

  while (window.Update()) {
    renderer.Begin();
    renderer.Rect(50, 50, 50, 50, {0, 0, 255, 255});
    renderer.End();

    generator.Update(instrument, renderer.GetDelta());
  }
}
