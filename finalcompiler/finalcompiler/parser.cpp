#include "parser.h"




/**
  * function   : is_term(string s)
  * description: Õâ¸ö·½·¨ÓÃÓÚÅĞ¶Ï×Ö·û´®ÊÇ·ñÊÇÖÕ½á·ûºÅ
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
  * description: Õâ¸ö·½·¨ÓÃÓÚ´ÓÎÄ¼ş¶ÁÈëÎÄ·¨£¬³õÊ¼»¯grammer[100], term, non_term
  * param      : filePath
  */

void Base::scan_grammer(string filePath) {
	ifstream t(filePath);
	string line = "";
	int index = 0;//grammer[100]ÏÂ±ê
	while (getline(t, line)) //ÖğĞĞ¶ÁÈ¡ÎÄ·¨
	{
		line += " ";
		bool isleft = true;//ÊÇ·ñÊÇÎÄ·¨×ó²¿
		for (int i = 0, j = 0; i < line.length();) {//Í¨¹ı¿Õ¸ñ·Ö¸îÎÄ·¨×Ö·û´®
			
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

			//ÎÄ·¨×ó²¿
			else if (line[i] == ' ' && isleft) {
				string temp = line.substr(j, i-j);
				grammer[index].left = temp;
				j = i + 1;
				i++;
			}

			//ÎÄ·¨ÓÒ²¿
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

	//³õÊ¼»¯ÖÕ½á·ûºÅºÍ·ÇÖÕ½á·ûºÅ±í
	for (int i = 0; i < index; i++) {
		non_term.insert(grammer[i].left);
		for (vector<string>::iterator it = grammer[i].right.begin(); it!= grammer[i].right.end(); it++) {
			if (is_term(*it))
				term.insert(*it);//²åÈëÖÕ½á·ûºÅ
			else
				non_term.insert(*it);//²åÈë·ÇÖÕ½á·ûºÅ
		}
	}

	//Êä³öÎÄ·¨
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
  * description: Õâ¸ö·½·¨ÓÃÓÚÇóÖ¸¶¨·ÇÖÕ½á·ûºÅµÄfirst¼¯
  * param	   : target
  */

void Base::set_first(string target) {
	
	//Æ¥ÅäÎÄ·¨×ó²¿
	for (int i = 0; i < grammer_num; i++) {
		if (grammer[i].left == target) {	
			int num = grammer[i].right.size();
			for (vector<string>::iterator it = grammer[i].right.begin(); it != grammer[i].right.end(); it++) {
				
				//ÖÕ½á·ûºÅ
				if (is_term(*it)) {
					first_set[target].insert(*it);
					break;
				}

				//¿Õ´®
				else if (*it == "@") {
					if ((it + 1) == grammer[i].right.end())//×îºóÒ»¸ö×Ö·û´®
						first_set[target].insert("@");
				}

				//·ÇÖÕ½á·ûºÅ
				else {
					set_first(*it);//µİ¹éÇófirst¼¯
					if (first_set[*it].count("@") == 0)//Èç¹ûÕâ¸ö·ÇÖÕ½á·ûºÅµÄfirst¼¯Ã»ÓĞ@
					{
						set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(),inserter(first_set[target], first_set[target].begin())); // Çó²¢¼¯
						break;
					}
					else {
						set_union(first_set[target].begin(), first_set[target].end(), first_set[*it].begin(), first_set[*it].end(), inserter(first_set[target], first_set[target].begin())); // Çó²¢¼¯
						first_set[target].erase("@");
					}
				}
			}
		}
	}
}

/**
  * function   : display_first()
  * description: Õâ¸ö·½·¨ÓÃÓÚ´òÓ¡first¼¯ºÍfollow¼¯
  */
void Base::display_firstAndFollow() {
	ofstream fout;
	fout.open("FirstAndFollow.txt");
	fout << "ÎÄ·¨first¼¯ÈçÏÂ£º\n";
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		fout<< std::left<<setw(25) << (*it).first << setw(20) << " first¼¯£º";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
	}
	fout << "+------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	fout << "ÎÄ·¨follow¼¯ÈçÏÂ£º\n";
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		fout << std::left << setw(25) << (*it).first <<setw(20) <<" follow¼¯£º";
		for (set<string>::iterator it2 = follow_set[(*it).first].begin(); it2 != follow_set[(*it).first].end(); it2++) {
			fout << *it2 << " ";
		}
		fout << endl;
	}
}


