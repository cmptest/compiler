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


bool is_nonterm(string s) {
	if (s[0] == '<' && s[s.length() - 1] == '>')
		return true;
	return false;
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
  * description: ����������ڴ�ӡfirst����follow��
  */
void Base::display_firstAndFollow() {
	ofstream fout;
	fout.open("FirstAndFollow.txt");
	fout << "�ķ�first�����£�\n";
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		fout<< std::left<<setw(25) << (*it).first << setw(20) << " first����";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
	}
	fout << "+------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	fout << "�ķ�follow�����£�\n";
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		fout << std::left << setw(25) << (*it).first <<setw(20) <<" follow����";
		for (set<string>::iterator it2 = follow_set[(*it).first].begin(); it2 != follow_set[(*it).first].end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
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
		if (grammer[i].left == "<program>")
			follow_set["<program>"].insert("$");
	}
}






/**
  * function   : getTopToBottomTable
  * description: ��������������϶��¹��������
  * return	   : map<pair<string, string>, int>>
  */
map<pair<string, string>, int> Base::getTopToBottomTable() {
	for (int i = 0; i < grammer_num; i++) 
	{
		for (vector<string>::iterator it0 = grammer[i].right.begin(); it0 != grammer[i].right.end(); it0++) {
			string s = *it0;
			if (is_term(s)) {
				pair<string, string> position;
				position.first = grammer[i].left;
				position.second = s;
				analysisTable_1[position] = i;
				break;
			}
			else if (s == "@" && (it0+1)== grammer[i].right.end()) {
				for (set<string>::iterator it2 = follow_set[grammer[i].left].begin(); it2 != follow_set[grammer[i].left].end(); it2++) {
					pair<string, string> position;
					position.first = grammer[i].left;
					position.second = *it2;
					analysisTable_1[position] = -1;
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
						analysisTable_1[position] = i;
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
	return analysisTable_1;
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
  * function   : analysis_TopToBottom_Exp()
  * description: �����������ջ�������Ŵ��Ƿ�����﷨�淶����ȷ����0�����󷵻��к�
  * return	   : int
  * param	   : s
  */
int Base::analysis_TopToBottom_Exp(vector<Token> s) {//�������Ŵ�(���϶���)
	stack<string> left;
	int index = 0;

	s.push_back(Token(0, "$", s[s.size() - 1].col));
	left.push("$");
	left.push("<program>");

	while (index < s.size()) 
	{
		string exp = s[index].value; 
		string leftTop = left.top();

		pair<string, string>temp;
		temp.first = leftTop;
		temp.second = exp;
		if (leftTop==exp) {//����򶼳�ջ
			left.pop();
			index++;
		}	
		else if (analysisTable_1.count(temp) != 0) {
			left.pop();
			int i = analysisTable_1[temp];
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
			return s[index].col;
		}
	}

	if (left.empty())
		return 0;
	
}



/**
  * function   : analysis_BottomToTop_Exp()
  * description: �����������ջ�������Ŵ��Ƿ�����﷨�淶����ȷ����0�����󷵻��к�
  * return	   : int
  * param	   : s
  */
//int Base::analysis_BottomToTop_Exp(vector<Token> s) {
//
//}




/**
  * function   : parser()
  * description: �﷨����
  */
void Base::parser(vector<Token> tokenList) {
	scan_grammer("Testgrammer.txt");//ɨ���ķ�
	//for (int i = 0; i < grammer_num; i++) {//��first��
	//	set_first(grammer[i].left);		
	//}
	//for (int i = 0; i < grammer_num; i++) {//��follow��
	//	set_follow(grammer[i].left);
	//}
	//
	//display_firstAndFollow();//��ӡfirst����follow��

	//map<pair<string, string>, int> table = getTopToBottomTable();//�������϶��·��ű�
	//
	//int flag = analysis_BottomToTop_Exp(tokenList);//����
	//if (flag==0) {
	//	cout <<  "�����﷨�淶" << endl;
	//}
	//else
	//	cout<<"��"<<flag<<"�в������﷨�淶" << endl;
}

//���ķ�������Ŀ����
void Base:: generateProjectSet() {
	//��ǰ��Ŀ��
	I tmp;
	int id = 0;
	tmp.id = id;
	id++;
	tmp.num = 1;
	tmp.vec.push_back(grammer[0]);
	queue<I> que;//�ȴ���ɵ���Ŀ������
	que.push(tmp);
	while (!que.empty()) {
		tmp = que.front();
		que.pop();

		int size = tmp.vec.size();
		bool first = true;
		set<string> already;
		while (first || size != tmp.vec.size()) {
			first = false;
			size = tmp.vec.size();
			set<string> left;
			for (int i = 0; i < size; i++) {
				node t = tmp.vec[i];//��ǰ�ķ���
				if (t.index < t.right.size()) {//���������ķ�����
					string s = t.right[t.index];
					if (!is_term(s) && already.count(s)==0 ) {//����Ƿ��ս������û�����
						left.insert(t.right[t.index]);//�ѵ��ķ��ս��ķ����żӵ�left��
					}
				}
			}
			for (set<string>::iterator it = left.begin(); it != left.end(); it++) {
				for (int j = 0; j < grammer_num; j++) {
					if (grammer[j].left == *it) {
						tmp.vec.push_back(grammer[j]);
					}
				}
				already.insert(*it);
			}
		}
		//���Ϲ���������Ŀ�����ķ��������湹��ת����ϵ

		set<string> stringSet;
		stringSet.insert("@");
		for (int i = 0; i < tmp.vec.size();i++) {
			node t = tmp.vec[i];//��ǰ�ķ���
			if (t.index < t.right.size()) {//���������ķ�����
				string s = t.right[t.index]; //�ķ�����
				if (stringSet.count(s) == 0) {
					stringSet.insert(s);
				}
				else {
					continue;
				}
				vector<node> mainGrammerOfProjectSet; //��Ŀ������Ҫ�ķ� �������ķ��������ķ��Ƴ�
				for (int j = 0; j < tmp.vec.size(); j++) { //����tmp��Ŀ���ķ���Ѱ�ҵ��Ϊ�ķ�����s���ķ�
					node newT = tmp.vec[j];
					if (newT.index < newT.right.size() && newT.right[newT.index] == s) {
						newT.index++;
						mainGrammerOfProjectSet.push_back(newT);
					}
				}
				//�ж��Ƿ������ɸ���Ŀ����������������Ŀ���ӵ�projectSet����
				int tmpid = 0;
				if (is_existTheI(mainGrammerOfProjectSet,tmpid)) {
					cout << "*******" << tmpid << "*******" << endl;
					tmp.m[s] = tmpid;
				}
				else {
					I newI;
					newI.id = id;
					cout << "*******" << id << "*******" << endl;
					id++;
					newI.vec = mainGrammerOfProjectSet;
					newI.num = mainGrammerOfProjectSet.size();
					que.push(newI);
					tmp.m[s] = newI.id;
				}
			}
		}
		printI(tmp);
		projectSet.push_back(tmp);
	}
}

void Base::printI(I pi) {
	cout << "I" << pi.id << endl;
	vector<node> v = pi.vec;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].left << "->";
		for (int j = 0; j < v[i].right.size(); j++) {
			if (j == v[i].index) cout << ".";
			cout << v[i].right[j] << " ";
		}
		if (v[i].index == v[i].right.size()) cout << ".";
		cout << endl;
	}
	for (map<string, int>::iterator it = pi.m.begin(); it != pi.m.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	cout << endl;
}

bool judgeIs_SameVecOfNode(vector<node> tmp, vector<node> v);
bool judgeIs_SameVecOfString(vector<string> tmps, vector<string> vs);

bool Base::is_existTheI(vector<node> v,int & tmpid) {
	for (int i = 0; i < projectSet.size(); i++) {
		vector<node> tmp(projectSet[i].vec.begin(), projectSet[i].vec.begin() + projectSet[i].num); //tmp.num��v sizeһ���� �ж�tmp��v�ǲ�����ȫһ��
		if (judgeIs_SameVecOfNode(tmp, v)) {
			tmpid = projectSet[i].id;
			return true;
		}
	}
	return false;
}

bool judgeIs_SameVecOfNode(vector<node> tmp, vector<node> v) {
	if (tmp.size() != v.size()) return false;
	for (int j = 0; j < v.size(); j++) {//����һ��v������tmp����û��v[j]
		bool has_vj = false;
		for (int k = 0; k < tmp.size(); k++) {
			if (v[j].index == tmp[k].index && v[j].left == tmp[k].left) {
				vector<string> tmps = tmp[k].right;
				vector<string> vs = v[j].right;
				if (judgeIs_SameVecOfString(tmps, vs)) {
					has_vj = true;
					break;
				}
			}
		}
		//���û�ҵ����Ͳ�һ��
		if (has_vj == false) return false;
	}
	return true;
}

bool judgeIs_SameVecOfString(vector<string> tmps, vector<string> vs) {
	if (tmps.size() == vs.size()) {
		for (int z = 0; z < tmps.size(); z++) {
			if (tmps[z] != vs[z]) {
				return false;
			}
		}
		return true;
	}
	return false;
}