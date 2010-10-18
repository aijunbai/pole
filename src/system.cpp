/*
 * system.cpp
 *
 *  Created on: Sep 15, 2010
 *      Author: baj
 */

#include <iostream>
#include <cassert>

#include "state.h"
#include "system.h"
#include "agent.h"
#include "logger.h"

using namespace std;

double System::simulate(Agent & agent, bool verbose, Logger *logger)
{
	int step = 0;
	double rewards = 0.0;

	State state = pole_.get_signal<State>();
	int action = agent.plan(state);
	assert(action == 0 || action == 1);

	do {
		step += 1;

		if (verbose) {
			pole_.print_state(step);
			cout << " | State: " << pole_.get_signal<State>() << " | Action: " << action;
		}

		if (logger) {
			pole_.log(logger, action);
			logger->Flush();
		}

		pole_.step(action); //taking action

		if (pole_.fail()) {
			agent.fail(state, action, get_failure_reward()); //failure state - ����ʧ��״̬��һ��δ֪״̬��δ֪״̬��ʼ��Ϊ�㣩
			if (verbose) {
				cout << " | Failure" << endl;
			}
			step += 1;
			break;
		}

		State post_state = pole_.get_signal<State>(); //observing s'
		double reward = get_reward(); //observing reward
		int post_action = agent.plan(post_state); //choosing a'
		assert(post_action == 0 || post_action == 1);

		agent.learn(state, action, reward, post_state, post_action); //learning from experience

		state = post_state;
		action = post_action;

		if (verbose) {
			cout << " | Reward: " << reward << endl;
		}

		rewards += reward;
	} while(1);

	if (verbose) {
		pole_.print_state(step);
		cout << " | State: " << pole_.get_signal<State>() <<  " | The End" << endl;
	}

	if (logger) {
		pole_.log(logger, 0);
		logger->Flush();
	}

	return rewards;
}
