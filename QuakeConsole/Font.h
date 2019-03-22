#ifndef FONT_H
#define FONT_H

#include <vector>

#include "GL/gl.h"

#include "TextDefs.h"

class Font
{
    public:
        Font(int, int);
        virtual ~Font();

        GLuint tex;
        int fH, fW;
        GLfloat fFH, fFW;
        std::vector<Symbol> symbols;
    private:
        bool _loaded;

};

#endif // FONT_H
