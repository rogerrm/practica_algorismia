#include "matriu.h"
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 1e6

void matriu::construir_kshingles(){
	//Agafem la matriu de chars paraules_documents i el transformem en k-shingles.
	
	//PRIMER INICIALITZEM LA MATRIU KSHINGLES
	kshingles_resultants = vector<vector<string> >(nombre_documents);
	for (int i = 0; i < nombre_documents; ++i){
		string doc = "";
		for (int j = 0; j < int(paraules_documents[i].size()); ++j){
			doc = doc + paraules_documents[i][j] + " ";
		}
		if (word_shingles) {
			if (int(doc.size()) <= num_shingles) {
				kshingles_resultants[i].push_back(doc);
			}
			for (int j = 0; j < int(doc.size())-num_shingles; ++j){
				kshingles_resultants[i].push_back(doc.substr(j, num_shingles));
			}
		}
		else {
			for (int j = 0; j < int(paraules_documents[i].size()); ++j){
				string paraula;
				paraula = paraules_documents[i][j];
				if (paraula.size()>num_shingles){
					//Voldra dir que la podem dividir en kshingles
					string r;
					for(int k = 0; k <= int(paraula.size())-num_shingles; ++k){
						r = paraula.substr(k,num_shingles);
						kshingles_resultants[i].push_back(r);
					}
				}
				else{
						kshingles_resultants[i].push_back(paraula);
					}
			}
		}
	}
	//ESCRIVIM LA MATRIU DE NOU
	/*for (int i = 0; i < nombre_documents; ++i){
		for(int j = 0; j < int(paraules_documents[i].size()); ++j){
			cout <<paraules_documents[i][j]<<" ";
		}
		cout << endl;
	}*/
	 
	 
	 
	//ESCRIVIM ELS KSHINGLES
	for(int i = 0; i < kshingles_resultants.size(); ++i){
		for(int j = 0; j < kshingles_resultants[i].size(); ++j){
		}
	}
}

void matriu::mapeig_per_conjunts(){
	//guardarem al vector de maps, cada document;
	hash<string>funcio_hash;
	
	mapeig_documents = vector<map<string,int> >(nombre_documents);
	//A partir dara cada document sera un map, ja que no ens interessen les paraules en si
	for (int i = 0; i < nombre_documents; ++i){
		for (int j = 0; j < kshingles_resultants[i].size(); ++j){
			mapeig_documents[i][kshingles_resultants[i][j]] = funcio_hash(kshingles_resultants[i][j]);
		}
	}
	for (int i = 0; i < int(mapeig_documents.size()); ++i){
		map<string,int>::iterator it;
		//cout << "El document "<<i<<"s'ha mapejat a"<<endl;
		for(it = mapeig_documents[i].begin(); it != mapeig_documents[i].end(); ++it){
			//cout << it->first<<"->"<<it->second<<" ";
		}
		cout << endl;
	}
	//JA TENIM ELS DOCUMENTS MAPEJATS. Kshingles repetits els hem anul·lat
	
	
	
}

void matriu::mapeig_final(){
	
	
	for (int i = 0; i < nombre_documents; ++i){
		//Entro al document i afegeixo la paraula
		map<string,int>::iterator it;
		for(it=mapeig_documents[i].begin(); it!= mapeig_documents[i].end(); ++it){
			map_general[it->first] = it->second;
		}
	}
	cout << endl;
	int contador = map_general.size(); //Contador hi haura el nombre total de kshingles
	map<string,int>::iterator it;
	for(it=map_general.begin(); it!= map_general.end(); ++it){
		map_general[it->first] = it->second;
		//cout <<it->first << "->"<< map_general[it->first]<<endl;
	}
	//cout << contador << "<-contadora"<<endl;
	
}	

vector<vector<bool> > matriu::matriu_caracterisica(){
	num_k_shingles = int(map_general.size());
	matriu_a_retornar = vector<vector<bool> >(num_k_shingles,vector<bool>(nombre_documents));
	//cout <<"1r" <<num_k_shingles << endl;
	//cout << nombre_documents<<endl;
	//cout << "mapeig-doc-size->"<<mapeig_documents.size()<<endl;
	
	map<string,int>::iterator it;
	int contador = 0;
	for(it = map_general.begin(); it != map_general.end(); ++it){
		for(int j = 0; j < nombre_documents; ++j){
			if(mapeig_documents[j].find(it->first) != mapeig_documents[j].end()){
				matriu_a_retornar[contador][j] = true;
				//cout << it->first <<endl;
			}
			else{
				matriu_a_retornar[contador][j] = false;
			}
		}
		
		++contador;
	
	}
	
	//cout << "UOI"<<endl;
	for(int i = 0; i < num_k_shingles; ++i){
		for(int j = 0; j < nombre_documents; ++j){
			cout << matriu_a_retornar[i][j]<<" ";
		}
		cout << endl;
	}
	return matriu_a_retornar;
}

vector<vector<int> > matriu::minihash_signature(int t){
	srand (time(NULL));
	vector<vector<bool> > matriu_car = matriu_caracterisica();

	vector<vector<int> > sig = vector<vector<int> >(t, vector<int>(nombre_documents, INF));
	
	//Inicialitzem les funcions de hash
	vector<int> funcions_hash(t);
	for (int i = 0; i < t; ++i) {
		funcions_hash[i] = rand()%num_k_shingles + 1;
	}

	//Recorrem la matriu de signatura per files per a calcular-la
	for (int i = 0; i < num_k_shingles; ++i) {
		//Ara recorrem per columnes
		for (int j = 0; j < nombre_documents; ++j) {
			//Si te un 1 a la posicio, actualitzem la matriu de signatura
			if (matriu_car[i][j]) {
				for (int k = 0; k < t; ++k){
					if (sig[k][j] > (funcions_hash[k]*i+1)%num_k_shingles) {
						sig[k][j] = (funcions_hash[k]*i+1)%num_k_shingles;
					}
				}
			}
		}
	}

	for (int i = 0; i < t; ++i) {
		for (int j = 0; j < nombre_documents; ++j) {
			cout << sig[i][j] << " ";
		}
		cout << endl;
	}

	return sig;
}

int matriu::calcular_similitud(int a, int b){
	int contador_1 = 0;
	int contador_2 = 0;
	for(int i= 0; i < num_k_shingles; ++i){
		if((matriu_a_retornar[i][a] == 1) and ( matriu_a_retornar[i][b] == 1)) ++contador_1;
		if(not((matriu_a_retornar[i][a] == 0) and ( matriu_a_retornar[i][b] == 0))) ++contador_2;
	}
	cout << double(contador_1) / double(contador_2)<<endl;
	return double(contador_1) / double(contador_2);
}

matriu::matriu(int k, vector<vector<string> > documents, bool word) {
    num_shingles = k;
    //cout << "PRINCIPI"<<endl;
    paraules_documents = documents;
    nombre_documents = documents.size();
    word_shingles = word;
   
	
    construir_kshingles();
    mapeig_per_conjunts();
    mapeig_final();
    matriu_caracterisica();
    //calcular_similitud(0,1);
    /*hashShingles();
    generateUniversal();    
    computeCM();*/

}
