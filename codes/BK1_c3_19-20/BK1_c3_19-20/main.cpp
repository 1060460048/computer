#include<iostream>
#include <string>
#include<vector>
using namespace std;
int operPriority(char a);
int main(){
	string oper_str;
	cout<<"��������ʽ"<<endl;
	cin>>oper_str;
	cout<<"������ʽΪ:"<<oper_str<<endl;
	vector<string>result_vec;
	vector<string>opera_vec;
	string temp_str="";
	for(unsigned i=0; i<oper_str.length();i++ ){
		if(oper_str[i]>='0' && oper_str[i]<='9'){//����
			temp_str += oper_str[i];
		}else{
			if(temp_str.length()>0){
				result_vec.push_back(temp_str);
				temp_str = "";
			}
			int cur_prio = operPriority(oper_str[i]);
			if(cur_prio==0){
				cout<<"���ʽ��������"<<endl;
				break;
			}else if(oper_str[i]==')'){
				vector<string>::iterator it;
				bool is_find = false;
				for(it=opera_vec.end();it!=opera_vec.begin();it--){
					cout<<*it<<endl;
					if(1){
						result_vec.push_back(*it);
						opera_vec.erase(it);
					}else{
						opera_vec.erase(it);
						is_find = true;
						break;
					}
				}

				if(!is_find){
					cout<<"���ʽ1��������"<<endl;
					break;
				}
			}else{
				vector<string>::iterator it;
				for(it=opera_vec.end();it!=opera_vec.begin();it--){
					string it_str = *it;
					int temp_prio = operPriority(it_str[0]);
					if(temp_prio>=cur_prio){
						result_vec.push_back(*it);
						opera_vec.erase(it);
					}else{
						break;
					}
				}
				string op_str = "";
				op_str+= oper_str[i];
				opera_vec.push_back(op_str);
			}
		}
	}
	system("pause");
	return 0;
}

int operPriority(char a){
	if(a=='+'||a=='-'){
		return 1;
	}else if(a=='*'||a=='/'){
		return 2;
	}else if(a=='^'){
		return 3;
	}else if(a=='(' || a==')'){
		return 4;
	}else{
		return 0;
	}
}