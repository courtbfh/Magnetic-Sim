#include "Particle.hpp"
#include "MagneticField.hpp"

#include <cstdlib>
#include <ctime>

//TODO: Make particul more independent from magneticfield
std::vector<float> Particle::SpreadAndSaveParticle(int n, char gradient, ParticleSettings settings,  MagneticFieldSettings Magnet_settings){
    MagneticField field = settings.field;
    std::vector<glm::vec4> point =  createParticlePosition(n, settings, Magnet_settings);
    field.logNormalization(point, n);

    std::vector<float> data;

    for (int i=0; i<n; i++){
        //Modifing the data struc
        glm::vec3 color = field.toColorGradient(point[i][3], gradient);
        data.push_back((float) point[i].x);
        data.push_back((float) point[i].y);
        data.push_back((float) point[i].z);
        data.push_back((float) color.x);
        data.push_back((float) color.y);
        data.push_back((float) color.z);
    };


    return data;
};


std::vector<glm::vec4> Particle::createParticlePosition(int n, ParticleSettings settings, MagneticFieldSettings Magnet_settings){
    srand(time(0));
    float x;
    float y;

    std::vector<glm::vec4> points;
    for (int i=0; i<n; ++i) {   
        x = ((double)rand() / RAND_MAX) * (5.0f - (-5.0f)) + (-5.0f);
        y = ((double)rand() / RAND_MAX) * (5.0f - (-5.0f)) + (-5.0f);
        float magneticValue = settings.field.computeParticleMagnetic(glm::vec3(x, y, 0.0f), Magnet_settings);

        points.push_back(glm::vec4(x, y, 0.0f, magneticValue));
    };
    
    return points;
};

std::vector<float> Particle::createParticle(){
    float diameter = 0.2f;
    float radius = 0.01f;
    int sectorCount = 15; // 20*15 = 
    int stackCount = 20;

    std::vector<float> vertices;

    vertices = {
        // back face
        -radius, -radius, -radius,
         radius, -radius, -radius,
         radius,  radius, -radius,
         radius,  radius, -radius,
        -radius,  radius, -radius,
        -radius, -radius, -radius,

        // front face
        -radius, -radius,  radius,
         radius, -radius,  radius,
         radius,  radius,  radius,
         radius,  radius,  radius,
        -radius,  radius,  radius,
        -radius, -radius,  radius,

        // left face
        -radius,  radius,  radius,
        -radius,  radius, -radius,
        -radius, -radius, -radius,
        -radius, -radius, -radius,
        -radius, -radius,  radius,
        -radius,  radius,  radius,

        // right face
         radius,  radius,  radius,
         radius,  radius, -radius,
         radius, -radius, -radius,
         radius, -radius, -radius,
         radius, -radius,  radius,
         radius,  radius,  radius,

        // bottom face
        -radius, -radius, -radius,
         radius, -radius, -radius,
         radius, -radius,  radius,
         radius, -radius,  radius,
        -radius, -radius,  radius,
        -radius, -radius, -radius,

        // top face
        -radius,  radius, -radius,
         radius,  radius, -radius,
         radius,  radius,  radius,
         radius,  radius,  radius,
        -radius,  radius,  radius,
        -radius,  radius, -radius
    };

    return vertices;
};