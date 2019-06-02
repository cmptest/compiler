#include "parser.h"

//�ؼ�����Ŀ�͹ؼ���
const int keywordnum = 25;
const string keyword[] = { "break","case","char","const","continue","default","do","double","else","enum",
"extern","float","for","if","int","long","return","short","sizeof","static","struct","switch","void"
"unsigned","while","main" };

/**
  * function   : wordsAnalysis(string filepath)
  * description: �ʷ����������ڴ�ָ��·����ȡ�ַ��������ɴʷ���Ԫ
  * param      : filepath
  * return	   : bool
  */
void Base::wordsAnalysis(string filepath) {
	map<string, int> m;//����keyword��hashmap
	ifstream t(filepath);
	stringstream buffer;
	buffer << t.rdbuf();
	string s = buffer.str();
	//��ʼ��map
	for (int i = 0; i < keywordnum; i++)
		m[keyword[i]] = i + 2;

	int n = s.length();
	int col = 1;
	for (int i = 0; i < n; i++) {

		if (s[i] == '\n') { col++; continue; }
		else if (s[i] == ' ' || s[i] == '\t') continue;
		//�޳�ע�ͣ�// ��/* */
		if (i < n - 2) {
			string t = s.substr(i, 2);
			if (t == "/*") {
				while (i < n - 2 && !(s[i - 1] == '*' && s[i] == '/')) {
					i++;
					if (s[i] == '\n') col++;
				}
				if (i == n - 2)
					words.push_back(Token(-1, "δ�ҵ���/*��Ӧ��*/", col));
				continue;
			}
			else if (t == "//") {
				while (i < n - 1 && s[i] != '\n')
					i++;
				col++;
				continue;
			}
			else if (t == "++") words.push_back(Token(57, "++", col)), i += 2;
			else if (t == "--") words.push_back(Token(56, "--", col)), i += 2;
			else if (t == "+=") words.push_back(Token(29, "+=", col)), i += 2;
			else if (t == "-=") words.push_back(Token(31, "-=", col)), i += 2;
			else if (t == "*=") words.push_back(Token(33, "*=", col)), i += 2;
			else if (t == "/=") words.push_back(Token(35, "/=", col)), i += 2;
			else if (t == "==") words.push_back(Token(37, "==", col)), i += 2;
			else if (t == ">=") words.push_back(Token(39, ">=", col)), i += 2;
			else if (t == ">>") words.push_back(Token(40, ">>", col)), i += 2;
			else if (t == "<=") words.push_back(Token(42, "<=", col)), i += 2;
			else if (t == "<<") words.push_back(Token(43, "<<", col)), i += 2;
		}

		if (isalpha(s[i]) || s[i] == '_') {
			string t(1, s[i++]);
			while (isalnum(s[i]) || s[i] == '_') t += s[i++];
			i--;
			if (m.count(t)) words.push_back(Token(m[t], t, col));
			else words.push_back(Token(1, t, col));
		}
		else if (isdigit(s[i])) {
			string t(1, s[i++]);
			/*while (isalnum(s[i]) || s[i] == '_' || s[i] == '.') t += s[i++];
			regex r("\\w+day");*/

			int dotnum = 0;//С�������
			while (isdigit(s[i]) || s[i] == '.')
			{
				if (s[i] == '.') {
					dotnum++;
				}
				t += s[i++];
			}
			i--;
			if (dotnum == 0) {
				words.push_back(Token(100, t, col));//����
			}
			else if (dotnum == 1) {
				words.push_back(Token(101, t, col));//С��
			}
			else
				words.push_back(Token(-1, "���ֳ���", col));
		}
		else if (s[i] == ',') words.push_back(Token(44, ",", col));
		else if (s[i] == ';') words.push_back(Token(45, ";", col));
		else if (s[i] == '(') words.push_back(Token(46, "(", col));
		else if (s[i] == ')') words.push_back(Token(47, ")", col));
		else if (s[i] == '{') words.push_back(Token(48, "{", col));
		else if (s[i] == '}') words.push_back(Token(49, "}", col));
		else if (s[i] == '[') words.push_back(Token(50, "[", col));
		else if (s[i] == ']') words.push_back(Token(51, "]", col));
		else if (s[i] == '\'') words.push_back(Token(52, "\'", col));
		else if (s[i] == '\"') words.push_back(Token(53, "\"", col));
		else if (s[i] == '+') words.push_back(Token(28, "+", col));
		else if (s[i] == '-') words.push_back(Token(30, "-", col));
		else if (s[i] == '*') words.push_back(Token(32, "*", col));
		else if (s[i] == '/') words.push_back(Token(34, "/", col));
		else if (s[i] == '>') words.push_back(Token(38, ">", col));
		else if (s[i] == '<') words.push_back(Token(41, "<", col));
		else if (s[i] == '=') words.push_back(Token(36, "=", col));
	}
	ofstream fout;
	fout.open("words.txt");
	for (int i = 0; i < words.size(); i++) {
		fout << words[i].col << "\t<" << words[i].num << "," << words[i].value << ">\n";
	}
}


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
		return true;
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
					if ((*it) != grammer[i].left)//������ݹ�
					{
						set_first(*it);//�ݹ���first��
						if (first_set[*it].count("@") == 0)//���������ս���ŵ�first��û��@
						{
							set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(), inserter(first_set[target], first_set[target].begin())); // �󲢼�
							break;
						}
						else {
							set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(), inserter(first_set[target], first_set[target].begin())); // �󲢼�
							first_set[target].erase("@");
						}
					}
					else
						break;
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
	cout << "�ķ�first�����£�\n";
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		cout<< std::left<<setw(25) << (*it).first << setw(20) << " first����";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	cout << "�ķ�follow�����£�\n";
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		cout << std::left << setw(25) << (*it).first <<setw(20) <<" follow����";
		for (set<string>::iterator it2 = follow_set[(*it).first].begin(); it2 != follow_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}


