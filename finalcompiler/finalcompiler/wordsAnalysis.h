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
	int num;      //�ڲ�����,Ϊ-1�������
	string value; //����ֵ
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

string scanffile(string filepath);//��Դ�ļ���ȡԴ���򷵻�Դ������ַ���
vector<Token> wordsAnalysis(string source_code,bool is_store);//������ֱ�ӵ��ôʷ���������,is_store,�Ƿ񽲽��������txt�ļ���
bool is_num(int i); //�ж� source_code[i]�Ƿ���һ������ 
bool is_alpha(int i); //�ж� source_code[i]�Ƿ���һ����ĸ 
Token is_idOrKeyword(int i); //�� source_code[i]��ʼ�ж��Ƿ��Ǳ����ֻ��߱�ʶ�������� token�������ǣ����� null����ʾ����Token is_op��int i��//�� source_code[i]��ʼ�ж��Ƿ�������������� token�������ǣ����� null����ʾ����
Token is_delim(int i); //�� source_code[i]��ʼ�ж��Ƿ��Ƿָ��������� token�������ǣ����� null����ʾ����
