#include "skyCubeObject.h"
#include "Geometry.h"
#include "Camera.h"

SkyCubeObject::SkyCubeObject() : Object(10)
{
    init();
}

void SkyCubeObject::init()
{
    float vertices[] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    unsigned int indices[] = {0};
    vertexSize = sizeof(vertices) / sizeof(vertices[0]);
    // Create a buffer and set the stride of information
    myBuffer.CreateBufferLayout(3, vertexSize, 0, &vertices[0], &indices[0]);

    // Setup shaders
    std::string vertexShader = myShader.LoadShader("./shaders/skycube/vert.glsl");
    std::string fragmentShader = myShader.LoadShader("./shaders/skycube/frag.glsl");
    // Actually create our shader
    myShader.CreateShader(vertexShader, fragmentShader);
}

void SkyCubeObject::render()
{
    // Reference - https://stackoverflow.com/a/2859795/1518924
    glDisable(GL_DEPTH_TEST);
    Bind();
    //Render data
    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexSize);
    glEnable(GL_DEPTH_TEST);
}

void SkyCubeObject::LoadTextures(std::vector<std::string> fileNames)
{
    diffuseMap.LoadTexture(fileNames);
}

void SkyCubeObject::update(unsigned int screenWidth, unsigned int screenHeight)
{
    Bind();
    myShader.setUniform1i("u_DiffuseMap", 0);
    projectionMatrix = glm::perspective(45.0f, ((float)screenWidth) / ((float)screenHeight), 0.1f, 20.0f);
    myShader.setUniformMatrix4fv("model", &transform.getInternalMatrix()[0][0]);
    glm::mat4 viewMatrix = glm::mat4(glm::mat3(Camera::instance().getWorldToViewmatrix()));
    myShader.setUniformMatrix4fv("view", &viewMatrix[0][0]);
    myShader.setUniformMatrix4fv("projection", &projectionMatrix[0][0]);
}