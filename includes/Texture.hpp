#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#define GL_GLEXT_PROTOTYPES

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <GLFW/glfw3.h>

struct Texture
{
    int width;
    int height;

    std::vector<unsigned char> pixeles;
};

GLuint createTextura(const Texture &tex);
bool loadPPM(const std::string &path, Texture &tex);
float updateTextura(float current, bool useTextura, float dt);

#endif