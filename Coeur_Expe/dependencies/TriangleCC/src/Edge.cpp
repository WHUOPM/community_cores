/*
 * Edge.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#include "Edge.hpp"


Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

unsigned int Edge::getSource(){
	return this->source;
}

unsigned int Edge::getTarget(){
	return this->target;
}

char Edge::getDirection() const{
	return this->direction;
}

std::ostream& operator<<( std::ostream &flux, Edge const& edge ){
	flux << edge.source << " " << edge.target << " " << edge.direction;

	return flux;
}

bool operator<(Edge const& a, Edge const& b){
	return a.compareInf(b);
}

bool operator>(Edge const& a, Edge const& b){
	return b.compareInf(a);
}

bool operator==(Edge const& a, Edge const& b){
	return a.compareEqual(b);
}

bool Edge::compareInf(Edge const &e) const{
	if(this->source == e.source){
		return this->target < e.target;
	}
	return this->source < e.source;
}


bool Edge::compareEqual(Edge const &e) const{
	if(this->source == e.source && this->target == e.target)
		return true;
	return false;
}

void Edge::setDirection(int _dir){
	this->direction = _dir;
}

void Edge::setSource(unsigned int s){
	this->source = s;
}

void Edge::setTarget(unsigned int t){
	this->target = t;
}
