#include "QuakeConsole.h"
#include "shaders.h"

#include "../__trash.h"
#include "../include/Model.h"

QuakeConsole::QuakeConsole() : _enabled{false}
{
	v.push_back({-0.9f, -0.9f, 0.0f});
	v.push_back({0.9f, -0.9f, 0.0f});
	v.push_back({-0.9f,  0.9f, 0.0f});
	v.push_back({0.9f,  0.9f, 0.0f});

	uvs.push_back({0.0, 0.0});
	uvs.push_back({1.0, 0.0});
	uvs.push_back({0.0, 1.0});
	uvs.push_back({1.0, 1.0});

	strcpy(p1, ".\\billboard.vert");
	strcpy(p2, ".\\billboard.frag");

    GLfloat offsetX = 16.0;
    GLfloat offsetY = 20.0;
	GLfloat dim = 256.0;

	std::vector<Symbol> true_uvs;
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

        true_uvs.push_back(s);
        keyIndex++;
    }

	bsp = glCreateProgram();
    compileShaderProgramm(&bsp, p1, p2);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, v.size()*sizeof(vec3), &(v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    int sz = true_uvs.size();
    glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(vec2), &(true_uvs[23].uv[0]), GL_DYNAMIC_DRAW);

    _tex = loadBMP_custom(".\\shizzle.bmp");
    for (int i = 0; i < 8; i++)
    {
        _buf[i] = i*3;
    }

    for (int i = 0; i < sizeof(_buf); i++)
    {

    }
}

void QuakeConsole::calcOGLcoords(int i, )
{
    vec2 lt, lb, rt, rb;
    float w = 800.0;
    float h=600.0;
    float cw=16.0;
    float ch=20.0;
    lt.x = QCXPAD*w + XGAP + cw*i;
    lt.y = QCYPAD*h + YGAP + 0*i;

    lb.x = QCXPAD*w + XGAP + cw*i;
    lb.y = QCXPAD*w + YGAP + ch*(i+1);

    rt.x = QCXPAD*w + XGAP + cw*(i+1);
    rt.y = QCYPAD*h + YGAP + 0*i;

    lt.x = QCXPAD*w + XGAP + cw*(i+1);
    lt.x = QCXPAD*w + YGAP + ch*(i+1);

}

void QuakeConsole::draw()
{
    if (!_enabled) return;

    glUseProgram(bsp);

	//GLuint CameraRight_worldspace_ID  = glGetUniformLocation(bsp, "CameraRight_worldspace");
	//GLuint CameraUp_worldspace_ID  = glGetUniformLocation(bsp, "CameraUp_worldspace");
	//GLuint ViewProjMatrixID = glGetUniformLocation(bsp, "VP");
	//GLuint BillboardPosID = glGetUniformLocation(bsp, "BillboardPos");
	//GLuint BillboardSizeID = glGetUniformLocation(bsp, "BillboardSize");

	//mat4 ViewMatrix = IDENTITY_MATRIX;
    //glUniform3f(CameraRight_worldspace_ID, ViewMatrix.m[0], ViewMatrix.m[1], ViewMatrix.m[2]);
    //glUniform3f(CameraUp_worldspace_ID   , ViewMatrix.m[0+4*1], ViewMatrix.m[1 + 4*1], ViewMatrix.m[2 + 4*1]);

    //glUniform3f(BillboardPosID, 0.0f, 0.5f, 0.0f); // The billboard will be just above the cube
    //glUniform2f(BillboardSizeID, 1.0f, 0.125f); // and 1m*12cm, because it matches its 256*32 resolution =)
	//glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &(ViewMatrix.m[0]));

	GLuint TextureID = glGetUniformLocation(bsp, "texSampler");

    glActiveTexture(_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glUniform1i(TextureID, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

QuakeConsole::~QuakeConsole()
{
    //dtor
}
