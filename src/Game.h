#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Dungeon.h"
#include "Character.h"

class Game {
public:
    // Matches the lecturer's main.cpp expectations
    void loadFromFile(const std::string& filename);
    void executeCommands();
    void outputFinalState(const std::string& filename);

private:
    void handleLine(const std::string& line);

    void cmdCreate(const std::vector<std::string>& t);
    void cmdCreateRoom(const std::vector<std::string>& t);
    void cmdConnect(const std::vector<std::string>& t);
    void cmdSetStart(const std::vector<std::string>& t);
    void cmdEnter(const std::vector<std::string>& t);
    void cmdMove(const std::vector<std::string>& t);
    void cmdPlaceItem(const std::vector<std::string>& t);
    void cmdPlaceMonster(const std::vector<std::string>& t);
    void cmdFight(const std::vector<std::string>& t);
    void cmdPickUp(const std::vector<std::string>& t);

    Character* getChar(const std::string& name);
    void logLine(const std::string& s);

private:
    Dungeon m_dungeon;
    std::unordered_map<std::string, Character> m_chars;

    std::vector<std::string> m_commands; // loaded from file
    std::vector<std::string> m_log;      // output lines to be written at end
};
