#include <iostream>
#include  <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include "Digraph.hpp"
#include "EdgeWeight.hpp"
#include "time.h"

using namespace std;

//graph type1 type2 type3 ...

int main(int argc, char *argv[]) {

	if(argc > 3){

		vector<bool> trianglesType = vector<bool>(false, 7);
		string pathRelabFile = string(argv[2]);
		for(int i=3; i<argc; i++){
			if(atoi(argv[i])-1 < 7)
				trianglesType[atoi(argv[i])-1] = true;
		}

		Digraph *g = new Digraph(true, pathRelabFile);

		//cout << "Reading graph... "<< argv[1] << endl ;
		g->loadEdgeList(string(argv[1]));
		//cout << "done"<< endl;

		//cout << "Triangle_count... "<<endl;
		vector<Triangle> vt = g->triangle_count() ;
		//cout << "done"<<endl;

		unsigned long int nbSommet = g->getDim();
		delete g;

		vector< vector <EdgeWeight> > edges = vector< vector<EdgeWeight> >();
		for(unsigned long int i=0; i<nbSommet; i++){
			edges.push_back(vector<EdgeWeight>());
		}

		ofstream triangle("Triangles-" + string(argv[1]), ios::out);

		//cout << "Creating edges from triangles..." << endl;
		//Triangles are ordered by id ( a > b > c )
		unsigned long int maxId = 0;
		for(Triangle t : vt){
			if(trianglesType[t.getType()]){
				unsigned long int a = t.getA();
				unsigned long int b = t.getB();
				unsigned long int c = t.getC();

				// Ecriture des triangles dans un fichier
				triangle << t.getType() << " " << a << " " << b << " " << c << endl;	
				maxId = max(maxId, a);
				maxId = max(maxId, b);
				maxId = max(maxId, c);

				// a-b
				bool found = false;
				for(unsigned long int i=0; i<edges[a].size(); i++){
					if(edges[a][i].getTarget() == b){
						edges[a][i].incrementeWeight();
						i = edges[a].size();
						found = true;
					}
				}
				if(!found){
					edges[a].push_back(EdgeWeight(a, b));
				}

				// b-c
				found = false;
				for(unsigned long int i=0; i<edges[b].size(); i++){
					if(edges[b][i].getTarget() == c){
						edges[b][i].incrementeWeight();
						i = edges[b].size();
						found = true;
					}
				}
				if(!found){
					edges[b].push_back(EdgeWeight(b, c));
				}

				// c-a ( or a-c )
				found = false;
				unsigned long int maxV = max(a, c);
				unsigned long int minV = min(a, c);
				for(unsigned long int i=0; i<edges[maxV].size(); i++){
					if(edges[maxV][i].getTarget() == minV){
						edges[maxV][i].incrementeWeight();
						i = edges[maxV].size();
						found = true;
					}
				}
				if(!found){
					edges[maxV].push_back(EdgeWeight(maxV, minV));
				}


			}

		}
		//cout << "done" << endl;
		triangle.close();

//		cout << "Writing graph... "<<endl;
//		ofstream resultFile("graphTriangle", ios::out);
		for(unsigned long int i=0; i<edges.size(); i++){
			std::sort(edges[i].begin(), edges[i].end());
			for(unsigned long int j=0; j<edges[i].size(); j++){
				cout << edges[i][j] << endl;
//				resultFile << edges[i][j] << endl;
			}
		}
//		resultFile.close();
//		cout << "done"<< endl;
	}
	else
		cout << "Usage : " << endl << "TriangleCC graph outputPath type1 [type2] [...]" << endl;

	return 0;
}

