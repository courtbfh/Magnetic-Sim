#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 iOffset;
layout (location = 2) in vec3 fColor;

out vec4 position;
out vec3 aColor;

uniform vec2 isParticle;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    aColor = fColor;
    // mat4 model = mat4(
    //     vec4(1.0f, 0.0f, 0.0f, iOffset.x),
    //     vec4(0.0f, 1.0f, 0.0f, iOffset.y),
    //     vec4(0.0f, 0.0f, 1.0f, iOffset.z),
    //     vec4(0.0f, 0.0f, 0.0f, 1.0f)
    // );

    gl_Position = projection * view * model * vec4(aPos+iOffset, 1.0f);
    position = gl_Position;
}