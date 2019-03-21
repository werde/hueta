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

        GLuint _tex;
        int fH, fW;
        GLfloat fFH, fFW;

    private:
        bool _loaded;
        std::vector<Symbol> _symbols;
};

#endif // FONT_H
