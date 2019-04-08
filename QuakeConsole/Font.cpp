#include "Font.h"

#include "../__trash.h"
#include "../src/IMAGELoad.h"

Font::Font(int w, int h)
    : _loaded{false}
{
    fH = 20; fW = 16;
    fFW = fW*2.0/(GLfloat)w;
    fFH = fH*2.0/(GLfloat)h;

    /// Fill symbol table
    GLfloat offsetX = 16;
    GLfloat offsetY = 20;
	GLfloat dim = 256.0;
	char keyIndex = 0;
	for (int x = 0; x < dim; x+=16)
        for(int y = 16; y < dim; y+=20)
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
            symbols.push_back(s);
            keyIndex++;
        }

    /// Load font texture
    tex = loadTex(".\\assets\\shizzle_i.png");
}

Font::~Font()
{
    //dtor
}
