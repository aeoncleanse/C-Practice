// LuaScript class implementation

#include <string>
#include <iostream>
#include "luascript.h"

using namespace std;

LuaScript::LuaScript(const string& filename) {
    L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        cout<<"Error: script not loaded ("<<filename<<")"<<endl;
        L = 0;
    }
}

LuaScript::~LuaScript() {
    if(L) lua_close(L);
}

void LuaScript::printError(const string& variableName, const string& reason) {
     cout<<"Error: can't get ["<<variableName<<"]. "<<reason<<endl;
}
