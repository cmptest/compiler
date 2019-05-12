#include "parser.h"
using namespace std;

Base base;

int main() {
	vector<Token> tokenList = wordsAnalysis("code.txt", true);
	
	base.parser(tokenList);

	return 0;
}