#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
    if(!glfwInit())
    {
        std::cerr << "ERROR: No se puede iniciar GLFW" << std::endl;
        return 1;
    }

    // a la hora de crear la ventana acotamos la version de OPENGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *win= glfwCreateWindow(800,600, "scop", NULL,NULL);

    if(!win)
    {
        std::cerr << "ERROR: No se puede iniciar la ventana" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(win);

    while(!glfwWindowShouldClose(win))
    {
        //bueno saber que hay inputs manuales esto es para que se cierree
        // si pulsas el escape
        if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(win, GLFW_TRUE);
        }

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
}