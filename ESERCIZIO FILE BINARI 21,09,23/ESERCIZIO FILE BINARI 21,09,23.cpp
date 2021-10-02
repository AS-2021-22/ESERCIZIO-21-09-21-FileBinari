#pragma once
#include "Header.h"

std::map<std::string, int> collection; //is defined extern in globals.h and needs to be declared in a cpp

int main()
{
    //createEmptyFile();
    LoadCollection();
    //LoadTestData();
    int n = 0;
    while (n != 6) {
        n = menu();
        system("cls");
        if (n == 1)
        {
            for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
                cout << "CF:" << it->first << " pos in data.bin: " << it->second << endl;
            }
        }
        else if (n == 2) {
            printAllDato();
        }
        else if (n == 3) {
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            try { readFromFile(CF).print(); }
            catch (...) {
                cout << "User not found" << endl;
            }
        }
        else if (n == 4) {
            insertDato();
        }
        else if (n == 5) {
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            collection.erase(CF);
            updateCollection();
        }
        else {
            cout << "updating map.csv ....";
        }
        cout << endl << endl;
        system("pause");
        system("cls");
    }

    updateCollection();
    return 0;
}
