#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <functional>
#include <string>

#include "Dato.h"

#define DB_COLLECTION 100 // 1% probability of collision
#define NAME_FILE_DATA "Data.bin"
//#include <vector> 

using namespace std;

map<string, int> collection;

int menu();
bool positionIsFree(int pos);
void insertDato();
string hashString(string CF);
int hashInt(string CF);
void LoadCollection();
void updateCollection();
void writeOnFile(Dato& data,int pos);
Dato readFromFile(string CF);
string atos(char a[]);
void createEmptyFile();
void writeDataOnFile(Dato& data);
void LoadTestData() {
    Dato a[] = {
         Dato("CRMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21"),
         Dato("BLTDVD03A20H910B","Davide","Belotti","5IB","Palestra","Sangiovanni bianco","15-06-21 / 06-09-21"),
         Dato("FSNGNN03T23B157Z","Giovanni","Fusini","5IB","Pulito magazzini","Azienda SRL","15-06-21 / 06-09-21"),
         Dato("SCTDVD03R14A794X","Davide","Scotti","5IB","C# programming","Azienda ricca","15-06-21 / 06-09-21")
    };

    for (int i = 0; i < 4; i++)writeDataOnFile(a[i]);
}


int main()
{
    //createEmptyFile();
    LoadCollection();
    //LoadTestData();
    int n = 0;
    while (n != 5) {
        n = menu();
        system("cls");
        if (n == 1)
        {
            for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
                cout << "CF:" << it->first << " pos in data.bin: " << it->second << endl;
            }
        }
        else if (n == 2) {
            for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
                try { readFromFile(it->first).print(); }
                catch (...) { cout << "index: " << it->first << " not found" << endl; }
            }
        }
        else if (n == 3) {
            string CF;
            cout << "Insert CF of the user: "; cin >> CF;
            try { readFromFile("3RMGNN03A21H910M").print(); }
            catch (...) {
                cout << "index not found" << endl;
            }
        }
        else if (n == 4) {
            insertDato();
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

string atos(char a[]) {
    string r = "";
    for (int i = 0; a[i] != '\0'; i++)r += a[i];
    return r;
}

string hashString(string CF) {
    size_t a = hash<string>{}(CF);
    a = a % DB_COLLECTION;
    string hash = to_string(a);
    return hash;
}

int hashInt(string CF) {
    size_t a = hash<string>{}(CF);
    return a % DB_COLLECTION;
}

void updateCollection() {
    fstream csvOut("map.csv", ios::out);
    if (csvOut.is_open()) {
        for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
            csvOut << it->first << ',' << it->second << endl;
        }
        csvOut.close();
    }
}

void writeOnFile(Dato& data,int pos) {
    fstream BinaryFileW(NAME_FILE_DATA,ios::in | ios::out | ios::binary);
    if (BinaryFileW.is_open()) {    //write on bin

        BinaryFileW.seekp(0, ios::end); //default n = eof
        int n = BinaryFileW.tellp();
        if(pos != -1) n = pos * sizeof(Dato);
        BinaryFileW.seekp(n);
        cout << " after: " << BinaryFileW.tellp() <<endl;

        BinaryFileW.write((char*)&data, sizeof(Dato));

        
        BinaryFileW.close();
    }
}

void writeDataOnFile(Dato& data) {
    int pos = hashInt(data.CF);
    if (!positionIsFree(pos)) {
        pos = -1;
    }
    collection.insert(pair<string, int>(atos(data.CF), pos)); //inserisco nella mappa CF come chiave e posizione come valore
    writeOnFile(data, pos);
    updateCollection();
}

bool positionIsFree(int pos) { //true if the position is free
    fstream in(NAME_FILE_DATA, ios::in | ios::binary);
    if (in.is_open()) {
        char sread[sizeof(Dato)];
        in.seekg(pos * sizeof(Dato));
        in.read(sread, sizeof(Dato));
        if (sread[0] == char(0)) return true;
        else return false;
    }
    else return false;
}

Dato readFromFile(string CF) {
    int pos = collection[CF];
    fstream BinaryFileR(NAME_FILE_DATA, ios::in | ios::binary);
    if (BinaryFileR.is_open()) {
        Dato r;
        BinaryFileR.seekg(pos * sizeof(Dato), ios::beg);
        BinaryFileR.read((char*)&r, sizeof(Dato));
        r.print();
        return r;
    }
    else throw "No item found";
}

void LoadCollection() { //loads all the key-values from the dictionary | CSV file reading
    fstream in("map.csv", ios::in);
    string line, skey, svalue;
    if (in.is_open()) {
        while (getline(in, line)) {
            //cout << line << endl;
            stringstream sl(line); //using line as a stream
            getline(sl, skey, ','); //take the key
            //cout << skey << endl;
            getline(sl, svalue, ','); //take the value
            //cout << svalue << endl; 
            collection.insert(pair<string, int>(skey, stoi(svalue)));
        }
        in.close();
    }
}

void insertDato() {

    cin.ignore();
    string CF, nome, cognome, classe, progetto, sede, periodo;
    cout << "Insert following fields: " << endl;
    cout << "CF: "; getline(cin, CF);
    cout << "nome: ";  getline(cin, nome);
    cout << "cognome: ";  getline(cin, cognome);
    cout << "classe: ";  getline(cin, classe);
    cout << "progetto: ";  getline(cin, progetto);
    cout << "sede: ";  getline(cin, sede);
    cout << "periodo: ";  getline(cin, periodo);

    Dato a(CF, nome, cognome, classe, progetto, sede, periodo);

    a.print();

    writeDataOnFile(a);

}

int menu() {
    int scelta = 0;
    cout << "Select the operation:" << endl;
    cout << "1. Show the collection map (key-values)" << endl;
    cout << "2. Print all the users informations:" << endl;
    cout << "3. Print a specific user information:" << endl;
    cout << "4. Add an user:" << endl;
    cout << "5. Exit:" << endl;
    while (scelta < 1 || scelta>5) {
        scelta = 0;
        cin >> scelta;
    }
    return scelta;
}


void createEmptyFile() {
    fstream clr(NAME_FILE_DATA, ios::out | ios::binary);
    char emptyDato[sizeof(Dato)];
    if (clr.is_open()) {
        for (int i = 0; i < sizeof(Dato); i++)emptyDato[i] = char(0);
        if (clr.is_open()) {
            for (int i = 0; i < DB_COLLECTION; i++)clr.write((char*)emptyDato, sizeof(Dato));
        }
    }

    clr.open("map.csv", ios::out);
    if (clr.is_open()) {
        clr.clear();
        clr.close();
    }
}

