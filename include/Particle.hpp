#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "MagneticField.hpp"

struct ParticleSettings {
    MagneticField field;
};

class Particle {
    public:
        Particle() = default;
        std::vector<float> createParticle();
        std::vector<glm::vec4> createParticlePosition(int n, ParticleSettings settings);
        std::vector<float> SpreadAndSaveParticle(int n, char gradient, ParticleSettings settings);
};