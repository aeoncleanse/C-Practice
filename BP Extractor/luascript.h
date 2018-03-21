#ifndef LUASCRIPT_H_INCLUDED
#define LUASCRIPT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

// Lua is written in C, so compiler needs to know how to link its libraries
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class LuaScript {
public:
    LuaScript(const std::string& filename);
    ~LuaScript();
    void printError(const std::string& variableName, const std::string& reason);

    template<typename T>
    T get(const std::string& variableName) {
        // will be implemented later in tutorial
    }
    bool lua_gettostack(const std::string& variableName) {
       // will be explained later too
    }

    // Generic get
    template<typename T>
    T lua_get(const std::string& variableName) {
      return 0;
    }

    // Generic default get
    template<typename T>
    T lua_getdefault(const std::string& variableName) {
      return 0;
    }
private:
    lua_State* L;
};

#endif // LUASCRIPT_H_INCLUDED
