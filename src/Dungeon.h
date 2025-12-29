#pragma once
#include <memory>
#include <string>

class Room;

class Dungeon {
public:
    Dungeon();
    ~Dungeon(); // מוגדר ב-cpp כדי ש-Room יהיה שלם בזמן destroy

    Dungeon(const Dungeon&) = delete;
    Dungeon& operator=(const Dungeon&) = delete;
    Dungeon(Dungeon&&) noexcept = default;
    Dungeon& operator=(Dungeon&&) noexcept = default;

    bool createRoom(const std::string& name, std::string& outMsg);
    Room* findRoom(const std::string& name) const;

    bool connect(const std::string& a, const std::string& b, const std::string& dir, std::string& outMsg);

    bool setStartRoom(const std::string& name, std::string& outMsg);
    Room* startRoom() const { return m_start; }

    bool reachable(Room* from, Room* target) const;
    bool hasIncoming(Room* target) const;

private:
    struct Node {
        std::unique_ptr<Room> room;
        std::unique_ptr<Node> next;

        explicit Node(std::unique_ptr<Room> r);
        ~Node(); // גם זה ב-cpp
    };

    std::unique_ptr<Node> m_head;
    Room* m_start{nullptr};
};
