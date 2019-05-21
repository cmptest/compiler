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
 * node: ����ʽ
 * left: ����ʽ��
 * right:����ʽ�Ҳ�
 * index:�﷨����ʱ�ĵ�
 */
struct node
{
	string left;
	vector<string>right;
	int index = 0;
};

//��Ŀ��
struct I {
	int id;				//��Ŀ����
	vector<node> vec;   //��Ŀ��
	map<string, int> m; //ת����ϵ
	int num;			//��Ŀ�����ķ�����Ŀ�����������ķ��Ƴ������ķ�
};

class Base{

private:
	int grammer_num;//�ķ�����
	
	node grammer[400]; //�ķ�

	map<string, set<string>>first_set;//first��
	map<string, set<string>>follow_set;//follow��

	set<string>term;//�ս����
	set<string>non_term;//���ս����

	vector<I> projectSet; //��Ŀ��

	map<pair<string, string>, int>analysisTable_1;//���϶��·����� (<�ķ���, �ս����+&>, ����ʽ�±�)

public:


	void scan_grammer(string filePath);//��ȡ�ķ�;

	bool is_term(string s);//�ж��ַ����Ƿ����ս����

	void set_first(string target);//���ָ�����ս���ŵ�first��
	void set_follow(string target);//���ָ�����ս���ŵ�follow��

	void display_firstAndFollow();//��ӡfirst��
	//void display_table();//��ӡ������

	bool is_existTheI(vector<node> v,int & tmpid );

	// TODO ���ķ�������Ŀ���淶��
	void generateProjectSet();

	void printI(I pi);

	// TODO ������
	

	map<pair<string, string>, int> getTopToBottomTable();//�������϶��·�����

	map<pair<string, int>, string> getBottomToTopTable();//�������¶��Ϸ�����

	int analysis_TopToBottom_Exp(vector<Token> s);//�������Ŵ������϶��£�����ȷ�򷵻�0�������򷵻��к�

	int analysis_BottomToTop_Exp(vector<Token> s);//�������Ŵ������϶��£�����ȷ�򷵻�0�������򷵻��к�

	void parser(vector<Token> tokenList);//���մʷ�������token�������﷨����
};


/*https://www.cnblogs.com/acm-icpcer/p/9107838.html */
/*https://blog.csdn.net/wq897387/article/details/6082912 */
/*https://wenku.baidu.com/view/6c415aac58fafab068dc0227.html */