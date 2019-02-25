#include "QuakeConsole.h"
#include "shaders.h"

#include "../__trash.h"

QuakeConsole::QuakeConsole()
{
	v.push_back({-0.5f, -0.5f, 0.0f});
	v.push_back({0.5f, -0.5f, 0.0f});
	v.push_back({-0.5f,  0.5f, 0.0f});
	v.push_back({0.5f,  0.5f, 0.0f});

    compileShaderProgramm(&bsp, ".\\billboard.vert", ".\\billboard.frag");

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), &(v[0]), GL_DYNAMIC_DRAW);
}

void QuakeConsole::draw()
{
    glUseProgram(bsp);

	GLuint CameraRight_worldspace_ID  = glGetUniformLocation(bsp, "CameraRight_worldspace");
	GLuint CameraUp_worldspace_ID  = glGetUniformLocation(bsp, "CameraUp_worldspace");
	GLuint ViewProjMatrixID = glGetUniformLocation(bsp, "VP");
	GLuint BillboardPosID = glGetUniformLocation(bsp, "BillboardPos");
	GLuint BillboardSizeID = glGetUniformLocation(bsp, "BillboardSize");


	mat4 ViewMatrix = IDENTITY_MATRIX;
    glUniform3f(CameraRight_worldspace_ID, ViewMatrix.m[0], ViewMatrix.m[1], ViewMatrix.m[2]);
    glUniform3f(CameraUp_worldspace_ID   , ViewMatrix.m[0+4*1], ViewMatrix.m[1 + 4*1], ViewMatrix.m[2 + 4*1]);

    glUniform3f(BillboardPosID, 0.0f, 0.5f, 0.0f); // The billboard will be just above the cube
    glUniform2f(BillboardSizeID, 1.0f, 0.125f); // and 1m*12cm, because it matches its 256*32 resolution =)
	glUniformMatrix4fv(ViewProjMatrixID, 1, GL_FALSE, &(ViewMatrix.m[0]));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
}

QuakeConsole::~QuakeConsole()
{
    //dtor
}
