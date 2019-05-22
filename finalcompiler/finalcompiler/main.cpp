#include "parser.h"
using namespace std;

Base base;

int main() {
	base.scan_grammer("Test.txt");
	base.generate_FirstAndFollow();
	//base.generateProjectSet();
	//base.generateSL0Table();
	//base.printSL0Table();
	return 0;
}