/**
  * function   : set_follow(string target)
  * description: �������������ָ�����ս���ŵ�follow��
  * param	   : target
  */
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
			if ((it + 1) == grammer[i].right.end()) {
				if (*it != grammer[i].left) {
					set_follow(grammer[i].left);
					set_union(follow_set[*it].begin(), follow_set[*it].end(), follow_set[grammer[i].left].begin(), follow_set[grammer[i].left].end(), inserter(follow_set[*it], follow_set[*it].begin())); // �󲢼�
				}
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
						set_union(follow_set[*it].begin(), follow_set[*it].end(), follow_set[*it2].begin(), follow_set[*it2].end(), inserter(follow_set[*it], follow_set[*it].begin())); // �󲢼�
						follow_set[*it].erase("@");
					}
				}
			}

		}
		if (grammer[i].left == "<Begin>")
			follow_set["<Begin>"].insert("$");
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
			if (is_term(s) && s != "@") {	//�ս����
				pair<string, string> position;
				position.first = grammer[i].left;
				position.second = s;
				analysisTable_1[position] = i;
				break;
			}
			else if (s == "@" && (it0 + 1) == grammer[i].right.end()) {
				for (set<string>::iterator it2 = follow_set[grammer[i].left].begin(); it2 != follow_set[grammer[i].left].end(); it2++) {
					pair<string, string> position;
					position.first = grammer[i].left;
					position.second = *it2;
					analysisTable_1[position] = -1;
				}
				analysisTable_1[make_pair(grammer[i].left, "$")] = -1;
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
				if (!flag)
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
void Base::display_Table() {
	set<string>::iterator it1, it2;

	cout << std::left << setw(15) << "";
	for (it1 = term.begin(); it1 != term.end(); it1++) {
		cout << std::left << setw(15) << *it1;
	}
	cout << endl;

	for (it2 = non_term.begin(); it2 != non_term.end(); it2++) {
		cout << std::left << setw(15) << *it2;
		for (it1 = term.begin(); it1 != term.end(); it1++)
		{
			pair<string, string> temp;
			temp.first = *it2;
			temp.second = *it1;
			if (analysisTable_1.count(temp) == 0) {
				cout << std::left << std::left << setw(15) << "";
			}
			else {
				cout << std::left << setw(15);
				int i = analysisTable_1[temp];
				if (i == -1) {
					cout << std::left << setw(15) << "@";
				}
				else {
					for (vector<string>::iterator it = grammer[i].right.begin(); it != grammer[i].right.end(); it++) {
						cout << *it;
					}
				}
			}
		}
		cout << endl;
	}
}


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
	left.push("<Begin>");

	while (index < s.size())
	{
		string exp;
		if (s[index].num == 1)
			exp = "id";
		else if (s[index].num == 100 || s[index].num == 101)
			exp = "num";
		else
			exp = s[index].value;
		string leftTop = left.top();

		pair<string, string>temp;
		temp.first = leftTop;
		temp.second = exp;
		if (leftTop == exp) {//����򶼳�ջ
			cout << "��ջ" << " " << exp << endl;
			left.pop();
			index++;
		}
		else if (analysisTable_1.count(temp) != 0) {
			left.pop();
			int i = analysisTable_1[temp];
			if (i == -1) {
				cout << temp.first << "->@" << endl;
				continue;//�մ�
			}
			else {
				vector<string> exchange = grammer[i].right;
				vector<string>::iterator it;
				cout << grammer[i].left << "->";
				for (it = exchange.begin(); it != exchange.end(); it++) {
					cout << *it;
				}
				cout << endl;
				for (it = exchange.end() - 1; it != exchange.begin(); it--) {
					left.push(*it);
				}
				left.push(*it);
			}
		}
		else {
			cout << "����" << endl;
			return s[index].col;
		}
	}

	if (left.empty())
		return 0;

}




