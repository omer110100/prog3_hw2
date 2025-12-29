#pragma once
#include <string>

class Monster {
public:
    Monster() = default;
    Monster(std::string name, int hp, int str, int def);

    const std::string& name() const { return m_name; }
    int hp() const { return m_hp; }
    int str() const { return m_str; }
    int def() const { return m_def; }

    bool isDead() const { return m_hp <= 0; }
    void takeDamage(int dmg);

private:
    std::string m_name;
    int m_hp{0};
    int m_str{0};
    int m_def{0};
};
