#include "CommandLine.h"

#include "../src/ImgLoad.h"
#include "../__trash.h"
#include "../include/Model.h"

CommandLine::CommandLine(Pos p, Font* f)
    : _f{f}
{
    w = 800; h = 600;
    g = 6;
    fg = g*2.0/(GLfloat)w;

    _pos.x = p.x + fg;
    _pos.y = p.y - p.h + fg;
    _pos.h = 2*fg + f->fFH;
    _pos.w = p.w - 2*fg;
    bottomLine = _pos.y;
    leftLine = _pos.x;

    memset(_buf, '90', 10)
    sz_Buf=25;
    /*for (int i = 0; i < sz_Buf-1; i++)
    {
        _buf[i] = convert(_buf[i]);
    }*/

    fillvv();

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);
}

void CommandLine::fillvv()
{
    unsigned char* pEnd = _buf + sz_Buf - 1;
    unsigned char* pStart = _buf;

    unsigned char* p = _buf;
    int i = 0;
    while (p <= pEnd)
    {

        GLfloat b = bottomLine;
        GLfloat t = bottomLine + fg + fFH;
        GLfloat l = leftLine + (fg + i*_f->fFW);
        GLfloat r = leftLine + (fg + (i+1)*_f->fFW);

        _v.push_back({l, b, 0.0f});
        _v.push_back({r, b, 0.0f});
        _v.push_back({r, t, 0.0f});
        _v.push_back({l, t, 0.0f});

        i++;
    }
}

void CommandLine::render(GLuint sp)
{
/*	GLuint TextureID = glGetUniformLocation(sp, "texSampler");

    glActiveTexture(_f->tex);
    glBindTexture(GL_TEXTURE_2D, _f->tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);*/
/*
    glActiveTexture(_f->tex);
    glBindTexture(GL_TEXTURE_2D, _f->tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);*/
}

CommandLine::~CommandLine()
{
}
