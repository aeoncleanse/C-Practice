#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// Files we will need in the FAForever install location
string logFile = "C:\\ProgramData\\FAForever\\bin\\PerfTestLog.txt";
string resultsFile = "C:\\ProgramData\\FAForever\\bin\\PerfTestResults.csv";
char* commandLine = (char*)"C:\\ProgramData\\FAForever\\bin\\ForgedAlliance.exe /init \"init_dev.lua\" /EnableDiskWatch /showlog /size 1024 768 /nomovie /nointro /perf /log \"C:\\ProgramData\\FAForever\\bin\\PerfTestLog.txt\"";

int main()
{
    cout << "Welcome to the FAF Performance Test" << endl;
    cout << "Please enter the number of tests you would like to run: " << endl;

    // Wait on user input
    int tests;
    cin >> tests;

    cout << "Beginning execution of " << tests << " tests. Please stand by." << endl;

    int counter = 1;

    // Information and setup for the program
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    while(counter <= tests) {
        cout << "Test number " << counter << " currently in progress." << endl;

        // Run the program
        if(!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("CreateProcess failed (%d).\n", GetLastError());
            return 1;
        }

        // Wait for the game to finish and quit
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Read the log file
        string results;
        ifstream infile(logFile.c_str());
        if(infile.fail()) {
            printf("Couldn't load PerfTestLog.txt - (%d).n", GetLastError());
            return 1;
        } else {
            for(string line; getline(infile, line);) {
                if(line.find("Results: ") != string::npos) {
                    results = line;
                    infile.close();
                    break;
                }
            }
        }

        // Open the output file for appending
        ofstream outfile;
        outfile.open(resultsFile.c_str(), ios::app);
        if(outfile.fail()) {
            printf("Couldn't load PerfTestResults.csv - (%d).n", GetLastError());
            return 1;
        } else {
            // Write the results to the file
            outfile << results.substr(18) << endl;
            outfile.close();
        }

        // Increment our execution counter
        counter += 1;
    }

    cout << "Test run complete" << endl;

    return 0;
}
