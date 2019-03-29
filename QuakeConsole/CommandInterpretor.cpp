#include "CommandInterpretor.h"
#include "../App.h"
#include "../MyWindow.h"

#include "TextDefs.h"

CommandInterpretor::CommandInterpretor()
{
    //ctor
}

char* CommandInterpretor::process(char* p, int sz)
{
    char* com1 = "res1";
    char* com2 = "res2";
    char* com3 = "res3";

    printf("Command %s %d \n", p, sz);

    if (memcmp(com1, p, sz) == 0)
    {
        a->_mw->fullscreenBorderless();
        printf("res1");
    }
    else if (memcmp(com2, p, sz) == 0)
    {
        printf("res2");
    }
    else if (memcmp(com3, p, sz) == 0)
    {
        printf("res3");
    }
    char* str = "kokokoko";

    return str;
}

CommandInterpretor::~CommandInterpretor()
{
    //dtor
}
;
