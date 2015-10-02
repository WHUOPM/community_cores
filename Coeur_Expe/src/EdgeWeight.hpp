/*
 * EdgeWeight.hpp
 *
 *  Created on: 20 mai 2014
 *      Author: ten
 *      Modif: anthony
 */

#ifndef EDGEWEIGHT_HPP_
#define EDGEWEIGHT_HPP_
#include "Edge.hpp"

class EdgeWeight : public Edge {

    private:

        unsigned long int weight;

    public:

        EdgeWeight(): Edge(), weight(1){};
        EdgeWeight(unsigned int _source, unsigned int _target) : Edge(_source, _target, 0), weight(1){};
        EdgeWeight(unsigned int _source, unsigned int _target, unsigned long int _weight) : Edge(_source, _target, 0), weight(_weight){};

        void incrementeWeight();

        virtual ~EdgeWeight();

        friend std::ostream& operator<<( std::ostream &flux, EdgeWeight const& edge );

        unsigned long int getWeight() const {
            return weight;
        }

        void setWeight(unsigned long int weight) {
            this->weight = weight;
        }

};

#endif /* EDGEWEIGHT_HPP_ */
