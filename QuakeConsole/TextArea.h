#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <vector>

#include "TextDefs.h"
#include "../mat.h"

#include "Font.h"

class TextArea
{
    public:
        TextArea(Pos p, Font* f);
        virtual ~TextArea();

        void render(GLuint sp);
    protected:

    private:
        std::vector<vec3> _v;
        std::vector<vec2> _uv;
        GLuint _vbo;
        GLuint _uvbo;
        GLuint _tex;

        unsigned char _buf[900];
        int sz_Buf;
        std::vector<Symbol> _symbols;

        Font* _f;

        //
        int fH, fW;
        GLfloat fFH, fFW;
        int w, h;
        int g;
        GLfloat fg;
        int symPerStr;
        int numStrings;

        void uv(int i);
        void ss(int strNum, int);
        void fillvv();

        //
        Pos _pos;
        GLfloat bottom, left;

};

#endif // TEXTAREA_H
