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

	if ( argc > 3 ) {

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

		unsigned int nbLouvain = atoi(argv[2]);

       	// TODO: renumeroter en utilisant Louvain, et donc ne plus avoir ce truc la...
       	// Renumerotation du graphe
		Digraph l = Digraph();
		l.loadEdgeList(graphPath, false);

		unsigned int nbSommets = l.getDim();

		cout << nbSommets << endl;

		vector < unordered_map<unsigned long int,unsigned int> > cooccur(nbSommets);
		vector< vector<unsigned long int> > comm;

		// Conversion et generation des communautes une fois par type de triangle
		cout << "Converting" << endl;
		system(("./" + path + "dependencies/louvain/convert -i " + graphPath + " -o " + path + "RUN/" + argv[3] + "-OLD" + "/Louvain/graph.bin ").c_str());

		for ( int k = 1; k <= nbLouvain; k++ ) {

			stringstream fileName;
			fileName << "RUN/" << argv[3] << "-OLD" << "/Louvain/graph" << k;

			comm = vector< vector<unsigned long int> >();

			// TODO : un .tree par itération du Louvain ?
			system(("./" + path + "dependencies/louvain/community -l -1 "+path+"RUN/" + argv[3] + "-OLD" + "/Louvain/graph.bin > " + path + "RUN/" + argv[3] + "-OLD" + "/Louvain/graph.tree").c_str());
			system(("./" + path + "dependencies/louvain/hierarchy -l 0 " + path + "RUN/" + argv[3] + "-OLD" + "/Louvain/graph.tree > " + path +fileName.str()).c_str());

			// On parcourt le fichier des communautés (dernier niveau de la hiérarchie)
			FILE* file = fopen((path + fileName.str()).c_str(), "r");
			long source, target, tmp;
			int scanfReturn;

			// On charge les communautés dans un vecteur
			cout << "reading graph from : " << (path + fileName.str()).c_str() << endl;

			cout << "updating map..." << endl;

			unordered_map<unsigned long int,unsigned int>::iterator it;

			while ( (scanfReturn = fscanf(file,"%ld %ld", &source, &target)) != EOF ) {

				if ( scanfReturn == 2 ){

					while( target >= comm.size() ) {

						comm.push_back(vector<unsigned int long>());

					}

					comm[target].push_back(source);
				}

			}

			fclose(file);

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
			
			for(unsigned int i = 0; i < comm.size(); i++) 
			
				comm[i].erase(comm[i].begin(), comm[i].end());
				
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

		/*ofstream file1(path + "RUN/" + argv[3] + "-OLD" + "/1/CooccurOLD_" + graphName);
		ofstream file2(path + "RUN/" + argv[3] + "-OLD" + "/2/CooccurOLD_" + graphName);
		ofstream file3(path + "RUN/" + argv[3] + "-OLD" + "/3/CooccurOLD_" + graphName);
		ofstream file4(path + "RUN/" + argv[3] + "-OLD" + "/4/CooccurOLD_" + graphName);*/
		ofstream file5(path + "RUN/" + argv[3] + "-OLD" + "/5/CooccurOLD_" + graphName);
		ofstream file6(path + "RUN/" + argv[3] + "-OLD" + "/6/CooccurOLD_" + graphName);
		ofstream file7(path + "RUN/" + argv[3] + "-OLD" + "/7/CooccurOLD_" + graphName);
		ofstream file8(path + "RUN/" + argv[3] + "-OLD" + "/8/CooccurOLD_" + graphName);
		ofstream file9(path + "RUN/" + argv[3] + "-OLD" + "/9/CooccurOLD_" + graphName);

		while ( inFile >> source >> target >> nbOccur ) {
			/*if( (double) (((double)nbOccur) / nbLouvain >= (0.1)) ) {

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

			}*/
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

		/*file1.close();
		file2.close();
		file3.close();
		file4.close();*/
		file5.close();
		file6.close();
		file7.close();
		file8.close();
		file9.close();

		inFile.close();

		cout << "Writing WeightedEdges/unweightedEdges done" << endl;

		for ( unsigned int i = 5; i < 10; i++ ) {

			Digraph d = Digraph();
			d.loadEdgeList(path + "RUN/" + argv[3] + "-OLD" + "/" + to_string(i) + "/CooccurOLD_" + graphName, false);
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
			cout << "creating relabeled communities" << endl;

			ofstream unweightedRelabeledGraph(path + "RUN/" + argv[3] + "-OLD" + "/" + to_string(i) + "/CooccurOLD_" + graphName +"_relabeled", ios::out);
			ifstream inFile(path + "CooccurOLD_"+graphName);

			while ( inFile >> source >> target >> weight ) {

				// INUTILE : il suffit de reparcourir le CooccurOLD_ qui est dans le dossier alpha
				if ( (double) (((double)weight) / nbLouvain >= (i/10.0)) ) {

					unweightedRelabeledGraph << relab2[source] << " " << relab2[target] << endl;

				}

			}

			inFile.close();
			unweightedRelabeledGraph.close();

			cout << "done" << endl;

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
			ofstream comFile(path + "RUN/" + argv[3] + "-OLD" + "/" + to_string(i) + "/Communities_" + graphName, ios::out);

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
