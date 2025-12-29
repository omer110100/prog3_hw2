#include "Monster.h"
#include <algorithm>

Monster::Monster(std::string name, int hp, int str, int def)
    : m_name(std::move(name)), m_hp(hp), m_str(str), m_def(def) {}

void Monster::takeDamage(int dmg) {
    m_hp -= std::max(0, dmg);
}
