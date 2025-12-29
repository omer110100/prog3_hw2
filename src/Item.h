#pragma once
#include <string>

enum class ItemKind {
    Sword, Dagger, Wand, Shield,
    HealthPotion, StrengthPotion, DefensePotion,
    Unknown
};

struct StatsBonus {
    int hp{0};
    int str{0};
    int def{0};
    int total() const { return hp + str + def; }
};

class Item {
public:
    Item() = default;
    Item(ItemKind k, std::string name, StatsBonus b, bool potion);

    const std::string& name() const { return m_name; }
    ItemKind kind() const { return m_kind; }
    const StatsBonus& bonus() const { return m_bonus; }
    bool isPotion() const { return m_isPotion; }

    static ItemKind parseKind(const std::string& s);
    static Item createDefault(ItemKind k);

private:
    ItemKind m_kind{ItemKind::Unknown};
    std::string m_name;
    StatsBonus m_bonus;
    bool m_isPotion{false};
};
