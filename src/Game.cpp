#include <string>
#include "Game.h"
#include <raylib.h>
#include <vector>

// Widgets
#include "TimeWidget.h"
#include "WeatherWidget.h"

Game::Game(int width, int height, std::string title) {
    InitWindow(width, height, title.c_str());

    TimeWidget* timeWidget = new TimeWidget;
    WeatherWidget* weatherWidget = new WeatherWidget;

    widgets.push_back(timeWidget);
    widgets.push_back(weatherWidget);
}

Game::~Game() noexcept {
    CloseWindow();
}

bool Game::GameShouldClose() const {
    return WindowShouldClose();
}

void Game::Tick() {
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}

void Game::Draw() {
    ClearBackground(BLACK);

    DrawRectangle(0, 0, MONITOR_SIZE_X, MONITOR_SIZE_Y, SKYBLUE);
    DrawRectangle(1, 1, MONITOR_SIZE_X-3, MONITOR_SIZE_Y-3, BLACK);

    std::vector<Widget*> ::iterator i;
    for (i = widgets.begin(); i != widgets.end(); i++) {
        (*i)->update();
    }
}

void Game::Update() {

}