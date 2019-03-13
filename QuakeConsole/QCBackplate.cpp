#include "QCBackplate.h"

#include "../__trash.h"
#include "../include/Model.h"

QCBackplate::QCBackplate()
{
    _v.push_back({-0.95f, -0.95f, 0.0f});
    _v.push_back({0.95f, -0.95f, 0.0f});
    _v.push_back({-0.95f,  0.95f, 0.0f});
    _v.push_back({0.95f,  0.95f, 0.0f});

    _uv.push_back({0.0, 0.0});
    _uv.push_back({1.0, 0.0});
    _uv.push_back({0.0, 1.0});
    _uv.push_back({1.0, 1.0});

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _tex = loadBMP_custom(".\\QCbg.bmp");
    //_tex = loadTex();
}

QCBackplate::QCBackplate(GLfloat ofTop, GLfloat ofBottom, GLfloat ofLeft, GLfloat ofRight)
{
    GLfloat top = 1.0f - ofTop;
    GLfloat bottom = -1.0f + ofBottom;
    GLfloat left = -1.0f + ofLeft;
    GLfloat right = 1.0f - ofRight;

    _v.push_back({left , bottom, 0.0f});
    _v.push_back({right, bottom, 0.0f});
    _v.push_back({left ,  top,   0.0f});
    _v.push_back({right,  top,   0.0f});

    _uv.push_back({0.0, 0.0});
    _uv.push_back({1.0, 0.0});
    _uv.push_back({0.0, 1.0});
    _uv.push_back({1.0, 1.0});

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _tex = loadBMP_custom(".\\QCbg.bmp");
}

void QCBackplate::render(GLuint sp)
{
	GLuint TextureID = glGetUniformLocation(sp, "texSampler");

    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

QCBackplate::~QCBackplate()
{
    //dtor
}
