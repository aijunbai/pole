/*
 * system.h
 *
 *  Created on: Sep 15, 2010
 *      Author: baj
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <cstdlib>
#include <cmath>

#include "pole.h"

class Agent;
class Logger;

class System {
public:
	System() {
		pole_.perturbation();
	}

	void reset() {
		pole_.reset();
	}

	double get_reward() { //���۷�Χ [-1.0, 1.0]
		return cos(pole_.theta()); //�Ա��ֲ���Ϊ���
	}

	double simulate(Agent & agent, int max_steps = 512, bool verbose = false, Logger *logger = 0);

private:
	Pole pole_;
};

#endif /* SYSTEM_H_ */
