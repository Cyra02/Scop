#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

struct Transform
{
    float rotX;
    float rotY;
    float posX;
    float posY;
    float posZ;
};

void input(GLFWwindow *win, Transform &t, float dt);

#endif