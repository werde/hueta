#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <vector>


#include "../mat.h"
#include "TextDefs.h"
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

        unsigned char _buf[900];
        int sz_Buf;

        Font* _f;
        //
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
