#include "QuakeConsole.h"
#include "shaders.h"

#include "../__trash.h"
#include "../include/Model.h"

QuakeConsole::QuakeConsole() : _enabled{false}
{
    /// Symbol table
    GLfloat offsetX = 16.0;
    GLfloat offsetY = 20.0;
	GLfloat dim = 256.0;

	std::vector<Symbol> symbols;
	char keyIndex = 0;
	for (int x = 0; x < dim; x+=16)
        for(int y = 16; y < 256; y+=20)
    {
        Symbol s;
        s.c = keyIndex;

        s.uv[0].x = x/          (GLfloat)dim;
        s.uv[0].y = y/          (GLfloat)dim;

        s.uv[1].x = (x+offsetX)/(GLfloat)dim;
        s.uv[1].y = y/          (GLfloat)dim;

        s.uv[2].x = x/          (GLfloat)dim;
        s.uv[2].y = (y+offsetY)/(GLfloat)dim;

        s.uv[3].x = (x+offsetX)/(GLfloat)dim;
        s.uv[3].y = (y+offsetY)/(GLfloat)dim;
/*
        s.uv[0].x = x/          (GLfloat)dim;
        s.uv[0].y = (y+offsetY)/(GLfloat)dim;

        s.uv[1].x = (x+offsetX)/(GLfloat)dim;
        s.uv[1].y = (y+offsetY)/(GLfloat)dim;

        s.uv[2].x = x/          (GLfloat)dim;
        s.uv[2].y = y/          (GLfloat)dim;

        s.uv[3].x = (x+offsetX)/(GLfloat)dim;
        s.uv[3].y =  y          /(GLfloat)dim;
*/
        symbols.push_back(s);
        keyIndex++;

    }

    /// Shader program
	_bsp = glCreateProgram();
    compileShaderProgramm(&_bsp, ".\\billboard.vert", ".\\billboard.frag");

    /// rest
    _tex = loadTex(loadPNG(".\\shizzle.png"));
    //_tex = loadBMP_custom(".\\shizzle.bmp");

    _buf[0] = 41;
    _buf[1] = 64;
    _buf[2] = 52;
    _buf[3] = 65;
    _buf[4] = 11;
    _buf[5] = 29;
    _buf[6] = 64;
    _buf[7] = 52;
    _buf[8] = 52;
    _buf[9] = 41;


    for (int i = 0; i < sizeof(_buf); i++)
    {
        int sIndex = _buf[i];
        calcOGLcoords(i);
        _uv.push_back(symbols[sIndex].uv[0]);
        _uv.push_back(symbols[sIndex].uv[1]);
        _uv.push_back(symbols[sIndex].uv[2]);
        _uv.push_back(symbols[sIndex].uv[3]);
    }

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);

    _qbc = new QCBackplate();
}

void QuakeConsole::calcOGLcoords(int i)
{
    vec3 lt, lb, rt, rb;
    float w = 800.0/2;
    float h = 600.0/2;
    float cw= 16.0;
    float ch= 20.0;

    lt.x = -1.0 + (QCXPAD*w + XGAP + i*cw)/w;
    lt.y = 1.0 - (QCYPAD*h + YGAP)/h;
    lt.z = 0.0;

    lb.x = -1.0 + (QCXPAD*w + XGAP + i*cw)/w;
    lb.y = 1.0 - (QCYPAD*h + YGAP + ch)/h;
    lt.z = 0.0;

    rt.x = -1.0 + (QCXPAD*w + XGAP + cw+ i*cw)/w;
    rt.y = 1.0 - (QCYPAD*h + YGAP)/h;
    lt.z = 0.0;

    rb.x = -1.0 + (QCXPAD*w + XGAP + cw+ i*cw)/w;
    rb.y = 1.0 - (QCYPAD*h + YGAP + ch)/h;
    rb.z = 0.0;

    _v.push_back(lb);
    _v.push_back(rb);
    _v.push_back(lt);
    _v.push_back(rt);
}

void QuakeConsole::draw()
{
    if (!_enabled) return;

    glUseProgram(_bsp);

    _qbc->render(_bsp);

	GLuint TextureID = glGetUniformLocation(_bsp, "texSampler");

    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _v.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

QuakeConsole::~QuakeConsole()
{
    delete _qbc;
}
