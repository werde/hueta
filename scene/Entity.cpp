#include "Entity.h"

#include "Model.h"
#include "IMAGELoad.h"

Entity::Entity(const char* p1=".\\assets\\meshes\\t.obj", const char* p2=".\\assets\\t.dds")
    : _pos{0.0, 0.0, 0.0}
{
    _m = new Model();
    _m->LoadObj(_m, p1);
    _t=loadTex(p2);
    printf("%skoko%d", p2, _t);
}

Entity::Entity(Model* m, GLuint texture)
    : _pos{0.0, 0.0, 0.0}
{
    _m = m;
    _t = texture;
}

Entity::~Entity()
{

}
