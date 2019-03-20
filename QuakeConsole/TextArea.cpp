#include "TextArea.h"

#include "../__trash.h"
#include "../include/Model.h"


TextArea::TextArea()
{
    fH = 20; fW = 16;
    w = 800; h = 600;
    g = 10;

    symPerStr = (w - 2*g)/fW;
    numStrings = (h/2 - g)/(g + fH);

    /// Fill symbol table
    GLfloat offsetX = fW;
    GLfloat offsetY = fH;
	GLfloat dim = 256.0;

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
        _symbols.push_back(s);
        keyIndex++;
    }

    /// Load texture
    _tex = loadTex(loadPNG(".\\shizzle_i.png"));

    /// Buffer
    unsigned char* str = "Based on your input, get \na\nrandom alpha numeric string.\n The random string \ngenerator creates a series of \nnumbers and letters \nthat have no pattern.\n These can be helpful for creating security \n codes.\n";
    int len = strlen(str);
    sz_Buf = len;
    memcpy(_buf, str, len);

    for (int i = 0; i < sz_Buf; i++)
    {
        _buf[i] = convert(_buf[i]);
    }

    fillvv();

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(vec3), &(_v[0]), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);
}

void TextArea::uv(int i)
{
    int sIndex = _buf[i];
    _uv.push_back(_symbols[sIndex].uv[0]);
    _uv.push_back(_symbols[sIndex].uv[1]);
    _uv.push_back(_symbols[sIndex].uv[3]);
    _uv.push_back(_symbols[sIndex].uv[2]);
}

void TextArea::ss(int strNum, int xpos)
{
    vec3 lt, lb, rt, rb;
    GLfloat fFH = fH*2.0/(GLfloat)h;
    GLfloat fFW = fW*2.0/(GLfloat)w;
    GLfloat fg = 2.0*g/(GLfloat)h;

    GLfloat bottomLine = _pos.y - _pos.h;
    GLfloat leftLine = _pos.x;

    int n2 = strNum;

    GLfloat b = bottomLine + (fg + n2*fFH + n2*fg);
    GLfloat t = bottomLine + (fg + (n2+1)*fFH + n2*fg);
    GLfloat l = leftLine + (fg + xpos*fFW);
    GLfloat r = leftLine + (fg + (xpos+1)*fFW);

    _v.push_back({l, b, 0.0f});
    _v.push_back({r, b, 0.0f});
    _v.push_back({r, t, 0.0f});
    _v.push_back({l, t, 0.0f});
}

void TextArea::fillvv()
{
    unsigned char* pEnd = _buf + sz_Buf - 1;
    unsigned char* pStart = _buf;
    printf("// ne nuzhno int charIndex = ;\n\n\n\n");

    int curStr = 0;

    unsigned char* p = pEnd - 1;
        printf("*****test******* %d %d %d %d %d %c \n", pEnd - pStart, pEnd - _buf, pEnd - p, *p, *p );

    while (p >= pStart)
    {
        unsigned char* sEnd = p;
        do
        {
            p--;
        } while ((*p != '\n') && (p >= pStart));

        int i = 0;

        for (unsigned char* tPtr = p + 1; tPtr != sEnd; tPtr++)
        {
            ss(curStr, i);
            uv(tPtr - pStart);
            i++;
        }
        printf("$ # %d %d-- % \n", curStr, sEnd - p + 1);
        curStr++;
    }
}

void TextArea::render(GLuint sp)
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

    glDrawArrays(GL_QUADS, 0, _v.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

TextArea::~TextArea()
{
    //dtor
}
