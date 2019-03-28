#include "QuakeConsole.h"
#include "shaders.h"
#include "../__trash.h"
#include "TextDefs.h"

QuakeConsole::QuakeConsole() : _enabled{false}
{
    _pos = {-1.0f, 1.0f, 2.0f, 1.0f}; // x y width height

    /// Shader program
	_bsp = glCreateProgram();
    compileShaderProgramm(&_bsp, ".\\billboard.vert", ".\\billboard.frag");

    f = new Font(800, 600);

    _qbc = new QCBackplate(_pos);
    _ta = new TextArea(_pos, f);
    _cl = new CommandLine(_pos, f);
}

void QuakeConsole::draw()
{
    if (!_enabled) return;

    glUseProgram(_bsp);

    _qbc->render(_bsp);
    _ta->render(_bsp);
    _cl->render(_bsp);
}

void QuakeConsole::key(WPARAM wParam, bool zaglav)
{
    switch (wParam)
    {
    case VK_LEFT:
        _cl->left();
        break;
    case VK_UP:
        //_cl->up();
        break;
    case VK_RIGHT:
        _cl->right();
        break;
    case VK_DOWN:
        //_cl->right();
        break;
    case VK_RETURN:
        _cl->enter(_ta);
        break;
    case VK_DELETE:
        _cl->delet();
        break;
    case VK_BACK:
        _cl->backspace();
        break;
    case 0x41 ... 0x5A:
        {
            char l;
            if (zaglav)
                l = convert(wParam);
            else
                l = convert(wParam + 32);

            _cl->addLetter(l);
        }
        break;
    default:
        break;
    }


    /*
    if (zaglav)
        _buf[0] = convert(wParam);
    else
        _buf[0] = convert(wParam + 32);

    for (int i = 0; i < sizeof(_buf); i++)
    {
        int sIndex = _buf[i];
        calcOGLcoords(i);

        _uv.push_back(_symbols[sIndex].uv[0]);
        _uv.push_back(_symbols[sIndex].uv[1]);
        _uv.push_back(_symbols[sIndex].uv[2]);
        _uv.push_back(_symbols[sIndex].uv[3]);

        _uv[4*i+0] = _symbols[sIndex].uv[0];
        _uv[4*i+1] = _symbols[sIndex].uv[1];
        _uv[4*i+2] = _symbols[sIndex].uv[2];
        _uv[4*i+3] = _symbols[sIndex].uv[3];
    }

    glBindBuffer(GL_ARRAY_BUFFER, _uvbo);
    glBufferData(GL_ARRAY_BUFFER, _uv.size()*sizeof(vec2), &(_uv[0]), GL_DYNAMIC_DRAW);
    */
}

QuakeConsole::~QuakeConsole()
{
    delete _qbc;
    delete _ta;
    delete _cl;
}
