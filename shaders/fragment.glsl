#version 330 core
out vec4 FragColor;

uniform vec4 fColor;


in vec4 position;
in vec3 aColor;

void main()
{   
    FragColor = vec4(aColor,1.0f);
    //FragColor = fColor;

} 