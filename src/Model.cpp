#include "Model.h"

Model::Model()
{
    //ctor
}

bool Model::LoadObj(Model* m)
{
    std::string path = ".\\t.obj";

    FILE * f = fopen(path.c_str(), "rb");
    if( f == NULL ){
        printf("Impossible to open the file !\n");
        printf("%s\n", path.c_str());
        return false;
    }


    printf("loadobj end !\n");

    while (1)
    {
        char buf[256];
        int res = fscanf(f, "%s", buf);
        printf("%s\n", buf);

        if (res == EOF)
            break;

        GLfloat f1, f2, f3;

        if (strcmp(buf, "v"))
        {
            fscanf(f, "%f %f %f\n", &f1, &f2, &f3);//&(m->v.back().m[0]), &(m->v.back().m[1]), &(m->v.back().m[2])
        }
        m->v.back()
        if (strcmp(buf, "vt"))
        {

        }

        if (strcmp(buf, "vt"))
        {

        }

        if (strcmp(buf, "f"))
        {

        }
    }



    fclose(f);
    return true;
}

Model::~Model()
{
    //dtor
}
