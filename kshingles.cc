#include <iostream>
#include <map>
#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include <string>
#include <functional>
	#include "matriu.h"
using namespace std;

vector<string> total;
int contador = 0;
map<string,int> mappeig;

void llegir_documents(){
	string paraula;
	ifstream infile;
	infile.open("out.txt");
	while(infile >> paraula){
	//cout << paraula << endl;
		if (paraula.size()>= 9){
			for (int i = 0; i <= int(paraula.size()) - 9; ++i){
				string r = paraula.substr(i, 9);
				total.push_back(r); 
				//cout << "->"<<i<<"->"<<8+i;
				//cout << r << endl;			
			}
		}
		else{
			total.push_back(paraula);
		}
	}
	infile.close();
	
	
	infile.open("out1.txt");
	while(infile >> paraula){
	//cout << paraula << endl;
		if (paraula.size()>= 9){
			for (int i = 0; i <= int(paraula.size()) - 9; ++i){
				string r = paraula.substr(i, 9);
				total.push_back(r); 
				//cout << "->"<<i<<"->"<<8+i;
				//cout << r << endl;			
			}
		}
		else{
			total.push_back(paraula);
		}
	}
	
}



int main(){
	
	
	
	//Aquest programa nomes llegira els documents i cridara a una classe matriu que et retornara matriu caracteristica
	
	/*vector<char> v(5);
	v[0]='a';
	v[1]='b';
	v[2]='c';
	v[3]='e';
	string str(v.begin(),v.begin()+2);
	cout << str << endl;*/
	
	
	vector<vector<string> > entrada;
	entrada = vector<vector<string>>(2); //no li he de passar cap parametre mes, sino els inicialitza a buits
	
	entrada[0].push_back("hola");	
	entrada[0].push_back("holaa");
	entrada[1].push_back("holaa");
	entrada[1].push_back("holaaaaaaaaaa");
	
	
	/*for(int i = 0; i < entrada.size(); ++i){
		for(int j = 0; j < entrada[i].size(); ++j){
			cout << entrada[i][j]<<" ";
		}
		cout << endl;
	}*/
	
	matriu primera(9,entrada);

	//llegir_documents();

}
