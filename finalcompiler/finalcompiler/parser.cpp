#include "parser.h"




/**
  * function   : is_term(string s)
  * description: ������������ж��ַ����Ƿ����ս����
  * param      : s
  * return	   : bool
  */

bool Base::is_term(string s) {
	if (s[0] == '<' && s[s.length() - 1] == '>')
		return false;
	else if (s == "@")
		return false;
	return true;
}




/**
  * function   : scan_grammer(string filePath)
  * description: ����������ڴ��ļ������ķ�����ʼ��grammer[100], term, non_term
  * param      : filePath
  */

void Base::scan_grammer(string filePath) {
	ifstream t(filePath);
	string line = "";
	int index = 0;//grammer[100]�±�
	while (getline(t, line)) //���ж�ȡ�ķ�
	{
		line += " ";
		bool isleft = true;//�Ƿ����ķ���
		for (int i = 0, j = 0; i < line.length();) {//ͨ���ո�ָ��ķ��ַ���
			
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
			}

			//�ķ���
			else if (line[i] == ' ' && isleft) {
				string temp = line.substr(j, i-j);
				grammer[index].left = temp;
				j = i + 1;
				i++;
			}

			//�ķ��Ҳ�
			else if (line[i] == ' ' && !isleft) {
				string temp = line.substr(j, i-j);
				grammer[index].right.push_back( temp);
				j = i + 1;
				i++;
			}

			else i++;
				
		}
		index++;
	}

	grammer_num = index;

	//��ʼ���ս���źͷ��ս���ű�
	for (int i = 0; i < index; i++) {
		non_term.insert(grammer[i].left);
		for (vector<string>::iterator it = grammer[i].right.begin(); it!= grammer[i].right.end(); it++) {
			if (is_term(*it))
				term.insert(*it);//�����ս����
			else
				non_term.insert(*it);//������ս����
		}
	}

	//����ķ�
	/*for (int i = 0; i < index; i++) {
		cout << grammer[i].left << "->";
		for (vector<string>::iterator it = grammer[i].right.begin(); it != grammer[i].right.end(); it++) {
			cout << *it;
		}
		cout << endl;
	}*/
	
	




	

	
}





/**
  * function   : set_first(string target)
  * description: �������������ָ�����ս���ŵ�first��
  * param	   : target
  */

void Base::set_first(string target) {
	
	//ƥ���ķ���
	for (int i = 0; i < grammer_num; i++) {
		if (grammer[i].left == target) {	
			int num = grammer[i].right.size();
			for (vector<string>::iterator it = grammer[i].right.begin(); it != grammer[i].right.end(); it++) {
				
				//�ս����
				if (is_term(*it)) {
					first_set[target].insert(*it);
					break;
				}

				//�մ�
				else if (*it == "@") {
					if ((it + 1) == grammer[i].right.end())//���һ���ַ���
						first_set[target].insert("@");
				}

				//���ս����
				else {
					set_first(*it);//�ݹ���first��
					if (first_set[*it].count("@") == 0)//���������ս���ŵ�first��û��@
					{
						set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(),inserter(first_set[target], first_set[target].begin())); // �󲢼�
						break;
					}
					else {
						set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(), inserter(first_set[target], first_set[target].begin())); // �󲢼�
						first_set[target].erase("@");
					}
				}
			}
		}
	}
}

/**
  * function   : display_first()
  * description: ����������ڴ�ӡfirst��
  */
void Base::display_first() {
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		cout << (*it).first << " first����";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}


/**
  * function   : set_follow(string target)
  * description: �������������ָ�����ս���ŵ�follow��
  * param	   : target
  */

void Base::set_follow(string target) {
	for (int i = 0; i < grammer_num; i++) {
		bool flag = false;
		vector<string>::iterator it;
		for (it = grammer[i].right.begin(); it != grammer[i].right.end(); it++)
		{
			if (*it == target) {
				flag = true;
				break;
			}
		}
		if (flag) {
			//�ұ�Ϊ�մ�
			if (it == grammer[i].right.end()) {
				set_follow(grammer[i].left);
				follow_set[*it] = follow_set[grammer[i].left];
			}
			//�ұ߲�Ϊ��
			else {
				vector<string>::iterator it2;
				for (it2 = it + 1; it2 != grammer[i].right.end(); it2++) {
					if (is_term(*it2)) {
						follow_set[*it].insert(*it2);
						break;
					}
					else if (first_set[*it2].count("@") == 0)
					{
						set_union(follow_set[*it].begin(), follow_set[*it].end(), first_set[*it2].begin(), first_set[*it2].end(), inserter(follow_set[*it], follow_set[*it].begin())); // �󲢼�
						break;
					}
					else {
						set_union(follow_set[*it].begin(), follow_set[*it].end(), first_set[*it2].begin(), first_set[*it2].end(), inserter(follow_set[*it], follow_set[*it].begin())); // �󲢼�
						follow_set[*it].emplace("@");
					}
				}
			}

		}
	}
}

