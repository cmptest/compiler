#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <cmath>
#include <stack>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>
using namespace std;

/*
 * struct: 产生式
 * left: 产生式左部
 * right:产生式右部
 */
struct node
{
	string left;
	vector<string>right;
};


class Base{

private:
	int grammer_num;//文法数量

	node grammer[400]; //文法

	map<string, set<string>>first_set;//first集
	map<string, set<string>>follow_set;//follow集

	set<string>term;//终结符号
	set<string>non_term;//非终结符号

	map<pair<string, string>, int>analysisTable;//分析表

	int row = 30;
	int col = 30;

public:


	void scan_grammer(string filePath);//读取文法;

	bool is_term(string s);//判断字符串是否是终结符号

	void set_first(string target);//求出指定非终结符号的first集
	void set_follow(string target);//求出指定非终结符号的follow集

	void display_first();//打印first集
	void display_follow();//打印follow集
	void display_table();//打印分析表

	map<pair<string, string>, int> getTable();//构造分析表

	bool analysis_Exp(vector<string> s);//分析符号串

	void parser();//语法分析
};


