#define GL_GLEXT_PROTOTYPES // libreria libGL
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <GLFW/glfw3.h>
#include "../includes/Mat4.hpp"
#include "../includes/ObjLoad.hpp"
#include "../includes/Input.hpp"
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

static float ToRadians(float grados)
{
    return grados * 3.14159f / 180.0f;

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
    glEnable(GL_DEPTH_TEST);


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

    // cargar objeto
    std::vector<Vec3> objVertices;
    std::vector<unsigned int> objIndices;

    if(!objLoad("resources/Flower.obj", objVertices, objIndices))
        return 1;
    
    std::cout << "vertices leidos: " << objVertices.size() << std::endl;
    std::cout << "primero: " << objVertices[0].x << " " << objVertices[0].y << " " << objVertices[0].z << std::endl;
    std::cout << "vertices: " << objVertices.size() << "triangulos: " << objIndices.size() / 3 << std::endl; 

    std::vector<float> data;
    for(size_t i = 0; i < objVertices.size(); i++)
    {
        float gray = 0.3f + 0.1f * (i % 6);
        data.push_back(objVertices[i].x);
        data.push_back(objVertices[i].y);
        data.push_back(objVertices[i].z);
        data.push_back(gray);
        data.push_back(gray);
        data.push_back(gray);
    }
    std::cout << "floats en data " << data.size() << std::endl;

    //triangulo
    /* float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    }; */

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
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

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

    //otra mierda mas el EBO
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // a ver que esto lo tenia mal y no entiendo muy bien porque osea no es sizeof(float) sino unisgned int no solo por que los indices
    // no puedan ser negativos sino qeu tambien es por como lo lee del tipo de cada vector
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, objIndices.size() * sizeof(unsigned int), objIndices.data(), GL_STATIC_DRAW); 


    //std::cout << readFile("shaders/basic.vert") << std::endl;

   //centrarlo
   Vec3 centre = Vec3::centro(objVertices);
   std::cout << "centro: " << centre.x << " " << centre.y << " " << centre.z << std::endl;

    Transform t = {0.0f, ToRadians(-90), 0.0f, 0.0f, -8.0f}; // rotado porque viene de lado el 42
    float lastTime =(float)glfwGetTime();

    while(!glfwWindowShouldClose(win))
    {
        //bueno saber que hay inputs manuales esto es para que se cierree
        // si pulsas el escape
        

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // dibujar
        glUseProgram(program);

        //rotar
        float now = (float)glfwGetTime();
        float dt = now -lastTime;
        lastTime = now;
        input(win, t, dt);
        
        // el orden importa el 0.5 es el angulo en el que crece si es negativo irapara el otro lado jeje
        Mat4 model =  Mat4::translate(t.posX, t.posY, t.posZ)  * Mat4::rotateY(t.rotY) * Mat4::rotateX(t.rotX)* Mat4::translate(-centre.x, -centre.y, -centre.z) ;
        

        Mat4 proj = Mat4::perspectiva(ToRadians(50.0f), 800.0f / 600.0f, 0.1f , 100.0f );
        GLint locP = glGetUniformLocation(program, "uProjection");

     
        glUniformMatrix4fv(locP, 1, GL_FALSE, proj.m);

        GLint loc = glGetUniformLocation(program, "uModel");
        glUniformMatrix4fv(loc, 1, GL_FALSE, model.m);

        glBindVertexArray(vao);
       // glDrawArrays(GL_TRIANGLES, 0, 3); para el triangulo
        glDrawElements(GL_TRIANGLES, objIndices.size(), GL_UNSIGNED_INT, 0);
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
    glDeleteBuffers(1, &ebo);

    glDeleteProgram(program);

    glfwDestroyWindow(win);
    glfwTerminate();
}