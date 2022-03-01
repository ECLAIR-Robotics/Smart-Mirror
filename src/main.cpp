#include "Game.h"
#include <iostream>
using namespace std;

int main(void){
    //Initialization
    const int screenWidth  = 800;
    const int screenHeight = 450;

    cout << "In main.cpp\n";

    Game game {screenWidth, screenHeight, "Smart Mirror"};

    while (!game.GameShouldClose()) {
        game.Tick();
    }

    return 0;
}