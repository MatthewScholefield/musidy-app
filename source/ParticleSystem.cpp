#include "ParticleSystem.hpp"


Particle::Particle(float x, float y, float vx, float vy, Color color, double time_left) :
    x_(x), y_(y), vx_(vx), vvy_(vy), color_(color), time_left_(time_left) {}

void Particle::Render(Renderer &renderer) {
  Color render_color(color_);
  render_color.a = Uint8(255 * std::min(1.0, time_left_));
  renderer.Rect(x_, y_, 0.01f, 0.01f, render_color);
}

bool Particle::Update(double dt) {
  x_ += vx_ * dt;
  y_ += vvy_ * dt;
  vx_ *= 0.9999f;
  vvy_ *= 0.9999f;
  time_left_ -= dt;
  return time_left_ > 0;
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
