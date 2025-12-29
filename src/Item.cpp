#include "Item.h"
#include "Utils.h"

Item::Item(ItemKind k, std::string name, StatsBonus b, bool potion)
    : m_kind(k), m_name(std::move(name)), m_bonus(b), m_isPotion(potion) {}

ItemKind Item::parseKind(const std::string& s) {
    const std::string t = utils::toLower(s);

    if (t == "sword") return ItemKind::Sword;
    if (t == "dagger") return ItemKind::Dagger;
    if (t == "wand") return ItemKind::Wand;
    if (t == "shield") return ItemKind::Shield;

    if (t == "healthpotion" || t == "health_potion" || t == "health") return ItemKind::HealthPotion;
    if (t == "strengthpotion" || t == "strength_potion" || t == "strength") return ItemKind::StrengthPotion;
    if (t == "defensepotion" || t == "defense_potion" || t == "defense") return ItemKind::DefensePotion;

    return ItemKind::Unknown;
}

Item Item::createDefault(ItemKind k) {
    switch (k) {
        case ItemKind::Sword:  return Item(k, "Sword",  {0, 5, 10}, false);
        case ItemKind::Dagger: return Item(k, "Dagger", {0, 7, 3},  false);
        case ItemKind::Wand:   return Item(k, "Wand",   {0,10, 0},  false);
        case ItemKind::Shield: return Item(k, "Shield", {0, 0, 5},  false);

        case ItemKind::HealthPotion:   return Item(k, "HealthPotion",   {10,0,0}, true);
        case ItemKind::StrengthPotion: return Item(k, "StrengthPotion", {0,5,0},  true);
        case ItemKind::DefensePotion:  return Item(k, "DefensePotion",  {0,0,5},  true);

        default: return Item(ItemKind::Unknown, "Unknown", {0,0,0}, false);
    }
}
