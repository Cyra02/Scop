#ifndef OBJLOAD_HPP
#define OBJLOAD_HPP

#include <string>
#include <vector>

struct Vec3
{
    float  x, y, z;
     static Vec3 centro(const std::vector<Vec3> &vertices);
};

bool objLoad(const std::string &path, std::vector<Vec3> &objvertices, std::vector<unsigned int> &indices);


#endif