#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "parser.h"
using namespace std;
#define local freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);


Base base;
int main() {
	local

	//�ʷ����������¶����﷨�������������
	base.wordsAnalysis("code1.txt");
	base.scan_grammer("SLR(1).txt");
	base.generate_FirstAndFollow();
	base.generateProjectSet();
	base.generateSL0Table();
	base.printSL0Table();
	base.SL0GrammaAnalysis();
	base.printGENOrFalseMes();


	//�ʷ����������϶����﷨����
	/*base.wordsAnalysis("code4.txt");
	base.parser();*/


	return 0;
}