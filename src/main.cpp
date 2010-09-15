#include "pole.h"
#include "logger.h"
#include "system.h"
#include "agent.h"
#include "qlearning.h"
#include "monte-carlo.h"

/**
 * TODO:
 * 		1������״̬���� - done���������ȿ��Եõ���ϸ�µĲ���
 * 		2���Ľ��ر����� - done���ر�����Խ�ܾ�ȷ���֣�״̬��������Խ������ѧϰ
 *      3�����ӷ������� - ������
 *      4����֤���ϸ������gamma��alpha�ȶ�ѧϰ���̵�Ӱ�죺
 *      	a����gamma=1��Ч���ǳ���
 *      	b��q���ʼ��Ϊ0Ч���������ʼ����
 *      5�����rcg��ʽ���� - done
 *      6��ȡ��|theta|���� - done����ѧϰ������
 *      7���������� - done��Ĭ��������
 *      8��״̬�Ƿ���Ҫ����x? - ȷ���޹�
 */

using namespace std;

Agent *CreatorAgent(AgentType agent_t, bool train)
{
	switch (agent_t) {
	case AT_QLearning: return new QLearningAgent(!train);
	case AT_MonteCarlo: return new MonteCarloAgent(!train);
	default: return 0;
	}
}

void usage(const char *progname) {
	cerr << "Usage:\n\t" << progname << " [-t] [-s seed] [-d]\n"
			<< "Options:\n"
			<< "\t-t\ttrain mode\n"
			<< "\t-s\tset random seed\n"
			<< "\t-q\tuse q-learning method\n"
			<< "\t-m\tuse monte-carlo method\n"
			;
}

int main(int argc, char **argv) {
	int seed = getpid();
	bool train = false;
	AgentType agent_t = AT_None;

	int  opt;
	while ((opt = getopt(argc, argv, "qmts:")) != -1) {
		switch (opt) {
		case 't': train = true; break;
		case 'q': agent_t = AT_QLearning; break;
		case 'm': agent_t = AT_MonteCarlo; break;
		case 's': seed = atoi(optarg); break;
		default: usage(argv[0]); exit(1);
		}
	}

	srand48(seed);

	Agent *agent = CreatorAgent(agent_t, train);

	if (!agent) {
		cerr << "Error: No learning method provided" << endl;
		usage(argv[0]);
		return 1;
	}

	if (!train) { //test
		Logger logger("cart-pole.rcg");
		double reward = System().simulate(*agent, true, & logger);
		cout << "Reward: " << reward << endl;
	}
	else { //train
		const int episodes = 1024;
		double rewards = 0.0;
		int loops = episodes;

		do {
			rewards += System().simulate(*agent, false);
		} while(loops--);

		cout << "#Avg Reward:\n" << rewards / double(episodes) << endl;
	}

	delete agent;

	return 0;
}
