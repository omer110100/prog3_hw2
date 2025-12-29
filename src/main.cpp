#include "Game.h"

int main() {

    Game game;
    game.loadFromFile("input.txt");

    // Run game logic based on loaded commands
    game.executeCommands();

    game.outputFinalState("output.txt");

    return 0;
}