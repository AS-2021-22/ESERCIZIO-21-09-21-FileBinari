#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <functional>
#include <string>

#include "Dato.h"
#include "globals.h"

using namespace std;

#ifndef FUNCTIONS_DECLARETIONS
#define FUNCTIONS_DECLARATIONS

int menu();
void updateDato(int pos, Dato dato);
int searchPosDato(string CF);
int posInOverflow(string CF);
bool positionIsFree(int pos);
void insertDato();
string hashString(string CF);
int hashInt(string CF);
void LoadCollection();
void updateCollection();
Dato collisionMinusOnePosition(string CF);
void writeOnFile(Dato& data, int pos);
Dato readFromFile(string CF);
string atos(char a[]);
void createEmptyFile();
void writeDataOnFile(Dato& data);
void LoadTestData();
void printAllDato();
void copy(char a[], const char* b);

void copy(char a[], string b);

#endif // !FUNCTIONS_DECLARETIONS
