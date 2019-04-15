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
				if (i == n - 2) 
					v.push_back(Token(-1, "未找到与/*相应的*/",col));
				continue;
			}
			else if (t == "//") {
				while (i < n - 1 && s[i] != '\n')
					i++;
				col++;
				continue;
			}
			else if (t == "++") v.push_back(Token(57, "++",col)), i+=2;
			else if (t == "--") v.push_back(Token(56, "--",col)), i += 2;
			else if (t == "+=") v.push_back(Token(29, "+=",col)), i += 2;
			else if (t == "-=") v.push_back(Token(31, "-=",col)), i += 2;
			else if (t == "*=") v.push_back(Token(33, "*=",col)), i += 2;
			else if (t == "/=") v.push_back(Token(35, "/=",col)), i += 2;
			else if (t == "==") v.push_back(Token(37, "==",col)), i += 2;
			else if (t == ">=") v.push_back(Token(39, ">=",col)), i += 2;
			else if (t == ">>") v.push_back(Token(40, ">>",col)), i += 2;
			else if (t == "<=") v.push_back(Token(42, "<=",col)), i += 2;
			else if (t == "<<") v.push_back(Token(43, "<<",col)), i += 2;
		}

		if (isalpha(s[i]) || s[i] == '_') {
			string t(1, s[i++]);
			while (isalnum(s[i]) || s[i] == '_') t += s[i++];
			i--;
			if (m.count(t)) v.push_back(Token(m[t], t,col));
			else v.push_back(Token(1, t,col));
		}
		else if (isdigit(s[i])) {
			string t(1, s[i++]);
			while (isalnum(s[i]) || s[i] == '_' || s[i] == '.') t += s[i++];
			regex r("\\w+day");
		}
		else if (s[i] == ',') v.push_back(Token(44, ",",col));
		else if (s[i] == ';') v.push_back(Token(45, ";",col));
		else if (s[i] == '(') v.push_back(Token(46, "(",col));
		else if (s[i] == ')') v.push_back(Token(47, ")",col));
		else if (s[i] == '{') v.push_back(Token(48, "{",col));
		else if (s[i] == '}') v.push_back(Token(49, "}",col));
		else if (s[i] == '[') v.push_back(Token(50, "[",col));
		else if (s[i] == ']') v.push_back(Token(51, "]",col));
		else if (s[i] == '\'') v.push_back(Token(52, "\'",col));
		else if (s[i] == '\"') v.push_back(Token(53, "\"",col));
		else if (s[i] == '+') v.push_back(Token(28, "+",col));
		else if (s[i] == '-') v.push_back(Token(30, "-",col));
		else if (s[i] == '*') v.push_back(Token(32, "*",col));
		else if (s[i] == '/') v.push_back(Token(34, "/",col));
		else if (s[i] == '>') v.push_back(Token(38, ">",col));
		else if (s[i] == '<') v.push_back(Token(41, "<",col));
		else if (s[i] == '=') v.push_back(Token(36, "=",col));
	}

	if (is_store) {
		ofstream fout;
		fout.open("test.txt");
		for (int i = 0; i < v.size(); i++)
			fout << '<' << v[i].num << ',' << v[i].value << '>' << endl;
	}
	return v;
}