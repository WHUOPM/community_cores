/*
 * nodeDeg.cpp
 *
 *  Created on: 3 avr. 2014
 *      Author: ten
 */

#include "nodeDeg.hpp"

nodeDeg::~nodeDeg() {

	// TODO Auto-generated destructor stub

}

unsigned int nodeDeg::getDeg() {

    return (*this).deg;

}

bool nodeDeg::compare_desc_deg(const nodeDeg &n) const{

	if((*this).deg != n.deg)

		return (*this).deg>n.deg;

	return (*this).node < n.node;

}

bool operator>(nodeDeg const& a, nodeDeg const& b){

	return a.compare_desc_deg(b);

}
