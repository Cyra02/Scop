#include "../includes/ObjLoad.hpp"



#include <fstream>
#include <sstream>
#include <iostream>

bool ObjLoad(const std::string &path, std::vector<Vec3> &objvertices, std::vector<unsigned int> &indices)
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