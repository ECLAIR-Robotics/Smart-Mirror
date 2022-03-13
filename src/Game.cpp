#include <string>
#include "Game.h"
#include <raylib.h>
#include <vector>

// Widgets
#include "TimeWidget.h"
#include "NewsWidget.h"

Game::Game(int width, int height, std::string title) {
    InitWindow(width, height, title.c_str());

    TimeWidget* timeWidget = new TimeWidget(TIME_X, TIME_Y, TIME_W, TIME_H, "Time Widget");
    NewsWidget* newsWidget = new NewsWidget(NEWS_X, NEWS_Y, NEWS_W, NEWS_H, "News Widget");
    widgets.push_back(timeWidget);
    widgets.push_back(newsWidget);
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

    DrawRectangleLines(1, 1, MONITOR_SIZE_X-3, MONITOR_SIZE_Y-3, SKYBLUE);

    std::vector<Widget*> ::iterator i;
    for (i = widgets.begin(); i != widgets.end(); i++) {
        (*i)->update();
    }
}

void Game::Update() {

}