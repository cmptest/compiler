#include "wordsAnalysis.h"
map<string, int> m;//保存keyword得hashmap

const string keyword[] = { "break","case","char","const","continue","default","do","double","else","enum",
"extern","float","for","if","int","long","retrun","short","sizeof","static","struct","switch","void"
"unsigned","while" };
string scanffile(string filepath) {
	return NULL;
}
vector<Token> wordsAnalysis(string filepath, bool is_store) {
	ifstream t(filepath);
	stringstream buffer;
	buffer << t.rdbuf();
	string s = buffer.str();
	vector<Token> v;
	//初始化map
	for (int i = 0; i < keyword->length(); i++) 
		m[keyword[i]] = i + 2;
	int n = s.length();
	int col = 1;
	for (int i = 0; i <n; i++) {
		if (s[i] == '\n') {col++; continue;}
		else if (s[i] == ' '||s[i] == '\t') continue;
		//剔除注释，// 和/* */
		if (i < n - 2) {
			string t = s.substr(i, 2);
			if (t == "/*") {
				while (i < n - 2 && !(s[i-1] == '*' && s[i] == '/')) {
					i++;
					if (s[i] == '\n') col++;
				}
				if (i == n - 2) {
					cout << "为找到与/*相应的*/" << endl; return v;
				}
				continue;
			}
			else if (t == "//") {
				while (i < n - 1 && s[i] != '\n')
					i++;
				col++;
				continue;
			}
			else if (t == "++") v.push_back(Token(57, "++")), i+=2;
			else if (t == "--") v.push_back(Token(56, "--")), i += 2;
			else if (t == "+=") v.push_back(Token(29, "+=")), i += 2;
			else if (t == "-=") v.push_back(Token(31, "-=")), i += 2;
			else if (t == "*=") v.push_back(Token(33, "*=")), i += 2;
			else if (t == "/=") v.push_back(Token(35, "/=")), i += 2;
			else if (t == "==") v.push_back(Token(37, "==")), i += 2;
			else if (t == ">=") v.push_back(Token(39, ">=")), i += 2;
			else if (t == ">>") v.push_back(Token(40, ">>")), i += 2;
			else if (t == "<=") v.push_back(Token(42, "<=")), i += 2;
			else if (t == "<<") v.push_back(Token(43, "<<")), i += 2;
		}

		if (isalpha(s[i]) || s[i] == '_') {
			string t(1, s[i++]);
			while (isalnum(s[i]) || s[i] == '_') t += s[i++];
			i--;
			if (m.count(t)) v.push_back(Token(m[t], t));
			else v.push_back(Token(1, t));
		}
		else if (isdigit(s[i])) {
			double t = s[i++] - '0';
			int numlen = 1;
			while (isdigit(s[i]))
				t = t * 10 + s[i++] - '0', numlen++;
			if (s[i] == '.') {
				double num = 10;
				i++, numlen++;
				while (isdigit(s[i])) {
					t += (s[i++] - '0') / num;
					num *= 10;
					numlen++;
				}
				if (isalpha(s[i])) {
					cout <<"在第" << col++ << "行无法识别" << to_string(t).substr(0,numlen) + s[i] << "为字符串或数字" << endl;
					return v;
				}
				v.push_back(Token(2,to_string(t)));
			}
			else if (isalpha(s[i])) {
				cout << "在第" << col++ << "行无法识别" << to_string(t).substr(0, numlen) + s[i] << "为字符串或数字" << endl;
				return v;
			}
			else v.push_back(Token(2, to_string(int(t))));
			i--;
		}
		else if (s[i] == ',') v.push_back(Token(44, ","));
		else if (s[i] == ';') v.push_back(Token(45, ";"));
		else if (s[i] == '(') v.push_back(Token(46, "("));
		else if (s[i] == ')') v.push_back(Token(47, ")"));
		else if (s[i] == '{') v.push_back(Token(48, "{"));
		else if (s[i] == '}') v.push_back(Token(49, "}"));
		else if (s[i] == '[') v.push_back(Token(50, "["));
		else if (s[i] == ']') v.push_back(Token(51, "]"));
		else if (s[i] == '\'') v.push_back(Token(52, "\'"));
		else if (s[i] == '\"') v.push_back(Token(53, "\""));
		else if (s[i] == '+') v.push_back(Token(28, "+"));
		else if (s[i] == '-') v.push_back(Token(30, "-"));
		else if (s[i] == '*') v.push_back(Token(32, "*"));
		else if (s[i] == '/') v.push_back(Token(34, "/"));
		else if (s[i] == '>') v.push_back(Token(38, ">"));
		else if (s[i] == '<') v.push_back(Token(41, "<"));
		else if (s[i] == '=') v.push_back(Token(36, "="));
	}

	if (is_store) {
		ofstream fout;
		fout.open("test.txt");
		for (int i = 0; i < v.size(); i++)
			fout << '<' << v[i].num << ',' << v[i].value << '>' << endl;
	}
	return v;
}