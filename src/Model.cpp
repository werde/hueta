#include "Model.h"

#include "IMAGELoad.h"

Model::Model()
{
    tex = 0;
    v.reserve(100);
    vt.reserve(100);
    vn.reserve(100);
}

bool Model::LoadObj(Model* m, const char* path = ".\\assets\\meshes\\t.obj")
{
    FILE * f = fopen(path, "rb");
    if( f == NULL ){
        printf("Impossible to open the file !\n");
        printf("%s\n", path);
        return false;
    }
    printf("loadobj end !\n");

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    std::vector<GLuint> vi;
    std::vector<GLuint> uvi;
    std::vector<GLuint> ni;

    while (1)
    {
        char buf[256];
        int res = fscanf(f, "%s", buf);

        if (res == EOF)
            break;

        if (strcmp(buf, "v") == 0)
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            v.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "vt") == 0)
        {
            vec2 vBuf;
            fscanf(f, "%f %f\n", &(vBuf.m[0]), &(vBuf.m[1]));
            vBuf.m[1] = 1 - vBuf.m[1];
            vt.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "vn") == 0)
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            vn.push_back(vBuf);
            continue;
        }

        if (strcmp(buf, "f") == 0)
        {
            GLuint viBuf[3], uviBuf[3], niBuf[3];
            fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &viBuf[0], &uviBuf[0], &niBuf[0],
                                                        &viBuf[1], &uviBuf[1], &niBuf[1],
                                                        &viBuf[2], &uviBuf[2], &niBuf[2]);

            vi.push_back(viBuf[0]);
            vi.push_back(viBuf[1]);
            vi.push_back(viBuf[2]);
            uvi.push_back(uviBuf[0]);
            uvi.push_back(uviBuf[1]);
            uvi.push_back(uviBuf[2]);
            ni.push_back(niBuf[0]);
            ni.push_back(niBuf[1]);
            ni.push_back(niBuf[2]);
            continue;
        }
        char ubuffer[1024];
        fgets(ubuffer, sizeof(ubuffer), f);
    }

	// For each vertex of each triangle
    for (unsigned int i = 0; i < vi.size(); i++ )
    {

        // Get the indices of its attributes
        unsigned int vit = vi[i];
        unsigned int uvit = uvi[i];
        unsigned int nit = ni[i];

        // Get the attributes thanks to the index
        vec3 vertex = v[vit-1];
        vec2 uv = vt[uvit-1];
        vec3 normal = vn[nit-1];

        // Put the attributes in buffers
        m->v.push_back(vertex);
        m->vt.push_back(uv);
        m->vn.push_back(normal);
    }

    for (int i = 0; i < m->v.size(); i++)
    {
        //printf("#%d %f %f %f \n", i, m->v[i].m[0],  m->v[i].m[1],  m->v[i].m[2]);
        //printf("    %f %f    \n", m->vt[i].m[0], m->vt[i].m[1]);
    }

    fclose(f);

    //
    m->tex = loadTex(".\\assets\\t.dds");

    return true;
}

Model::~Model()
{
    //dtor
}
