#include "Room.h"
#include "Utils.h"

Room::Room(std::string name) : m_name(std::move(name)) {}

Room* Room::get(Direction d) const {
    switch (d) {
        case Direction::North: return m_north;
        case Direction::South: return m_south;
        case Direction::East:  return m_east;
        case Direction::West:  return m_west;
        default: return nullptr;
    }
}

bool Room::set(Direction d, Room* other) {
    if (!other) return false;
    if (get(d) != nullptr) return false;

    switch (d) {
        case Direction::North: m_north = other; return true;
        case Direction::South: m_south = other; return true;
        case Direction::East:  m_east  = other; return true;
        case Direction::West:  m_west  = other; return true;
        default: return false;
    }
}

Direction Room::parseDirection(const std::string& s) {
    const std::string t = utils::toLower(s);
    if (t == "north") return Direction::North;
    if (t == "south") return Direction::South;
    if (t == "east")  return Direction::East;
    if (t == "west")  return Direction::West;
    return Direction::Invalid;
}
