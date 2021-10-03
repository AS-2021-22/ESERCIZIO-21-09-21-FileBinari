#include "Header.h"

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
    cout << "3. SEARCH - Print a specific user information:" << endl;
    cout << "4. INSERT - Add an user:" << endl;
    cout << "5. DELETE - Delete an user:" << endl;
    cout << "6. UPDATE - Update an user:" << endl;
    cout << "7. Exit:" << endl;
    while (scelta < 1 || scelta>7) {
        scelta = 0;
        cin >> scelta;
    }
    return scelta;
}

void LoadTestData() {
    Dato a[] = {
         Dato("CRMGNN03A21H910M","Giovanni","Carminati","5IB","Lavapiatti","Rifugio Laghi Gemelli","15-06-21 / 06-09-21"),
         Dato("BLTDVD03A20H910B","Davide","Belotti","5IB","Palestra","Sangiovanni bianco","15-06-21 / 06-09-21"),
         Dato("FSNGNN03T23B157Z","Giovanni","Fusini","5IB","Pulito magazzini","Azienda SRL","15-06-21 / 06-09-21"),
         Dato("SCTDVD03R14A794X","Davide","Scotti","5IB","C# programming","Azienda ricca","15-06-21 / 06-09-21")
    };

    for (int i = 0; i < 4; i++)writeDataOnFile(a[i]);
}

void printAllDato() {
    for (map<string, int>::iterator it = collection.begin(); it != collection.end(); it++) {
        try { readFromFile(it->first).print(); }
        catch (...) { cout << "index: " << it->first << " not found" << endl; }
    }
}

void copy(char a[], const char* b) {
    int i;
    for (i = 0; *(b + i) != '\0'; i++)a[i] = *(b + i);
    a[i] = '\0';
}

void copy(char a[], string b) {
    int i;
    for (i = 0; b[i] != '\0'; i++)a[i] = b[i];
    a[i] = '\0';
}