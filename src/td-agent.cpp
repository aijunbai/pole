/*
 * td-agent.cpp
 *
 *  Created on: Sep 27, 2010
 *      Author: baj
 */

#include "td-agent.h"

double & TemporalDifferenceAgent::qvalue(const State & state, const int & action)
{
	return qtable_(state, action);
}
