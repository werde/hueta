#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"
#include "../src/PNGLoad.h"

class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(Model* m, const char* path = ".\\assets\\meshes\\t.obj");

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;
};

#endif // MODEL_H
