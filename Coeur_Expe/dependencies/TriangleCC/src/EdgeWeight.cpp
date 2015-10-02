/*
 * EdgeWeight.cpp
 *
 *  Created on: 20 mai 2014
 *      Author: ten
 */

#include "EdgeWeight.hpp"


EdgeWeight::~EdgeWeight() {
	// TODO Auto-generated destructor stub
}

void EdgeWeight::incrementeWeight(){
	this->weight++;
}

std::ostream& operator<<( std::ostream &flux, EdgeWeight const& edge ){
	flux << edge.source << " " << edge.target << " " << edge.weight;

	return flux;
}

int EdgeWeight::getWeight(){
	return this->weight;
}
