#include "../includes/Input.hpp"

void input(GLFWwindow *win, Transform &t, float dt)
{
    const float rotspeed = 1.5f;
    const float movespeed = 3.0f;

    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }


    if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        t.rotY -= rotspeed *dt;
    if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        t.rotY += rotspeed *dt;
    if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        t.rotX -= rotspeed *dt;
    if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        t.rotX += rotspeed *dt;


    if(glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        t.posX -= movespeed *dt;
    if(glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        t.posX += movespeed *dt;
    if(glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) 
        t.posY += movespeed *dt;
    if(glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        t.posY -= movespeed *dt;
    if(glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
        t.posZ -= movespeed *dt;
    if(glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
        t.posZ += movespeed *dt;
}