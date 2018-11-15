
#include <SDL_events.h>
#include "Renderer.hpp"
#include "SdlWindow.hpp"

int main(int argc, char **argv) {
  SdlWindow window;
  Renderer renderer(window.getRaw());

  while (window.update()) {
    renderer.begin();
    renderer.rect(50, 50, 50, 50, {0, 0, 255, 255});
    renderer.end();
  }
}
