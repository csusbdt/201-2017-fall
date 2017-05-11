#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

using namespace std;

const char * dirname = "./temp";
const int w = 72;
const int h = 48;

unsigned char pixels[w * 3][h] = { 0 };

void paintRect(	
	unsigned char r, 
	unsigned char g, 
	unsigned char b, 
	int i0, 
	int j0, 
	int i1, 
	int j1
){
	for (int i = i0; i < i1; ++i) {
		for (int j = j0; j < j1; ++j) {
			pixels[i + 0][j] = r;
			pixels[i + 1][j] = g;
			pixels[i + 2][j] = b;
		}
	}
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		cout << "arguments: <duration>" << endl; 
		return 1;
	}
	int duration = stoi(argv[1]);

	struct stat st;
	if(stat(dirname, &st) != 0) {
		cout << "Directory not found: " << dirname << endl;
		return 1;
	}

	for (int i = 0; i < duration; ++i) {
		stringstream outfilename;
		outfilename << dirname << "/" << i << ".raw";

		paintRect(0xff, 0x00, 0x00, 20, 10, 50, 48);

		ofstream outfile;
		outfile.open(outfilename.str(), ios::out | ios::binary | ios_base::trunc); 
		outfile.write((const char *)(&pixels), w * h * 3);
		outfile.close();
	}

	cout << "Raw video images created." << endl;
	return 0;
}

