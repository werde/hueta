#ifndef QUAKECONSOLE_H
#define QUAKECONSOLE_H

#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>

#include "../mat.h"
#include "TextDefs.h"
#include "QCBackplate.h"
#include "TextArea.h"
#include "CommandLine.h"
#include "Font.h"

class QuakeConsole
{
    public:
        QuakeConsole();
        virtual ~QuakeConsole();


        void draw();
        void key(WPARAM wParam, bool zaglav);

        void toggle(){_enabled = !_enabled;};
        bool status(){return _enabled;};

        Font* f;
    private:
        bool    _enabled;
        GLuint  _bsp;
        Pos     _pos;

        QCBackplate* _qbc;
        TextArea*    _ta;
        CommandLine* _cl;
};

#endif // QUAKECONSOLE_H
