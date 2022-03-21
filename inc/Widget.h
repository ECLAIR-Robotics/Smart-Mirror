#ifndef WIDGET
#define WIDGET
#include <string>
#include <iostream>
#include <raylib.h>
#include "Constants.h"
using namespace std;

class Widget {

public:

    Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string n) {
        updatePosition(x, y);
        updateDimensions(w, h);
        name = n;
        render = true;
        render_border = false;
    };

    std::string name;
    bool render;
    bool render_border;

    void update() {
        if (render) {
            if (render_border) {
                DrawRectangleLines(pos_x, pos_y, width, height, SKYBLUE);
            }
            BeginScissorMode(pos_x, pos_y, width, height);
            draw();
            EndScissorMode();
        }
    }

    void updatePosition(uint32_t x, uint32_t y) {
        pos_x = x;
        pos_y = y;
    }

    void updateDimensions(uint32_t w, uint32_t h) {
        width = w;
        height = h;
    }

    virtual void draw() {};

protected:

    uint32_t height;
    uint32_t width;
    uint32_t pos_x;
    uint32_t pos_y;

};

#endif