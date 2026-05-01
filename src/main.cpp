#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <stack>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>

//include our lib 

#include "Particle.hpp"
#include "MagneticField.hpp"
#include "Cursor.hpp"


# define M_PI           3.14159265358979323846 

using namespace std;

// Define some type for particle 

typedef tuple<glm::vec3, glm::vec3> PARTICLE_DATA;




float half = 0.5f;
float cube[] = {

       // back face
        -half, -half, -half,
         half, -half, -half,
         half,  half, -half,
         half,  half, -half,
        -half,  half, -half,
        -half, -half, -half,

        // front face
        -half, -half,  half,
         half, -half,  half,
         half,  half,  half,
         half,  half,  half,
        -half,  half,  half,
        -half, -half,  half,

        // left face
        -half,  half,  half,
        -half,  half, -half,
        -half, -half, -half,
        -half, -half, -half,
        -half, -half,  half,
        -half,  half,  half,

        // right face
         half,  half,  half,
         half,  half, -half,
         half, -half, -half,
         half, -half, -half,
         half, -half,  half,
         half,  half,  half,

        // bottom face
        -half, -half, -half,
         half, -half, -half,
         half, -half,  half,
         half, -half,  half,
        -half, -half,  half,
        -half, -half, -half,

        // top face
        -half,  half, -half,
         half,  half, -half,
         half,  half,  half,
         half,  half,  half,
        -half,  half,  half,
        -half,  half, -half
    
};



    // std::vector<float> vertices;


    // float x, y, z, xy;                              // vertex position
    // float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    // float s, t;                                     // vertex texCoord

    // float sectorStep = 2 * M_PI / sectorCount;
    // float stackStep = M_PI / stackCount;
    // float sectorAngle, stackAngle;

    // for(int i = 0; i <= stackCount; ++i)
    // {
    //     stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
    //     xy = radius * cosf(stackAngle);             // r * cos(u)
    //     z = radius * sinf(stackAngle);              // r * sin(u)

    //     // add (sectorCount+1) vertices per stack
    //     // first and last vertices have same position and normal, but different tex coords
    //     for(int j = 0; j <= sectorCount; ++j)
    //     {
    //         sectorAngle = j * sectorStep;           // starting from 0 to 2pi

    //         // vertex position (x, y, z)
    //         x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
    //         y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
    //         vertices.push_back(x);
    //         vertices.push_back(y);
    //         vertices.push_back(z);

    //     }
    // }



