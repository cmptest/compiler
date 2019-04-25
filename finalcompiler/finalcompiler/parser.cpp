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
		int k = 0;
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
				k = 0;
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
				grammer[index].right[k++] = temp;
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
		for (int j = 0; j < 100; j++) {
			if (is_term(grammer[i].right[j]))
				term.insert(grammer[i].right[j]);//�����ս����
			else
				non_term.insert(grammer[i].right[j]);//������ս����
		}
	}

	//����ķ�
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
		cout << (*it).first << " first����";
		for (set<string>::iterator it2 = first_set[(*it).first].begin(); it2 != first_set[(*it).first].end(); it2++) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
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
			if (is_term(grammer[i].right[0])) {
				first_set[target].insert(grammer[i].right[0]);//����Ҳ���һ���ַ������ս���ţ���ֱ�Ӳ���
			}
			else {
				set_first(grammer[i].right[0]);//����Ƿ��ս���ţ��ݹ���first��
				first_set[target] = first_set[grammer[i].right[0]];
			}
		}
	}
}


/**
  * function   : set_follow(string target)
  * description: �������������ָ�����ս���ŵ�follow��
  * param	   : target
  */

void Base::set_follow(string target) {

}