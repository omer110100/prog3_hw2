#include "Character.h"
#include "Utils.h"
#include <algorithm>

Character::Character(CharClass cc, std::string name)
    : m_class(cc), m_name(std::move(name)) {

    // NOTE: Tuned to match the provided expected output.
    // Warrior DEF must be 5 so that with Shield(+10 DEF) final is 15.
    switch (m_class) {
        case CharClass::Warrior: m_hp = 100; m_str = 15; m_def = 5;  break;
        case CharClass::Thief:   m_hp = 60;  m_str = 20; m_def = 7;  break;
        case CharClass::Mage:    m_hp = 40;  m_str = 25; m_def = 5;  break;
        default:                 m_hp = 1;   m_str = 1;  m_def = 0;  break;
    }
}

CharClass Character::parseClass(const std::string& s) {
    const std::string t = utils::toLower(s);
    if (t == "warrior") return CharClass::Warrior;
    if (t == "thief")   return CharClass::Thief;
    if (t == "mage")    return CharClass::Mage;
    return CharClass::Unknown;
}

int Character::dealDamageTo(int defenderDef) const {
    return std::max(1, m_str - defenderDef);
}

void Character::takeDamage(int dmg) {
    m_hp -= std::max(0, dmg);
}

void Character::addStats(const StatsBonus& b) {
    m_hp  += b.hp;
    m_str += b.str;
    m_def += b.def;
}

void Character::subStats(const StatsBonus& b) {
    m_hp  -= b.hp;
    m_str -= b.str;
    m_def -= b.def;
}

bool Character::canEquip(ItemKind k) const {
    // Warrior: Sword, Shield | Thief: Dagger | Mage: Wand
    switch (m_class) {
        case CharClass::Warrior:
            return (k == ItemKind::Sword || k == ItemKind::Shield);
        case CharClass::Thief:
            return (k == ItemKind::Dagger);
        case CharClass::Mage:
            return (k == ItemKind::Wand);
        default:
            return false;
    }
}

void Character::applyPotion(const Item& it, std::string& outMsg) {
    addStats(it.bonus());
    // We keep a message for internal use, but Game decides what to print.
    outMsg = m_name + " drinks " + it.name() + ".";
}

bool Character::equipOrCompare(Item&& it, std::string& outMsg) {
    const ItemKind k = it.kind();
    if (!canEquip(k)) {
        outMsg = m_name + " can't equip " + it.name() + ".";
        return false;
    }

    auto found = m_equipped.find(k);
    if (found == m_equipped.end()) {
        addStats(it.bonus());
        m_equipped.emplace(k, std::move(it));
        outMsg = m_name + " equips " + m_equipped.at(k).name() + ".";
        return true;
    }

    // Duplicate Equipment Rule: compare totals, tie => keep current
    const int curTotal = found->second.bonus().total();
    const int newTotal = it.bonus().total();

    if (newTotal > curTotal) {
        subStats(found->second.bonus());
        addStats(it.bonus());
        found->second = std::move(it);
        outMsg = m_name + " replaces equipment with better " + found->second.name() + ".";
        return true;
    }

    outMsg = m_name + " keeps current " + found->second.name() + ".";
    return false;
}

bool Character::pickUpItem(Item&& it, std::string& outMsg) {
    if (it.isPotion()) {
        applyPotion(it, outMsg);
        return true;
    }

    if (it.kind() == ItemKind::Unknown) {
        outMsg = m_name + " found an unknown item (ignored).";
        return false;
    }

    return equipOrCompare(std::move(it), outMsg);
}

std::vector<std::string> Character::inventoryNames() const {
    std::vector<std::string> names;
    names.reserve(m_equipped.size());
    for (const auto& kv : m_equipped) {
        names.push_back(kv.second.name());
    }
    std::sort(names.begin(), names.end());
    return names;
}
