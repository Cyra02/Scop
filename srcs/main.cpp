#define GL_GLEXT_PROTOTYPES // libreria libGL
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <GLFW/glfw3.h>
#include "../includes/Mat4.hpp"
#include <iostream>
#include <fstream> // para leer archivos
#include <sstream> // volcartexto
#include <string>


static std::string readFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


static GLuint compileShader(GLenum type, const std::string &path)
{
    std::string code = readFile(path);
    const char *src = code.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint bien;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &bien);
    if(!bien)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cerr << "Error comilando " << path << ":\n" << log << std::endl;

    }
    return shader;
}

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


    // compilacion de shaders
    GLuint vs = compileShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    // dibujar
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    //log de error
    GLint bien;
    glGetProgramiv(program, GL_LINK_STATUS, &bien);
    if (!bien)
    {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cerr << "Error enlazando el programa:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    //triangulo
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    };

    // vale no lo entiendo muy bien
    //VBO(Vertex BUffer object) bloque de memoria donde copio el array de vertices
    //VAO la gpu no sabe como lo hemos puesto de los 3 primeros posicio 0 y los 3 siguentes colo el 1 
    //guAarda la descripcion y como leer el VBO -> cuantos vertices tiene que tipo cuanto ocupa cada vertice offset donde empieza  y que VBO leer
    // a ver si me estero


    
    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao); // el vao va primero para grabar lo de despues
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // y ahora atributos
    // son el 0/1 de lyout de los shaders
    //3 cuantso valores
    //GL_Float tipo de valor
    //GLFALSE no normalizar nos e
    //6 * sizeog(float) porque cada vertice ocupa 6
    //offset suma de los atributos anteriores de 0-24 de 4 4n 4

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    //std::cout << readFile("shaders/basic.vert") << std::endl;


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

        // dibujar
        glUseProgram(program);

        //rotar
        float angle = (float)glfwGetTime();
        Mat4 model = Mat4::rotateY(angle);

        GLint loc = glGetUniformLocation(program, "uModel");
        glUniformMatrix4fv(loc, 1, GL_FALSE, model.m);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //para error del dibujado
        GLint bien;
        glGetProgramiv(program, GL_LINK_STATUS, &bien);
        if (!bien)
        {
            char log[512];
            glGetProgramInfoLog(program, 512, NULL, log);
            std::cerr << "Error enlazando el programa:\n" << log << std::endl;
        }



        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    //limpiamos
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glDeleteProgram(program);

    glfwDestroyWindow(win);
    glfwTerminate();
}