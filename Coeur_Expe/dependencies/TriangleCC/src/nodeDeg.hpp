/*
 * nodeDeg.hpp
 *
 *  Created on: 3 avr. 2014
 *      Author: ten
 */

#ifndef NODEDEG_HPP_
#define NODEDEG_HPP_

class nodeDeg {
public:
	unsigned int node;
	unsigned int deg;
	nodeDeg(int _node, int _deg):node(_node), deg(_deg){};
	nodeDeg():node(0), deg(0){};
	virtual ~nodeDeg();
	bool compare_desc_deg(const nodeDeg &n) const;
};

bool operator>(nodeDeg const& a, nodeDeg const& b);

#endif /* NODEDEG_HPP_ */
