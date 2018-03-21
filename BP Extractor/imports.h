#ifndef IMPORTS_H_INCLUDED
#define IMPORTS_H_INCLUDED

#include <string>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>

static void Error(const std::string& errmsg) {
    std::cout << "Error: " << errmsg << std::endl;
    exit(1);
}

#endif // IMPORTS_H_INCLUDED
