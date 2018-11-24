#include <SDL_events.h>
#include "Renderer.hpp"
#include "SdlWindow.hpp"
#include "SoundSystem.hpp"


int main(int argc, char **argv) {
  SdlWindow window;
  Renderer renderer(window.getRaw());
  SoundSystem system([&](float *f, size_t n) {
    for (int i = 0; i < n; ++i) {
      *f++ = (rand() % 200) / 100.f - 1.f;
      *f++ = (rand() % 200) / 100.f - 1.f;
    }
    return 0;
  });

  while (window.update()) {
    renderer.begin();
    renderer.rect(50, 50, 50, 50, {0, 0, 255, 255});
    renderer.end();
  }
}
