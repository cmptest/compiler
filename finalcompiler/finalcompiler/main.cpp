#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "parser.h"
using namespace std;
#define local freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);


Base base;
int main() {
	local
	//base.words = wordsAnalysis("code.txt", false);
	vector<Token> vec;
	vec.push_back(Token(0, "id", 0));
	vec.push_back(Token(0, "*", 0));
	vec.push_back(Token(0, "id", 0));
	vec.push_back(Token(0, "+", 0));
	vec.push_back(Token(0, "id", 0));
	base.words = vec;
	//base.scan_grammer("Test.txt");
	base.scan_grammer("h.txt");
	base.generate_FirstAndFollow();
	base.generateProjectSet();
	base.generateSL0Table();
	base.printSL0Table();
	base.SL0GrammaAnalysis();
	return 0;


	// = wordsAnalysis("code.txt", false);
	//"NoRecursiveGrammer.txt"
	//vector<Token> vec;
	//vec.push_back(Token(0, "id", 0));
	//vec.push_back(Token(0, "*", 0));
	//vec.push_back(Token(0, "id", 0));
	//vec.push_back(Token(0, "+", 0));
	//vec.push_back(Token(0, "id", 0));
	//base.words = vec;
	//base.scan_grammer("h.txt");
	////base.generate_FirstAndFollow();

	//set<string> s;
	//s.insert("$");
	//base.follow_set["<Begin>"] = s;
	//s.insert(")"); s.insert("+");
	//base.follow_set["<E>"] = s;
	//s.insert("*");
	//base.follow_set["<T>"] = s;
	//base.follow_set["<F>"] = s;

	//base.generateProjectSet();
	//base.generateSL0Table();
	//base.printSL0Table();
	//base.SL0GrammaAnalysis();
	//return 0;
}