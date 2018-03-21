// unit.h contains declarations for a class to contain relevant data extracted from unit blueprints

#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#include "weapon.h"

struct Unit {
    std::string fromfile;
    std::string tofile;
    std::string uid;
    std::vector<Weapon> weapons;
    lua_State* L;

    Unit(const std::string fileName);

    void buildWeapons();
    std::string adjustFile();
    void closeLua();
    void loadLUA(std::string input);
    void createWeapons();
    void populateWeapon(int index);
};

#endif // UNIT_H_INCLUDED
