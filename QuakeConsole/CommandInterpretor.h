#ifndef COMMANDINTERPRETOR_H
#define COMMANDINTERPRETOR_H

#include <stdio.h>
#include <memory>
#include <zlib.h>

class App;
extern App* a;

class CommandInterpretor
{
    public:
        CommandInterpretor();
        virtual ~CommandInterpretor();

        char* process(char*, int);
    protected:

    private:
};

#endif // COMMANDINTERPRETOR_H
