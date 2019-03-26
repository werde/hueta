#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <vector>


#include "../mat.h"
#include "TextDefs.h"
#include "Font.h"

#define TA_MAX_BUF 900

class TextArea
{
    public:
        TextArea(Pos p, Font* f);
        virtual ~TextArea();

        void render(GLuint sp);
        void appendBuffer(char* p, int len);
    protected:

    private:
        std::vector<vec3> _v;
        std::vector<vec2> _uv;
        GLuint _vbo;
        GLuint _uvbo;

        unsigned char _buf[TA_MAX_BUF];
        int _szBuf;

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
