#ifndef QCTEXTBUFFER_H
#define QCTEXTBUFFER_H

#include <vector>
#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"

class QCTextBuffer
{
public:
    QCTextBuffer();
    virtual ~QCTextBuffer();

    void render(GLuint sp);
protected:

private:
    std::vector<vec3> _v;
    std::vector<vec2> _uv;

    GLuint _tex;
    GLuint _bsp;
    GLuint _vbo;
    GLuint _uvbo;
};

#endif // QCTEXTBUFFER_H
