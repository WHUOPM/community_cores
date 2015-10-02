/*
 * Diagraph.hpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 *      Modif: anthony
 */

#ifndef DIGRAPH_HPP_
#define DIGRAPH_HPP_

#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "EdgeWeight.hpp"

class Digraph {

    private:

        std::vector<unsigned long int> degcum;
        std::vector<EdgeWeight> neigh;
        unsigned int dim;
        unsigned int max3(unsigned int x, unsigned int y, unsigned int z);
        unsigned int nbEdge;
        unsigned int simpleEdge;
        unsigned int nbNode;
        unsigned int doubleEdge;

    public:

        Digraph():degcum(0), neigh(0), dim(0), nbEdge(0), simpleEdge(0), doubleEdge(0), nbNode(0){};
        void loadEdgeList(std::string data, bool weighted);

        unsigned long int getDim();
        std::vector<EdgeWeight> getEdgeList();
        unsigned int getNbEdge();
        unsigned int getNbSimpleEdge();
        unsigned int getNbDoubleEdge();
        std::vector< std::vector<int> > getConnectedNode();

        std::vector<unsigned long int> getDegcum();
        void sortEdgeList();
        std::vector<long int> relabel();
        void genDegcum();

        ~Digraph();

        friend std::ostream& operator<<( std::ostream &flux, std::vector<EdgeWeight> const& edgeList );

};

#endif /* DIGRAPH_HPP_ */
