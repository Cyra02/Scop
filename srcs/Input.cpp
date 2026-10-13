#include "../includes/Input.hpp"

void input(GLFWwindow *win, Transform &t, float dt, int texCount)
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

    if(glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
        t.rotZ -= rotspeed *dt;
    if(glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS)
        t.rotZ += rotspeed *dt;


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

    bool tDown = (glfwGetKey(win, GLFW_KEY_T) == GLFW_PRESS);
    if(tDown && !t.tDown)
        t.useTexture = !t.useTexture;
    t.tDown = tDown;

    bool nDown = (glfwGetKey(win, GLFW_KEY_N) == GLFW_PRESS);
    if(nDown && !t.nDown && texCount > 0)
        t.texIndex = (t.texIndex + 1) %texCount; // para dar la vuelta al llegar al final
    t.nDown = nDown;
}