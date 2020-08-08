#ifndef SKYOBJECT_H
#define SKYOBJECT_H

#include <vector>
#include "skyCubeTexture.h"
#include "Object.h"

class SkyCubeObject : public Object
{
public:
    SkyCubeObject();
    void init();
    void render();
    void LoadTextures(std::vector<std::string> fileNames);
    void update(unsigned int screenWidth, unsigned int screenHeight);

protected:
    int vertexSize;
    SkyCubeTexture diffuseMap;
};

#endif