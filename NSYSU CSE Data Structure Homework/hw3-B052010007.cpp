//Author:���R�� B052010007
//Date:Oct. 13,2019
//Purpose:��v�M�h���X 
#include <iostream>
using namespace std;
class Stack{
	public:
		Stack(int stackCapacity); //stackCapacity�O�M�h�����ѽL�һݪ��B�� 
		~Stack(); 
		bool IsEmpty() const;
		int* top() const;
		void push(int i,int j,int route); //(i,j)�����L���y��,route����V�s�� 
		void pop();
		int getTop() {return Top;} 
	private:
		int capacity;
		int **stack;
		int Top;
		int *a;
};
void knight(int);
int main(void){
	knight(1); //�ѽL1*1 
	knight(2); //�ѽL2*2 
	knight(3); //�ѽL3*3 
	knight(4); //�ѽL4*4 
	knight(5); //�ѽL5*5 
	knight(6); //�ѽL6*6 
	system("pause");
	return 0;
}
Stack::Stack(int stackCapacity) : capacity(stackCapacity)
{
	stack=new int* [capacity]; //�t�m�@�ӤG���}�C�����M�h�Ҩ������| 
	Top=-1;
	a=new int [3]; //����|���ťB�ݭn�Apop��,���@���H�����|���ܼ�,�ϵ{���ॿ�`�B��ܵ��� 
	for(int i=0;i<3;i++) a[i]=-1; //�Na[3]��l�Ƭ�-1 
}
Stack::~Stack(){
	delete [] stack; //�{�������ɧR���ʺA�O����t�m 
}
bool Stack::IsEmpty() const{
	return Top==-1;
}
int* Stack::top() const{
	if(IsEmpty()){
		return a;
	}
	return stack[Top];
}
void Stack::push(int i,int j,int route){
	if(Top==capacity-1) throw "Stack Overflows";
	Top+=1;
	stack[Top]=new int [3]; //�bstack�}�C�������A�t�m�@�ӰʺA�}�C�����M�h���| 
	stack[Top][0]=i;
	stack[Top][1]=j;
	stack[Top][2]=route;
}
void Stack::pop(){
	if(IsEmpty()){
		Top=-2; //��@�j�鵲���ɪ��P�_�̾� 
		return;
	}
	delete [] stack[Top];
	Top--;
}
void knight(int n){ //�M�h���X�禡,n���ѽL��� 
	if(n==1){
		cout<<"no-solution"<<endl;
		cout<<endl;
		return;
	}
	int array[n][n]; //�t�m��v�ѽL 
	for(int i=0;i<n;i++){ //�N�ѽL��l�Ƭ�0 
		for(int i1=0;i1<n;i1++){
			array[i][i1]=0;
		}
	}
	int i=0; //�M�h�}�l���X���J�f 
	int j=0;
	array[i][j]=1;
	int k,l;
	int count=1; //�p�⨫���B�� 
	int route; //��V�s�� 
	int Route[8]={1,1,1,1,1,1,1,1};
	Stack s(n*n-1); //n*n-1���M�h�������{�����X�B�� 
	while(s.getTop()!=-2 && s.getTop()<n*n-2){ //��Top�Ȭ�-2�ɪ�ܵL��,Top�Ȭ�n*n-2�ɪ�ܤw�����ѽL 
		if(i-2>=0 && j+1<n && array[i-2][j+1]==0 && Route[0]){
			k=i-2;
			l=j+1;
			route=0;
			count++;
			array[k][l]=count;
		}else if(i-1>=0 && j+2<n && array[i-1][j+2]==0 && Route[1]){
			k=i-1;
			l=j+2;
			route=1;
			count++;
			array[k][l]=count;
		}else if(i+1<n && j+2<n && array[i+1][j+2]==0 && Route[2]){
			k=i+1;
			l=j+2;
			route=2;
			count++;
			array[k][l]=count;
		}else if(i+2<n && j+1<n && array[i+2][j+1]==0 && Route[3]){
			k=i+2;
			l=j+1;
			route=3;
			count++;
			array[k][l]=count;
		}else if(i+2<n && j-1>=0 && array[i+2][j-1]==0 && Route[4]){
			k=i+2;
			l=j-1;
			route=4;
			count++;
			array[k][l]=count;
		}else if(i+1<n && j-2>=0 && array[i+1][j-2]==0 && Route[5]){
			k=i+1;
			l=j-2;
			route=5;
			count++;
			array[k][l]=count;
		}else if(i-1>=0 && j-2>=0 && array[i-1][j-2]==0 && Route[6]){
			k=i-1;
			l=j-2;
			route=6;
			count++;
			array[k][l]=count;
		}else if(i-2>=0 && j-1>=0 && array[i-2][j-1]==0 && Route[7]){
			k=i-2;
			l=j-1;
			route=7;
			count++;
			array[k][l]=count;
		}else{ //��K�Ӥ�V���L�k���� 
			for(int i1=0;i1<8;i1++) Route[i1]=1;
			array[i][j]=0; //��e���y�еL�k�~�򨫤U�h,�ҥH�]��0 
			count--; //�h�@�B 
			i=s.top()[0]; //�N���|���ݪ��������X�� 
			j=s.top()[1];
			int num[8]={0,1,2,3,4,5,6,7};
			for(int i1=0;i1<8;i1++){ //��ثe�����|s.top()[2]���ਫ��,�N���U�@�Ӥ�V��,��W����V�s�����ਫ,�ҥH�]��0���� 
				if(s.top()[2]>=num[i1]) Route[num[i1]]=0;
			}
			s.pop();
			continue;
		}
		for(int i1=0;i1<8;i1++) Route[i1]=1;
		s.push(i,j,route);
		i=k;
		j=l;
	}
	if(s.getTop()==-2){
		cout<<"no solution\n";
		cout<<endl;
	}
	else{
		for(int i1=0;i1<n;i1++){
			for(int i2=0;i2<n;i2++){
				cout<<array[i1][i2]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
}
