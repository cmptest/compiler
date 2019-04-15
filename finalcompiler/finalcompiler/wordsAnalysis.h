#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
using namespace std;

struct Token {
	int num;      //内部编码,为-1代表错误
	string value; //内码值
	int col;
	Token(int _num, string _value,int _col) {
		num = _num;
		value = _value;
		col = _col;
	}
};


//const string foper[] = { "*","/" };
//const string soper[] = { "+","-","<<",">>","&","|" };
//const string voper[] = { "=","-=","+=","/=","*=" };
//const string coper[] = { "<","<=","==",">",">=" };

string scanffile(string filepath);//从源文件读取源程序返回源程序的字符串
vector<Token> wordsAnalysis(string source_code,bool is_store);//主函数直接调用词法分析函数,is_store,是否讲结果保存再txt文件中
bool is_num(int i); //判断 source_code[i]是否是一个数字 
bool is_alpha(int i); //判断 source_code[i]是否是一个字母 
Token is_idOrKeyword(int i); //从 source_code[i]开始判断是否是保留字或者标识符，返回 token。若不是，返回 null（表示错误）Token is_op（int i）//从 source_code[i]开始判断是否是运算符，返回 token。若不是，返回 null（表示错误）
Token is_delim(int i); //从 source_code[i]开始判断是否是分隔符，返回 token。若不是，返回 null（表示错误）
