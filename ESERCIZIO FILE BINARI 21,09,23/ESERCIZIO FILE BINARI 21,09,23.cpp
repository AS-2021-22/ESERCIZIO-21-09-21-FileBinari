#pragma once //THIS CODE HAS BEEN CREATED FOR 4-10-2021
#include "Header.h"

std::map<std::string, int> collection; //is defined extern in globals.h and needs to be declared in a cpp

int main()
{
    //createEmptyFile();
    LoadCollection();
    //LoadTestData();
    int n = 0;
    while (n != 7) { 
        n = menu();
        system("cls");
        if (n == 1) //PRINT MAP
        {
            for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
                cout << "CF:" << it->first << " pos in data.bin: " << it->second << endl;
            }
        }
        else if (n == 2) { //PRINT ALL INFORMATION
            printAllDato();
        }
        else if (n == 3) { //PRINT A SPECIFIC USER INFORMATION
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            try { readFromFile(CF).print();}
            catch (...) {
                cout << "User not found" << endl;
            }
        }
        else if (n == 4) { //ADD A NEW USER
            insertDato();
        }
        else if (n == 5) { //DELETE AN USER
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            collection.erase(CF);
            updateCollection();
        }
        else if (n == 6){ //UPDATE
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            try { updateDato(searchPosDato(CF), readFromFile(CF)); } //readFromFile generate an exception if the CF doesn't exist, so it is not needed to handle searchPosDato == -1
            catch (...) { cout << "The user doesn't exists, try checking the CF" << endl; }
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
