#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "GL/gl.h"
#include "../mat.h"

class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(Model* m);

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    GLuint tex;

    protected:

    private:
};

#endif // MODEL_H
