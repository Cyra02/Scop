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

    bool useTexture;
    bool tDown;
    int texIndex;
    bool nDown;
};

void input(GLFWwindow *win, Transform &t, float dt, int texCount);

#endif