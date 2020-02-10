//Author:王昱翔 B052010007
//Date:Oct. 13,2019
//Purpose:西洋騎士走訪 
#include <iostream>
using namespace std;
class Stack{
	public:
		Stack(int stackCapacity); //stackCapacity是騎士走完棋盤所需的步數 
		~Stack(); 
		bool IsEmpty() const;
		int* top() const;
		void push(int i,int j,int route); //(i,j)為走過的座標,route為方向編號 
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
	knight(1); //棋盤1*1 
	knight(2); //棋盤2*2 
	knight(3); //棋盤3*3 
	knight(4); //棋盤4*4 
	knight(5); //棋盤5*5 
	knight(6); //棋盤6*6 
	system("pause");
	return 0;
}
Stack::Stack(int stackCapacity) : capacity(stackCapacity)
{
	stack=new int* [capacity]; //配置一個二維陣列紀錄騎士所走的路徑 
	Top=-1;
	a=new int [3]; //當堆疊為空且需要再pop時,給一個隨機路徑給變數,使程式能正常運行至結束 
	for(int i=0;i<3;i++) a[i]=-1; //將a[3]初始化為-1 
}
Stack::~Stack(){
	delete [] stack; //程式結束時刪除動態記憶體配置 
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
	stack[Top]=new int [3]; //在stack陣列元素中再配置一個動態陣列紀錄騎士路徑 
	stack[Top][0]=i;
	stack[Top][1]=j;
	stack[Top][2]=route;
}
void Stack::pop(){
	if(IsEmpty()){
		Top=-2; //當作迴圈結束時的判斷依據 
		return;
	}
	delete [] stack[Top];
	Top--;
}
void knight(int n){ //騎士走訪函式,n為棋盤邊長 
	if(n==1){
		cout<<"no-solution"<<endl;
		cout<<endl;
		return;
	}
	int array[n][n]; //配置西洋棋盤 
	for(int i=0;i<n;i++){ //將棋盤初始化為0 
		for(int i1=0;i1<n;i1++){
			array[i][i1]=0;
		}
	}
	int i=0; //騎士開始走訪的入口 
	int j=0;
	array[i][j]=1;
	int k,l;
	int count=1; //計算走的步數 
	int route; //方向編號 
	int Route[8]={1,1,1,1,1,1,1,1};
	Stack s(n*n-1); //n*n-1為騎士走完全程的走訪步數 
	while(s.getTop()!=-2 && s.getTop()<n*n-2){ //當Top值為-2時表示無解,Top值為n*n-2時表示已走完棋盤 
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
		}else{ //當八個方向都無法走時 
			for(int i1=0;i1<8;i1++) Route[i1]=1;
			array[i][j]=0; //當前的座標無法繼續走下去,所以設為0 
			count--; //退一步 
			i=s.top()[0]; //將堆疊頂端的紀錄拿出來 
			j=s.top()[1];
			int num[8]={0,1,2,3,4,5,6,7};
			for(int i1=0;i1<8;i1++){ //當目前的路徑s.top()[2]不能走時,就往下一個方向走,其上的方向編號不能走,所以設為0關閉 
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
