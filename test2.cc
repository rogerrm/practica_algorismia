#include <iostream>
#include <map>
#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include "Matriu.h"
#include "lsh.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef std::vector<std::string> stringvec;

vector<string> total;
int contador = 0;
map<string,int> doc_to_int;
vector <vector <string> > entrada;
vector<string> noms;
stringvec v;
int numdocs = 0;

void llegir_documents(){
	string cami = "./dades_permutacions/";
	//Hi copiare tots els noms excepte . i ..
	for (int i = 0; i < int(v.size()); ++i){
		if(v[i][0] != '.'){
			noms.push_back(string(v[i]));
			doc_to_int[v[i]] = numdocs;
			numdocs++;
		}
	}
	entrada = vector<vector<string> >(int(noms.size()));
	for (int i = 0; i < int(noms.size()); ++i){
		string paraula;
		ifstream infile;
		string converter;
		converter = cami + noms[i];
		infile.open(converter);
		while(infile >> paraula){
			entrada[i].push_back(paraula);
		}
		infile.close();
	}
}

void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}

int main(){
	//Comencem amb les proves amb dades generades aleatoriament
    read_directory("./dades_permutacions", v);

	llegir_documents();

	cout << "Aquests son els documents llegits:" << endl;

	for (int i = 0; i < int(v.size()); ++i) {
		if(v[i][0] != '.'){
			cout << v[i] << ' ';
		}
	}
	cout << endl;

	vector<float> temps_k = vector<float>(11);

	for (int k = 1; k < 12; ++k) {
		Matriu m(k,entrada);

		clock_t start = clock();
		for (int i = 0; i < 10000; ++i) {
			int a = rand()%numdocs;
			int b = rand()%numdocs;
			m.calcular_similitud_kshingles(a,b);
		}
		temps_k[k-1] = float(clock()-start)/float(CLOCKS_PER_SEC);
	}

	for (int i = 0; i < 11; ++i) cout << temps_k[i] << ' ';
	cout << endl;

	//Amb aixo, veiem que conforme augmenta la k augmenta tambe el temps de calcular similituds.
	//Hem vist que amb k = 5, fer 10000 comparacions triga 0.533707 segons.
	//Ara, ens desem la matriu m amb k = 5 i experimentem amb t

	Matriu m(5,entrada);
	for (int t = 1; t < 1e6; t*=10) {
		m.set_matriu_signatura(t);
		clock_t start = clock();		
		for (int i = 0; i < 10000; ++i) {
			int a = rand()%numdocs;
			int b = rand()%numdocs;
			m.calcular_similitud_minihash(a, b);
		}
		cout << t << ": " << float(clock()-start)/float(CLOCKS_PER_SEC) << endl;
	}

	//D'aquesta manera veiem que conforme augmenta la t, tambe augmenta el temps de calcular similituds.
	//De totes formes, aquest no supera el d'utilitzar k-shingles fins que t no es 10000.
}
