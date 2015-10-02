/*
 * Triangle.hpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

class Triangle {
private:
	unsigned long int a;
	unsigned long int b;
	unsigned long int c;
	int type;

public:
	Triangle(unsigned long int _a, unsigned long int _b, unsigned long int _c, char _type):a(_a), b(_b), c(_c), type(_type){};
	Triangle():a(0), b(0), c(0), type(0){};
	unsigned long int getA();
	unsigned long int getB();
	unsigned long int getC();
	int getType();
	void setType(int _type);
	friend std::ostream& operator<<( std::ostream &flux, Triangle const& t);
	virtual ~Triangle();
};

#endif /* TRIANGLE_HPP_ */
