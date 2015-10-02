/*
 * Edge.hpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <iostream>

class Edge {
protected:
	unsigned int source;
	unsigned int target;
	int direction; // Edge direction: 1=from source to target, 2=from target to source, 3=bidirectional.

public:
	Edge(unsigned int _source, unsigned int _target, int _direction):source(_source), target(_target), direction(_direction){};
	Edge(): source(0), target(0), direction(0){};
	unsigned int getSource();
	unsigned int getTarget();
	char getDirection() const;
	void setDirection(int _dir);
	bool compareInf(Edge const &e) const;
	bool compareEqual(Edge const &e) const;
	friend std::ostream& operator<<( std::ostream &flux, Edge const& edge );
	void setSource(unsigned int s);
	void setTarget(unsigned int t);
	~Edge();
};

bool operator<(Edge const& a, Edge const& b);
bool operator>(Edge const& a, Edge const& b);
bool operator==(Edge const& a, Edge const& b);

#endif /* EDGE_HPP_ */
