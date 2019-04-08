#include "Entity.h"

Entity::Entity(const char* p1=".\\assets\\meshes\\t.obj", const char* p2=".\\assets\\t.dds")
{
    _m = new Model(p1);
}

Entity::~Entity()
{

}
