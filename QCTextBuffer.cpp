#include "QCTextBuffer.h"

#include "../__trash.h"

QCTextBuffer::QCTextBuffer()
{
    //ctor
}

void QCTextBuffer::render(GLuint sp)
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

QCTextBuffer::~QCTextBuffer()
{
    //dtor
}