/**
  * function   : display_follow()
  * description: ����������ڴ�ӡfollow��
  */
void Base::display_follow() {
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		cout << (*it).first << " follow����";
		for (set<string>::iterator it2 = follow_set[(*it).first].begin(); it2 != follow_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}




/**
  * function   : getTable()
  * description: ����������ڹ��������
  * return	   : map<pair<string, string>, int>>
  */
map<pair<string, string>, int> Base::getTable() {
	for (int i = 0; i < grammer_num; i++) 
	{
		for (vector<string>::iterator it0 = grammer[i].right.begin(); it0 != grammer[i].right.end(); it0++) {
			string s = *it0;
			if (is_term(s)) {
				pair<string, string> position;
				position.first = grammer[i].left;
				position.second = s;
				analysisTable[position] = i;
				break;
			}
			else if (s == "@" && (it0+1)== grammer[i].right.end()) {
				for (set<string>::iterator it2 = follow_set[grammer[i].left].begin(); it2 != follow_set[grammer[i].left].end(); it2++) {
					pair<string, string> position;
					position.first = grammer[i].left;
					position.second = *it2;
					analysisTable[position] = -1;
				}
				break;
			}
			else {
				set<string>::iterator it;
				bool flag = false;
				for (it = first_set[s].begin(); it != first_set[s].end(); it++) {
					if (*it != "@") {
						pair<string, string> position;
						position.first = grammer[i].left;
						position.second = *it;
						analysisTable[position] = i;
					}
					else {
						flag = true;
						continue;
					}
				}
				if(!flag)
					break;
			}

		}

		
	}
	return analysisTable;
}


/**
  * function   : display_table
  * description: ����������ڴ�ӡ������
  */
//void Base::display_table() {
//	set<string>::iterator it1, it2;
//
//	for (it1 = term.begin(); it1 != term.end(); it1++) {
//		cout << setw(20) << *it1;
//	}
//	cout << endl;
//
//	for (it2 = non_term.begin(); it2 != non_term.end(); it2++) {
//		for (it1 = term.begin(); it1 != term.end(); it1++)
//		{
//			pair<string, string> temp;
//			temp.first = *it2;
//			temp.second = *it1;
//			if (analysisTable.count(temp) == 0) {
//				cout << setw(20) << "";
//			}
//			else {
//				cout << setw(20);
//				int i = analysisTable[temp];
//				if (i == -1) {
//					cout << setw(20) << "@";
//				}
//				else {
//					for (vector<string>::iterator it = grammer[i].right.begin(); it != grammer[i].right.end(); it++) {
//						cout << *it;
//					}
//				}
//			}
//			cout << endl;
//		}
//	}
//}


/**
  * function   : analysis_Exp()
  * description: �����������ջ�������Ŵ��Ƿ�����﷨�淶
  * return	   : boolean
  * param	   : s
  */
bool Base::analysis_Exp(vector<string> s) {//�������Ŵ�
	stack<string> left;
	int index = 0;
	
	left.push("<program>");

	while (index<s.size()) 
	{
		string exp = s[index]; 
		string leftTop = left.top();

		pair<string, string>temp;
		temp.first = leftTop;
		temp.second = exp;
		if (leftTop==exp) {//����򶼳�ջ
			left.pop();
			index++;
		}	
		else if (analysisTable.count(temp) != 0) {
			left.pop();
			int i = analysisTable[temp];
			if (i == -1) {
				continue;//�մ�
			}
			else {
				vector<string> exchange = grammer[i].right;
				vector<string>::iterator it;
				for (it = exchange.end()-1; it != exchange.begin(); it--) {
					left.push(*it);
				}
				left.push(*it);
			}
		}
		else {
			return false;
		}
	}

	if (left.empty())
		return true;
}



/**
  * function   : parser()
  * description: �﷨����
  */
void Base::parser() {
	scan_grammer("grammer.txt");//ɨ���ķ�
	for (int i = 0; i < grammer_num; i++) {//��first����follow��
		set_first(grammer[i].left);
		set_follow(grammer[i].left);
	}

	map<pair<string, string>, int> table = getTable();//�������ű�
	vector<string> s;
	s.push_back("int"); s.push_back("main"); s.push_back("("); s.push_back(")"); s.push_back("{"); 
	s.push_back("int"); s.push_back("a"); s.push_back("="); s.push_back("4"); s.push_back(";"); s.push_back("}");
	bool flag = analysis_Exp(s);//����
	if (flag) {
		cout <<  "�����﷨�淶" << endl;
	}
	else
		cout << "�������﷨�淶" << endl;
}