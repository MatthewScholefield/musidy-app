#include "ParticleSystem.hpp"


Particle::Particle(float x, float y, float vx, float vy, Color color, double timeLeft) :
        x(x), y(y), vx(vx), vy(vy), color(color), initialTimeLeft(timeLeft), timeLeft(timeLeft) {}

void Particle::render(Renderer &renderer) {
    Color renderColor(color);
    renderColor.a = Uint8(255 * timeLeft / initialTimeLeft);
    renderer.rect(x, y, 0.01f, 0.01f, renderColor);
}

bool Particle::update(double dt) {
    x += vx * dt;
    y += vy * dt;
    vx *= 0.9999f;
    vy *= 0.9999f;
    timeLeft -= dt;
    return timeLeft > 0;
}

void ParticleSystem::render(Renderer &renderer) {
    for (auto &particle : particles) {
        particle.render(renderer);
    }
}

void ParticleSystem::update(double dt) {
    for (auto it = particles.begin(); it != particles.end();) {
        if (it->update(dt)) {
            ++it;
        } else {
            it = particles.erase(it);
        }
    }
}

void ParticleSystem::add(Particle particle) {
    particles.push_back(particle);
}
