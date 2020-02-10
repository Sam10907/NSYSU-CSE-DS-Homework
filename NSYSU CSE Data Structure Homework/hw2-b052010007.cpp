//Author:王昱翔 B052010007
//Date:Sep.27,2019
//Purpose:以c++實作集合類別 
#include <iostream>
#include <cstring>
using namespace std;
class TSet{ //集合類別 
	public:
		TSet();
		TSet(char *c);
		const TSet operator +(const TSet& t) const;
		const TSet operator -(const TSet& t1) const;
		const TSet operator *(const TSet& t2) const;
		bool operator >=(const TSet& t3) const;
		bool contain(char c1);
		void getArray();
	private:
		char array[256];
};
int main(void){
	int n; //n個Test case 
	cin>>n;
	int test=1; //Test case 1 
	while(test<=n){
		char setA[80]; //集合A 
		char setB[80]; //集合B 
		char c; //輸入一個字元,查看是否在集合A或B裡 
		cin.ignore();
		cin.get(setA,80);
		cin.ignore();
		cin.get(setB,80);
		cin.ignore();
		cin.get(c);
		cout<<"Test Case "<<test<<":\n";
		TSet A(setA),B(setB);
		cout<<"A: {";
		A.getArray(); //印出A集合元素 
		cout<<"}\n";
		
		cout<<"B: {";
		B.getArray();
		cout<<"}\n"; 
		
		TSet C,D,E,F;
		C=A+B; //A集合與B集合聯集 
		D=A*B; //A集合與B集合交集 
		E=A-B; //A集合差集B集合 
		F=B-A; //B集合差集A集合 
		cout<<"A+B: {";
		C.getArray();
		cout<<"}\n"; 
		
		cout<<"A*B: {";
		D.getArray();
		cout<<"}\n";
		
		cout<<"A-B: {";
		E.getArray();
		cout<<"}\n";
		
		cout<<"B-A: {";
		F.getArray();
		cout<<"}\n";
		
		if(A>=B) cout<<"A contain B"<<endl; //如果A集合包含B集合 
		else cout<<"A does not contain B"<<endl; 
		if(B>=A) cout<<"B contain A"<<endl; //如果B集合包含A集合 
		else cout<<"B does not contain A"<<endl;
		if(A.contain(c)) cout<<c<<" is in A"<<endl; //如果A集合包含某字元c 
		else cout<<c<<" is not in A"<<endl;
		if(B.contain(c)) cout<<c<<" is in B"<<endl; //如果B集合包含某字元c 
		else cout<<c<<" is not in B"<<endl;
		test++;
		cout<<"\n";
	}
	system("pause");
	return 0;
}
TSet::TSet(){
	for(int i=0;i<256;i++){
		array[i]='\0'; //初始化陣列array的所有元素為'\0' 
	}
}
TSet::TSet(char *c){ //*c接收陣列輸入 
	for(int i=0;i<256;i++){
		array[i]='\0'; //先初始化 
	}
	for(int i=0;i<strlen(c);i++){
		int n=c[i]; //得到字元所對應的十進制數字 
		array[n]=c[i]; //將字元放進所對應的位置 
	}
}
const TSet TSet::operator +(const TSet& t) const //t為其他TSet物件,call by reference 
{
	char Union[200]={'\0'}; //宣告一個聯集集合 
	int index=0; //Union陣列的引數 
	for(int i=0;i<256;i++){
		if(array[i] || t.array[i]){
			char c=(array[i] | t.array[i]); //聯集運算 
			Union[index]=c;
			index++;
		}
	}
	return TSet(Union); //回傳聯集的集合物件 
}
const TSet TSet::operator -(const TSet& t1) const //t1為其他TSet物件,call by reference 
{
	char difference[100]={'\0'};  //宣告一個差集集合
	int index=0; //difference陣列的引數 
	for(int i=0;i<256;i++){
		if(array[i] && t1.array[i]=='\0'){ //差集運算 
			char c=array[i];
			difference[index]=c;
			index++;
		}
	}
	return TSet(difference); //回傳差集的集合物件 
}
const TSet TSet::operator *(const TSet& t2) const
{
	char intersection[100]={'\0'};  //宣告一個交集集合
	int index=0; //intersection陣列的引數
	for(int i=0;i<256;i++){
		if(array[i] && t2.array[i]){
			char c=(array[i] & t2.array[i]); //交集運算 
			intersection[index]=c;
			index++;
		}
	}
	return TSet(intersection); //回傳交集的集合物件 
}
bool TSet::operator >=(const TSet& t3) const
{
	char array1[256]={'\0'}; //用來存放與t3交集後的結果 
	for(int i=0;i<256;i++){
		if(array[i] && t3.array[i]){
			int n=(array[i] & t3.array[i]);
			array1[n]=array[i];
		}
	}
	for(int i=0;i<256;i++){
		if(array1[i]!=t3.array[i]) return false; //比較array1與t3.array是否相同,是的話表示array包含t3.array,反之則否 
	}
	return true;
}
bool TSet::contain(char c1){ //c1為一個字元 
	int n=c1;
	return array[n]==c1; //查看c1是否在array裡 
}
void TSet::getArray(){ //印出集合元素 
	for(int i=0;i<256;i++){
		if(array[i]) cout<<array[i];
	}
}
