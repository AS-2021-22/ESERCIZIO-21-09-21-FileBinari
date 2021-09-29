#pragma once
#include <string>
using namespace std;
class Dato
{
	public:
		Dato();
		Dato(const char* CF, const char* nome, const char* cognome, const char* classe, const char* nomeProgetto, const char* sede, const char* periodo);
		Dato(string CF, string nome, string cognome, string classe, string nomeProgetto, string sede, string periodo);
		char CF[17];
		char nome[20];
		char cognome[20];
		char classe[5];
		char nomeProgetto[50];
		char sede[50];
		char periodo[30];

		void print();
};

