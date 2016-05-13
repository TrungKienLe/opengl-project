//
// Created by kienlb on 11/05/2016.
//
#ifndef CUBE_RENDER_H
#define CUBE_RENDER_H
#include "platform.hpp"

// third-party libraries

#include "Model.h"
#include "Camera.h"

//renders a single `ModelInstance`
static void RenderInstance(const ModelInstance *inst, const tdogl::Camera& camera) {
    ModelAsset* asset = inst->asset;
    tdogl::Program* shaders = asset->shaders;

    //bind the shaders
    shaders->use();

    //set the shader uniforms
    shaders->setUniform("camera", camera.matrix());
    shaders->setUniform("model", inst->transform);
    shaders->setUniform("materialTex", 0); //set to 0 because the texture will be bound to GL_TEXTURE0

    //bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset->texture->object());

    //bind VAO and draw
    glBindVertexArray(asset->vao);
    glDrawArrays(asset->drawType, asset->drawStart, asset->drawCount);

    //unbind everything
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shaders->stopUsing();
}

// draws a single frame
static void Render(const std::vector<ModelInstance*> vInstances, GLFWwindow* pWindow , tdogl::Camera camera) {
    // clear everything
    glClearColor(0, 0, 0, 1); // black

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render all the instances
    for(auto it = vInstances.begin(); it != vInstances.end(); ++it){
        RenderInstance(*it, camera);
    }

    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(pWindow);
}
#endif //CUBE_RENDER_H
