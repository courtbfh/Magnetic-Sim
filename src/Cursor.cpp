#include "Cursor.hpp"


glm::vec3 Cursor::getCoords(GLFWwindow* window){
    double xpos, ypos;
    //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec3(xpos, ypos, 0.0f);
}

// How can we get the position relative to our projection ??