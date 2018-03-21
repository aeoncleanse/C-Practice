#include "unit.h"

using namespace std;

const string fileDir = ".\\bin\\Debug\\";

/**
Populates the units table
**/
void makeUnits(const string fileDir, vector<Unit> &units) {
    DIR* dir = opendir(fileDir.c_str());
    dirent* pdir;

    while ((pdir = readdir(dir))) {
        string fileName = string(pdir->d_name);
        if((fileName.rfind(".bp") != string::npos) && (fileName.length() > 0)) { // True if .bp is found anywhere in the string
            units.push_back(Unit(fileName));
        }
    }
}

int main() {
    vector<Unit> units;
    makeUnits(fileDir, units);

    // Attempt to create an output file
    ofstream outfile(fileDir + "output.txt");
    if(outfile.fail()) {
        cout << "Couldn't create output file: " << fileDir << "output.txt" << endl;
    }

    // Loop over all weapons in each unit and output relevant data
    for(unsigned int i = 0; i < units.size(); i++) {
        outfile << units[i].uid << endl;

        for(unsigned int j = 0; j < units[i].weapons.size(); j++) {
            outfile << units[i].weapons[j].Strings["Label"] << endl;

            for(auto k : units[i].weapons[j].Numbers) {
                outfile << k.first << " = " << k.second << endl;
            }
        }
    }

    units.clear();

    return 0;
}
