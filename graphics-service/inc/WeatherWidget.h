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
    WeatherWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string n) :
        Widget (x, y, w, h, n) { 

        Image weatherIcons = LoadImage("../resources/Adjusted-Weather-Icons.png");
        ImageResize(&weatherIcons, 50, 50);
        icons = LoadTextureFromImage(weatherIcons);
        UnloadImage(weatherIcons);

        std::ostringstream api_url;
        api_url << "https://api.openweathermap.org/data/2.5/weather?lat="
         << std::to_string(AUSTIN_LATITUDE) << "&lon=" << std::to_string(AUSTIN_LONGITUDE) 
         << "&appid=" << WEATHER_API;
        get_http_request(&weatherAPIFinished, api_url.str(), &informations);
    };

    void draw() override {
        if (weatherAPIFinished && !retrievedStrings) {
            float ktemp = -1;
            float ctemp = -1;
            float ftemp = -1;
            Json::StreamWriterBuilder builder;
            builder["indentation"] = ""; 
            // Convert json to string
            ktemp = stof(Json::writeString(builder, informations["main"]["temp"]));
            weatherConditions = Json::writeString(builder, informations["weather"][0]["main"]);
            weatherConditions = weatherConditions.substr(1, weatherConditions.length() - 2);
            city = Json::writeString(builder, informations["name"]);
            city = city.substr(1, city.length() - 2);
            // Convert to celsius and fahrenheit
            ctemp = ktemp - 273.15;
            ftemp = ((ctemp * 9)/5) + 32;
            std::ostringstream x;
            x << std::to_string((int) (isCelsius ? ctemp : ftemp)) << (isCelsius ? "°C" : "°F");
            temperature = x.str();
            retrievedStrings = true;
        }
        else if (!weatherAPIFinished) {
            // don't use json here!
            temperature = "Loading...";
            weatherConditions = "Loading...";
        }
        // Obtains rectangle for weather icon
        Rectangle rect = iconMap["Clear"];
        // Position for icon on screen
        Vector2 icon_pos {(float) pos_x, (float) (pos_y) + 30};
        DrawTextureRec(icons, rect, icon_pos, WHITE);

        DrawText(temperature.c_str(), pos_x + 80, pos_y + 60, 30, SKYBLUE); 
        DrawText(weatherConditions.c_str(), pos_x, pos_y + 100, 30, SKYBLUE); 
        DrawText(city.c_str(), pos_x, pos_y, 30, SKYBLUE);
    }

private:
    Texture2D icons;
    bool weatherAPIFinished = false;
    bool retrievedStrings = false;
    bool isCelsius = false;
    Json::Value informations = new Json::Value();

    std::string temperature;
    std::string city;
    std::string weatherConditions;

    std::map<std::string, Rectangle> iconMap = {
        {"Clouds", {50, 50, 50, 50}},  /* Cloudy */
        {"Thunderstorm", {50/10, 50/2.3, 50, 50}},  /* Thunderstorm */
        {"Clear", {50/3.8, 50/6.3, 50, 50}}, /* Sunny/Clear */
        {"Rain", {50/3.8, 50/2.3, 50, 50}}, /* Rain */
        {"Drizzle", {50/3.8, 50/2.3, 50, 50}}, /* Drizzle */
        {"Snow", {50/2.3, 50/2.3, 50, 50}}, /* Snow */
        {"Mist", {50/1.63, 50/2.3, 50, 50}}, /* Mist */
        {"Smoke", {50/1.63, 50/2.3, 50, 50}}, /* Smoke */
        {"Haze", {50/1.63, 50/2.3, 50, 50}}, /* Haze */
        {"Dust", {50/1.63, 50/2.3, 50, 50}}, /* Dust */
        {"Fog", {50/1.63, 50/2.3, 50, 50}}, /* Fog */
        {"Sand", {50/1.63, 50/2.3, 50, 50}}, /* Sand */
        {"Dust", {50/1.63, 50/2.3, 50, 50}}, /* Dust */
        {"Ash", {50/1.63, 50/2.3, 50, 50}}, /* Ash */
        {"Squall", {50/1.63, 50/2.3, 50, 50}}, /* Squall */
        {"Tornado", {50/1.63, 50/2.3, 50, 50}}, /* Tornado */
        {"Loading...", {50/1.63, 50/2.3, 50, 50}} /* Default */
    };
};


#endif