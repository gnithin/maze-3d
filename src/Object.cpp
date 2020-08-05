#include "Object.h"
#include "Camera.h"
// for std min, max
#include <algorithm>

// This assert inserts a breakpoint in your code!
// That way we can get the line number and file.
// #define ASSERT(x) if(!(x)) __debugbreak(); (__debugbreak() is only available
// on MSVC)
#define GLCall(x)         \
    GLClearErrorStates(); \
    x;                    \
    GLCheckError(#x, __LINE__);

// New error handling routine
static void GLClearErrorStates()
{
    // Return all of the errors that occur.
    while (glGetError() != GL_NO_ERROR)
    {
        ;
    }
}

// Returns false if an error occurs
static bool GLCheckError(const char *function, int line)
{
    while (GLenum error = glGetError())
    {
        // __LINE__ is a special preprocessor macro that
        // Can tell us what line any errors occurred on.
        std::cout << "[OpenGL Error]" << error << "|" << function << " Line: " << line << "\n";
        return false;
    }
    return true;
}

Object::Object()
{
    init();
}

Object::~Object()
{
}

// TODO: In the future it may be good to
// think about loading a 'default' texture
// if the user forgets to do this action!
void Object::LoadTexture(std::string fileName)
{
    // Load our actual textures
    diffuseMap.LoadTexture(fileName);    
}

void Object::LoadTexture(std::string diffuseFileName, std::string normalFileName) {
    diffuseMap.LoadTexture(diffuseFileName);
    normalMap.LoadTexture(normalFileName);
}

// Initialization of object
// This could be called in the constructor, or
// it is more typicaly to 'explicitly' call this
// so we create our objects at the correct time
void Object::init()
{
    // Setup geometry
    // Be careful not to forget comma's after each line
    // (except the last line of course)!
    geometry.addVertex(0.0f, 0.0f, 0.0f); // Position and Normal
    geometry.addTexture(0.0f, 0.0f);      // Texture

    geometry.addVertex(1.0f, 0.0f, 0.0f); // Position and Normal
    geometry.addTexture(1.0f, 0.0f);      // Texture

    geometry.addVertex(1.0f, 1.0f, 0.0f); // Position and Normal
    geometry.addTexture(1.0f, 1.0f);      // Texture

    geometry.addVertex(0.0f, 1.0f, 0.0f); // Position and Normal
    geometry.addTexture(0.0f, 1.0f);      // Texture
    // Make our triangles and populate our
    // indices data structure
    geometry.makeTriangle(0, 1, 2);
    geometry.makeTriangle(2, 3, 0);

    geometry.gen();

    // The bounding box follows the initial set of vertices exactly
    boundingBox.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    boundingBox.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    boundingBox.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
    boundingBox.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

    // Create a buffer and set the stride of information
    myBuffer.CreateBufferNormalMapLayout(14,
                                         geometry.getSize(),
                                         geometry.getIndicesSize(),
                                         geometry.getData(),
                                         geometry.getIndicesData());

    // Setup shaders
    std::string vertexShader = myShader.LoadShader("./shaders/vert.glsl");
    std::string fragmentShader = myShader.LoadShader("./shaders/frag.glsl");
    // Actually create our shader
    myShader.CreateShader(vertexShader, fragmentShader);
}

// Bind everything we need in our object
// Generally this is called in update() and render()
// before we do any actual work with our object
void Object::Bind()
{
    // Make sure we are updating the correct 'buffers'
    myBuffer.Bind();
    // Diffuse map is 0 by default, but it is good to set it explicitly
    diffuseMap.Bind(0);
    // We need to set the texture slot explicitly for the normal map
    normalMap.Bind(1);
    // Select our appropriate shader
    myShader.Bind();
}

void Object::update(unsigned int screenWidth, unsigned int screenHeight)
{
    Bind();
    // TODO: Read and understand
    // For our object, we apply the texture in the following way
    // Note that we set the value to 0, because we have bound
    // our texture to slot 0.
    myShader.setUniform1i("u_DiffuseMap", 0);
    // If we want to load another texture, we assign it to another slot
    myShader.setUniform1i("u_NormalMap", 1);
    // Here we apply the 'view' matrix which creates perspective.
    // The first argument is 'field of view'
    // Then perspective
    // Then the near and far clipping plane.
    // Note I cannot see anything closer than 0.1f units from the screen.
    // TODO: In the future this type of operation would be abstracted away
    //       in a camera class.
    projectionMatrix = glm::perspective(45.0f, ((float)screenWidth) / ((float)screenHeight), 0.1f, 20.0f);
    // Set the uniforms in our current shader

    // Set the MVP Matrix for our object
    // Send it into our shader
    myShader.setUniformMatrix4fv("model", &transform.getInternalMatrix()[0][0]);
    myShader.setUniformMatrix4fv("view", &Camera::instance().getWorldToViewmatrix()[0][0]);
    myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);

    myShader.setUniform3f("lightPos", 5.0f, 20.0f, 10.0f);//same as pointLights[0].lightPos
    myShader.setUniform3f("viewPos", Camera::instance().getEyeXPosition(), Camera::instance().getEyeYPosition(), Camera::instance().getEyeZPosition());

    // Create a first 'light'
    myShader.setUniform3f("pointLights[0].lightColor", 0.8f, 0.9f, 0.8f);
    myShader.setUniform3f("pointLights[0].lightPos", 5.0f, 20.0f, 10.0f);
    myShader.setUniform1f("pointLights[0].ambientIntensity", 0.9f);
    myShader.setUniform1f("pointLights[0].specularStrength", 0.0f);
    myShader.setUniform1f("pointLights[0].constant", 1.0f);
    myShader.setUniform1f("pointLights[0].linear", 0.09f);
    myShader.setUniform1f("pointLights[0].attentuateFactor", 0.0f);
    myShader.setUniform1f("pointLights[0].quadratic", 0.032f);
}

void Object::render()
{
    Bind();
    //Render data
    glDrawElements(GL_TRIANGLES,
                   geometry.getIndicesSize(), // The number of indicies, not triangles.
                   GL_UNSIGNED_INT,           // Make sure the data type matches
                   nullptr);                  // Offset pointer to the data. nullptr because we are currently bound:
}

// Returns the actual transform stored in our object
// which can then be modified
Transform &Object::getTransform()
{
    return transform;
}

CoordMax Object::getBoundingBox()
{
    CoordMax coordMax;
    for (int i = 0; i < boundingBox.size(); i += 1)
    {
        glm::vec3 box = boundingBox[i];
        glm::vec4 res = transform.getInternalMatrix() * glm::vec4(box[0], box[1], box[2], 1.0f);
        if (i == 0)
        {
            coordMax.xMax = res[0];
            coordMax.xMin = res[0];
            coordMax.yMax = res[1];
            coordMax.yMin = res[1];
            coordMax.zMax = res[2];
            coordMax.zMin = res[2];
        }
        else
        {
            coordMax.xMax = std::max(res[0], coordMax.xMax);
            coordMax.xMin = std::min(res[0], coordMax.xMin);
            coordMax.yMax = std::max(res[1], coordMax.yMax);
            coordMax.yMin = std::min(res[1], coordMax.yMin);
            coordMax.zMax = std::max(res[2], coordMax.zMax);
            coordMax.zMin = std::min(res[2], coordMax.zMin);
        }
    }
    return coordMax;
}