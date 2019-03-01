#ifndef QCBACKPLATE_H
#define QCBACKPLATE_H

#include <vector>
#include "GL/gl.h"
#include "GL/glext.h"

#include "../mat.h"

class QCBackplate
{
public:
    QCBackplate();
    QCBackplate(GLfloat ofTop, GLfloat ofBottom, GLfloat ofLeft, GLfloat ofRight);

    virtual ~QCBackplate();

    void render(GLuint sp);
protected:
private:
    GLuint _tex;
    GLuint _vbo;
    GLuint _uvbo;

    std::vector<vec3> _v;
    std::vector<vec2> _uv;
};

#endif // QCBACKPLATE_H
