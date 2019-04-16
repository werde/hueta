#ifndef ENTITY_H
#define ENTITY_H

#include <GL/gl.h>

#include "../mat.h"

class Model;

class Entity
{
public:
    Entity(const char* p1=".\\assets\\meshes\\t.obj", const char* p2=".\\assets\\t.dds");
    Entity::Entity(Model* m, GLuint texture);
    virtual ~Entity();

    Model*  _m;
    GLuint _t;
    vec3 _pos;
private:
};

#endif // ENTITY_H
