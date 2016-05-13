//
// Created by kienlb on 13/05/2016.
//

#include "ultility.h"
#include "List_logo.h"

List_logo::List_logo() : vInstance()
{ }

/*
 * Add a logo to list and calculate the position;
 *
 */
const float LEFT_SCREEN = -5.5;
const float TOP_SCREEN = 4;
const float LOGO_GAP = 2.5;

void List_logo::push_back(Logo& app_logo) {

    // calculate the position;
    float y_pos =  TOP_SCREEN - LOGO_GAP * vInstance.size();
    app_logo.update(translate(LEFT_SCREEN, y_pos, 0));

    vInstance.push_back(app_logo.get_instance());
}

ModelInstance* List_logo::front() {
    return vInstance.front();
}

std::vector<ModelInstance*>& List_logo::get_list_logo() {
    return vInstance;
}