/**
  * function   : set_follow(string target)
  * description: Õâ¸ö·½·¨ÓÃÓÚÇóÖ¸¶¨·ÇÖÕ½á·ûºÅµÄfollow¼¯
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
			//ÓÒ±ßÎª¿Õ´®
			if (it == grammer[i].right.end()) {
				set_follow(grammer[i].left);
				follow_set[*it] = follow_set[grammer[i].left];
			}
			//ÓÒ±ß²»Îª¿Õ
			else {
				vector<string>::iterator it2;
				for (it2 = it + 1; it2 != grammer[i].right.end(); it2++) {
					if (is_term(*it2)) {
						follow_set[*it].insert(*it2);
						break;
					}
					else if (first_set[*it2].count("@") == 0)
					{
						set_union(follow_set[*it].begin(), follow_set[*it].end(), first_set[*it2].begin(), first_set[*it2].end(), inserter(follow_set[*it], follow_set[*it].begin())); // Çó²¢¼¯
						break;
					}
					else {						
						set_union(follow_set[*it].begin(), follow_set[*it].end(), first_set[*it2].begin(), first_set[*it2].end(), inserter(follow_set[*it], follow_set[*it].begin())); // Çó²¢¼¯
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
  * description: Õâ¸ö·½·¨ÓÃÓÚ×ÔÉÏ¶øÏÂ¹¹Ôì·ÖÎö±í
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
  * description: Õâ¸ö·½·¨ÓÃÓÚ´òÓ¡·ÖÎö±í
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
  * description: Õâ¸ö·½·¨ÀûÓÃÕ»·ÖÎö·ûºÅ´®ÊÇ·ñ·ûºÏÓï·¨¹æ·¶£¬ÕıÈ··µ»Ø0£¬´íÎó·µ»ØĞĞºÅ
  * return	   : int
  * param	   : s
  */
