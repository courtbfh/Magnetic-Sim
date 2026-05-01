#pragma once
#include <vector>
#include <glm/glm.hpp>

struct MagneticFieldSettings {
    float magneticMoment;
    std::vector<glm::vec3> MagnetCenters;
};

class MagneticField {
    public:
        MagneticField() = default;
        float computeParticleMagnetic(glm::vec3 position, MagneticFieldSettings settings);
        glm::vec3 toColorGradient(float value, char gradient);
        void logNormalization(std::vector<glm::vec4> &points, int n);

};