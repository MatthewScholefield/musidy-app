#pragma once

#include "Renderer.hpp"

class Particle {
public:
  Particle(float x, float y, float vx, float vy, Color color, double timeLeft = 1.0);

  void render(Renderer &renderer);
  bool update(double dt);

private:
  float x, y, vx, vy;
  Color color;
  double timeLeft = 1.0;
};

class ParticleSystem {
public:
  void render(Renderer &renderer);
  void update(double dt);
  void add(Particle particle);

private:
  std::vector<Particle> particles;
};
