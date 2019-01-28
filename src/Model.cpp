#include "Model.h"

Model::Model()
{
    //ctor
}

bool Model::LoadObj(std::string path = "./assets/t.obj")
{
    FILE * file = fopen(path.c_str(), "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }


}

Model::~Model()
{
    //dtor
}
