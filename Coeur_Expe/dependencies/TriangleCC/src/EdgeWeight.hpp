/*
 * EdgeWeight.hpp
 *
 *  Created on: 20 mai 2014
 *      Author: ten
 */

#ifndef EDGEWEIGHT_HPP_
#define EDGEWEIGHT_HPP_
#include "Edge.hpp"

class EdgeWeight : public Edge{
private:
	int weight;
public:
	EdgeWeight(): Edge(), weight(1){};
	EdgeWeight(unsigned int _source, unsigned int _target) : Edge(_source, _target, 0), weight(1){};
	void incrementeWeight();
	int getWeight();
	virtual ~EdgeWeight();
	friend std::ostream& operator<<( std::ostream &flux, EdgeWeight const& edge );
};

#endif /* EDGEWEIGHT_HPP_ */
