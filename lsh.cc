#include <iostream>
#include <map>
#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include "matriu.h"
#include "lsh.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib> 
#include <ctime> 


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
	string cami = "./documents/";
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
				if (paraula.size()>= 9){
					for (int k = 0; k <= int(paraula.size()) - 9; ++k){
						string r = paraula.substr(k, 9);
						entrada[i].push_back(r);			
					}
				}
				else{
					entrada[i].push_back(paraula);
				}
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
	
	/*vector<vector<string> > entradaa;
	entradaa = vector<vector<string>>(3); //no li he de passar cap parametre mes, sino els inicialitza a buits
	
	entradaa[0].push_back("abcddefghijklm");	
	entradaa[0].push_back("abchijklm");	
	entradaa[0].push_back("abcdefghijklmno");
	entradaa[1].push_back("abcdefghijklmnop");
	entradaa[1].push_back("abcdefghijklmn");
	entradaa[1].push_back("abcdefghijklmnopq");
	entradaa[2].push_back("abcdefghijk");
	entradaa[2].push_back("abcdefghijkl");*/

    read_directory("./documents", v);
	
	/*for(int i = 0; i < entrada.size(); ++i){
		for(int j = 0; j < entrada[i].size(); ++j){
			cout << entrada[i][j]<<" ";
		}
		cout << endl;
	}*/
	
	

	/*llegir_documents();
	cout << "------------------------------------------"<<endl;
	for (int i = 0; i < int(entrada.size()); ++i){
		for (int j = 0; j < int(entrada[i].size()); ++j){
			cout <<entrada[i][j]<<" ";
		}cout <<endl;
		cout << "----------"<<endl;
	}
	
	matriu primera(9,entrada);
	primera.calcular_similitud(1,3);*/
	vector<vector<int> >entrada(100,vector<int>(20));
	for (int i = 0; i < int(entrada.size()); ++i){
		for(int j = 0; j < int(entrada[i].size()); ++j){
			entrada[i][j] = rand()%10;
		}
	}
	
	for (int i = 0; i < int(entrada.size()); ++i){
		for(int j = 0; j < int(entrada[i].size()); ++j){
			cout << entrada[i][j]<<" ";
		}
		cout << endl;
	}
	
	lsh prova(entrada);

}
