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

using namespace std;

typedef std::vector<std::string> stringvec;

vector<string> total;
int contador = 0;
map<string,int> mappeig;
vector <vector <string> > entrada;
stringvec v;


void llegir_documents(){
	cout <<endl;
	vector<string> noms;
	string cami = "./proves/";
	//Hi copiare tots els noms excepte . i ..
	for (int i = 0; i < int(v.size()); ++i){
		if(string(v[i]) != "." and string(v[i])!= ".."){
			noms.push_back(string(v[i]));
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
    read_directory("./proves", v);

	llegir_documents();

	cout << "Aquests son els documents llegits:" << endl;

	for (int i = 0; i < int(v.size()); ++i) {
		if(string(v[i]) != "." and string(v[i])!= ".."){
			cout << v[i] << ' ';
		}
	}
	cout << endl;

	Matriu m(9,entrada,true);
	cout << m.calcular_similitud_kshingles(2,3) << endl;
	m.set_matriu_signatura(10000);
	cout << m.calcular_similitud_minihash(2,3) << endl;
}
