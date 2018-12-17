#include <map>
#include <vector>
#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <vector>
#include <map>

using namespace std;

typedef vector<bool> VB;
typedef vector<vector<bool> > VBB;

typedef vector<int> VI;
typedef vector<VI> VII;

typedef vector<string> VS;
typedef vector<vector<string> > VSS ;

class Matriu{
	
	public:		
		//CONSTRUCTORA
		Matriu(int k, VSS docs);

		//GETTERS
		VBB get_matriu_caracteristica();
		VII get_matriu_signatura();

		//SETTERS
		void set_matriu_signatura(int t);

		//Calcular similituds
		double calcular_similitud_kshingles(int a, int b);
		double calcular_similitud_minihash(int a, int b);
		
		
	private:
		int nombre_documents; //Nombre de documents del corpus
		int llargada_shingles; //Llargada dels shingles
		int num_k_shingles; //Nombre total de shingles que hem trobat al corpus
		int t_actual; //t de la signatura que hi ha actualment a memoria
		
		//Tot el que ens hem de guardar per implementar la classe es
		
		vector<map<string,int> > mapeig_documents; //Hi guardarem el mapeig kshingle -> enter per a cada document
		map<string,int> map_general; //Hi guardarem el map k-shingle -> enter
		VSS paraules_documents; //Servirà per passar la informacio a la classe amb totes les paraules dels documents
		vector<vector<string> > kshingles_resultants; //Servira per guardar els kshingles que es crein
		VBB matriu_caracteristica; //Matriu caracteristica dels k-shingles
		VII matriu_signatura; //Matriu de signatura minihash

		void construir_kshingles();
		void mapeig_per_conjunts();
		void mapeig_final();
		void construir_matriu_caracteristica();
		void construir_matriu_signatura(int t);

};
