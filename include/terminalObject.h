#ifndef TERMINAL_OBJECT_H
#define TERMINAL_OBJECT_H

#include <vector>
#include "Object.h"

class TerminalObject : public Object
{
public:
    TerminalObject();
    void init();
    void render();
    void update(unsigned int screenWidth, unsigned int screenHeight);
};

#endif