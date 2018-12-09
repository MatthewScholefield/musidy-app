#pragma once

#include "Renderer.hpp"

/**
 * Single visual particle
 */
class Particle {
public:
    /**
     * Create a new particle
     * @param x X position
     * @param y Y position
     * @param vx X velocity
     * @param vy Y velocity
     * @param color Color of particle
     * @param timeLeft Time until particle disappears
     */
    Particle(float x, float y, float vx, float vy, Color color, double timeLeft = 1.0);

    /**
     * Render this particle to the screen
     * @param renderer Renderer instance
     */
    void render(Renderer &renderer);

    /**
     * Update the particles position based on its velocity
     * @param dt Amount of time passed
     * @return True if the particle is still alive
     */
    bool update(double dt);

private:
    float x, y, vx, vy;
    Color color;
    double timeLeft;
    double initialTimeLeft;
};

/**
 * Particle system for music visualization
 */
class ParticleSystem {
public:
    /**
     * Render render
     * @param renderer
     */
    void render(Renderer &renderer);

    /**
     * Update the position of all particles
     * @param dt Time passed
     */
    void update(double dt);

    /**
     * Create a new particle
     * @param particle New particle object
     */
    void add(Particle particle);

private:
    std::vector<Particle> particles;
};
