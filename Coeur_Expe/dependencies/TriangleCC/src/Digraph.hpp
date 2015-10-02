/*
 * Diagraph.hpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#ifndef DIGRAPH_HPP_
#define DIGRAPH_HPP_

#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "Triangle.hpp"

class Digraph {
private:
	std::vector<unsigned long int> degcum;
	std::vector<Edge> neigh;
	unsigned int dim;
	unsigned int max3(unsigned int x, unsigned int y, unsigned int z);
	unsigned int nbEdge;
	std::vector<unsigned long int> typeTriangle;
	std::vector<unsigned long int> typeWedge;
	std::vector<unsigned long int> typeTripler2;
	unsigned int simpleEdge;
	unsigned int doubleEdge;
	std::string pathRelabFile;
	bool evo;
	void genDegcum();

public:
	void triplet1_count();
	Digraph(bool _evo, std::string _pathRelabFile):degcum(0), neigh(0), dim(0), nbEdge(0), typeTriangle(7), typeWedge(6), typeTripler2(6), simpleEdge(0), doubleEdge(0), evo(_evo), pathRelabFile(_pathRelabFile){};
	void setEdgeList(std::vector<Edge> _edgeList);
	void loadEdgeList(std::string data);
	std::vector<Edge> getEdgeList();
	friend std::ostream& operator<<( std::ostream &flux, std::vector<Edge> const& edgeList );
	unsigned long int getDim();
	std::vector<unsigned long int> getDegcum();
	std::vector<Triangle> triangle_count();
	unsigned int getNbEdge();
	int identifyTypeTriangle(int e1, int e2, int e3);
	unsigned int getNbSimpleEdge();
	unsigned int getNbDoubleEdge();
	std::vector<unsigned long int> getTypeTriangle();
	std::vector<unsigned long int> getTypeWedge();
	void triplet2Count();
	std::vector<unsigned long int> getTriplet2();
	void relabel();
	~Digraph();
};

#endif /* DIGRAPH_HPP_ */
