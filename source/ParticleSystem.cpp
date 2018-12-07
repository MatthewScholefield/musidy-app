#include "ParticleSystem.hpp"

void Particle::Render(Renderer &renderer) {
  Color render_color(color);
  render_color.a = Uint8(255 * std::min(1.0, time_left));
  renderer.Rect(x, y, 0.01f, 0.01f, render_color);
}

bool Particle::Update(double dt) {
  x += vx * dt;
  y += vy * dt;
  vx *= 0.9999f;
  vy *= 0.9999f;
  time_left -= dt;
  return time_left > 0;
}

void ParticleSystem::Render(Renderer &renderer) {
  for (auto &particle : particles) {
    particle.Render(renderer);
  }
}

void ParticleSystem::Update(double dt) {
  for (auto it = particles.begin(); it != particles.end();) {
    if (it->Update(dt)) {
      ++it;
    } else {
      it = particles.erase(it);
    }
  }
}

void ParticleSystem::Add(Particle particle) {
  particles.push_back(particle);
}
