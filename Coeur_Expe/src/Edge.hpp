/*
 * Edge.hpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 *      Modif: anthony
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <iostream>

class Edge {

    protected:

        unsigned long int source;
        unsigned long int target;
        int direction; // Edge direction: 1=from source to target, 2=from target to source, 3=bidirectional.

    public:

        Edge(unsigned long int _source, unsigned long int _target, int _direction):source(_source), target(_target), direction(_direction){};
        Edge(): source(0), target(0), direction(0){};

        unsigned long int getSource();
        unsigned long int getTarget();
        char getDirection() const;

        void setDirection(int _dir);
        void setSource(unsigned int s);
        void setTarget(unsigned int t);

        bool compareInf(Edge const &e) const;
        bool compareEqual(Edge const &e) const;

        friend std::ostream& operator<<( std::ostream &flux, Edge const& edge );

        ~Edge();

};

bool operator<(Edge const& a, Edge const& b);
bool operator>(Edge const& a, Edge const& b);
bool operator==(Edge const& a, Edge const& b);

#endif /* EDGE_HPP_ */
