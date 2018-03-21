// Unit class implementation

#include "unit.h"

using namespace std;

string fileDir = ".\\bin\\Debug\\";

/**
The file name of the source unit blueprint file is passed in
**/
Unit::Unit(const string filename) {
    // Create and save file paths
    fromfile = fileDir + filename;
    tofile = fromfile.substr(0, fromfile.size()-3) + ".new";

    uid = filename.substr(0, filename.size()-8); // "UEL0001_unit.bp" --> "UEL0001"

    string file = adjustFile(); // Create new file compatible with being loaded as lua (Remove GPG special sauce)
    loadLUA(file);
    createWeapons();

    closeLua();
}

/**
Adjusts the file from GPG's special Blueprint format to match lua's table format
Strips the first and last lines, and remove the first 4 spaces from the start of all remaining lines
**/
string Unit::adjustFile() {
    // Create streams in and out
    ifstream infile(fromfile);
    ostringstream out;

    // Check for failures
    if(infile.fail()) {
        cout << "Couldn't load file: " << fromfile << endl;
    } else {
        for(string line; getline(infile, line);) {
            if(line == "UnitBlueprint {") {
                line = "UnitBlueprint = {";
            }
            // TODO: Remove # and anything proceeding it
            // fix further instances of GPG sauce, eg AirUnitWaterImpact = Sound {, missing an =
            out << line << endl;
        }
        infile.close();
    }

    return out.str();
}

/**
Loads a LUA state and saves it as luaInstance, then opens up the necessary file and navigates to the Weapon table
**/
void Unit::loadLUA(string input) {
    L = lua_open();
    luaL_loadstring(L, input.c_str()); // Load the string
    lua_pcall(L, 0, 0, 0); // 'Run' the file, putting things ready for processing
    lua_getglobal(L, "UnitBlueprint"); // Loads the whole table to the lua stack
    lua_getfield(L, -1, "Weapon");
}

void Unit::createWeapons() {
    lua_pushnil(L);
    int wepNumber = 0;
    while(lua_next(L, -2) != 0) {
        if(lua_istable(L, -1)) {
            weapons.push_back(Weapon());
            populateWeapon(wepNumber);
            weapons[wepNumber].calculateDPS();
        }
        lua_pop(L, 1);
        wepNumber += 1;
    }
}

/**
k.first is the string I need to go and find, for example, "Damage"
k.second defaults at 0 in weapon.cpp for all values, then gets set to a new value if it exists in LUA
**/
void Unit::populateWeapon(int wepNumber) {
    lua_pushnil(L);
    int index = 0;
    // Loop the weapon and store any values by type
    while(lua_next(L, -2) != 0) {

        if(lua_isnumber(L, -1)) {
            weapons[wepNumber].Numbers[lua_tostring(L, -2)] = lua_tonumber(L, -1);
        } else if(lua_isstring(L, -1)) {
            weapons[wepNumber].Strings[lua_tostring(L, -2)] = lua_tostring(L, -1);
        } else if (lua_isboolean(L, -1)) {
            weapons[wepNumber].Booleans[lua_tostring(L, -2)] = lua_toboolean(L, -1);
        } else if ((lua_istable(L, -1)) && (string(lua_tostring(L, -2)) == "RackBones")) {
            lua_pushnil(L);
            int rack = 0;
            while(lua_next(L, -2) != 0) {
                string rackBone;
                lua_getfield(L, -1, "RackBone");
                rackBone = lua_tostring(L, -1);
                lua_pop(L, 1);

                int muzzleCount;
                lua_getfield(L, -1, "MuzzleBones");
                muzzleCount = lua_objlen(L, -1);
                lua_pop(L, 1);

                weapons[wepNumber].Racks[rackBone] = muzzleCount;

                lua_pop(L, 1);
                rack += 1;
            }
        }

        lua_pop(L, 1);
        index += 1;
    }
}

void Unit::closeLua() {
    if(!L) {
        return;
    }
    lua_close(L);
    L = nullptr;
}
