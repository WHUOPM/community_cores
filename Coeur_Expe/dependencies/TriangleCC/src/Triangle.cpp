/*
 * Triangle.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#include "Edge.hpp"
#include "Triangle.hpp"
#include <iostream>

using namespace std;

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<( std::ostream &flux, Triangle const& t){
	flux << t.a << " | " << t.b << " | " << t.c << " / " << t.type;
	return flux;
}

void Triangle::setType(int _type){
	this->type = _type;
}

int Triangle::getType(){
	return this->type;
}

unsigned long int Triangle::getA(){
	return this->a;
}
unsigned long int Triangle::getB(){
	return this->b;
}
unsigned long int Triangle::getC(){
	return this->c;
}
