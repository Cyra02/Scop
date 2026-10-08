#include "../includes/ObjLoad.hpp"



#include <fstream>
#include <sstream>
#include <iostream>

bool objLoad(const std::string &path, std::vector<Vec3> &objvertices, std::vector<unsigned int> &indices)
{
    std::ifstream file(path);

    if(!file.is_open())
    {
        std::cerr << "ERROR: No se pudo abrir " << path << std::endl;
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line); // convierte la line extraida en texto que se puede leer
        std::string type;
        iss >> type;

        if(type == "v")
        {
            Vec3 v;
            iss >> v.x >> v.y >> v.z; // leer uno por uno
            objvertices.push_back(v);// y pues ponerlo al final
        }
        else if(type == "f")
        {
            std::vector <unsigned int> face;
            std::string token;
            while(iss >> token)
                face.push_back(std::stoi(token) - 1); //para contar desde cero
            
            for(size_t i = 1 ; i + 1 < face.size(); i ++)
            {
                indices.push_back(face[0]);
                indices.push_back(face[i]);
                indices.push_back(face[i + 1]);
            }
        }


    }
    return true;
}

Vec3 Vec3::centro(const std::vector<Vec3> &vertices)
{
    if(vertices.empty())
        return Vec3{0.0f, 0.0f, 0.0f};
    
    Vec3 mn = vertices[0];
    Vec3 mx = vertices[0];

    for(size_t i = 1 ; i < vertices.size(); i++)
    {
        if(vertices[i].x < mn.x)
            mn.x = vertices[i].x;
        if(vertices[i].y < mn.y)
            mn.y = vertices[i].y;
        if(vertices[i].z < mn.z)
            mn.z = vertices[i].z;

        if(vertices[i].x > mx.x)
            mx.x = vertices[i].x;
        if(vertices[i].y > mx.y)
            mx.y = vertices[i].y;
        if(vertices[i].z > mx.z)
            mx.z = vertices[i].z;

    }
    /* std::cout << "min: " << mn.x << " " << mn.y << " " << mn.z << std::endl;
    std::cout << "max: " << mx.x << " " << mx.y << " " << mx.z << std::endl; */
    return Vec3{(mn.x + mx.x)/ 2.0f,
                (mn.y + mx.y)/ 2.0f,
                (mn.z + mx.z)/ 2.0f,};
}

std::vector<float> faceData(const std::vector<Vec3> &vertices, const std::vector<unsigned int> &indices)
{
    std::vector<float> data;
    data.reserve(indices.size() * 6);

    for(size_t tri = 0; tri < indices.size() / 3; tri++)
    {
        float gray = 0.3f + 0.4f * (float)((tri * 37) % 10) / 10.0f; // mas variacon de grises 

        for(int k = 0; k < 3; k++)
        {
            const Vec3 &v = vertices[indices[tri * 3 + k]];
            data.push_back(v.x);
            data.push_back(v.y);
            data.push_back(v.z);
            data.push_back(gray);
            data.push_back(gray);
            data.push_back(gray);

            
        }
    }
    return data;
}

float maxExtent(const std::vector<Vec3> &vertices)
{
    if(vertices.empty())
        return 1.0f;
    
    Vec3 mn = vertices[0];
    Vec3 mx = vertices[0];

    for(size_t i = 1; i < vertices.size(); i++)
    {
        if(vertices[i].x < mn.x)
            mn.x = vertices[i].x;
        if(vertices[i].y < mn.y)
            mn.y = vertices[i].y;
        if(vertices[i].z < mn.z)
            mn.z = vertices[i].z;

        if(vertices[i].x > mx.x)
            mx.x = vertices[i].x;
        if(vertices[i].y > mx.y)
            mx.y = vertices[i].y;
        if(vertices[i].z > mx.z)
            mx.z = vertices[i].z;
    }

    float ex = mx.x - mn.x;
    float ey = mx.y - mn.y;
    float ez = mx.z - mn.z;

    float m = ex;
    if(ey > m) 
        m = ey;
    if(ez > m)
        m = ez;

    return(m > 0.0f) ? m : 1.0f;
    
}