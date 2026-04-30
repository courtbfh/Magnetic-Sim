#include "MagneticField.hpp"

#include <vector>
#include <glm/glm.hpp>


#define M_PI 3.14159265358979323846 


void MagneticField::logNormalization(std::vector<glm::vec4> &points, int n){
    float sum =0.0f; // log(a*b) = log(a) + log (b)

    for (int i=0; i<n; i++){
        if (points[i][3] > 0.0f){
            sum += log(points[i][3]);
        } else {
            sum += log(0.0001f);
        };
    };

    // std::cout << sum << '\n';
    for (int i=0; i<n; i++){
        if (points[i][3] > 0.0f){
            points[i][3] = abs((log(abs(points[i][3])))/(log(abs(sum)))+1);
        }else {
            points[i][3] = abs((log(0.0001f))/(log(abs(sum)))+1);
        };
        // std::cout << points[i][3] << '\n';
    };
};

glm::vec3 MagneticField::toColorGradient(float value, char gradient){
    glm::vec3 color;

    if( gradient == 'v'){
        color = glm::mix(glm::vec3(0.26,0.0,0.32), glm::vec3(1.0,1.0,0.15), value);
    }
    return color;
}; 

float MagneticField::computeParticleMagnetic(glm::vec3 position){
    //Let firstly represent only the magnetic Strength without the materials propriety

    float permeability = 4 *  M_PI * pow(10,-7);
    float magneticMoment = 1.2f; // 1.2 Am^2 .

    //Compute the magnetic Strength in a point
    float distance = abs(glm::length(position));
    
    // Prevent division by zero
    if (distance < 0.1f) distance = 0.1f; 

    // B = (u0 * 2m)/(4pi * r^3)
    return (permeability * 2 * magneticMoment) / (4.0f * M_PI * pow(distance,3));

};