/**
  * function   : parser()
  * description: �﷨����
  */
void Base::parser() {
	scan_grammer("LL1.txt");//ɨ���ķ�
	for (int i = 0; i < grammer_num; i++) {//��first��
		set_first(grammer[i].left);		
	}
	for (int i = 0; i < grammer_num; i++) {//��follow��
		set_follow(grammer[i].left);
	}
	
	display_firstAndFollow();//��ӡfirst����follow��

	getTopToBottomTable();//�������϶��·��ű�
	
	int flag = analysis_TopToBottom_Exp(words);//����
	if (flag==0) {
		cout <<  "�����﷨�淶" << endl;
	}
	else
		cout<<"��"<<flag<<"�в������﷨�淶" << endl;
}

bool judgeIs_SameVecOfNode(vector<node> tmp, vector<node> v);
bool judgeIs_SameVecOfString(vector<string> tmps, vector<string> vs);


/**
  * function   : generateProjectSet()
  * description: ���ķ�������Ŀ����
  */
void Base:: generateProjectSet() {
	//��ǰ��Ŀ��
	I tmp;
	int id = 0;
	tmp.id = id;
	id++;
	tmp.vec.push_back(grammer[0]);
	queue<I> que;//�ȴ���ɵ���Ŀ������
	que.push(tmp);

	vector<vector<node> > vecv;//
	vecv.push_back(tmp.vec);
	map<int, vector<node> > mapvi;
	mapvi[tmp.id] = tmp.vec;

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
					if (!is_term(s) && already.count(s)==0) {//����Ƿ��ս������û�����
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
		//stringSet.insert("@");
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
				//if (mainGrammerOfProjectSet.size() == 0) continue;
				//�ж��Ƿ������ɸ���Ŀ����������������Ŀ���ӵ�projectSet����
				bool exist = false;
				for (int j = 0; j < vecv.size(); j++) {
					if (judgeIs_SameVecOfNode(vecv[j], mainGrammerOfProjectSet)) {
						exist = true;
						break;
					}
				}
				if (exist) {
					int id = -1;
					for (map<int, vector<node> >::iterator it = mapvi.begin(); it != mapvi.end(); it++) {
						if (judgeIs_SameVecOfNode(it->second, mainGrammerOfProjectSet)) {
							id = it->first;
							break;
						}
					}
					if (id == -1) cout << "mapvi����" << endl;
					tmp.m[s] = id;
				}
				else {
					I newI;
					newI.id = id;
					tmp.m[s] = newI.id;
					id++;
					newI.vec = mainGrammerOfProjectSet;
					que.push(newI);
					vecv.push_back(mainGrammerOfProjectSet);
					mapvi[newI.id] = mainGrammerOfProjectSet;
				}
			}
		}
		printI(tmp);
		projectSet.push_back(tmp);
	}
}
/**
  * function   : printI(I pi)
  * description: ��ӡ��Ŀ��
  * param :pi
  */
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



