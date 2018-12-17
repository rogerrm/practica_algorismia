#include <vector>
#include <iostream>
#include <vector>

using namespace std;

class lsh{

	public:
		lsh(vector<vector<int> > matriu_signatures, double semblanca, int bandes);
	
	private:
		double similitud;
		int bandes; //nombre de bandes
		int n; //nombre de files per banda
		int tamany_signatures;
		int nombre_documents;
		vector<pair<int,int> > candidats; //Hi guardare els candidats a la similitud buscada
		vector<vector<int> > matriu_signatures;
		vector<vector<int> > resultats_hash;

		//Necessitem funcio que retorni els parells similars en funcio d'un parametre i la seva similitud real
		void similars();
		double similitud_jaccard(int a, int b);
};
