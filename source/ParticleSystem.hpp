#pragma once

#include "Renderer.hpp"

class Particle {
public:
  Particle(float x, float y, float vx, float vy, Color color, double time_left = 1.0);

  void Render(Renderer &renderer);
  bool Update(double dt);

private:
  float x_, y_, vx_, vvy_;
  Color color_;
  double time_left_ = 1.0;
};

class ParticleSystem {
public:
  void Render(Renderer &renderer);
  void Update(double dt);
  void Add(Particle particle);

private:
  std::vector<Particle> particles;
};
