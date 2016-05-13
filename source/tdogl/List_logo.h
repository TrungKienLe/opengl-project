//
// Created by kienlb on 13/05/2016.
//

#ifndef CUBE_LIST_LOGO_H
#define CUBE_LIST_LOGO_H

#include "logo.h"
#include <vector>

class List_logo {
public:
    List_logo();
    void push_back(Logo& app_logo);
    ModelInstance* front();
    std::vector<ModelInstance*>& get_list_logo();
    void update();
private:
    std::vector<ModelInstance*> vInstance;
};


#endif //CUBE_LIST_LOGO_H
