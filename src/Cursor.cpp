#include "Cursor.hpp"


double Cursor::getCoords(){
    double xpos, ypos;
    //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);
    return xpos, ypos;
}

float getValue(std::vector<glm::vec4> points, float x, float y){
    if(point[])
}