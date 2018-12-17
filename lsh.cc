#include "lsh.h"
#include <vector>
#include <functional>

lsh::lsh(vector <vector <int> > matriu_signatures, double semblanca, int bandes){
	this->matriu_signatures = matriu_signatures;
	this->tamany_signatures = int(matriu_signatures.size());
	this->nombre_documents = int(matriu_signatures[0].size());
	this->similitud = semblanca;
	this->bandes = bandes;
	this->n = tamany_signatures / bandes;
	
	similars();
}

void lsh::similars(){
	//Busquem tots els que tinguin similitud >= parametre
	hash<int> hash_columna;
	resultats_hash = vector<vector<int> >(n*bandes,vector<int>(nombre_documents)); 
	
	for (int i = 0; i < bandes; ++i){
		vector<pair<int,int> >total(0);
		//HI GUARDEM ELS VALORS DE HASH
		for (int j = 0; j < nombre_documents; ++j){
			//hem de posar la columna a un int
			long long int suma = 0;
			int producte = 1;
			for (int k = 0; k < n; ++k){
				suma += producte * matriu_signatures[n*i + k][j];
				producte *= 10;
			}
			resultats_hash[i][j] = hash_columna(suma);
			total.push_back(make_pair(hash_columna(suma),j));
		}
		
		//HEM DE MIRAR SI 2 HAN ANAT AL MATEIX LLOC, EN CAS QUE SI ELS AFEGIM A CANDIDATS
		sort(total.begin(),total.end());
		for (int i = 1; i < int(total.size()); ++i){
			if(total[i].first == total[i-1].first){
				candidats.push_back(make_pair(total[i-1].second,total[i].second));
			}
		}
	}
	//Ara volem saber si realment els candidats que tenim tenen la similitud esperada o no
	vector<pair<int,int> >definitius;
	for (int i = 0; i < int(candidats.size()); ++i){
		pair<int,int> primer = candidats[i];
		if(similitud_jaccard(primer.first, primer.second)>= similitud){
			definitius.push_back(make_pair(primer.first, primer.second));
		}
	}
	cout << "Els parells que tenen similitud de Jaccard >="<<similitud<<" son:"<<endl;
	for (int i = 0; i < int(definitius.size()); ++i){
		cout<<definitius[i].first<<","<<definitius[i].second<<endl;
	}
}

double lsh::similitud_jaccard(int a, int b){
	double contador = 0;
	for (int i = 0; i < tamany_signatures; ++i){
		if(matriu_signatures[i][a] ==  matriu_signatures[i][b]) ++contador;
	}
	return (double(contador)/double(tamany_signatures));
}
