#include "Matriu.h"
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 1e9

typedef vector<bool> VB;
typedef vector<VB> VBB;

typedef vector<int> VI;
typedef vector<VI> VII;

typedef vector<string> VS;
typedef vector<VS> VSS;

Matriu::Matriu(int k, VSS documents, bool word) {
    llargada_shingles = k;
    paraules_documents = documents;
    nombre_documents = documents.size();
    word_shingles = word;
   
    construir_kshingles();
    mapeig_per_conjunts();
    mapeig_final();
    construir_matriu_caracteristica();
}

VBB Matriu::get_matriu_caracteristica() {
	return matriu_caracteristica;
}

VII Matriu::get_matriu_signatura() {
	return matriu_signatura;
}

void Matriu::set_matriu_signatura(int t) {
	t_actual = t;
	construir_matriu_signatura(t);
}

double Matriu::calcular_similitud_kshingles(int a, int b){
	int contador_1 = 0;
	int contador_2 = 0;
	for(int i = 0; i < num_k_shingles; ++i){
		if((matriu_caracteristica[i][a] == 1) and ( matriu_caracteristica[i][b] == 1)) ++contador_1;
		if(not((matriu_caracteristica[i][a] == 0) and ( matriu_caracteristica[i][b] == 0))) ++contador_2;
	}
	return double(contador_1)/double(contador_2);
}

double Matriu::calcular_similitud_minihash(int a, int b) {
	double suma = 0.0;

	for (int i = 0; i < t_actual; ++i) {
		if (matriu_signatura[i][a] == matriu_signatura[i][b]) suma += 1.0;
	}

	return suma/double(t_actual);
}

void Matriu::construir_kshingles(){
	//Agafem la Matriu de chars paraules_documents i el transformem en k-shingles.
	
	//PRIMER INICIALITZEM LA Matriu KSHINGLES
	kshingles_resultants = VSS(nombre_documents);
	for (int i = 0; i < nombre_documents; ++i){
		if (word_shingles) {
			string doc = "";
			for (int j = 0; j < int(paraules_documents[i].size()); ++j){
				doc = doc + paraules_documents[i][j] + " ";
			}
			if (int(doc.size()) <= llargada_shingles) {
				kshingles_resultants[i].push_back(doc);
			}
			for (int j = 0; j < int(doc.size())-llargada_shingles; ++j){
				kshingles_resultants[i].push_back(doc.substr(j, llargada_shingles));
			}
		}
		else {
			for (int j = 0; j < int(paraules_documents[i].size()); ++j){
				string paraula;
				paraula = paraules_documents[i][j];
				if (paraula.size()>llargada_shingles){
					//Voldra dir que la podem dividir en kshingles
					string r;
					for(int k = 0; k <= int(paraula.size())-llargada_shingles; ++k){
						r = paraula.substr(k,llargada_shingles);
						kshingles_resultants[i].push_back(r);
					}
				}
				else{
					kshingles_resultants[i].push_back(paraula);
				}
			}
		}
	}
}

void Matriu::mapeig_per_conjunts(){
	//Guardarem al vector de maps, cada document;
	hash<string>funcio_hash;
	
	mapeig_documents = vector<map<string,int> >(nombre_documents);
	//A partir dara cada document sera un map, ja que no ens interessen les paraules en si
	for (int i = 0; i < nombre_documents; ++i){
		for (int j = 0; j < kshingles_resultants[i].size(); ++j){
			mapeig_documents[i][kshingles_resultants[i][j]] = funcio_hash(kshingles_resultants[i][j]);
		}
	}
}

void Matriu::mapeig_final(){
	for (int i = 0; i < nombre_documents; ++i){
		//Entro al document i afegeixo la paraula
		map<string,int>::iterator it;
		for(it=mapeig_documents[i].begin(); it!= mapeig_documents[i].end(); ++it){
			map_general[it->first] = it->second;
		}
	}
	num_k_shingles = int(map_general.size());
}	

void Matriu::construir_matriu_caracteristica(){
	matriu_caracteristica = VBB(num_k_shingles,VB(nombre_documents));
	
	map<string,int>::iterator it;
	int contador = 0;
	for(it = map_general.begin(); it != map_general.end(); ++it){
		for(int j = 0; j < nombre_documents; ++j){
			if(mapeig_documents[j].find(it->first) != mapeig_documents[j].end()){
				matriu_caracteristica[contador][j] = true;
			}
			else{
				matriu_caracteristica[contador][j] = false;
			}
		}
		++contador;
	}
}

void Matriu::construir_matriu_signatura(int t){
	srand (time(NULL));
	VBB matriu_car = get_matriu_caracteristica();

	matriu_signatura = VII(t, VI(nombre_documents, INF));
	
	//Inicialitzem les funcions de hash
	VI funcions_hash(t);
	for (int i = 0; i < t; ++i) {
		funcions_hash[i] = rand()%1000000 + 1;
	}

	//Recorrem la matriu caracteristica per files per a calcular la de signatura
	for (int i = 0; i < num_k_shingles; ++i) {
		//Ara recorrem per columnes
		for (int j = 0; j < nombre_documents; ++j) {
			//Si te un 1 a la posicio, actualitzem la matriu de signatura
			if (matriu_car[i][j]) {
				for (int k = 0; k < t; ++k){
					if (matriu_signatura[k][j] > (funcions_hash[k]*i+1)%num_k_shingles) {
						matriu_signatura[k][j] = (funcions_hash[k]*i+1)%num_k_shingles;
					}
				}
			}
		}
	}
}
