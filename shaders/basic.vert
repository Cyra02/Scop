#version 330


layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUV;

out vec3 vColor;
out vec2 vUV;
uniform mat4 uModel;
uniform mat4 uProjection;

void main()
{
    vColor = aColor;
    vUV = aUV;
    gl_Position =  uProjection * uModel * vec4(aPos, 1.0);
}