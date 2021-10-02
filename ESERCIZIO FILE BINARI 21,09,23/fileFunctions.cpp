#include "Header.h"

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

Dato readFromFile(string CF) {
    int pos = collection[CF];
    if (pos == 0) { //when there is no CF in the collection
        throw "CF not found";
    }
    else if (pos == -1) { //when the data is in the staging
        return collisionMinusOnePosition(CF);
    }
    else {
        fstream BinaryFileR(NAME_FILE_DATA, ios::in | ios::binary);
        if (BinaryFileR.is_open()) {
            Dato r;
            BinaryFileR.seekg(pos * sizeof(Dato), ios::beg);
            BinaryFileR.read((char*)&r, sizeof(Dato));
            //r.print();
            return r;
        }
        throw "CF not found";
    }

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

void writeOnFile(Dato& data, int pos) {
    fstream BinaryFileW(NAME_FILE_DATA, ios::in | ios::out | ios::binary);
    if (BinaryFileW.is_open()) {    //write on bin      
        int n = DB_COLLECTION * sizeof(Dato); //default n = eof
        if (pos != -1) n = pos * sizeof(Dato);
        BinaryFileW.seekp(n);
        BinaryFileW.write((char*)&data, sizeof(Dato));
        BinaryFileW.close();
    }
}

void writeDataOnFile(Dato& data) {
    int pos = hashInt(data.CF);
    if (!positionIsFree(pos)) {
        pos = -1;
    }
    //HARDCODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TODO: delete this line
    //pos = -1;
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

Dato collisionMinusOnePosition(string CF) {
    Dato searched; int counter = 0;
    int eof = DB_COLLECTION * sizeof(Dato);
    bool trovato = false;
    fstream searchFile(NAME_FILE_DATA, ios::in | ios::binary);
    while (trovato == false && !searchFile.eof()) {
        searchFile.seekg(eof + counter * sizeof(Dato));
        searchFile.read((char*)&searched, sizeof(Dato));
        if (atos(searched.CF) == CF) trovato = true;
        counter++;
    }
    searchFile.close();
    return searched;
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