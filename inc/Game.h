#ifndef GAME
#define GAME

#include <string>
#include <vector>
#include "Widget.h"
#include "Constants.h"

class Game {

public:
    Game(int width, int height, std::string title);
    ~Game() noexcept;

    bool GameShouldClose() const;

    void Tick();
private:

    std::vector<Widget*> widgets;
    void Draw();
    void Update();
    Shader glowing_shader;
    RenderTexture2D target;
};

#endif