#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#else
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#endif

#include <iostream>

#include "initializer.h"
#include "window.h"
#include "callback.h"
#include "mouse.h"

class PositionPrintCallback: public gl::Callback<gl::MousePosition> {
public:
    void run(gl::MousePosition position) override {
        std::cout << "X: " << position.x << ", Y: " << position.y << std::endl;
    }
};

int main(int argc, char *argv[])
{
    gl::Initializer initializer{{ .major = 3, .minor =  3 }};
    initializer.init();

    gl::Window window{"OpenGL", { .width = 1024, .height = 768 }};

    auto &mouse_control = window.getMousePositionControl();

    PositionPrintCallback position_print_callback{};
    mouse_control.registerCallback(reinterpret_cast<gl::Callback<gl::MousePosition>*>(&position_print_callback));

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    do {
        glClear(GL_COLOR_BUFFER_BIT);

        window.update();
    } while (window.isClose());

    return 0;
}