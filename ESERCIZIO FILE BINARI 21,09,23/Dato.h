#pragma once
#ifndef LIBRARY_H_DATO
#define LIBRARY_H_DATO
#include <string>
#endif

#ifndef DATO_CLASS_H
#define DATO_CLASS_H
	class Dato
	{
	public:
		Dato();
		Dato(const char* CF, const char* nome, const char* cognome, const char* classe, const char* nomeProgetto, const char* sede, const char* periodo);
		Dato(std::string CF, std::string nome, std::string cognome, std::string classe, std::string nomeProgetto, std::string sede, std::string periodo);
		char CF[17];
		char nome[20];
		char cognome[20];
		char classe[5];
		char nomeProgetto[50];
		char sede[50];
		char periodo[30];

		void print();
	};
#endif // !DATO_CLASS_H

