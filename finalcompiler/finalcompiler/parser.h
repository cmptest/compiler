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
#include <queue>
#include "wordsAnalysis.h"
using namespace std;

/*
 * node: 产生式
 * left: 产生式左部
 * right:产生式右部
 * index:语法分析时的点
 */
struct node
{
	string left;
	vector<string>right;
	int index = 0;
};

//项目集
struct I {
	int id;				//项目集号
	vector<node> vec;   //项目集
	map<string, int> m; //转化关系
	int num;			//项目集主文法的数目，可以由主文法推出所有文法
};

class Base{

private:
	int grammer_num;//文法数量
	
	node grammer[400]; //文法

	map<string, set<string>>first_set;//first集
	map<string, set<string>>follow_set;//follow集

	set<string>term;//终结符号
	set<string>non_term;//非终结符号

	vector<I> projectSet; //项目集

	map<pair<string, string>, int>analysisTable_1;//自上而下分析表 (<文法左部, 终结符号+&>, 产生式下标)

public:


	void scan_grammer(string filePath);//读取文法;

	bool is_term(string s);//判断字符串是否是终结符号

	void set_first(string target);//求出指定非终结符号的first集
	void set_follow(string target);//求出指定非终结符号的follow集

	void display_firstAndFollow();//打印first集
	//void display_table();//打印分析表

	bool is_existTheI(vector<node> v,int & tmpid );

	// TODO 由文法生成项目集规范簇
	void generateProjectSet();

	void printI(I pi);

	// TODO 分析表
	

	map<pair<string, string>, int> getTopToBottomTable();//构造自上而下分析表

	map<pair<string, int>, string> getBottomToTopTable();//构建自下而上分析表

	int analysis_TopToBottom_Exp(vector<Token> s);//分析符号串（自上而下），正确则返回0，错误则返回行号

	int analysis_BottomToTop_Exp(vector<Token> s);//分析符号串（自上而下），正确则返回0，错误则返回行号

	void parser(vector<Token> tokenList);//接收词法分析的token，进行语法分析
};


/*https://www.cnblogs.com/acm-icpcer/p/9107838.html */
/*https://blog.csdn.net/wq897387/article/details/6082912 */
/*https://wenku.baidu.com/view/6c415aac58fafab068dc0227.html */