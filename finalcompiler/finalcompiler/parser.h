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

protected:
	int grammer_num;//文法数量

	node grammer[400]; //文法

	map<string, set<string>>first_set;//first集
	map<string, set<string>>follow_set;//follow集

	set<string>term;//终结符号
	set<string>non_term;//非终结符号

public:


	void scan_grammer(string filePath);//读取文法;

	bool is_term(string s);//判断字符串是否是终结符号

	void set_first(string target);//求出指定非终结符号的first集
	void set_follow(string target);//求出指定非终结符号的follow集

	set<string> get_first(string target);//获得指定符号的first集
	set<string> get_follow(string target);//获得指定符号的follow集

	void display_first();//打印first集
	void display_follow();//打印follow集
};


