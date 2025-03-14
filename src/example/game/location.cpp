#include "location.h"
#include "map.h"

// Constructor
Location::Location(std::string name, LocationID id)
        : name(name), id(id), map_slot(nullptr), first_visit(true),
          fog_of_war(true), unique_event_id(-1), reward_icon_1(-1), reward_icon_2(-1),
          quest_marker(false) {}

Location::Location( LocationID id)
        : name("Dummy"), id(id), map_slot(nullptr), first_visit(true),
          fog_of_war(true), unique_event_id(-1), reward_icon_1(-1), reward_icon_2(-1),
          quest_marker(false) {}

// Gets active connections from the Map_Slot
std::vector<int> Location::GetActiveConnections() const {
    std::vector<int> active_connections;
    for (const auto& connection : map_slot->connections) {
        if (connection.second) {
            active_connections.push_back(connection.first);
        }
    }
    return active_connections;
}

// Resets all connections to desired state
void Location::ResetConnections(bool state) {
    if(map_slot) {
        for (auto &connection: map_slot->connections) {
            connection.second = state;
        }
    }
}

void Location::SetMapSlot(Map_Slot* slot) {
    map_slot = slot;
}
LocationID Location::GetLocationID() const { return id;}
std::string Location::GetLocationString() const {return name;}

Map_Slot* Location::GetMapSlot() {
    if(!map_slot) {
        std::cerr << "Error: Map_Slot " << map_slot << " does not exist.\n";
        return nullptr;
    }else{
        return map_slot;
    }
}

void Location::SetName(std::string newname) {
    name = std::move(newname);
}

MonsterID Location::AddMonster(const Monster& monster) {
    monsters.push_back(monster);
    return monster.id;// Copy the Monster into the location
}
void Location::RemoveMonster(MonsterID id) {
    auto it = std::find_if(monsters.begin(), monsters.end(),
                           [id](const Monster& m) { return m.id == id; });
    if (it != monsters.end()) {
        monsters.erase(it);  // Only removes the first matching monster

    }
}

Monster Location::GetMonster(MonsterID id)  {
    for (const auto& monster : monsters) {
        if (monster.id == id) {
            return monster; // Return a copy of the found monster
        }
    }
    throw std::runtime_error("Monster not found in this location");
}



void Location::AddEncounter(EncounterID id) {
    // Check if the encounter is already in the vector to prevent duplicates
    if (std::find(related_events.begin(), related_events.end(), id) == related_events.end()) {
        related_events.push_back(id);
    }
}

void Location::RemoveEncounter(EncounterID id) {
    // Use erase-remove idiom to remove the encounter ID if it exists
    related_events.erase(std::remove(related_events.begin(), related_events.end(), id), related_events.end());
}

