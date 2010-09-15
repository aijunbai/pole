#include "pole.h"
#include "logger.h"
#include "system.h"
#include "agent.h"
#include "qlearning.h"

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

void usage(const char *progname) {
	cout << "Usage:\n\t" << progname << " [-t] [-s seed] [-d]\n"
			<< "Options:\n"
			<< "\t-t\ttrain mode\n"
			<< "\t-s\tset random seed\n"
			;
}

int main(int argc, char **argv) {
	int seed = getpid();
	bool train = false;

	int  opt;
	while ((opt = getopt(argc, argv, "dts:")) != -1) {
		switch (opt) {
		case 't': train = true; break;
		case 's': seed = atoi(optarg); break;
		default: usage(argv[0]); exit(1);
		}
	}

	srand48(seed);

	if (!train) { //test
		QLearningAgent agent(-0.0, true);
		Logger logger("cart-pole.rcg");
		double reward = System().simulate(agent, true, & logger);
		cout << "Reward: " << reward << endl;
	}
	else { //train
		const int episodes = 1024;

		QLearningAgent agent;

		double rewards = 0.0;
		int loops = episodes;

		do {
			rewards += System().simulate(agent, false);
		} while(loops--);

		cout << "#Avg Reward:\n" << rewards / double(episodes) << endl;
	}

	return 0;
}
