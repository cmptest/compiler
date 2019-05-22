#include "parser.h"
using namespace std;

Base base;

int main() {
	base.scan_grammer("Test.txt");
	base.generate_FirstAndFollow();
<<<<<<< HEAD
	//base.generateProjectSet();
	//base.generateSL0Table();
	//base.printSL0Table();
=======
	base.generateProjectSet();
	base.generateSL0Table();
	base.printSL0Table();
>>>>>>> 最新
	return 0;
}