#ifndef WEATHER_WIDGET
#define WEATHER_WIDGET

#include <string>
#include "Widget.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include "Constants.h"
using namespace std;

class WeatherWidget : public Widget {

public:
    /* Docker Checklist
            Open CMD
            cd to Smart-Mirror Directory
            find ip with ipconfig and replace <ip_address> with it
            run docker run --rm -i -t -v %cd%:/usr/smart-mirror -w /usr/smart-mirror -e DISPLAY=<ip_address>:0.0 smart-mirror
            you're good to go*/
    WeatherWidget() {
        cout << "Initialized WeatherWidget\n";
        render = true;
        Image weatherIcons = LoadImage("../resources/Weather-Icons.png");
        ImageResize(&weatherIcons, MONITOR_SIZE_X / 2, MONITOR_SIZE_Y / 1.5);
        icons = LoadTextureFromImage(weatherIcons);
        UnloadImage(weatherIcons);
    };

    void draw() override {
        Rectangle rect {75, 75, 75, 75};
        Vector2 icon_pos {0, 0};
        DrawTextureRec(icons, rect, icon_pos, WHITE);
        int temp = 69;
        std::string text = std::to_string(temp);
        DrawText(text.c_str(), 70, 20, 30, SKYBLUE); 
        std::string weather = "Cloudy";
        DrawText(weather.c_str(), 10, 60, 30, SKYBLUE); 

    }

private:
    Texture2D icons;
};

#endif