#include "Model.h"

Model::Model()
{
    v.reserve(10);
    vt.reserve(10);
    vn.reserve(10);
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

    std::vector<vec3> v;
    std::vector<vec2> vt;
    std::vector<vec3> vn;

    std::vector<veci3> vi;
    std::vector<veci3> uvi;
    std::vector<veci3> ni;

    while (1)
    {
        char buf[256];
        int res = fscanf(f, "%s", buf);

        if (res == EOF)
            break;

        if (!strcmp(buf, "v"))
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            v.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "vt"))
        {
            vec2 vBuf;
            fscanf(f, "%f %f\n", &(vBuf.m[0]), &(vBuf.m[1]));
            vt.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "vn"))
        {
            vec3 vBuf;
            fscanf(f, "%f %f %f\n", &(vBuf.m[0]), &(vBuf.m[1]), &(vBuf.m[2]));
            vn.push_back(vBuf);
            continue;
        }

        if (!strcmp(buf, "f"))
        {
            veci3 viBuf, uviBuf, niBuf;
            fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &viBuf.m[0], &viBuf.m[1], &viBuf.m[2],
                                                        &uviBuf.m[0], &uviBuf.m[1], &uviBuf.m[2],
                                                        &niBuf.m[0], &niBuf.m[1], &niBuf.m[2]);

            vi.push_back(viBuf);
            uvi.push_back(uviBuf);
            ni.push_back(niBuf);
        }
    }

	// For each vertex of each triangle
    for (unsigned int i = 0; i < vi.size(); i++ )
    {

        // Get the indices of its attributes
        unsigned int vertexIndex = vi[i];
        unsigned int uvIndex = uvi[i];
        unsigned int normalIndex = ni[i];

        // Get the attributes thanks to the index
        vec3 vertex = temp_vertices[ vertexIndex-1 ];
        vec2 uv = temp_uvs[ uvIndex-1 ];
        vec3 normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        m->v.push_back(vertex);
        m->vt.push_back(uv);
        m->vn.push_back(normal);

    }


    fclose(f);
    return true;
}

Model::~Model()
{
    //dtor
}
