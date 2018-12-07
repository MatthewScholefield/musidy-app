#pragma once

#include "Renderer.hpp"

struct Particle {
  float x, y, vx, vy;
  Color color;
  double time_left = 1.0;

  void Render(Renderer &renderer);
  bool Update(double dt);
};

class ParticleSystem {
public:
  void Render(Renderer &renderer);
  void Update(double dt);
  void Add(Particle particle);

private:
  std::vector<Particle> particles;
};
