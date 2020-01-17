#include <iostream>
#include <map>
#include <string>
#include <random>
#include <ctime>

using namespace std;

int main() {
	map<string, int> cities = {{"Moscow", 5000000}, {"Omsk", 1300000}, {"Samara", 1400000}, {"Piter", 15000000}};
	int c = 0, sum = 0;
	for (auto& p : cities) {
		sum += p.second;
		p.second += c;
		c = p.second;
	}

	srand(time(NULL)); // Seed the time
	int r = rand()%(sum)+1;

	for (auto p : cities) {
		if (r <= p.second) {
			cout << p.first << endl;
			break;
		}
	}
	return 0;
}
