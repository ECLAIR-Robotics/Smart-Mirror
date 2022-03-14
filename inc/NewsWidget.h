#ifndef NEWS_WIDGET
#define NEWS_WIDGET

#include <cstring>
#include <string>
#include "Widget.h"
#include <raylib.h>
#include <iostream>
#include "Constants.h"
#include <vector>
using namespace std;

class Article {
public:
    Article();

    Article(string t, string s, string c);

    string title;
    string source; // bbc, cnn, etc.
    string content;
};

class WorldMap {
public:
    WorldMap();

    vector<vector<Vector2>> GetPolygons() {
        return polygons;
    }

    std::vector<vector<Vector2>> polygons;

};

class NewsWidget : public Widget {

public:
    NewsWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, string n) :
        Widget (x, y, w, h, n) {
        // Calls widget's constructor
        //render = false;
    }

    void draw() override {
        float x_scale = ((float) width)  / ((float) POLY_SCALE);
        float y_scale = ((float) height) / ((float) POLY_SCALE) * 2;

        for (vector<Vector2> i: worldMap.GetPolygons()) {
            for (int j = 1; j < i.size() - 1; j++) {
                Vector2 a = i.at(j - 1);
                Vector2 b = i.at(j);

                DrawLine(
                    x_scale * a.x + pos_x, y_scale * a.y + pos_y,
                    x_scale * b.x + pos_x, y_scale * b.y + pos_y,
                    SKYBLUE
                );
            }

            Vector2 a = i.at(i.size() - 2);
            Vector2 b = i.at(0);
            DrawLine(
                x_scale * a.x + pos_x, y_scale * a.y + pos_y,
                x_scale * b.x + pos_x, y_scale * b.y + pos_y,
                SKYBLUE
            );
        }
    }

private:
    WorldMap worldMap {};
};

#endif