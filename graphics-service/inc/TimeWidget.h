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
    TimeWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string n) :
        Widget (x, y, w, h, n) {
        // Calls widget's constructor
        //render = false;
    }

    void draw() override {

        // Put code here for drawing!
        time_t result;
        std::time(&result);
        struct tm * timeinfo = gmtime(&result);

        timeinfo->tm_hour = (timeinfo->tm_hour+CST+24)%24;
        char* text = asctime(timeinfo);
        int textWidth = MeasureText(text, 30);

        int32_t middle_x = pos_x + (width / 2);
        int32_t middle_y = pos_y + (height / 2);

        uint32_t x_cord = middle_x - (textWidth / 2);
        DrawText(text, x_cord, middle_y + 20, 30, SKYBLUE);

        std::string text2 = "Jarvis";
        textWidth = MeasureText(text2.c_str(), 60);
        x_cord = middle_x - (textWidth / 2);
        DrawText(text2.c_str(), x_cord, middle_y - 60, 60, SKYBLUE);
    }

private:

};

#endif