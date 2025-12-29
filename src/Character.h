#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Item.h"

class Room;

enum class CharClass { Warrior, Thief, Mage, Unknown };

class Character {
public:
    Character() = default;
    Character(CharClass cc, std::string name);

    const std::string& name() const { return m_name; }
    CharClass cclass() const { return m_class; }

    int hp() const { return m_hp; }
    int str() const { return m_str; }
    int def() const { return m_def; }
    bool isAlive() const { return m_hp > 0; }

    Room* room() const { return m_room; }
    void setRoom(Room* r) { m_room = r; }

    // Combat (player side)
    int dealDamageTo(int defenderDef) const; // max(1, STR - DEF)
    void takeDamage(int dmg);

    // Items
    bool pickUpItem(Item&& it, std::string& outMsg);

    // Inventory names for final stats output
    std::vector<std::string> inventoryNames() const;

    static CharClass parseClass(const std::string& s);

private:
    bool canEquip(ItemKind k) const;
    bool equipOrCompare(Item&& it, std::string& outMsg);
    void applyPotion(const Item& it, std::string& outMsg);

    void addStats(const StatsBonus& b);
    void subStats(const StatsBonus& b);

private:
    CharClass m_class{CharClass::Unknown};
    std::string m_name;

    int m_hp{0};
    int m_str{0};
    int m_def{0};

    Room* m_room{nullptr};

    // Equipment by kind (Sword/Dagger/Wand/Shield)
    std::unordered_map<ItemKind, Item> m_equipped;
};
