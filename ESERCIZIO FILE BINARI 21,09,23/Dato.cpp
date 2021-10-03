#include "Dato.h"
#include "Header.h"
#include <iostream>


using namespace std;



Dato::Dato() {

}

void Dato::print() {
	cout << ".............................." << endl;
	cout << "CF: " << CF << endl;
	cout << "nome: " << nome << endl;
	cout << "cognome: " << cognome << endl;
	cout << "classe: " << classe << endl;
	cout << "nome progetto: " << nomeProgetto << endl;
	cout << "sede: " << sede << endl;
	cout << "periodo: " << periodo << endl;
	cout << ".............................." << endl;
}

Dato::Dato(string CF, string nome, string cognome, string classe, string nomeProgetto, string sede, string periodo) {
	copy(this->CF, CF);
	copy(this->nome, nome);
	copy(this->cognome, cognome);
	copy(this->classe, classe);
	copy(this->nomeProgetto, nomeProgetto);
	copy(this->sede, sede);
	copy(this->periodo, periodo);
}
Dato::Dato(const char* CF, const char* nome, const char* cognome, const char* classe, const char* nomeProgetto, const char* sede, const char* periodo) {
	copy(this->CF, CF);
	copy(this->nome, nome);
	copy(this->cognome, cognome);
	copy(this->classe, classe);
	copy(this->nomeProgetto, nomeProgetto);
	copy(this->sede, sede);
	copy(this->periodo, periodo);
}