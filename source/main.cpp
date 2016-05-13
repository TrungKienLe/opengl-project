#include "platform.hpp"

// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// standard C++ libraries
#include <iostream>
#include <stdexcept>
#include <iostream>

// tdogl classes

#include "tdogl/render.h"
#include "tdogl/logo.h"
#include "tdogl/List_logo.h"


// constants
const glm::vec2 SCREEN_SIZE(800, 600);

// globals
GLFWwindow* gWindow = NULL;
tdogl::Camera gCamera;
GLfloat gDegreesRotated = 0.0f;
std::vector<ModelInstance*> list_logo;


GLfloat gTranslated = -5.5;
const GLfloat POS_MAX = 3;
const GLfloat POS_MIN = -5.5;

GLfloat gScaled = 1;
const GLfloat  SCAL_MAX = 3;
const GLfloat  SCAL_MIN = 1;

enum state { ZOOM_IN, ZOOM_OUT};
state current_state = ZOOM_IN;

// update the scene based on the time elapsed since last update
static void Update(float secondsElapsed, ModelInstance* pLogo) {
    switch (current_state){
        case ZOOM_OUT:
            gTranslated += secondsElapsed * 2.5;
            gScaled += secondsElapsed *2.5;
            if(gTranslated > POS_MAX)
                current_state = ZOOM_IN;
            break;
        case ZOOM_IN:
            gTranslated -= secondsElapsed * 2.5;
            gScaled -= secondsElapsed *2.5;
            if(gTranslated < POS_MIN)
                current_state = ZOOM_OUT;
            break;
    }
    //pLogo->transform = translate(gTranslated,0,0) * scale(gScaled,gScaled,gScaled);
    pLogo->transform = glm::translate(glm::mat4(), glm::vec3(gTranslated,4,0.1)) * glm::scale(glm::mat4(), glm::vec3(gScaled,gScaled,gScaled));

}

//
//enum state_trans { STAND, GOING_RIGHT, GOING_LEFT};
//
//const GLfloat POS_MAX = 3;
//const GLfloat POS_MIN = 0;
//
//void Go_left(List_logo* pList, float secondsElapsed){
//
//    std::cout << "Going left" << std::endl;
//
//    static state_trans current_state = GOING_RIGHT;
//    float translated = 0;
//    float scaled = 1;
//
//    switch (current_state){
//        case STAND:
//            break;
//        case GOING_RIGHT:
//            translated += secondsElapsed * 2;
//            scaled += secondsElapsed *2;
//            if(translated > POS_MAX)
//                current_state = STAND;
//            break;
//    }
//
//}
//
//void Go_right(List_logo* pLogo, float secondsElapsed){
//
//    std::cout << "Going right" << std::endl;
//
//    static state_trans current_state = GOING_LEFT;
//    float translated = 0;
//    float scaled = 1;
//    std::cout << "Going left" << std::endl;
//
//    switch (current_state){
//        case STAND:
//            break;
//        case GOING_RIGHT:
//            translated -= secondsElapsed * 2;
//            scaled -= secondsElapsed *2;
//            if(translated < POS_MIN)
//                current_state = STAND;
//            break;
//    }
//}
//
//
//enum state_logo {LEFT, RIGHT};
//
//static void Update(float secondsElapsed, List_logo* pLogo) {
//    static state_logo  current_state = LEFT;
//    switch (current_state){
//        case LEFT:
//            if(glfwGetKey(gWindow, 'S')){
//                Go_left(pLogo, secondsElapsed);
//            }
//            current_state = RIGHT;
//            break;
//        case RIGHT:
//            if(glfwGetKey(gWindow, 'A')){
//                Go_right(pLogo, secondsElapsed);
//            }
//            current_state = LEFT;
//            break;
//    }
//}

void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}

// the program starts here
void AppMain() {
    // initialise GLFW
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    gWindow = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "Cube test", NULL, NULL);
    if(!gWindow)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");

    // GLFW settings
    glfwMakeContextCurrent(gWindow);

    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Add new logo to list

    List_logo* main_list =  new List_logo();

    Logo youtube{"logo_youtube.jpg"};
    Logo barclays{"logo_barclays.jpg"};
    Logo hbo{"logo_hbo.jpg"};
    Logo facebook{"logo_facebook.jpg"};


    main_list->push_back(barclays);
    main_list->push_back(hbo);
    main_list->push_back(facebook);
    main_list->push_back(youtube);


    gCamera.setPosition(glm::vec3(0,0,10));
    gCamera.setViewportAspectRatio(SCREEN_SIZE.x / SCREEN_SIZE.y);
    gCamera.setNearAndFarPlanes(0.5f, 100.0f);


    int i = 0;
    // run while the window is open
    float lastTime = (float)glfwGetTime();
    while(!glfwWindowShouldClose(gWindow)){
        // process pending events
        glfwPollEvents();

        // update the scene based on the time elapsed since last update
        float thisTime = (float)glfwGetTime();
        Update(thisTime - lastTime, main_list->get_list_logo().at(0));


        lastTime = thisTime;

        // draw one frame
        Render(main_list->get_list_logo(),gWindow, gCamera);

        // check for errors
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
            std::cerr << "OpenGL Error " << error << std::endl;

        //exit program if escape key is pressed
        if(glfwGetKey(gWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(gWindow, GL_TRUE);
    }

    // clean up and exit
    glfwTerminate();
}


int main(int argc, char *argv[]) {
    try {
        AppMain();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