//bool Base::is_existTheI(vector<node> v,int & tmpid,I tmp) {
//	vector<node> vec(tmp.vec.begin(),tmp.vec.begin() + tmp.num); //tmp.num��v sizeһ���� �ж�tmp��v�ǲ�����ȫһ��
//	if (judgeIs_SameVecOfNode(vec, v)) {
//		tmpid = tmp.id;
//		return true;
//	}
//
//	for (int i = 0; i < projectSet.size(); i++) {
//		vector<node> tmp(projectSet[i].vec.begin(), projectSet[i].vec.begin() + projectSet[i].num); //tmp.num��v sizeһ���� �ж�tmp��v�ǲ�����ȫһ��
//		if (judgeIs_SameVecOfNode(tmp, v)) {
//			tmpid = projectSet[i].id;
//			return true;
//		}
//	}
//	return false;
//}
//��������
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
//��������
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

void Base::generateSL0Table() {
	for (int i = 0; i < projectSet.size(); i++) {
		I currentI = projectSet[i];
		for (int j = 0; j < currentI.vec.size(); j++) {
			node currentNode = currentI.vec[j];
			if (currentNode.index == 1 && currentNode.left == grammer[0].left &&
				currentNode.right.size() == 1 && currentNode.right[0] == grammer[0].right[0]) {
				ACTION[make_pair(currentI.id, "$")] = make_pair("acc", -1);
			}
			if (currentNode.index < currentNode.right.size()) {
				string a = currentNode.right[currentNode.index];
				if (is_term(a) && currentI.m.count(a) != 0) {
					ACTION[make_pair(currentI.id, a)] = make_pair("s", currentI.m[a]);
				}
			}
			else if (currentNode.index == currentNode.right.size()) {
				//set_follow(currentNode.left);
				set<string> s = follow_set[currentNode.left];
				for (set<string>::iterator it = s.begin(); it != s.end(); it++) {
					int id;
					//Ѱ�ҹ�Լ����ʽ��id��
					for (id = 0; id < grammer_num; id++) {
						if (currentNode.left == grammer[id].left &&
							judgeIs_SameVecOfString(currentNode.right, grammer[id].right)) break;
					}
					if (id == 0) continue;//����һ������ʽ��Լ��Ϊacc,���ù�
					if (id == grammer_num) cout << "û���ҵ���Լ����ʽ" << endl;
					ACTION[make_pair(currentI.id, *it)] = make_pair("r", id);
				}
			}
		}
		for (map<string, int>::iterator it = currentI.m.begin(); it != currentI.m.end(); it++) {
			if (!is_term(it->first)) {
				GOTO[make_pair(currentI.id, it->first)] = it->second;
			}
		}
	}
}

void Base::printSL0Table() {
	vector<vector<string>> SL0Table;
	int id = 0;
	vector<string> symbol;
	//symbol.push_back("״̬");
	map<string, int> symbolToId;
	for (set<string>::iterator it = term.begin(); it != term.end(); it++) {
		symbol.push_back(*it);
		symbolToId[*it] = id;
		id += 1;
	}
	symbol.push_back("$");
	symbolToId["$"] = id;
	id += 1;
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		symbol.push_back(*it);
		symbolToId[*it] = id;
		id += 1;
	}
	//SL0Table.push_back(symbol);
	for (int i = 0; i < projectSet.size(); i++) {
		vector<string> vec;
		for (int j = 0;j<term.size()+1;j++) {
			if (ACTION.count(make_pair(i, symbol[j])) != 0) {
				pair<string,int> p = ACTION[make_pair(i, symbol[j])];
				if (p.first == "acc") vec.push_back(p.first);
				else vec.push_back(p.first+to_string(p.second));
			}
			else vec.push_back(" ");
		}

		for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
			if (GOTO.count(make_pair(i, *it)) != 0) {
				vec.push_back(to_string(GOTO[make_pair(i, *it)]));
			}
			else vec.push_back(" ");
		}
		SL0Table.push_back(vec);
	}

	cout << setw(5) << setfill(' ') << "state";
	for (int j = 0; j < symbol.size(); j++) {
		cout << setw(5) << setfill(' ') << symbol[j];
	}
	cout << endl;
	for (int i = 0; i < SL0Table.size(); i++) {
		cout << setw(5) << setfill(' ') << i;
		for (int j = 0; j < SL0Table[j].size(); j++) {
			cout << setw(5) << setfill(' ') <<SL0Table[i][j];
		}
		cout << endl;
	}
}