int Base::analysis_TopToBottom_Exp(vector<Token> s) {//·ÖÎö·ûºÅ´®(×ÔÉÏ¶øÏÂ)
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
		if (leftTop==exp) {//ÏàµÈÔò¶¼³öÕ»
			left.pop();
			index++;
		}	
		else if (analysisTable_1.count(temp) != 0) {
			left.pop();
			int i = analysisTable_1[temp];
			if (i == -1) {
				continue;//¿Õ´®
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
  * description: Õâ¸ö·½·¨ÀûÓÃÕ»·ÖÎö·ûºÅ´®ÊÇ·ñ·ûºÏÓï·¨¹æ·¶£¬ÕıÈ··µ»Ø0£¬´íÎó·µ»ØĞĞºÅ
  * return	   : int
  * param	   : s
  */
//int Base::analysis_BottomToTop_Exp(vector<Token> s) {
//
//}




/**
  * function   : parser()
  * description: Óï·¨·ÖÎö
  */
void Base::parser(vector<Token> tokenList) {
	scan_grammer("Testgrammer.txt");//É¨ÃèÎÄ·¨
	//for (int i = 0; i < grammer_num; i++) {//Çófirst¼¯
	//	set_first(grammer[i].left);		
	//}
	//for (int i = 0; i < grammer_num; i++) {//Çófollow¼¯
	//	set_follow(grammer[i].left);
	//}
	//
	//display_firstAndFollow();//´òÓ¡first¼¯ºÍfollow¼¯

	//map<pair<string, string>, int> table = getTopToBottomTable();//¹¹½¨×ÔÉÏ¶øÏÂ·ûºÅ±í
	//
	//int flag = analysis_BottomToTop_Exp(tokenList);//·ÖÎö
	//if (flag==0) {
	//	cout <<  "·ûºÏÓï·¨¹æ·¶" << endl;
	//}
	//else
	//	cout<<"µÚ"<<flag<<"ĞĞ²»·ûºÏÓï·¨¹æ·¶" << endl;
}

bool judgeIs_SameVecOfNode(vector<node> tmp, vector<node> v);
bool judgeIs_SameVecOfString(vector<string> tmps, vector<string> vs);

//ÓÉÎÄ·¨Éú³ÉÏîÄ¿¼¯´Ø
void Base:: generateProjectSet() {
	//µ±Ç°ÏîÄ¿¼¯
	I tmp;
	int id = 0;
	tmp.id = id;
	id++;
	tmp.vec.push_back(grammer[0]);
	queue<I> que;//µÈ´ıÍê³ÉµÄÏîÄ¿¼¯¶ÓÁĞ
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
				node t = tmp.vec[i];//µ±Ç°ÎÄ·¨£»
				if (t.index < t.right.size()) {//Èç¹ûµãºóÓĞÎÄ·¨·ûºÅ
					string s = t.right[t.index];
					if (!is_term(s) && already.count(s)==0 ) {//Èç¹ûÊÇ·ÇÖÕ½á·ûºÅÇÒÃ»±»Ìí¼Ó
						left.insert(t.right[t.index]);//°ÑµãºóµÄ·ÇÖÕ½áÎÄ·¨·ûºÅ¼Óµ½leftÀï
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
		//ÒÔÉÏ¹¹½¨ÍêÁËÏîÄ¿¼¯µÄÎÄ·¨¼¯£¬ÏÂÃæ¹¹½¨×ª»¯¹ØÏµ

		set<string> stringSet;
		stringSet.insert("@");
		for (int i = 0; i < tmp.vec.size();i++) {
			node t = tmp.vec[i];//µ±Ç°ÎÄ·¨£»
			if (t.index < t.right.size()) {//Èç¹ûµãºóÓĞÎÄ·¨·ûºÅ
				string s = t.right[t.index]; //ÎÄ·¨·ûºÅ
				if (stringSet.count(s) == 0) {
					stringSet.insert(s);
				}
				else {
					continue;
				}
				vector<node> mainGrammerOfProjectSet; //ÏîÄ¿¼¯µÄÖ÷ÒªÎÄ·¨ £¬ÆäËûÎÄ·¨¿ÉÓÉÖ÷ÎÄ·¨ÍÆ³ö
				for (int j = 0; j < tmp.vec.size(); j++) { //±éÀútmpÏîÄ¿¼¯ÎÄ·¨£¬Ñ°ÕÒµãºóÎªÎÄ·¨·ûºÅsµÄÎÄ·¨
					node newT = tmp.vec[j];
					if (newT.index < newT.right.size() && newT.right[newT.index] == s) {
						newT.index++;
						mainGrammerOfProjectSet.push_back(newT);
					}
				}
				//ÅĞ¶ÏÊÇ·ñÒÑÉú³É¸ÃÏîÄ¿¼¯£¬·ñÔòÉú³ÉĞÂÏîÄ¿¼¯¼Óµ½projectSetÀïÃæ
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
					if (id == -1) cout << "mapvi´íÎó" << endl;
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
//	vector<node> vec(tmp.vec.begin(),tmp.vec.begin() + tmp.num); //tmp.numºÍv sizeÒ»Ñùºó ÅĞ¶ÏtmpºÍvÊÇ²»ÊÇÍêÈ«Ò»Ñù
//	if (judgeIs_SameVecOfNode(vec, v)) {
//		tmpid = tmp.id;
//		return true;
//	}
//
//	for (int i = 0; i < projectSet.size(); i++) {
//		vector<node> tmp(projectSet[i].vec.begin(), projectSet[i].vec.begin() + projectSet[i].num); //tmp.numºÍv sizeÒ»Ñùºó ÅĞ¶ÏtmpºÍvÊÇ²»ÊÇÍêÈ«Ò»Ñù
//		if (judgeIs_SameVecOfNode(tmp, v)) {
//			tmpid = projectSet[i].id;
//			return true;
//		}
//	}
//	return false;
//}
//±ãÀûº¯Êı
bool judgeIs_SameVecOfNode(vector<node> tmp, vector<node> v) {
	if (tmp.size() != v.size()) return false;
	for (int j = 0; j < v.size(); j++) {//±éÀúÒ»±év£¬¿´¿´tmpÀïÓĞÃ»ÓĞv[j]
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
		//Èç¹ûÃ»ÕÒµ½£¬¾Í²»Ò»Ñù
		if (has_vj == false) return false;
	}
	return true;
}
//±ãÀûº¯Êı
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
<<<<<<< HEAD
				set_follow(currentNode.left);
=======
				//set_follow(currentNode.left);
>>>>>>> æœ€æ–°
				set<string> s = follow_set[currentNode.left];
				for (set<string>::iterator it = s.begin(); it != s.end(); it++) {
					int id;
					//Ñ°ÕÒ¹æÔ¼²úÉúÊ½µÄid£»
					for (id = 0; id < grammer_num; id++) {
						if (currentNode.left == grammer[id].left &&
							judgeIs_SameVecOfString(currentNode.right, grammer[id].right)) break;
					}
					if (id == grammer_num) cout << "Ã»ÓĞÕÒµ½¹éÔ¼²úÉúÊ½" << endl;
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
	//symbol.push_back("×´Ì¬");
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

	cout << setw(6) << setfill(' ') << "×´Ì¬";
	for (int j = 0; j < symbol.size(); j++) {
		cout << setw(6) << setfill(' ') << symbol[j];
	}
	cout << endl;
	for (int i = 0; i < SL0Table.size(); i++) {
		cout << setw(6) << setfill(' ') << i;
		for (int j = 0; j < SL0Table[j].size(); j++) {
			cout << setw(6) << setfill(' ') <<SL0Table[i][j];
		}
		cout << endl;
	}
}

void Base::generate_FirstAndFollow() {
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_first(*it);
	}
	for (set<string>::iterator it = non_term.begin(); it != non_term.end(); it++) {
		set_follow(*it);
	}
	cout << "first¼¯" << endl;
	for (map<string, set<string>>::iterator it = first_set.begin(); it != first_set.end(); it++) {
		cout << it->first << ":" << endl;
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << "follow¼¯" << endl;
	for (map<string, set<string>>::iterator it = follow_set.begin(); it != follow_set.end(); it++) {
		cout << it->first << ":" << endl;
		for (set<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}
