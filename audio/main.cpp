#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <climits>
#include <stdint.h>

using namespace std;

const double PI = 3.14159265359;
const int samples_per_second = 44100;

int main(int argc, char * args[]) {
	assert(sizeof(short) == 2);

	FILE * result = freopen(0, "wb", stdout);
	if (result == 0) {
		perror("Error reopening stdout");
		exit(1);
	}

	double duration_in_seconds = 5;
	int num_samples = samples_per_second * duration_in_seconds;
	for (int i = 0; i < num_samples; ++i) {
		short sample = sin(2 * PI * i / 180.0) * SHRT_MAX;
		fwrite(reinterpret_cast<unsigned char *>(&sample), 1, 2, stdout);
	}

	cout << "OK" << endl;
}

