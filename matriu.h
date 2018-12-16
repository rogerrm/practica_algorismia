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

class matriu{
	
	public:
		int nombre_documents;
		int num_shingles;
		int num_k_shingles; //ES EL NOMBRE TOTAL DE KSHINGLES QUE HEM TROBAT
		bool word_shingles;
		
		//Tot el que ens hem de guardar per implementar la classe es
		
		vector<map<string,int> > mapeig_documents; //Hi guardarem mappeig de cada document
		map<string,int> map_general; //Hi guardarem el map general per saber nombre k-shingles
		VSS paraules_documents; //Servirà per passar la informacio a la classe amb totes les paraules dels documents
		vector<vector<string> > kshingles_resultants; //Servira per guardar els kshingles que es crein
		VBB matriu_a_retornar;
		//FUNCIONS
		
		//CONSTRUCTORA
		matriu(int k, VSS docs, bool word);
		//RECOLLIR LA MATRIU CARACTERÍSTICA
		VBB matriu_caracterisica();
		VII minihash_signature(int t);
		int calcular_similitud(int a, int b);
		
		
	private:
		void construir_kshingles(); //FUNCIONA
		void mapeig_per_conjunts();
		void mapeig_final();
		/*mappejar_kshingles();
		construir_matriu();*/
	
};
