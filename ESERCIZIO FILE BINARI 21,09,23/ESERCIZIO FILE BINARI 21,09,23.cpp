#include <iostream>
#include "Dato.h"
#include <fstream>
#include <map>
#include <sstream>
#include <stdlib.h>
//#include <vector>

using namespace std;


map<string, int> collection;

string atos(char a[]) {
    string r = "";
    for (int i = 0; a[i] != '\0'; i++)r += a[i];
    return r;
}

void writeOnFIle(Dato& data) {
    fstream BinaryFileW("Data.bin", ios::app | ios::binary);
    if (BinaryFileW.is_open()) {    //write on bin
        BinaryFileW.seekp(0, ios::end); //posiziono alla fine del file
        collection.insert(pair<string, int>(atos(data.CF), BinaryFileW.tellp() / sizeof(Dato))); //inserisco nella mappa CF come chiave e posizione come valore
        updateCollection();
        BinaryFileW.write((char*)&data, sizeof(Dato)); //scrivo su file nell'ultima posizione
        BinaryFileW.close();
    }
}

Dato readFromFile(string CF) {
    int pos = collection[CF];
    fstream BinaryFileR("Data.bin", ios::in | ios::binary);
    if (BinaryFileR.is_open()) {
        Dato r;
        BinaryFileR.seekg(pos * sizeof(Dato), ios::beg);
        BinaryFileR.read((char*)&r, sizeof(Dato));
        //r.print();
        return r;
    }
    else throw "No item found";
}

void LoadCollection() { //loads all the key-values from the dictionary | CSV file reading
    fstream in("map.csv",ios::in);
    string line,skey,svalue;
    if (in.is_open()) {
        while (getline(in, line)) {
            //cout << line << endl;
            stringstream sl(line); //using line as a stream
            getline(sl, skey, ','); //take the key
            //cout << skey << endl;
            getline(sl,svalue , ','); //take the value
            //cout << svalue << endl; 
            collection.insert(pair<string, int>(skey, stoi(svalue)));
        }
        in.close();
    }
}

void updateCollection() {
    fstream csvOut("map.csv", ios::out);
    if (csvOut.is_open()) {
        for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
            csvOut <<it->first << ',' << it->second << endl;
        }
        csvOut.close();
    }
}

void insertDato() {

    cin.ignore();
    string CF, nome, cognome, classe, progetto, sede, periodo;
    cout << "Insert following fields: " << endl;
    cout << "CF: "; getline(cin,CF);
    cout << "nome: ";  getline(cin, nome);
    cout << "cognome: ";  getline(cin, cognome);
    cout << "classe: ";  getline(cin, classe);
    cout << "progetto: ";  getline(cin, progetto);
    cout << "sede: ";  getline(cin, sede);
    cout << "periodo: ";  getline(cin, periodo);

    Dato a(CF, nome, cognome, classe, progetto, sede, periodo);

    a.print();

    writeOnFIle(a);
    
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


int main()
{
    LoadCollection();
    /*Dato a[] = {
         Dato("1RMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21"),
         Dato("2RMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21"),
         Dato("3RMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21"),
         Dato("4RMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21")
    };

    for(int i =0;i<4;i++)writeOnFIle(a[i]);*/
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
