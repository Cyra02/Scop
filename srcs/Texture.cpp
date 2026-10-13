#include "../includes/Texture.hpp"

bool loadPPM(const std::string &path, Texture &tex)
{
    std::ifstream file(path, std::ios::binary);

    if(!file.is_open())
    {
        std::cerr << "ERROR: no se puede abrir: " << path << std::endl;
        return false;
    }

    std::string m;
    int maxVal;
    file >> m >> tex.width >> tex.height >> maxVal;

    if(m != "P6" || maxVal != 255)
    {
        std::cerr << "ERROR: " << path << " no es valido necesita se PPM" << std::endl;
        return false;
    }
    file.get();

    size_t size = (size_t)tex.width * tex.height *3;
    tex.pixeles.resize(size);
    file.read((char *)tex.pixeles.data(), size);

    if((size_t)file.gcount() != size)
    {
        std::cerr << "ERROR: " << path << " no esta entero" << std::endl;
        return false;
    }
    return true;
}

GLuint createTextura(const Texture &tex)
{
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0 , GL_RGB, GL_UNSIGNED_BYTE, tex.pixeles.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return id;
}

float updateTextura(float current, bool useTextura, float dt)
{
    float target = useTextura ? 1.0f : 0.0f; // 0 gris 1 textura
    float step = 2.0f * dt; 
    if(current < target)
    {
        current += step;
        if(current > target)
            current= target;
    }else if(current > target)
    {
        current -= step;
        if(current < target)
            current = target;
    }
    return current;
}
