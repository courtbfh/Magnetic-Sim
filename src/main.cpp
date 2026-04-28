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
#include <stdlib.h>

using namespace std;




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

glm::vec3 creatParticul(){
    return glm::vec3(1.0f, 1.0f, 1.0f);
};

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
}



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
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 3. Upload data
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // 4. Set attribute pointers (this is now saved into the VAO)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Unbind VAO to prevent accidental changes
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


            // Creat two cube with different color, to represent our magnet

            drawMagnet(fColor, model, VAO, shaderProgram);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        glfwTerminate();
        return 0;
}