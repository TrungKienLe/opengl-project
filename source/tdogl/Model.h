//
// Created by kienlb on 11/05/2016.
//

#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "Program.h"
#include "Texture.h"
#include "platform.hpp"

#include <vector>


/*
 Represents a textured geometry asset

 Contains everything necessary to draw arbitrary geometry with a single texture:

  - shaders
  - a texture
  - a VBO
  - a VAO
  - the parameters to glDrawArrays (drawType, drawStart, drawCount)
 */
struct ModelAsset {
    tdogl::Program* shaders;
    tdogl::Texture* texture;
    GLuint vbo;
    GLuint vao;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
    GLfloat shininess;
    glm::vec3 specularColor;

    ModelAsset() :
            shaders(NULL),
            texture(NULL),
            vbo(0),
            vao(0),
            drawType(GL_TRIANGLES),
            drawStart(0),
            drawCount(0),
            shininess(0.0f),
            specularColor(1.0f, 1.0f, 1.0f)
    {}

};

/*
 Represents an instance of an `ModelAsset`

 Contains a pointer to the asset, and a model transformation matrix to be used when drawing.
 */
struct ModelInstance {
    ModelAsset* asset;
    glm::mat4 transform;

    ModelInstance() :
            asset(NULL),
            transform()
    {}

    ModelInstance(ModelAsset *asset_) :
            asset(asset_),
            transform()
    {}
};

// returns a new tdogl::Program created from the given vertex and fragment shader filenames
static tdogl::Program* LoadShaders(const char* vertFilename, const char* fragFilename) {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath(vertFilename), GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(ResourcePath(fragFilename), GL_FRAGMENT_SHADER));
    return new tdogl::Program(shaders);
}


// returns a new tdogl::Texture created from the given filename
static tdogl::Texture* LoadTexture(const char* filename) {
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(ResourcePath(filename));
    bmp.flipVertically();
    return new tdogl::Texture(bmp);
}

#endif //CUBE_MODEL_H
