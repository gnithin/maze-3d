#include "terminalObject.h"
#include "Geometry.h"
#include "Camera.h"
#include "mazeGenerator.h"

TerminalObject::TerminalObject() : Object(10)
{
    init();
}

void TerminalObject::init()
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

    // Create a buffer and set the stride of information
    myBuffer.CreateBufferTextureLayout(14,
                                       geometry.getSize(),
                                       geometry.getIndicesSize(),
                                       geometry.getData(),
                                       geometry.getIndicesData());

    // Setup shaders
    std::string vertexShader = myShader.LoadShader("./shaders/terminal/vert.glsl");
    std::string fragmentShader = myShader.LoadShader("./shaders/terminal/frag.glsl");

    // Actually create our shader
    myShader.CreateShader(vertexShader, fragmentShader);
}

void TerminalObject::render()
{
    Bind();
    //Render data
    glDrawElements(GL_TRIANGLES,
                   geometry.getIndicesSize(), // The number of indicies, not triangles.
                   GL_UNSIGNED_INT,           // Make sure the data type matches
                   nullptr);                  // Offset pointer to the data. nullptr because we are currently bound:
}

void TerminalObject::update(unsigned int screenWidth, unsigned int screenHeight)
{
    MazeGenerator *generator = MazeGenerator::instance();
    int r, c;
    generator->getEndingIndex(&r, &c);
    transform.loadIdentity();
    transform.translate(c, 0.0, r);

    Bind();
    myShader.setUniform1i("u_DiffuseMap", 0);

    projectionMatrix = glm::perspective(45.0f, ((float)screenWidth) / ((float)screenHeight), 0.1f, 20.0f);
    myShader.setUniformMatrix4fv("model", &transform.getInternalMatrix()[0][0]);
    myShader.setUniformMatrix4fv("view", &(Camera::instance().getWorldToViewmatrix())[0][0]);
    myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
}