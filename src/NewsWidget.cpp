#include <iostream>
#include <fstream>
#include "Constants.h"
#include "NewsWidget.h"
#include <string.h>
#include <stdio.h>
#include <raylib.h>
#include <vector>
using namespace std;


Article::Article() {
    title   = "Title";
    source  = "Source";
    content = "Content";
}

Article::Article(string t, string s, string c) {
    title   = t;
    source  = s;
    content = c;
}

WorldMap::WorldMap() {
    // Read the CSV file of polygon points
    ifstream vecfile {"../resources/news/world_map_vec.csv"};
    string line;

    if (vecfile.is_open()) {

        while (getline(vecfile, line)) {
            std::vector<Vector2> poly;
            
            // Iterate through the CSV row
            float x = 0;
            float y = 0;

            uint32_t start = 0;
            uint32_t i;

            for (i = 0; i < strlen(line.c_str()); i++) {

                // If space, then this is the x coordinate. Convert x string to float
                if (line[i] == ' ') {
                    x = 1 * stod(line.substr(start, i)) + POLY_MAX;
                    start = i + 1;
                }
                else if (line[i] == ',') {
                    y = -1 * stod(line.substr(start, i)) + (POLY_MAX / 2);
                    Vector2 vec {x, y};
                    poly.push_back(vec);
                    start = i + 1;
                }
            }

            // Edge case for last element
            y = stod(line.substr(start, i));
            Vector2 vec {x, y};
            poly.push_back(vec);


            polygons.push_back(poly);
        }
        vecfile.close();

        // for (vector<Vector2> i: polygons) {
        //     cout << "poly\n";
        //     for (Vector2 j : i) {
        //         cout << "|" << j.x << " " << j.y << "|\n";
        //     }
        //     cout << "\n\n";
        // }

    }

}