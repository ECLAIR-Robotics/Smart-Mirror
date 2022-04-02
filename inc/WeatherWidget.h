#ifndef WEATHER_WIDGET
#define WEATHER_WIDGET

#include <string>
#include "Widget.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include "Constants.h"
#include "Utility.h"
#include <json/json.h>
#include <sstream>
#include <map>
using namespace std;

class WeatherWidget : public Widget {

public:
    /* Docker Checklist
            Open CMD
            cd to Smart-Mirror Directory
            find ip with ipconfig and replace <ip_address> with it
            run docker run --rm -i -t -v %cd%:/usr/smart-mirror -w /usr/smart-mirror -e DISPLAY=<ip_address>:0.0 smart-mirror
            you're good to go*/
    WeatherWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string n) :
        Widget (x, y, w, h, n) { 

        Image weatherIcons = LoadImage("../resources/Adjusted-Weather-Icons.png");
        ImageResize(&weatherIcons, imageSizeX, imageSizeY);
        icons = LoadTextureFromImage(weatherIcons);
        UnloadImage(weatherIcons);

        std::ostringstream api_url;
        api_url << "https://api.openweathermap.org/data/2.5/weather?lat="
         << std::to_string(AUSTIN_LATITUDE) << "&lon=" << std::to_string(AUSTIN_LONGITUDE) 
         << "&appid=" << WEATHER_API;
        get_http_request(&weatherAPIFinished, api_url.str(), &informations);
    };

    void draw() override {
        std::string temp;
        std::string weather;
        float ktemp = -1;
        float ctemp = -1;
        float ftemp = -1;

        if (weatherAPIFinished) {
            // Use json here
            Json::StreamWriterBuilder builder;
            builder["indentation"] = ""; 
            // Convert json to string
            ktemp = stof(Json::writeString(builder, informations["main"]["temp"]));
            weather = Json::writeString(builder, informations["weather"][0]["main"]);
            weather = weather.substr(1, weather.length() - 2);
            // Convert to celsius and fahrenheit
            ctemp = ktemp - 273.15;
            ftemp = ((ctemp * 9)/5) + 32;
            std::ostringstream x;
            x << std::to_string((int) (isCelsius ? ctemp : ftemp)) << (isCelsius ? "°C" : "°F");
            temp = x.str();
        }
        else {
            // don't use json here!
            temp = "Loading...";
            weather = "Loading...";
        }
        // Obtains rectangle for weather icon
        Rectangle rect = iconMap[weather];
        // Position for icon on screen
        Vector2 icon_pos {pos_x, pos_y};
        DrawTextureRec(icons, rect, icon_pos, WHITE);

        DrawText(temp.c_str(), pos_x + 80, pos_y + 30, 30, SKYBLUE); 
        DrawText(weather.c_str(), pos_x, pos_y + 70, 30, SKYBLUE); 

    }

private:
    Texture2D icons;
    bool weatherAPIFinished = false;
    bool isCelsius = false;
    Json::Value informations = new Json::Value();
    int imageSizeX = MONITOR_SIZE_X / 2;
    int imageSizeY = MONITOR_SIZE_Y / 1.5;
    std::map<std::string, Rectangle> iconMap = {
        {"Clouds", {imageSizeX/10, imageSizeY/7, 75, 75}},  /* Cloudy */
        {"Thunderstorm", {imageSizeX/10, imageSizeY/2.3, 75, 75}},  /* Thunderstorm */
        {"Clear", {imageSizeX/3.8, imageSizeY/6.3, 75, 75}}, /* Sunny/Clear */
        {"Rain", {imageSizeX/3.8, imageSizeY/2.3, 75, 75}}, /* Rain */
        {"Drizzle", {imageSizeX/3.8, imageSizeY/2.3, 75, 75}}, /* Drizzle */
        {"Snow", {imageSizeX/2.3, imageSizeY/2.3, 75, 75}}, /* Snow */
        {"Mist", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Smoke", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Haze", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Dust", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Fog", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Sand", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Dust", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Ash", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Squall", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Tornado", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}}, /* Atmosphere (windy, dusty, hazy, etc*/
        {"Loading...", {imageSizeX/1.63, imageSizeY/2.3, 75, 75}} /*Default icon if loading */
    };
};

#endif