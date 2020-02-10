//Author:���R�� B052010007
//Date:Sep.27,2019
//Purpose:�Hc++��@���X���O 
#include <iostream>
#include <cstring>
using namespace std;
class TSet{ //���X���O 
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
	int n; //n��Test case 
	cin>>n;
	int test=1; //Test case 1 
	while(test<=n){
		char setA[80]; //���XA 
		char setB[80]; //���XB 
		char c; //��J�@�Ӧr��,�d�ݬO�_�b���XA��B�� 
		cin.ignore();
		cin.get(setA,80);
		cin.ignore();
		cin.get(setB,80);
		cin.ignore();
		cin.get(c);
		cout<<"Test Case "<<test<<":\n";
		TSet A(setA),B(setB);
		cout<<"A: {";
		A.getArray(); //�L�XA���X���� 
		cout<<"}\n";
		
		cout<<"B: {";
		B.getArray();
		cout<<"}\n"; 
		
		TSet C,D,E,F;
		C=A+B; //A���X�PB���X�p�� 
		D=A*B; //A���X�PB���X�涰 
		E=A-B; //A���X�t��B���X 
		F=B-A; //B���X�t��A���X 
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
		
		if(A>=B) cout<<"A contain B"<<endl; //�p�GA���X�]�tB���X 
		else cout<<"A does not contain B"<<endl; 
		if(B>=A) cout<<"B contain A"<<endl; //�p�GB���X�]�tA���X 
		else cout<<"B does not contain A"<<endl;
		if(A.contain(c)) cout<<c<<" is in A"<<endl; //�p�GA���X�]�t�Y�r��c 
		else cout<<c<<" is not in A"<<endl;
		if(B.contain(c)) cout<<c<<" is in B"<<endl; //�p�GB���X�]�t�Y�r��c 
		else cout<<c<<" is not in B"<<endl;
		test++;
		cout<<"\n";
	}
	system("pause");
	return 0;
}
TSet::TSet(){
	for(int i=0;i<256;i++){
		array[i]='\0'; //��l�ư}�Carray���Ҧ�������'\0' 
	}
}
TSet::TSet(char *c){ //*c�����}�C��J 
	for(int i=0;i<256;i++){
		array[i]='\0'; //����l�� 
	}
	for(int i=0;i<strlen(c);i++){
		int n=c[i]; //�o��r���ҹ������Q�i��Ʀr 
		array[n]=c[i]; //�N�r����i�ҹ�������m 
	}
}
const TSet TSet::operator +(const TSet& t) const //t����LTSet����,call by reference 
{
	char Union[200]={'\0'}; //�ŧi�@���p�����X 
	int index=0; //Union�}�C���޼� 
	for(int i=0;i<256;i++){
		if(array[i] || t.array[i]){
			char c=(array[i] | t.array[i]); //�p���B�� 
			Union[index]=c;
			index++;
		}
	}
	return TSet(Union); //�^���p�������X���� 
}
const TSet TSet::operator -(const TSet& t1) const //t1����LTSet����,call by reference 
{
	char difference[100]={'\0'};  //�ŧi�@�Ӯt�����X
	int index=0; //difference�}�C���޼� 
	for(int i=0;i<256;i++){
		if(array[i] && t1.array[i]=='\0'){ //�t���B�� 
			char c=array[i];
			difference[index]=c;
			index++;
		}
	}
	return TSet(difference); //�^�Ǯt�������X���� 
}
const TSet TSet::operator *(const TSet& t2) const
{
	char intersection[100]={'\0'};  //�ŧi�@�ӥ涰���X
	int index=0; //intersection�}�C���޼�
	for(int i=0;i<256;i++){
		if(array[i] && t2.array[i]){
			char c=(array[i] & t2.array[i]); //�涰�B�� 
			intersection[index]=c;
			index++;
		}
	}
	return TSet(intersection); //�^�ǥ涰�����X���� 
}
bool TSet::operator >=(const TSet& t3) const
{
	char array1[256]={'\0'}; //�ΨӦs��Pt3�涰�᪺���G 
	for(int i=0;i<256;i++){
		if(array[i] && t3.array[i]){
			int n=(array[i] & t3.array[i]);
			array1[n]=array[i];
		}
	}
	for(int i=0;i<256;i++){
		if(array1[i]!=t3.array[i]) return false; //���array1�Pt3.array�O�_�ۦP,�O���ܪ��array�]�tt3.array,�Ϥ��h�_ 
	}
	return true;
}
bool TSet::contain(char c1){ //c1���@�Ӧr�� 
	int n=c1;
	return array[n]==c1; //�d��c1�O�_�barray�� 
}
void TSet::getArray(){ //�L�X���X���� 
	for(int i=0;i<256;i++){
		if(array[i]) cout<<array[i];
	}
}
