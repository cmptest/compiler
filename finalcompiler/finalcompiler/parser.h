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
 * struct: ����ʽ
 * left: ����ʽ��
 * right:����ʽ�Ҳ�
 */
struct node
{
	string left;
	vector<string>right;
};


class Base{

private:
	int grammer_num;//�ķ�����

	node grammer[400]; //�ķ�

	map<string, set<string>>first_set;//first��
	map<string, set<string>>follow_set;//follow��

	set<string>term;//�ս����
	set<string>non_term;//���ս����

	map<pair<string, string>, int>analysisTable;//������

	int row = 30;
	int col = 30;

public:


	void scan_grammer(string filePath);//��ȡ�ķ�;

	bool is_term(string s);//�ж��ַ����Ƿ����ս����

	void set_first(string target);//���ָ�����ս���ŵ�first��
	void set_follow(string target);//���ָ�����ս���ŵ�follow��

	void display_first();//��ӡfirst��
	void display_follow();//��ӡfollow��
	void display_table();//��ӡ������

	map<pair<string, string>, int> getTable();//���������

	bool analysis_Exp(vector<string> s);//�������Ŵ�

	void parser();//�﷨����
};


