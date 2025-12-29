#include "Dungeon.h"
#include "Room.h"
#include <unordered_set>
#include <vector>
#include <utility>

Dungeon::Dungeon() = default;
Dungeon::~Dungeon() = default;

Dungeon::Node::Node(std::unique_ptr<Room> r)
    : room(std::move(r)) {}

Dungeon::Node::~Node() = default;

Room* Dungeon::findRoom(const std::string& name) const {
    for (Node* p = m_head.get(); p; p = p->next.get()) {
        if (p->room && p->room->name() == name) return p->room.get();
    }
    return nullptr;
}

bool Dungeon::createRoom(const std::string& name, std::string& outMsg) {
    if (name.empty()) {
        outMsg = "Error: room name is empty.";
        return false;
    }
    if (findRoom(name)) {
        outMsg = "Error: room '" + name + "' already exists.";
        return false;
    }

    auto newNode = std::make_unique<Node>(std::make_unique<Room>(name));
    newNode->next = std::move(m_head);
    m_head = std::move(newNode);

    outMsg = "Created room " + name + ".";
    return true;
}

bool Dungeon::reachable(Room* from, Room* target) const {
    if (!from || !target) return false;
    if (from == target) return true;

    std::unordered_set<Room*> vis;
    std::vector<Room*> st;
    st.push_back(from);
    vis.insert(from);

    while (!st.empty()) {
        Room* cur = st.back();
        st.pop_back();
        if (cur == target) return true;

        Room* neigh[4] = {
            cur->get(Direction::North),
            cur->get(Direction::South),
            cur->get(Direction::East),
            cur->get(Direction::West)
        };

        for (Room* nxt : neigh) {
            if (nxt && !vis.count(nxt)) {
                vis.insert(nxt);
                st.push_back(nxt);
            }
        }
    }
    return false;
}

bool Dungeon::hasIncoming(Room* target) const {
    if (!target) return false;
    for (Node* p = m_head.get(); p; p = p->next.get()) {
        Room* r = p->room.get();
        if (!r) continue;
        for (Direction d : {Direction::North, Direction::South, Direction::East, Direction::West}) {
            if (r->get(d) == target) return true;
        }
    }
    return false;
}

bool Dungeon::connect(const std::string& a, const std::string& b, const std::string& dir, std::string& outMsg) {
    Room* ra = findRoom(a);
    Room* rb = findRoom(b);

    if (!ra || !rb) {
        outMsg = "Error: connect failed (room not found).";
        return false;
    }

    Direction d = Room::parseDirection(dir);
    if (d == Direction::Invalid) {
        outMsg = "Error: invalid direction.";
        return false;
    }

    if (hasIncoming(rb)) {
        outMsg = "Error: room '" + b + "' already has an incoming connection.";
        return false;
    }

    if (reachable(rb, ra)) {
        outMsg = "Error: circular connection is not allowed.";
        return false;
    }

    if (!ra->set(d, rb)) {
        outMsg = "Error: direction already occupied from '" + a + "'.";
        return false;
    }

    outMsg = "Connected " + a + " -> " + b + " (" + dir + ").";
    return true;
}

bool Dungeon::setStartRoom(const std::string& name, std::string& outMsg) {
    Room* r = findRoom(name);
    if (!r) {
        outMsg = "Error: start room not found.";
        return false;
    }
    m_start = r;
    outMsg = "StartRoom set to " + name + ".";
    return true;
}
