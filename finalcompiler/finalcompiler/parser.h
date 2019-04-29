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

protected:
	int grammer_num;//�ķ�����

	node grammer[400]; //�ķ�

	map<string, set<string>>first_set;//first��
	map<string, set<string>>follow_set;//follow��

	set<string>term;//�ս����
	set<string>non_term;//���ս����

public:


	void scan_grammer(string filePath);//��ȡ�ķ�;

	bool is_term(string s);//�ж��ַ����Ƿ����ս����

	void set_first(string target);//���ָ�����ս���ŵ�first��
	void set_follow(string target);//���ָ�����ս���ŵ�follow��

	set<string> get_first(string target);//���ָ�����ŵ�first��
	set<string> get_follow(string target);//���ָ�����ŵ�follow��

	void display_first();//��ӡfirst��
	void display_follow();//��ӡfollow��
};


