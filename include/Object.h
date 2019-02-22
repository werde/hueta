#ifndef OBJECT_H
#define OBJECT_H

#include "../mat.h"

class Model;

class Object
{
    public:
        Object();
        virtual ~Object();

    protected:

    private:
        Model* _m;
        vec3 _pos;
};

#endif // OBJECT_H
