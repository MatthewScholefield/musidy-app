#include <SDL_events.h>
#include <iostream>
#include "Renderer.hpp"
#include "SdlWindow.hpp"
#include "SoundSystem.hpp"
#include "Instrument.hpp"
#include "CLI11.hpp"
#include "SongGenerator.hpp"
#include "Interface.hpp"
#include "ParticleSystem.hpp"


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
  Renderer renderer(window);
  ParticleSystem particles;
  SoundSystem system([&](float *f, size_t n) { instrument.Render(f, n); });
  SongGenerator generator(instrument, particles);
  Interface interface(generator, window);

  std::cout << "Tonality: " << TonalityToString(instrument.GetTonality()) << std::endl;
  for (int chord : generator.GetProgression()) {
    std::cout << ((chord + 7 * 100) % 7) + 1 << " ";
  }
  std::cout << std::endl;

  while (window.Update()) {
    renderer.Begin(100, 100, 100);
    particles.Render(renderer);
    interface.Render(renderer);
    renderer.End();


    double dt = renderer.GetDelta();
    std::cout << dt << std::endl;
    generator.Update(instrument, dt);
    particles.Update(dt);
  }
}
