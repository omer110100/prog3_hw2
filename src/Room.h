#pragma once
#include <memory>
#include <string>
#include "Item.h"
#include "Monster.h"

enum class Direction { North, South, East, West, Invalid };

class Room {
public:
    explicit Room(std::string name);

    const std::string& name() const { return m_name; }

    Room* get(Direction d) const;
    bool set(Direction d, Room* other);

    std::unique_ptr<Item>& item() { return m_item; }
    std::unique_ptr<Monster>& monster() { return m_monster; }

    static Direction parseDirection(const std::string& s);

private:
    std::string m_name;

    Room* m_north{nullptr};
    Room* m_south{nullptr};
    Room* m_east{nullptr};
    Room* m_west{nullptr};

    std::unique_ptr<Item> m_item;
    std::unique_ptr<Monster> m_monster;
};
