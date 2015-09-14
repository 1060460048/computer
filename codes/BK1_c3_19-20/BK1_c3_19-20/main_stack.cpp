#include<iostream>
#include <string>
#include<stack>
#include <strstream>
using namespace std;
//���������ȼ�
int operPriority(char a);
//��׺ת��׺
stack<string> MiddleToBack(string in_str);
//��׺ת��׺
string BackToMiddle(stack<string> in_stack);
float countBackOperation(stack<string> in_stack);
//�ж��Ƿ��ַ�����ֻ������
bool isNumber(string a);
int main(){
	string oper_str;
	cout<<"��������ʽ"<<endl;
	cin>>oper_str;
	cout<<"������ʽΪ:"<<oper_str<<endl;
	stack<string>result_stack;
	result_stack = MiddleToBack(oper_str);
	
	cout<<"��׺ת��׺�ı��ʽΪ:"<<endl;
	cout<<BackToMiddle(result_stack)<<endl;

	cout<<endl<<"��׺���ʽ�ļ�����Ϊ:"<<countBackOperation(result_stack)<<endl;

	system("pause");
	return 0;
}

stack<string> MiddleToBack(string oper_str){
	stack<string>out_stack;
	stack<string>opera_stack;
	string num_str="";
	cout<<"��׺���ʽΪ";
	for(unsigned i=0; i<oper_str.length();i++ ){
		if(oper_str[i]>='0' && oper_str[i]<='9'){//����
			num_str += oper_str[i];
		}else{//������
			if(num_str.length()>0){//������������ջ����Ϊ���ֿ����Ƕ�λ��
				out_stack.push(num_str);
				cout<<num_str<<",";
				num_str = "";
			}
			int cur_prio = operPriority(oper_str[i]);
			if(cur_prio==0){
				cout<<"���ʽ��������"<<endl;
				break;
			}else if(oper_str[i]==')'){
				bool is_find = false;
				while(opera_stack.size()){
					if(opera_stack.top()[0]!='('){
						out_stack.push(opera_stack.top());
						cout<<opera_stack.top()<<",";
						opera_stack.pop();
					}else{
						opera_stack.pop();
						is_find = true;
						break;
					}
				}

				if(!is_find){
					cout<<"���ʽ��()��������"<<endl;
					break;
				}
			}else{
				string temp_str;
				int temp_prio;
				while(opera_stack.size()){
					temp_str = opera_stack.top();
					temp_prio = operPriority(temp_str[0]);
					if(temp_prio>=cur_prio && temp_str[0] != '('){
						out_stack.push(temp_str);
						cout<<temp_str<<",";
						opera_stack.pop();
					}else{
						break;
					}
				}
				string op_str = "";
				op_str+= oper_str[i];
				opera_stack.push(op_str);
			}
		}
	}
	if(num_str.length()>0){
		out_stack.push(num_str);
		cout<<num_str<<",";
		num_str = "";
	}
	while(opera_stack.size()){
		out_stack.push(opera_stack.top());
		cout<<opera_stack.top()<<",";
		opera_stack.pop();
	}
	return out_stack;
}

float countValue(float first_num,float second_num,string op_str);
float countBackOperation(stack<string> in_stack){
	float out_result = 0;
	string temp_str="";
	stack<string> temp_stack;
	while(in_stack.size()){
		temp_str=in_stack.top();
		in_stack.pop();
		if(isNumber(temp_str)){
			float cur_num = atof(temp_str.c_str());
			while(temp_stack.size()){ 
				if(isNumber(temp_stack.top())){//��ջ��Ҳ����һ������ʱ�����±��ʽ
					float second_num = atof(temp_stack.top().c_str());
					temp_stack.pop();
					string op_temp = temp_stack.top();
					temp_stack.pop();
					out_result = countValue(cur_num,second_num,op_temp);
					temp_str="";
					cur_num = out_result;
				}else{
					if(temp_str==""){
						strstream ss;
						ss << out_result;
						string out_str;
						ss >> out_str;
						temp_stack.push(out_str);//�����ʽ����ջ
					}else{
						temp_stack.push(temp_str);//����������ջ
					}
					
					break;
				}
			}
		}else{
			temp_stack.push(temp_str);//������������ջ
		}
	}
	return out_result;

}

float countValue(float first_num,float second_num,string op_str){
	if(op_str[0]=='+'){
		return first_num+second_num;
	}else if(op_str[0]=='-'){
		return first_num-second_num;
	}else if(op_str[0]=='*'){
		return first_num*second_num;
	}else if(op_str[0]=='/'){
		return first_num/second_num;
	}else if(op_str[0]=='^'){
		return pow(first_num,second_num);
	}
	return 0;
}
//4+9*5^(3+8*(6/908*67-34)+67)
string BackToMiddle(stack<string> in_stack){
	stack<string> temp_stack;
	string temp_str="";
	int last_op_prio=4;
	string out_str="";
	while(in_stack.size()){
		temp_str=in_stack.top();
		in_stack.pop();
		if(temp_str[0]>='0' && temp_str[0]<='9' && temp_stack.size()){
			while(temp_stack.size()){ 
				if(temp_stack.top()[0]>='0' && temp_stack.top()[0]<='9'){//��ջ��Ҳ����һ������ʱ�����±��ʽ
					string num_str = temp_stack.top();
					temp_stack.pop();
					string op_temp = temp_stack.top();
					temp_stack.pop();

					int temp_prio = operPriority(op_temp[0]);
					if(temp_str==""){
						if(last_op_prio<temp_prio){
							out_str = "("+out_str +")";
						}
						out_str = out_str+op_temp+num_str;
					}else{
						if(last_op_prio<temp_prio && !isNumber(num_str)){
							num_str = "("+num_str +")";
						}
						out_str = temp_str+op_temp+num_str;
						temp_str="";
					}
					last_op_prio = temp_prio;//��¼���һ�������������ȼ�
				}else{
					if(temp_str==""){
						temp_stack.push(out_str);//�����ʽ����ջ
					}else{
						temp_stack.push(temp_str);//����������ջ
					}
					
					break;
				}
			}
		}else{
			temp_stack.push(temp_str);//������������ջ
		}
	}
	return out_str;
}

bool isNumber(string a){
	for(unsigned i=0;i<a.length();i++){
		if(a[i]>='0' && a[i]<='9' || (i==0 && a[i]=='-' && a.length()>1)||a[i]=='.')
			continue;
		else
			return false;
	}
	return true;
}