#pragma once
#include <vector>
#include <glm/glm.hpp>

class MagneticField {
    public:
        MagneticField() = default;
        float computeParticleMagnetic(glm::vec3 position);
        glm::vec3 toColorGradient(float value, char gradient);
        void logNormalization(std::vector<glm::vec4> &points, int n);

};