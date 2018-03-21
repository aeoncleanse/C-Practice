// weapon.h contains declarations for a class to take lua state at weapon and calculate DPS from it

#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "imports.h"

using std::string;
using std::unordered_map;

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

struct Weapon {
    double DPS;
    unordered_map<string, string> Strings;
    unordered_map<string, bool> Booleans;
    unordered_map<string, double> Numbers;
    unordered_map<string, int> Racks;

    Weapon();
    int calculateDPS();
    double calculateSalvoDamage(int muzzleSalvoSize);
    bool VerifyEssentials();
};

#endif // WEAPON_H_INCLUDED
