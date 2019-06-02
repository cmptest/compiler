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
#include <regex>
using namespace std;

/*
 * node: 产生式
 * @Param: left -- 产生式左部
 * @Param: right -- 产生式右部
 * @Param: index -- 语法分析时的点
 */
struct node
{
	string left;
	vector<string>right;
	int index = 0;
};

/*
 * I： 项目集 
 * @Param: id -- 项目集号
 * @Param: vec -- 项目集
 * @Param: m -- 转化关系
 */
struct I {
	int id;				
	vector<node> vec;   
	map<string, int> m; //
};
/*
 * Token -- 词法单元
 * @Param: num -- 内部编码,为-1代表错误
 * @Param: value -- 内码值
 * @Param: col -- 行号
 * @Param: type -- 类型，int或float
 */
struct Token {
	int num;      
	string value; 
	int col;
	string type;
	Token(int _num, string _value, int _col) {
		num = _num;
		value = _value;
		col = _col;
	}
	Token(){}
};


class Base{

private:
	bool is_right;//编译过程是否报错
	string false_mes;//报错信息
	vector<Token> words;//词法分析返回的Token
	int findIndex(string value);//根据value寻找Token的index

	int grammer_num;//文法数量
	
	node grammer[400]; //文法

	map<string, set<string>>first_set;//first集
	map<string, set<string>>follow_set;//follow集

	set<string>term;//终结符号
	set<string>non_term;//非终结符号

	vector<I> projectSet; //项目集

	map<pair<string, string>, int>analysisTable_1;//自上而下分析表 (<文法左部, 终结符号+&>, 产生式下标)

	map<pair<int, string>, pair<string, int>> ACTION; //ACTION函数
	map<pair<int, string>, int> GOTO;				  //GOTO函数

	vector<vector<string> > GEN;					 //生成的四元式

	

public:
	//主函数直接调用词法分析函数,is_store,是否讲结果保存再txt文件中
	void wordsAnalysis(string source_code); 

	void scan_grammer(string filePath);//读取文法;

	bool is_term(string s);//判断字符串是否是终结符号

	void set_first(string target);//求出指定非终结符号的first集
	void set_follow(string target);//求出指定非终结符号的follow集

	void display_firstAndFollow();//打印first集
	void display_Table();//打印分析表

	//求first,follow并打印
	void generate_FirstAndFollow();

	// TODO 由文法生成项目集规范簇
	void generateProjectSet();

	void printI(I pi);

	// TODO 分析表
	void generateSL0Table();

	void printSL0Table();

	void SL0GrammaAnalysis();

	void printGENOrFalseMes();
	

	map<pair<string, string>, int> getTopToBottomTable();//构造自上而下分析表

	int analysis_TopToBottom_Exp(vector<Token> s);//分析符号串（自上而下），正确则返回0，错误则返回行号


	void parser();//接收词法分析的token，进行语法分析
};


/*https://www.cnblogs.com/acm-icpcer/p/9107838.html */
/*https://blog.csdn.net/wq897387/article/details/6082912 */
/*https://wenku.baidu.com/view/6c415aac58fafab068dc0227.html */