//����first����follow������������ļ�FirstAndFolllow.txt��
void Base::generate_FirstAndFollow() {
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_first(*it);
	}
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_follow(*it);
	}
	cout << "first��" << endl;
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		cout << std::left << setw(20) << it->first << ":";
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << "+-------------------------------------------------------------+\n";
	cout << "follow��" << endl;
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		cout << std::left << setw(20) << it->first << ":";
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	/*ofstream fout;
	fout.open("FirstAndFollow.txt");
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_first(*it);
	}
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_follow(*it);
	}
	fout << "first��" << endl;
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		fout << std::left <<setw(20) << it->first << ":";
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
	}
	fout << "+-------------------------------------------------------------+\n";
	fout << "follow��" << endl;
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		fout <<std::left << setw(20) << it->first << ":";
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
	}*/
}

void printSta(stack<pair<string, Token>> s) {
	stack<pair<string, Token>> ss;
	while (!s.empty()) {
		ss.push(s.top());
		s.pop();
	}
	while (!ss.empty()) {
		cout << ss.top().first << " ";
		ss.pop();
	}
}

Token ViewInStack(stack<pair<string, Token>> s,int n) {
	while (n--) {
		s.pop();
	}
	return s.top().second;
}



void Base::SL0GrammaAnalysis() {
	string tempType;//��ʱ��������
	stack<int> idSta;//����״̬��
	idSta.push(0);
	vector<Token> vec = words;//���봮
	string a = vec[0].value;

	vector<Token> L;//�ķ�L�����id��
	stack<pair<string,Token>> sta;	//�����������Լ��ķ��ţ�id��num��Token����Ϣ
	vec.push_back(Token(0, "$", 0));
	
	map<string,Token> m;//����m["E"] = Token,�õ��кź�ֵ

	map<string, string> let;//���ű�����let["a"] = "int"
	int index = 0;
	int T = 0;
	while (true) {
		int s = idSta.top();
		if (ACTION[make_pair(s, a)].first == "s") {
			printSta(sta);
			idSta.push(ACTION[make_pair(s, a)].second);
			if (vec[index].num == 1)
				a = "id";
			else if (vec[index].num == 100) {
				a = "num";
				let[vec[index].value] = "int";
			}
			else if (vec[index].num == 101) {
				a = "num";
				let[vec[index].value] = "float";
			}
			else
				a = vec[index].value;
			sta.push(make_pair(a,vec[index]));
			index += 1;
			
			cout << "����" << endl;
			if (vec[index].num == 1)
				a = "id";
			else if (vec[index].num == 100) {
				a = "num";
				let[vec[index].value] = "int";
			}
			else if (vec[index].num == 101) {
				a = "num";
				let[vec[index].value] = "float";
			}
			else
				a = vec[index].value;
		}
		else if (ACTION[make_pair(s, a)].first == "r") {
			printSta(sta);

			int num = ACTION[make_pair(s, a)].second;
			int size = grammer[num].right.size();

			//���嶯������
			
			if (num == 20 || num == 19) {
				m["F"] = sta.top().second;
				m["F"].type = let[sta.top().second.value];
			}
			else if (num == 18) {
				m["F"] = m["E"];
			}
			else if (num == 17) {
				m["T"] = m["F"];
			}
			else if (num == 16) {
				T++;
				vector<string> s = { "/",m["T"].value,m["F"].value,"T" + to_string(T) };
				GEN.push_back(s);
				if (m["F"].type == "float" || m["T"].type == "float")
					tempType = "float";
				else
					tempType = "int";
				m["T"] = Token(0, "T" + to_string(T), 0);
				m["T"].type = tempType;
			}
			else if (num == 15) {
				T++;
				vector<string> s = { "*",m["T"].value,m["F"].value,"T" + to_string(T) };
				GEN.push_back(s);
				if (m["F"].type == "float" || m["T"].type == "float")
					tempType = "float";
				else
					tempType = "int";
				m["T"] = Token(0, "T" + to_string(T), 0);
				m["T"].type = tempType;
			}
			else if (num == 14) {
				m["E"] = m["T"];
			}
			else if (num == 13) {
				T++;
				vector<string> s = { "-",m["E"].value,m["T"].value,"T" + to_string(T) };
				GEN.push_back(s);
				if (m["E"].type == "float" || m["T"].type == "float")
					tempType = "float";
				else
					tempType = "int";
				m["E"] = Token(0, "T" + to_string(T), 0);
				m["E"].type = tempType;
			}
			else if (num == 12) {
				T++;
				vector<string> s = { "+",m["E"].value,m["T"].value,"T" + to_string(T) };
				GEN.push_back(s);
				if (m["E"].type == "float" || m["T"].type == "float")
					tempType = "float";
				else
					tempType = "int";
				m["E"] = Token(0, "T" + to_string(T), 0);
				m["E"].type = tempType;
			}
			else if (num == 11) {
				m["L"] = sta.top().second;
				L.push_back(sta.top().second);
			}
			else if (num == 10) {
				L.push_back(ViewInStack(sta, 2));
			}
			else if (num == 9) {
				m["type"] = Token(0, "float", 0);
			}
			else if (num == 8) {
				m["type"] = Token(0, "int", 0);
			}
			else if (num == 7) {
				m["D"] = m["L"];
				m["D"].type = let[L[0].value];
			}
			else if (num == 6) {
				m["D"] = m["L"];
				for (int i = 0; i < L.size(); i++) {
					if (let.count(L[i].value)) {
						is_right = false;
						false_mes = "��" + to_string(L[i].col) + "�У�" + L[i].value + "�ظ�����";
						return;
					}
					let[L[i].value] = m["type"].value;
				}
				m["D"].type = m["type"].value;
			}
			else if (num == 5) {
				L.clear();
			}else if (num == 4) {
				string s1 = m["E"].type, s2 = m["D"].type;
				if (s2 == "int" && s1 == "float") {
					is_right = false;
					false_mes = "��" + to_string(m["D"].col) + "�У��޷���" + s1 + "���͸�ֵ��" + m["D"].value;
					return;
				}
				vector<string> s = { "=",m["E"].value,"_",m["D"].value };
				GEN.push_back(s);
				L.clear();
			}

			while (size--) {
				idSta.pop();
				sta.pop();
			}
			size = grammer[num].right.size();
			sta.push(make_pair(grammer[num].left,Token(0,"",0)));
			int t = idSta.top();
			idSta.push(GOTO[make_pair(t, grammer[num].left)]);
			cout << "����" << grammer[num].left << "->";
			for (int j = 0; j < grammer[num].right.size(); j++) {
				cout << grammer[num].right[j];
			}
			cout << "��Լ" << endl;
		}
		else if (ACTION[make_pair(s, a)].first == "acc") {
			cout << "����" << endl;
			break;
		}
		else {
			cout << "��" << vec[index].col << "��" << vec[index].value << "�޷���Լ" << endl;
			break;
		}
	}
}



void Base::printGENOrFalseMes() {
	cout << endl;
	for (int i = 0; i < GEN.size(); i++) {
		cout << "(" << GEN[i][0] << "," << GEN[i][1] << "," << GEN[i][2] << "," << GEN[i][3] << ")" << endl;
	}
	if (!is_right) cout << false_mes;
}

