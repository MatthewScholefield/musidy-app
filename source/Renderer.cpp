#include <SDL_timer.h>
#include <iostream>
#include "Renderer.hpp"


Renderer::Renderer(SdlWindow &window) :
        renderer(SDL_CreateRenderer(window.getRaw(), -1, SDL_RENDERER_ACCELERATED)),
        lastTickTime(SDL_GetPerformanceCounter()), window(window) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Renderer::rect(float x, float y, float width, float height, const Color &color) {
    SDL_Rect rect{tx(x), ty(y), int(width * window.getScale()), int(height * window.getScale())};
    SDL_SetRenderDrawColor(renderer, uint8_t(color.r), uint8_t(color.g), uint8_t(color.b), uint8_t(color.a));
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::begin(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

void Renderer::finish() {
    SDL_RenderPresent(renderer);
    uint64_t timeTime = SDL_GetPerformanceCounter();
    delta = (timeTime - lastTickTime) / float(SDL_GetPerformanceFrequency());
    lastTickTime = timeTime;
}

double Renderer::getDelta() {
    return delta;
}

int Renderer::tx(float x) {
    return int((getXMargin() + x) * window.getScale());
}

int Renderer::ty(float y) {
    return int((getYMargin() + y) * window.getScale());
}
