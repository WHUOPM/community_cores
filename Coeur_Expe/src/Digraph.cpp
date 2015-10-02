/*
 * Diagraph.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 *      Modif: anthony
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <unordered_map>
#include "Digraph.hpp"
#include "Edge.hpp"
#include "nodeDeg.hpp"

using namespace std;

Digraph::~Digraph() {



}

void Digraph::loadEdgeList(string data, bool weighted){

	(*this).neigh = vector<EdgeWeight>(0);

	FILE* file = fopen(data.c_str(), "r");
	int source, target, weight;
	int scanfReturn;

	if(weighted) {

		while ((scanfReturn = fscanf(file,"%d %d %d", &source, &target, &weight)) != EOF) {

			if(scanfReturn == 3){

				//				cout << source << " " << target << endl;
				(*this).dim=max3((*this).dim,source,target);
				(*this).neigh.push_back(EdgeWeight(source, target, weight));
				(*this).neigh.push_back(EdgeWeight(target, source, weight));
				(*this).nbEdge++;

			}

		}

	}

	else {

		while ((scanfReturn = fscanf(file,"%d %d", &source, &target, &weight)) != EOF) {

			if(scanfReturn == 2){

				(*this).dim=max3((*this).dim,source,target);
				(*this).neigh.push_back(EdgeWeight(source, target, 1));
				(*this).neigh.push_back(EdgeWeight(target, source, 1));
				(*this).nbEdge++;

			}

		}

	}

	fclose(file);

	(*this).dim++;

}

unsigned int Digraph::max3(unsigned int x, unsigned int y, unsigned int z) {

	unsigned int max = x;

	if (y > max) {

		max = y;

	}

	if (z > max) {

		max = z;

	}

	return max;
}

ostream& operator<<( ostream &flux, std::vector<Edge> const& edgeList ) {

	for(unsigned int i=0; i<edgeList.size(); i++) {

		flux << edgeList[i] << " | ";

	}

	return flux;

}

unsigned long int Digraph::getDim() {

	return (*this).dim;

}

vector<EdgeWeight> Digraph::getEdgeList() {

	return (*this).neigh;

}

unsigned int Digraph::getNbEdge() {

	return (*this).nbEdge;

}

unsigned int Digraph::getNbSimpleEdge() {

	return (*this).simpleEdge;

}
unsigned int Digraph::getNbDoubleEdge() {

	return (*this).doubleEdge;

}

void Digraph::genDegcum() {

	vector<unsigned int> deg((*this).dim);

	(*this).degcum.resize((*this).dim);

	for(unsigned int i=0; i<(*this).neigh.size(); i++) {

		deg[(*this).neigh[i].getSource()]++;

	}

	unsigned int i;
	(*this).degcum[0] = deg[0];

	for(i=1; i<(*this).dim; i++) {

		(*this).degcum[i] = deg[i] + (*this).degcum[i-1];

	}

	deg.clear();
}

std::vector< std::vector<int> > Digraph::getConnectedNode() {

	int tab[(*this).dim];
	stack<int> pile;

	for(unsigned int i=0; i<(*this).dim; i++) {

		tab[i] = 0;

	}

	unsigned int i=0;
	int community = 0;

	while ( i < (*this).dim ) {

		community++;
		pile.push(i);

		while ( !pile.empty() ) {

			int s = pile.top();
			pile.pop();
			tab[s] = community;

			unsigned int j = 0;

			if( s > 0 ){

				j = degcum[s-1];

			}

			while ( j < degcum[s] ) {

				if ( tab[(*this).neigh[j].getTarget()] == 0 ) {

					pile.push((*this).neigh[j].getTarget());
					tab[(*this).neigh[j].getTarget()] = community;

				}

				j++;

			}

		}

		while ( i < (*this).dim && tab[i] != 0 ) {

			i++;

		}

	}

	std::vector< vector<int> > v;

	for ( int i = 0; i < community; i++) {

		vector<int> vt = vector<int>();
		v.push_back(vt);

	}

	for ( unsigned int i = 0; i < (*this).dim; i++ ) {

		v.at(tab[i]-1).push_back(i);

	}

	return v;

}


std::vector<unsigned long int> Digraph::getDegcum() {

	return (*this).degcum;

}

void Digraph::sortEdgeList() {

	std::sort((*this).neigh.begin(), (*this).neigh.end());

}


vector<long int> Digraph::relabel() {

	vector<long int> appear = vector<long int>((*this).dim, -1);
	unsigned long int maxId = 0;

	int unsigned i=0, j=0;

	for ( Edge e : neigh ) {

		if ( appear[e.getSource()] == -1 ) {

			appear[e.getSource()] = maxId;
			maxId++;

		}

		if ( appear[e.getTarget()] == -1 ) {

			appear[e.getTarget()] = maxId;
			maxId++;

		}

	}

	for ( unsigned int k = 0; k < (*this).neigh.size(); k++ ) {

		// LIGNE DU DESSOUS USELESS NON ?
		maxId = max(maxId,(unsigned long int) max(appear[neigh[k].getSource()], appear[neigh[k].getTarget()]));
		neigh[k].setSource(appear[neigh[k].getSource()]);
		neigh[k].setTarget(appear[neigh[k].getTarget()]);

	}

	(*this).dim = maxId;
	// IL FAIT QUOI CE PUTAIN DE SORT? VECTEUR D'ARÊTES...
	sort(neigh.begin(), neigh.end());

	return appear;
}



