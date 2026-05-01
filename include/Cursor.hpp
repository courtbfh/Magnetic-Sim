#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Cursor {
    public:
        Cursor() = default;
        glm::vec3 getCoords(GLFWwindow* window);
};