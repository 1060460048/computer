#include<iostream>
using namespace std;
struct Node{
	int NodeValue;
	Node* Next;
};
int main(){
	int M,N;
	cout<<"������M"<<endl;
	cin>>M;
	cout<<"������N"<<endl;
	cin>>N;
	cout<<"M="<<M<<";N="<<N<<endl;
	//��ʼ������
	Node* nodeList = (Node *)(malloc(sizeof(struct Node)));
	Node* temp,current;
	cout<<nodeList<<endl;
	//current = nodeList;
	for(int i=1;i<=N;i++){
		temp = (Node *)(malloc(sizeof(struct Node)));
		if(temp==NULL){
			cout<<"Error malloc"<<endl;
			break;
		}
		temp->NodeValue = i;
		temp->Next = NULL;
		nodeList->Next = temp;
		nodeList = temp;
	}
	system("pause");
	return 0;
}