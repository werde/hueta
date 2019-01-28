#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

class Model
{
    public:
        Model();
        virtual ~Model();

    static bool LoadObj(std::string path = "./assets/t.obj");
    protected:

    private:
};

#endif // MODEL_H
