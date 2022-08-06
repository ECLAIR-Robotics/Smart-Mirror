#include "Game.h"
#include <iostream>
#include "Constants.h"
#include "Utility.h"
#include <string>
using namespace std;

int main(void){

    //Initialization
    Game game {MONITOR_SIZE_X, MONITOR_SIZE_Y, "Smart Mirror"};

    while (!game.GameShouldClose()) {
        game.Tick();
    }

    return 0;
}