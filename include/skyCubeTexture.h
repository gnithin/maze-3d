#ifndef SKY_CUBE_TEXTURE_H
#define SKY_CUBE_TEXTURE_H

#include "Image.h"
#include "Texture.h"

#include <string>
#include <glad/glad.h>
#include <vector>

class SkyCubeTexture : public Texture
{
public:
    // Constructor
    SkyCubeTexture();
    // Destructor
    ~SkyCubeTexture();
    // Loads and sets up an actual texture
    void LoadTexture(const std::vector<std::string> filepaths);
    void Bind(unsigned int slot) const;
    void Unbind();

protected:
    // Filepath to the image loaded
    std::vector<std::string> filePaths;
};

#endif
