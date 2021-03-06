//============================================================================
// Name         : CoeurCommunaute.cpp
// Author       : Tennessy Kolubako
// Modifications: Anthony Perez, Nicolas Dugué
// Version      :
// Copyright    : Your copyright notice
//============================================================================

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "Digraph.hpp"
#include "EdgeWeight.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	if ( argc >= 4 ) {

		string graphPath = argv[1];
		string pathProg = argv[0];
		string path = pathProg.substr(0, pathProg.find_last_of("/"));

		if(path.at(path.length()-1) == '/') {

			path = path.substr(2, path.length()-10);

		}

		else {

			path = path.substr(2, path.length()-9);

		}

		string graphName = graphPath.substr(graphPath.find_last_of("/")+1, graphPath.length());

		cout << "Graph : " << graphName << endl;

		if(graphName.length() == 0) {

			graphName = graphPath;

		}

		unsigned int nbLouvain = atoi(argv[2]);
		unsigned int seuil_min = atoi(argv[4]);

		//Vectors of alpha to construct
		vector<unsigned int> alphas;
		for (unsigned int i= seuil_min; i < 10; i ++) {
			alphas.push_back(i);
		}
		for (unsigned int i= 92; i < 99; i+=2) {
			alphas.push_back(i);
		} 
		alphas.push_back(99);


				
		bool weighted=false;
		string w = "weighted";
		if (argc >= 6) {
			if (w.compare(argv[5])==0) {
				cout << "Weighted" << endl;
				weighted=true;
			}
		}
		double seuil = nbLouvain * (seuil_min / (10.0));

		cout << "Seuil : " << seuil << endl;

		//Digraph l = Digraph();
		//l.loadEdgeList(graphPath, false);

		//unsigned int nbSommets = l.getDim();

		//cout << nbSommets << " sommets."<< endl;

		vector < unordered_map<unsigned long int,unsigned int> > cooccur;
		vector< vector<unsigned long int> > comm;

		// Conversion et generation des communautes une fois par type de triangle
		cout << "Converting to binary " << endl;
		
		if (weighted) {
			system(("./" + path + "dependencies/louvain/convert -i " + graphPath + " -o " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.bin -w " + path + "RUN/" + argv[3] + "/Louvain/graph.weights").c_str());
		}
		else {
			system(("./" + path + "dependencies/louvain/convert -i " + graphPath + " -o " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.bin").c_str());
		}

		unsigned int nbSommets;
		for ( int k = 1; k <= nbLouvain; k++ ) {
			cout << "Louvain run " << k << endl;
			stringstream fileName;
			fileName << "RUN/" << argv[3] << "" << "/Louvain/graph" << k;

			comm = vector< vector<unsigned long int> >();

			// TODO : un .tree par itération du Louvain ?
			if (weighted) {
				cout << "Modularity : " << endl;
				system(("./" + path + "dependencies/louvain/community -l -1 "+path+"RUN/" + argv[3] + "" + "/Louvain/graph.bin -w " + path + "RUN/" + argv[3] + "/Louvain/graph.weights > " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.tree").c_str());
			}
			else {
				cout << "Modularity : " << endl;
				system(("./" + path + "dependencies/louvain/community -l -1 "+path+"RUN/" + argv[3] + "" + "/Louvain/graph.bin > " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.tree").c_str());
			}
			//system(("./" + path + "dependencies/louvain/community -l -1 "+path+"RUN/" + argv[3] + "" + "/Louvain/graph.bin > " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.tree").c_str());
			system(("./" + path + "dependencies/louvain/hierarchy -l 0 " + path + "RUN/" + argv[3] + "" + "/Louvain/graph.tree > " + path +fileName.str()).c_str());

			// On parcourt le fichier des communautés (dernier niveau de la hiérarchie)
			FILE* file = fopen((path + fileName.str()).c_str(), "r");
			long source, target, tmp;
			int scanfReturn;

			// On charge les communautés dans un vecteur
			//cout << "reading graph from : " << (path + fileName.str()).c_str() << endl;

			//cout << "updating map..." << endl;

			unordered_map<unsigned long int,unsigned int>::iterator it;
			nbSommets=0;

			while ( (scanfReturn = fscanf(file,"%ld %ld", &source, &target)) != EOF ) {

				if ( scanfReturn == 2 ){

					while( target >= comm.size() ) {

						comm.push_back(vector<unsigned int long>());

					}

					comm[target].push_back(source);
				}
				nbSommets+=1;

			}
			cooccur.resize(nbSommets);

			fclose(file);

			for( unsigned long int i = 0; i < comm.size(); i++ ) {

				for( unsigned long int j = 0; j < comm[i].size(); j++ ) {

					for( unsigned long int l = j+1; l < comm[i].size(); l++ ) {

						unsigned long int s = min(comm[i][j], comm[i][l]);
						unsigned long int d = max(comm[i][j], comm[i][l]);

						it = cooccur[s].find(d);

						// Ajout dans la map uniquement si on a une chance de depasser le seuil
                        if(it == cooccur[s].end()) { 

							if ((nbLouvain - k) >= seuil) 
		                                     
								cooccur[s].insert(make_pair(d, 1));
								
                        }
	
                        // Sinon, on verifie que la mise a jour est utile
                        else {

                       		unsigned int nbOccur = cooccur[s][d];

                            // Si le nombre d'iterations restant + le nombre de cooccur est >= a ce qu'on veut obtenir
                            if(((nbLouvain - k) + nbOccur) >= seuil) 
                            
                            	cooccur[s][d]++;

                            // Sinon suppression de la map
                            else 
                            
                            	cooccur[s].erase(it);

    					}
    					
					}

				}
			
				comm[i].erase(comm[i].begin(), comm[i].end());

			}
				
			comm.erase(comm.begin(), comm.end());

		}

		cout << "maps created. " << endl;
		cout << "computing cooccurrence file" << endl;

		ofstream hugeGraph;
		hugeGraph.open((path + "CooccurOLD_"+graphName).c_str(), ios::out);

		unordered_map<unsigned long int,unsigned int>::iterator it;

		for( unsigned int i = 0; i < nbSommets; i++) {

			for( it = cooccur[i].begin(); it != cooccur[i].end(); it++)  {

				hugeGraph << i << " " << (*it).first << " " << (*it).second << endl;

			}

		}

		hugeGraph.close();

		long source, target;
		unsigned int nbOccur;
		int scanfReturn;

		// Graphe des cooccurrences avec le alpha
		int weight = 1;

		cout << "computing alpha files" << endl;
		ifstream inFile(path + "CooccurOLD_"+graphName);

		vector<ofstream> files;
		unsigned int tmp_alpha;
		stringstream ss;
		string str;
		for(std::vector<unsigned int>::iterator i=alphas.begin();i!=alphas.end();i++) {
			ofstream out;
			tmp_alpha=*i;
			str = to_string(tmp_alpha);
			out.open(path + "RUN/" + argv[3] + "/"+ str +"/CooccurOLD_" + graphName);
			files.push_back(std::move(out));
		}

		unsigned cpt=0;
		while ( inFile >> source >> target >> nbOccur ) {

			cpt=0;
			for(std::vector<unsigned int>::iterator i=alphas.begin();i!=alphas.end();i++) {
				tmp_alpha=*i;
				
				if (tmp_alpha < 10) {
					seuil = tmp_alpha/ 10.0;	
				}
				else {
					seuil = tmp_alpha/ 100.0;
				}
				
				if( (double) (((double)nbOccur) / nbLouvain >= (seuil)) ) {
					files[cpt] << source << " " << target << endl;

				}
				else {
					break;
				}
				cpt++;
				
			}
			
		}
		cout << "Alpha files written" << endl;

		for(unsigned int i = 0;i < files.size();i++) {
			files[i].close();
		}
		cout << "Files closed" << endl;

		inFile.close();
		

		//cout << "Writing WeightedEdges/unweightedEdges done" << endl;
		unsigned int i;
		for (std::vector<unsigned int>::iterator j=alphas.begin();j!=alphas.end();j++) {
			i=*j;
			Digraph d = Digraph();
			d.loadEdgeList(path + "RUN/" + argv[3] + "" + "/" + to_string(i) + "/CooccurOLD_" + graphName, false);
			//cout << "graph loaded" << endl;

			//cout << "relabeling..." << endl;

			ofstream relabelFile2(path + "relabel2", ios::out);
			vector<long int> relab2 = d.relabel();

			for( long int i = 0; i < relab2.size(); i++ ) {

				if(relab2[i] != -1) {

					relabelFile2 << i << " " << relab2[i] << endl;

				}

			}

			relabelFile2.close();
			//cout << "done." << endl;
			//cout << "creating relabeled communities" << endl;

			ofstream unweightedRelabeledGraph(path + "RUN/" + argv[3] + "" + "/" + to_string(i) + "/CooccurOLD_" + graphName +"_relabeled", ios::out);
			ifstream inFile(path + "CooccurOLD_"+graphName);

			while ( inFile >> source >> target >> weight ) {

				// INUTILE : il suffit de reparcourir le CooccurOLD_ qui est dans le dossier alpha
				if ( (double) (((double)weight) / nbLouvain >= (i/10.0)) ) {

					unweightedRelabeledGraph << relab2[source] << " " << relab2[target] << endl;

				}

			}

			inFile.close();
			unweightedRelabeledGraph.close();

			//cout << "done" << endl;

			// Correspondance inverse entre CooccurOLDrence alpha et CooccurOLDrence classique
			/*vector<long int> labelBase = vector<long int>(d.getDim(), -1);
			
			for( unsigned long int i = 0; i < relab2.size(); i++) { 

				if( relab2[i] >= 0 )

					labelBase[relab2[i]] = i;

			}*/
	
			vector<long int> labelBase = vector<long int>(relab2.size(),-1);

			for( unsigned long int i=0; i < labelBase.size(); i++ ) {

				if ( relab2[i]>=0 ) {

					// ME SEMBLE IMPOSSIBLE
					if ( labelBase[relab2[i]] >= labelBase.size() ) {

						labelBase.reserve(relab2[i]+1);

					}

					labelBase[relab2[i]] = i;

				}

			}

			d.genDegcum();
			cout << "Graph created" << endl;

			vector< vector<int> > communities = d.getConnectedNode();
			ofstream comFile(path + "RUN/" + argv[3] + "" + "/" + to_string(i) + "/Communities_" + graphName, ios::out);

			for ( unsigned int i = 0; i < communities.size(); i++ ) {

				for ( unsigned int j = 0; j < communities[i].size(); j++ ) {

					comFile << labelBase[communities[i].at(j)];

					if ( j < communities[i].size()-1 ) {

						comFile  << ",";

					}

				}

				comFile << endl;

			}

			comFile.close();
			cout << "writing communities done" << endl;

		}

	}

	else {

		cout << "Usage : " << endl << "CoeurCommunaute graph nbLouvain graph_court" << endl;

	}

	return 0;
}
