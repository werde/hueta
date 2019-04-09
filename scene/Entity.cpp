#include "Entity.h"

#include "Model.h"
#include "IMAGELoad.h"

Entity::Entity(const char* p1=".\\assets\\meshes\\t.obj", const char* p2=".\\assets\\t.dds")
{
    _m = new Model();
    _m->LoadObj(_m, p1);
    _t=loadTex(p2);
}

Entity::~Entity()
{

}