void drawMagnet(glm::vec3 &fColor, glm::mat4 &model, unsigned int VAO, unsigned int shaderProgram ){

    //init the coordinate of the magnet
    glm::vec3 magnet_coords[]= {
        glm::vec3(-0.5f, 0.0f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f)
    };

    glBindVertexArray(VAO);
    // Creat two cube with different color, to represent our magnet
    for (int i = 0; i<2; i++){
        model = (glm::translate(
            glm::mat4(1.0f),
            magnet_coords[i]));
        
        if (i==1)
        {
            fColor = glm::vec3(1.0f, 0.0f, 0.0f);
        } else {
            fColor = glm::vec3(0.0f, 0.0f, 1.0f) ;
        }
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"),
            1, GL_FALSE, glm::value_ptr(model));
        glUniform4f(glGetUniformLocation(shaderProgram, "fColor"), fColor.x, fColor.y, fColor.z, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};

float normalize(float max, float min, float value){
    // std::cout << min << '\n';
    // std::cout << max << '\n';
    float normalized = (value-min)/(max-min);
    return normalized;
}



// void spreadParticle(int n, unsigned int VBO, std::vector<float> particle, unsigned int shaderProgram, glm::mat4 model){

//     //set limit for normalization
//     // float maxM = max(computeParticleMagnetic(glm::vec3(0.00001f, 0.00001f, 0.0f)), computeParticleMagnetic(glm::vec3(5.0f, 5.f, 0.0f)));
//     // float minM = min(computeParticleMagnetic(glm::vec3(0.00001f, 0.00001f, 0.0f)), computeParticleMagnetic(glm::vec3(5.0f, 5.f, 0.0f))); 


//     std::vector<glm::vec4> point =  createParticlePosition(n);
//     logNormalization(point, n);




//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, particle.size() * sizeof(float), particle.data(), GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     GLint colorLoc = glGetUniformLocation(shaderProgram, "fColor");
//     GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

//     for (int i=0; i<n; ++i) {
//         // float x = ((double)rand() / RAND_MAX) * (5.0f - (-5.0f)) + (-5.0f);
//         // float y = ((double)rand() / RAND_MAX) * (5.0f - (-5.0f)) + (-5.0f);
//         // model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
//         // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

//         //Set color based on Magnetic Field magnitude 

//         // float magneticValue = computeParticleMagnetic(glm::vec3(x, y, 0.0f));
        
//         // Apply logarithmic scaling to the magnetic value
//         // float logValue = log(1.0f + magneticValue);
    
//         // float logMaxM = log(1.0f + maxM);
//         // float logMinM = log(1.0f + minM);
//         // float normalizedValue = normalize(logMaxM, logMinM, logValue);
//         // std::cout << magneticValue << '\n';
//         // std::cout << normalizedValue << '\n';
//         // glm::vec3 gradient = toColorGradient(normalizedValue, 'v');

//         // std::cout << gradient.x << ", " << gradient.y << ", " << gradient.z << "\n";
//         model = glm::translate(glm::mat4(1.0f), glm::vec3(point[i][0], point[i][1], 0.0f));
//         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//         glm::vec3 gradient = toColorGradient(point[i][3], 'v');

//         glUniform4f(colorLoc, gradient.x, gradient.y, gradient.z, 1.0f);
//         glDrawArrays(GL_TRIANGLES, 0, 36);
//     };
// }




std::string loadShaderSource(const char* filepath)
{
    std::ifstream file(filepath);
    std::stringstream buffer;

    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
}




int main(){
    

    //init var
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 fColor;


    //Setup our lib
    MagneticField field;
    ParticleSettings PSettings;
    PSettings.field = field;

    MagneticFieldSettings MSettings;

    Particle ObjParticle;
        
    std::vector<float> particle = ObjParticle.createParticle();

    Cursor cursor;

    // User input space

    std::cout << R"(
            ░███     ░███                                                ░██               
        ░████   ░████                                                ░██               
        ░██░██ ░██░██  ░██████    ░████████ ░████████   ░███████  ░████████  ░███████  
        ░██ ░████ ░██       ░██  ░██    ░██ ░██    ░██ ░██    ░██    ░██    ░██    ░██ 
        ░██  ░██  ░██  ░███████  ░██    ░██ ░██    ░██ ░█████████    ░██    ░██    ░██ 
        ░██       ░██ ░██   ░██  ░██   ░███ ░██    ░██ ░██           ░██    ░██    ░██ 
        ░██       ░██  ░█████░██  ░█████░██ ░██    ░██  ░███████      ░████  ░███████  
                                        ░██                                            
                                ░███████                                             
                                                                                    
    )";

    std::cout << "What is the magnetic moment of your magnet (1200 recommended) ?\n";
    std::cout << "> ";
    std::cin >> MSettings.magneticMoment ;

    int countParticle = 500000;
    std::cout << "How many ploting particle do you want (500000 recommanded) ?\n";
    std::cout << "> ";
    std::cin >> countParticle ;


    //init glfw and window

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Magnetic-Simulator", NULL, NULL);

    

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSwapInterval(1);


    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    

    
    //Load Shaders :
    std::string fragmentCode = loadShaderSource("C:/Users/ordi2430538/Documents/coding_project_flavortown/magnetic-sim/shaders/fragment.glsl");
    const char* fragmentShaderSource = fragmentCode.c_str();

    std::string vertexCode = loadShaderSource("C:/Users/ordi2430538/Documents/coding_project_flavortown/magnetic-sim/shaders/vertex.glsl");
    const char* vertexShaderSource = vertexCode.c_str();


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glEnable(GL_DEPTH_TEST);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX_SHADER\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM\n" << infoLog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 1. Generate and bind VAO


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);



    // 2. Generate and bind VBO
    // unsigned int VBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // // 3. Upload data
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // // 4. Set attribute pointers (this is now saved into the VAO)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    //Test particle only :
    // Set mash particle VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 3. Upload data
    glBufferData(GL_ARRAY_BUFFER, particle.size() * sizeof(float), particle.data(), GL_STATIC_DRAW);

    // 4. Set attribute pointers (this is now saved into the VAO)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // ============
    // Static Mode 
    // ============


    // Get the particle data 
    std::vector<float> particlesData = ObjParticle.SpreadAndSaveParticle(countParticle , 'v', PSettings, MSettings);


    // We forget about this data organisation, it isn't great 
    
    
    // Upload to a second VBO
    //Set the VBO for the instance position
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, particlesData.size() * sizeof(float),
                particlesData.data(), GL_STATIC_DRAW);


    // Instance Position (Location 1) --> Ofset
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribDivisor(1, 1);
    glEnableVertexAttribArray(1);

    // Instance Color (Location 2)
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribDivisor(2, 1); // <--- update once per instance
    glEnableVertexAttribArray(2);

    // Unbind VAO to prevent accidental changes !!!!! AFTER VERTEX ATTRIB POINTER
    glBindVertexArray(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //Set the rendering params 

    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    projection = glm::perspective(glm::radians(45.0f), (float)mode->width / (float)mode->height, 0.1f, 100.0f);
    //set the position of the model 
    model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, 0.0f)
    );



    while (!glfwWindowShouldClose(window))
        {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shaderProgram);

             //Update the position of the model
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"),
                    1, GL_FALSE, glm::value_ptr(model));
            //update the view matrix
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
                    1, GL_FALSE, glm::value_ptr(view));
            //update the projection matrix
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
                    1, GL_FALSE, glm::value_ptr(projection));
            glBindVertexArray(VAO);

            // glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            // glEnableVertexAttribArray(0);


            // //Creat two cube with different color, to represent our magnet

            // glUniform2f(glGetUniformLocation(shaderProgram, "IsParticle"), 0.0f, 0);
            // glDisableVertexAttribArray(1);
            // drawMagnet(fColor, model, VAO, shaderProgram);


            glDrawArraysInstanced(GL_TRIANGLES, 0, 36, particlesData.size()/6);


            // glUniform2f(glGetUniformLocation(shaderProgram, "particleEnable"), 1, 1);
            // spreadParticle(10000,VBO, particle, shaderProgram, model);


            //std::cout << "Cursor Position: " << cursor.getCoords(window).x << ", " << cursor.getCoords(window).y << std::endl;



            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        glfwTerminate();
        return 0;
}