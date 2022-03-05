#ifndef TIME_WIDGET
#define TIME_WIDGET

#include <string>
#include "Widget.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include "Constants.h"
using namespace std;

class TimeWidget : public Widget {

public:
    TimeWidget() {
        cout << "Initialized TimeWidget\n";
        render = true;
    };

    void draw() override {

        // Put code here for drawing!
        time_t result = std::time(nullptr);
        char* text = ctime(&result);
        int textWidth = MeasureText(text, 30);

        uint32_t x_cord = (MONITOR_SIZE_X / 2) - (textWidth / 2);
        DrawText(text, x_cord, MONITOR_SIZE_Y / 2, 30, SKYBLUE);

        std::string text2 = "Jarvis";
        textWidth = MeasureText(text2.c_str(), 60);
        x_cord = (MONITOR_SIZE_X / 2) - (textWidth / 2);
        DrawText(text2.c_str(), x_cord, MONITOR_SIZE_Y / 2 - 60, 60, SKYBLUE);
    }

private:

};

#endif