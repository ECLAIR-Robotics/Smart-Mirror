#include <string>
#include "Game.h"
#include <raylib.h>
#include <vector>

// Widgets
#include "TimeWidget.h"
#include "WeatherWidget.h"
#include "NewsWidget.h"
#include "Calculator.h"
Game::Game(int width, int height, std::string title) //called from main.cpp
 {
    InitWindow(width, height, title.c_str()); //raylib function
    
    glowing_shader = LoadShader(0, "../resources/shaders/glow.fs");
    target = LoadRenderTexture(MONITOR_SIZE_X, MONITOR_SIZE_Y);
    int target0_loc = GetShaderLocation(glowing_shader, "texture0");
    SetShaderValue(glowing_shader, target0_loc, &target.texture, SHADER_UNIFORM_SAMPLER2D);

    TimeWidget* timeWidget = new TimeWidget(TIME_X, TIME_Y, TIME_W, TIME_H, "Time Widget");
    NewsWidget* newsWidget = new NewsWidget(NEWS_X, NEWS_Y, NEWS_W, NEWS_H, "News Widget");
    WeatherWidget* weatherWidget = new WeatherWidget(WEATHER_X, WEATHER_Y, WEATHER_W, WEATHER_H, "Weather Widget");
    Calculator * calculator = new Calculator(CALC_X, CALC_Y , CALC_W, CALC_H, "Calculator");
    widgets.push_back(timeWidget);
    widgets.push_back(newsWidget);
    widgets.push_back(weatherWidget);
    widgets.push_back(calculator);
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
    BeginTextureMode(target);
    ClearBackground(BLACK);

    DrawRectangleLines(1, 1, MONITOR_SIZE_X-3, MONITOR_SIZE_Y-3, SKYBLUE);

    std::vector<Widget*> ::iterator i;
    for (i = widgets.begin(); i != widgets.end(); i++) {
        (*i)->update();
    }
    EndTextureMode();

    BeginShaderMode(glowing_shader);
    DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0.0f, 0.0f }, WHITE);
    EndShaderMode();
}

void Game::Update() {

}