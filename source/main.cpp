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
    app.add_option("soundfont_file", instrument, "Soundfont file (.sf2) to play song with")->required();
    app.add_option("-g,--gain", gain, "Volume gain of instrument (negative or positive decimal)");
  }

  CLI::App app;
  std::string instrument;
  float gain = 0.f;
};


int main(int argc, char **argv) {
  srand(time(nullptr));
  Arguments args(argc, argv);
  CLI11_PARSE(args.app, argc, argv);

  std::cout << "Loading instrument..." << std::endl;
  Instrument instrument(args.instrument, args.gain);
  std::cout << "Starting app..." << std::endl;

  SdlWindow window;
  Renderer renderer(window);
  ParticleSystem particles;
  SoundSystem system([&](float *f, size_t n) { instrument.render(f, n); });
  SongGenerator generator(instrument, particles);
  Interface interface(generator, window);

  std::cout << "Tonality: " << tonalityToString(instrument.getTonality()) << std::endl;
  for (int chord : generator.getProgression()) {
    std::cout << ((chord + 7 * 100) % 7) + 1 << " ";
  }
  std::cout << std::endl;

  while (window.update()) {
    renderer.begin(100, 100, 100);
    particles.render(renderer);
    interface.render(renderer);
    renderer.finish();

    double dt = renderer.getDelta();
    std::cout << dt << std::endl;
    generator.update(instrument, dt);
    particles.update(dt);
  }
}
