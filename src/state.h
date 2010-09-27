/*
 * state.h
 *
 *  Created on: Sep 15, 2010
 *      Author: baj
 */

#ifndef STATE_H_
#define STATE_H_

#include "utils.h"
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/tuple/tuple_io.hpp"

class State: public boost::tuples::tuple<int, int, int> {
public:
	State() { }

	State(const double & dx, const double & theta, const double & dtheta) {
		get<0>() = dx * 100.0; //��ȷ������
		get<1>() = theta / one_degree; //��ȷ��һ��
		get<2>() = dtheta / one_degree; //��ȷ��һ��
	}
};


#endif /* STATE_H_ */
