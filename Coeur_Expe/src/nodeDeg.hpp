/*
 * nodeDeg.hpp
 *
 *  Created on: 3 avr. 2014
 *      Author: ten
 *      Modif: anthony
 */

#ifndef NODEDEG_HPP_
#define NODEDEG_HPP_

class nodeDeg {

    private:

        unsigned int node;
        unsigned int deg;

    public:

        nodeDeg(int _node, int _deg):node(_node), deg(_deg){};
        nodeDeg():node(0), deg(0){};

        bool compare_desc_deg(const nodeDeg &n) const;

        unsigned int getDeg();

        virtual ~nodeDeg();

};

bool operator>(nodeDeg const& a, nodeDeg const& b);

#endif /* NODEDEG_HPP_ */
