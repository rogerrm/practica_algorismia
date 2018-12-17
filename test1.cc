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
	string cami = "./20newsgroup/";
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
	//Comencem amb les proves amb 20newsgroup
    read_directory("./20newsgroup", v);

	llegir_documents();

	cout << "Aquests son els documents llegits:" << endl;

	for (int i = 0; i < int(v.size()); ++i) {
		if(v[i][0] != '.'){
			cout << v[i] << ' ';
		}
	}
	cout << endl;

	for (int k = 1; k < 12; ++k) {
		Matriu m(k,entrada);

		for (int i = 0; i < numdocs; ++i) {
			for (int j = i; j < numdocs; ++j) {
				double sim = m.calcular_similitud_kshingles(i, j);
				if (i != j and sim > 0.1) {
					cout << sim << ' ' << noms[i] << ' ' << noms[j] << endl;
				}
			}
		}

		cout << "------------------------------ " << k << endl;
	}

	//Amb aixo, veiem que la millor k es 5.
	//Per tant, ens desem la matriu m amb k = 5. Ara, experimentem amb t

	Matriu m(5,entrada);
	for (int t = 1; t < 1e6; t*=10) {
		m.set_matriu_signatura(t);
		double dif = 0.0;
		for (int i = 0; i < 50; ++i) {
			int a = rand()%numdocs;
			int b = rand()%numdocs;

			if (m.calcular_similitud_kshingles(a, b) > m.calcular_similitud_minihash(a, b))
				dif += m.calcular_similitud_kshingles(a, b) - m.calcular_similitud_minihash(a, b);
			else
				dif += m.calcular_similitud_minihash(a, b) - m.calcular_similitud_kshingles(a, b);
		}

		dif = dif/50.0;
		cout << t << ' ' << dif << endl;
	}

	//D'aquesta manera veiem que conforme augmenta la t, la diferencia disminueix.
	//A mes, veiem tambe com la diferencia es molt petita

	//Per ultim, utilitzem lsh per a trobar els dos documents mes semblants
	//Primer, comprovem que aixo triga molta estona
	lsh l(m.get_matriu_signatura(), 0.2, 100000);
	//En canvi, reduint a 20000, reduim molt el temps d'execucio i obtenim resultats semblants
	lsh l(m.get_matriu_signatura(), 0.2, 20000);
}
