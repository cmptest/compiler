#include "parser.h"



/**
  * function   : is_term(string s)
  * description: 这个方法用于判断字符串是否是终结符号
  * param      : s
  * return	   : bool
  */

bool Base::is_term(string s) {
	if (s[0] == '<' && s[s.length() - 1] == '>')
		return false;
	return true;
}




/**
  * function   : scan_grammer(string filePath)
  * description: 这个方法用于从文件读入文法，初始化grammer[100], term, non_term
  * param      : filePath
  */

void Base::scan_grammer(string filePath) {
	ifstream t(filePath);
	string line = "";
	int index = 0;//grammer[100]下标
	while (getline(t, line)) //逐行读取文法
	{
		line += " ";
		bool isleft = true;//是否是文法左部
		int k = 0;
		for (int i = 0, j = 0; i < line.length();) {//通过空格分割文法字符串
			
			// ->
			if (line[i] == '-' && line[i + 1] == '>') {
				i += 3;
				j += 3;
				isleft = false;
			}

			// |
			else if (line[i] == '|') {
				index++;
				grammer[index].left = grammer[index - 1].left;
				i += 2;
				j += 2;
				k = 0;
			}

			//文法左部
			else if (line[i] == ' ' && isleft) {
				string temp = line.substr(j, i-j);
				grammer[index].left = temp;
				j = i + 1;
				i++;
			}

			//文法右部
			else if (line[i] == ' ' && !isleft) {
				string temp = line.substr(j, i-j);
				grammer[index].right[k++] = temp;
				j = i + 1;
				i++;
			}

			else i++;
				
		}
		index++;
	}

	grammer_num = index;

	//初始化终结符号和非终结符号表
	for (int i = 0; i < index; i++) {
		non_term.insert(grammer[i].left);
		for (int j = 0; j < 100; j++) {
			if (is_term(grammer[i].right[j]))
				term.insert(grammer[i].right[j]);//插入终结符号
			else
				non_term.insert(grammer[i].right[j]);//插入非终结符号
		}
	}

	//输出文法
	for (int i = 0; i < index; i++) {
		cout << grammer[i].left << "->";
		for (int j = 0; j < 100; j++) {
			cout << grammer[i].right[j];
		}
		cout << endl;
	}
	
	for (int i = 0; i < index; i++) {
		set_first(grammer[i].left);	
	}


	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end();it++) {
		cout << (*it).first << " first集：";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}





/**
  * function   : set_first(string target)
  * description: 这个方法用于求指定非终结符号的first集
  * param	   : target
  */

void Base::set_first(string target) {
	
	//匹配文法左部
	for (int i = 0; i < grammer_num; i++) {
		if (grammer[i].left == target) {
			if (is_term(grammer[i].right[0])) {
				first_set[target].insert(grammer[i].right[0]);//如果右部第一个字符串是终结符号，则直接插入
			}
			else {
				set_first(grammer[i].right[0]);//如果是非终结符号，递归求first集
				first_set[target] = first_set[grammer[i].right[0]];
			}
		}
	}
}


/**
  * function   : set_follow(string target)
  * description: 这个方法用于求指定非终结符号的follow集
  * param	   : target
  */

void Base::set_follow(string target) {

}