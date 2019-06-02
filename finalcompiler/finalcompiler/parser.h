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
 * node: ����ʽ
 * @Param: left -- ����ʽ��
 * @Param: right -- ����ʽ�Ҳ�
 * @Param: index -- �﷨����ʱ�ĵ�
 */
struct node
{
	string left;
	vector<string>right;
	int index = 0;
};

/*
 * I�� ��Ŀ�� 
 * @Param: id -- ��Ŀ����
 * @Param: vec -- ��Ŀ��
 * @Param: m -- ת����ϵ
 */
struct I {
	int id;				
	vector<node> vec;   
	map<string, int> m; //
};
/*
 * Token -- �ʷ���Ԫ
 * @Param: num -- �ڲ�����,Ϊ-1�������
 * @Param: value -- ����ֵ
 * @Param: col -- �к�
 * @Param: type -- ���ͣ�int��float
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
	bool is_right;//��������Ƿ񱨴�
	string false_mes;//������Ϣ
	vector<Token> words;//�ʷ��������ص�Token
	int findIndex(string value);//����valueѰ��Token��index

	int grammer_num;//�ķ�����
	
	node grammer[400]; //�ķ�

	map<string, set<string>>first_set;//first��
	map<string, set<string>>follow_set;//follow��

	set<string>term;//�ս����
	set<string>non_term;//���ս����

	vector<I> projectSet; //��Ŀ��

	map<pair<string, string>, int>analysisTable_1;//���϶��·����� (<�ķ���, �ս����+&>, ����ʽ�±�)

	map<pair<int, string>, pair<string, int>> ACTION; //ACTION����
	map<pair<int, string>, int> GOTO;				  //GOTO����

	vector<vector<string> > GEN;					 //���ɵ���Ԫʽ

	

public:
	//������ֱ�ӵ��ôʷ���������,is_store,�Ƿ񽲽��������txt�ļ���
	void wordsAnalysis(string source_code); 

	void scan_grammer(string filePath);//��ȡ�ķ�;

	bool is_term(string s);//�ж��ַ����Ƿ����ս����

	void set_first(string target);//���ָ�����ս���ŵ�first��
	void set_follow(string target);//���ָ�����ս���ŵ�follow��

	void display_firstAndFollow();//��ӡfirst��
	void display_Table();//��ӡ������

	//��first,follow����ӡ
	void generate_FirstAndFollow();

	// TODO ���ķ�������Ŀ���淶��
	void generateProjectSet();

	void printI(I pi);

	// TODO ������
	void generateSL0Table();

	void printSL0Table();

	void SL0GrammaAnalysis();

	void printGENOrFalseMes();
	

	map<pair<string, string>, int> getTopToBottomTable();//�������϶��·�����

	int analysis_TopToBottom_Exp(vector<Token> s);//�������Ŵ������϶��£�����ȷ�򷵻�0�������򷵻��к�


	void parser();//���մʷ�������token�������﷨����
};


/*https://www.cnblogs.com/acm-icpcer/p/9107838.html */
/*https://blog.csdn.net/wq897387/article/details/6082912 */
/*https://wenku.baidu.com/view/6c415aac58fafab068dc0227.html */