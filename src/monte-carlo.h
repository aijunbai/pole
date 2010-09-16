/*
 * monte-carlo.h
 *
 *  Created on: Sep 15, 2010
 *      Author: baj
 */

#ifndef MONTE_CARLO_H_
#define MONTE_CARLO_H_

#include <list>

#include "table.h"
#include "epsilon-agent.h"

/**
 * first-visit on-policy Monte Carlo method
 */
class MonteCarloAgent: public EpsilonAgent {
public:
	MonteCarloAgent(const bool test): EpsilonAgent(test) {
		monte_carlo_.load("monte-carlo.txt");
	}

	virtual ~MonteCarloAgent() {
		if (!test()) {
			monte_carlo_.save("monte-carlo.txt");
		}
	}

	double & qvalue(const State &, const int &);

	virtual void learn(const State & pre_state, int pre_action, double reward, const State & state);
	virtual void fail(const State & state, int action, double reward);

private:
	std::list<std::pair<state_action_pair_t, double> > rewards_;
	StateActionPairTable<boost::tuples::tuple<double, u_int64_t> > monte_carlo_;
};

#endif /* MONTE_CARLO_H_ */
