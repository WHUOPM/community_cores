//============================================================================
// Name         : CoeurCommunaute.cpp
// Author       : Tennessy Kolubako
// Modification : Anthony Perez
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

	if ( argc > 4 ) {

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

		if(graphName.length() == 0) {

			graphName = graphPath;

		}

		int nbLouvain = atoi(argv[2]);
		string dossier = argv[3];
		string typeTriangle = argv[4];

		// Calcul des triangles sur le graphe initial
		cout << "computing triangles..." << endl;

		system(("./" + path + "dependencies/TriangleCC/Release/TriangleCC " + graphPath + " " + path + "/relabInit " + typeTriangle + " > " + path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Cooccur-Triangle-" + graphName).c_str());
		cout << "TriangleCC done " << endl;

		// On deplace le fichier des triangles
		system(("mv " + path + "Triangles-" + graphName + " TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/").c_str());
		cout << "creating graph from edge list :" <<  "Cooccur-Triangle-" << graphName << endl;
		// Graphe d'origine -RENUMEROTE
		Digraph *graphOri = new Digraph();

		// On ouvre le graphe des triangles

		graphOri->loadEdgeList(path + graphPath, true);
		int nbSommetsOri = graphOri->getDim();

		cout << nbSommetsOri << endl;

		Digraph *graphDep = new Digraph();
		graphDep->loadEdgeList(path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Cooccur-Triangle-" + graphName, true);
		if(graphDep->getEdgeList().empty()){
			cout << "Empty" << endl;
			delete graphDep;
			return 0;
		}

		cout << "graph created" << endl;
		// On est obligé de renuméroter les co-occurrences (tout le monde n'y est pas forcément)
		// Correspondance
		ofstream relabelFile1(path + "relabel1", ios::out);
		vector<long int> relab1 = graphDep->relabel();
		for(unsigned long int i=0; i<relab1.size(); i++){
			if(relab1[i] != -1){
				relabelFile1 << i << " " << relab1[i] << endl;
			}
		}
		relabelFile1.close();

		// Relabel du graphe de cooccurence des triangles
		ofstream relabelGraphT(path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Cooccur-Triangle-" + graphName + "-renum");
		vector<EdgeWeight> edge = graphDep->getEdgeList(); 

		for(int i=0; i<edge.size(); i++){
			relabelGraphT << edge[i].getSource() << " " << edge[i].getTarget() << " " << edge[i].getWeight() << endl;
		}
		relabelGraphT.close();
		delete graphDep;

        	// TODO: renumeroter en utilisant Louvain, et donc ne plus avoir ce truc la...
        	// Renumerotation du graphe
		Digraph l = Digraph();
		l.loadEdgeList(path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Cooccur-Triangle-" + graphName + "-renum", false);

		unsigned int nbSommets = l.getDim();

		cout << nbSommets << endl;

		vector < unordered_map<unsigned long int,unsigned int> > cooccur(nbSommets);
		vector< vector<unsigned long int> > comm;

		// Conversion et generation des communautes une fois par type de triangle
		cout << "Converting" << endl;
		system(("./" + path + "dependencies/louvain/convert -i " + path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Cooccur-Triangle-" + graphName + "-renum" + " -o " + path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" +  "Louvain/triangles.bin -w " + path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Louvain/triangles.weight").c_str());

		for ( int k = 0; k < nbLouvain; k++ ) {

			stringstream fileName;
			fileName << "TRIANGLE-RUN/" << dossier << "/TYPE" << typeTriangle << "/" << "Louvain/triangles" << k;

			comm = vector< vector<unsigned long int> >();

			// TODO : un .tree par itération du Louvain ?
			system(("./" + path + "dependencies/louvain/community -l -1 "+path+"TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Louvain/triangles.bin -w " +path+"TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Louvain/triangles.weight >" + path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Louvain/triangles.tree").c_str());
			system(("./" + path + "dependencies/louvain/hierarchy -l 0 " + path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Louvain/triangles.tree > " + path +fileName.str()).c_str());

			// On parcourt le fichier des communautés (dernier niveau de la hiérarchie)
			FILE* file = fopen((path + fileName.str()).c_str(), "r");
			long source, target, tmp;
			int scanfReturn;

			// On charge les communautés dans un vecteur
			cout << "reading graph from : " << (path + fileName.str()).c_str() << endl;

			while ( (scanfReturn = fscanf(file,"%ld %ld", &source, &target)) != EOF ) {

				if ( scanfReturn == 2 ){

					while( target >= comm.size() ) {

						comm.push_back(vector<unsigned int long>());

					}

					comm[target].push_back(source);

				}

			}

			fclose(file);

			cout << "updating map..." << endl;

			unordered_map<unsigned long int,unsigned int>::iterator it;

			for( unsigned long int i = 0; i < comm.size(); i++ ) {

				for( unsigned long int j = 0; j < comm[i].size(); j++ ) {

					for( unsigned long int l = j+1; l < comm[i].size(); l++ ) {

						unsigned long int s = min(comm[i][j], comm[i][l]);
						unsigned long int d = max(comm[i][j], comm[i][l]);

						it = cooccur[s].find(d);

						if(it == cooccur[s].end()) {

							cooccur[s].insert(make_pair(d, 1));

						}

						else {

							cooccur[s][d]++;

						}

					}

				}

			}

		}

		cout << "maps created. " << endl;
		cout << "computing cooccurrence file" << endl;

		ofstream hugeGraph;
		hugeGraph.open((path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Cooccur-"+graphName).c_str(), ios::out);

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
		ifstream inFile(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "Cooccur-"+graphName);

		ofstream file1(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "1/Cooccur-" + graphName, ios::out);
		ofstream file2(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "2/Cooccur-" + graphName, ios::out);
		ofstream file3(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "3/Cooccur-" + graphName, ios::out);
		ofstream file4(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "4/Cooccur-" + graphName, ios::out);
		ofstream file5(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "5/Cooccur-" + graphName, ios::out);
		ofstream file6(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "6/Cooccur-" + graphName, ios::out);
		ofstream file7(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "7/Cooccur-" + graphName, ios::out);
		ofstream file8(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "8/Cooccur-" + graphName, ios::out);
		ofstream file9(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + "9/Cooccur-" + graphName, ios::out);

		while ( inFile >> source >> target >> nbOccur ) {
			if( (double) (((double)nbOccur) / nbLouvain >= (0.1)) ) {

				file1 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.2)) ) {

				file2 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.3)) ) {

				file3 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.4)) ) {

				file4 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.5)) ) {

				file5 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.6)) ) {

				file6 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.7)) ) {

				file7 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.8)) ) {

				file8 << source << " " << target << endl;

			}
			if( (double) (((double)nbOccur) / nbLouvain >= (0.9))) {

				file9 << source << " " << target << endl;

			}

		}

		file1.close();
		file2.close();
		file3.close();
		file4.close();
		file5.close();
		file6.close();
		file7.close();
		file8.close();
		file9.close();

		inFile.close();

		cout << "Writing WeightedEdges/unweightedEdges done" << endl;

		for ( unsigned int i = 1; i < 10; i++ ) {

			Digraph d = Digraph();
			d.loadEdgeList(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" +  to_string(i) + "/Cooccur-" + graphName, false);
			cout << "graph loaded" << endl;

			cout << "relabeling..." << endl;

			ofstream relabelFile2(path + "relabel2", ios::out);
			vector<long int> relab2 = d.relabel();

			for( long int i = 0; i < relab2.size(); i++ ) {

				if(relab2[i] != -1) {

					relabelFile2 << i << " " << relab2[i] << endl;

				}

			}

			relabelFile2.close();
			cout << "done." << endl;

			/* ===== DEBUT DU CODE NON EXECUTE ===== */
			/*cout << "creating relabeled communities" << endl;

			ofstream unweightedRelabeledGraph(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + to_string(i) + "/Cooccur_" + graphName +"_relabeled", ios::out);
			ifstream inFile(path + "Cooccur_"+graphName);

			long source, target;
                	unsigned int weight;
			while ( inFile >> source >> target >> weight ) {

				// INUTILE : il suffit de reparcourir le Cooccur_ qui est dans le dossier alpha
				if ( (double) (((double)weight) / nbLouvain >= (i/10.0)) ) {

					unweightedRelabeledGraph << relab2[source] << " " << relab2[target] << endl;

				}

			}

			inFile.close();
			unweightedRelabeledGraph.close();

			cout << "done" << endl;*/
			/* ===== FIN DU CODE NON EXECUTE ===== */

			// Correspondance inverse entre Cooccurrence alpha et Cooccurrence classique
			vector<long int> labelBase = vector<long int>(d.getDim(), -1);
			
			for( unsigned long int i = 0; i < relab2.size(); i++) { 

				if( relab2[i] >= 0 )

					labelBase[relab2[i]] = i;

			}
	
			//vector<long int> labelBase = vector<long int>(relab2.size(),-1);

			//for( unsigned long int i=0; i < labelBase.size(); i++ ) {

				//if ( relab2[i]>=0 ) {

					// ME SEMBLE IMPOSSIBLE
					//if ( labelBase[relab2[i]] >= labelBase.size() ) {

						//labelBase.reserve(relab2[i]+1);

					//}

					//labelBase[relab2[i]] = i;

				//}

			//}

			d.genDegcum();
			cout << "Graph created" << endl;

			vector< vector<int> > communities = d.getConnectedNode();
			vector<long int> renum_louvain = vector<long int>(relab1.size());

			// Correspondance inverse entre cooccurrence et le graphe de depart ?
			for(int i=0; i<relab1.size(); i++){
				if(relab1[i] >= 0){
			//		if(relab1[i] >= renum_louvain.size())
			//			renum_louvain.reserve(relab1[i]+1);
					renum_louvain[relab1[i]] = i;
				}
			}

			ofstream comTriangle(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + to_string(i) + "/Communities-Triangles-" + graphName, ios::out);
			ofstream comFile(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + to_string(i) + "/Communities-" + graphName, ios::out);

			for ( unsigned int i = 0; i < communities.size(); i++ ) {

				for ( unsigned int j = 0; j < communities[i].size(); j++ ) {

					comFile << renum_louvain[labelBase[communities[i].at(j)]];
					comTriangle << labelBase[communities[i].at(j)];

					if ( j < communities[i].size()-1 ) {

						comFile  << ",";
						comTriangle << ",";

					}

				}

				comFile << endl;
				comTriangle << endl;

			}

			comTriangle.close();
			comFile.close();
			cout << "writing communities done" << endl;

			cout << "generating the corresponding cores in the original graph..." << endl;
			ofstream comparaison(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + to_string(i) + "/Comparaison-" + graphName, ios::app);

			// Ecriture des zones d'origine - ATTENTION : probablement une "," en trop
                        ofstream comOri(path + "TRIANGLE-RUN/" + dossier + "/TYPE" + typeTriangle + "/" + to_string(i) + "/Coeurs-Origine-" + graphName, ios::out);
	
			// Parcours des coeurs
			for ( unsigned int k = 0; k < communities.size(); k++ ) {

				vector<bool> coeur(nbSommetsOri, false);
				vector<bool> coeurOri(nbSommetsOri, false);

				// Calcul de la zone correspondant pour chaque coeur 
				for( unsigned int j = 0; j < communities[k].size(); j++ ) {

					coeur[renum_louvain[labelBase[communities[k].at(j)]]] = true;
					coeurOri[renum_louvain[labelBase[communities[k].at(j)]]] = true;
					comOri << renum_louvain[labelBase[communities[k].at(j)]] << ",";

				}

				// Parcours des triangles
				ifstream triangles(path + "TRIANGLE-RUN/" + dossier +"/TYPE" + typeTriangle + "/" + "Triangles-" + graphName, ios::in);
				unsigned int type, a, b, c;

				unsigned int size = communities[k].size();

				while(triangles >> type >> a >> b >> c) {

					// Si deux sommets du triangle sont dans le coeur
					if(coeur[a] && coeur[b]) {

						if(!coeurOri[c]) {

							coeurOri[c] = true;
							size++;
							comOri << c << ",";

						}

					}

					if(coeur[a] && coeur[c]) {
	
						if(!coeurOri[b]) {

                                                        coeurOri[b] = true;
                                                        size++;
							comOri << b << ",";
                                                }

					}

					if(coeur[b] && coeur[c]) {

						if(!coeurOri[a]) {

                                                        coeurOri[a] = true;
                                                        size++;
							comOri << a << ",";

                                                }

					}

				}
			
				comparaison << i << "\t" << communities[k].size() << "\t" << size << "\t" << (float)communities[k].size() / size << endl; 	
				triangles.close();
				coeur.clear();
	                        coeurOri.clear();

				comOri << endl;

			}

			comOri.close();
			comparaison.close();

		}

	}

	else {

		cout << "Usage : " << endl << "CoeurCommunaute graph nbLouvain graph_court" << endl;

	}

	return 0;
}
