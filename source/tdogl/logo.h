//
// Created by kienlb on 13/05/2016.
//

#ifndef CUBE_LOGO_H
#define CUBE_LOGO_H

#include "Program.h"
#include "Texture.h"
#include "Model.h"

class Logo {
public:

    Logo(const char*);
    void update(glm::mat4 transform_);
    ModelInstance* get_instance() {return &instance;}

private:
    ModelAsset asset;
//    std::vector<ModelInstance> instance;
    ModelInstance instance;
};

#endif //CUBE_LOGO_H
