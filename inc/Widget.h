#ifndef WIDGET
#define WIDGET
#include <string>
#include <iostream>
using namespace std;

class Widget {

public:
    Widget() {
        cout << "Creating new widget\n";
    };

    Widget(uint32_t x, uint32_t y, uint32_t h, uint32_t w, std::string &n) {
        updatePosition(x, y);
        updateDimensions(h, w);
        name = n;
    };

    std::string name;
    bool render;

    void update() {
        if (render) {
            draw();
        }
    }

    void updatePosition(uint32_t x, uint32_t y) {
        pos_x = x;
        pos_y = y;
    }

    void updateDimensions(uint32_t h, uint32_t w) {
        height = h;
        width = w;
    }

    virtual void draw() {};

private:

    uint32_t height;
    uint32_t width;
    uint32_t pos_x;
    uint32_t pos_y;

};

#endif