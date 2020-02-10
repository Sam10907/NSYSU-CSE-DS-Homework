//Author:���R�� B052010007
//Date:Oct. 19,2019
//Purpose:��v�M�h���X(���j) 
#include <iostream>
using namespace std;
bool KnightTravel(int,int,int,int**); //�P�_�M�h�O�_��������ѽL 
void DisplayResult(int,int,int,int**); //���1*1~6*6�ѽL�����G 
int array1[1][1]={0}; //1*1 
int array2[2][2]={{0},{0}}; //2*2 
int array3[3][3]={{0},{0},{0}}; //3*3 
int array4[4][4]={{0},{0},{0},{0}}; //4*4 
int array5[5][5]={{0},{0},{0},{0},{0}}; //5*5 
int array6[6][6]={{0},{0},{0},{0},{0},{0}}; //6*6 
int directionX[8]={1,2,2,1,-1,-2,-2,-1}; //�K���M�h�i�H������V(��directionX�MdirectionY���) 
int directionY[8]={-2,-1,1,2,2,1,-1,-2};  
int count=1; //�Ψӭp�⨫�L���� 
int main(void){	
	int i=0,j=0; //�M�h�@�}�l�����J�f 
	int *p1[1],*p2[2],*p3[3],*p4[4],*p5[5],*p6[6]; //�t�m�i�ǤJ�禡���G���}�C 
	p1[0]=array1[0];
	p2[0]=array2[0],p2[1]=array2[1];
	p3[0]=array3[0],p3[1]=array3[1],p3[2]=array3[2];
	p4[0]=array4[0],p4[1]=array4[1],p4[2]=array4[2],p4[3]=array4[3];
	p5[0]=array5[0],p5[1]=array5[1],p5[2]=array5[2],p5[3]=array5[3],p5[4]=array5[4];
	p6[0]=array6[0],p6[1]=array6[1],p6[2]=array6[2],p6[3]=array6[3],p6[4]=array6[4],p6[5]=array6[5];
	DisplayResult(i,j,1,p1); //���1*1�����G 
	DisplayResult(i,j,2,p2); //���2*2�����G 
	DisplayResult(i,j,3,p3); //���3*3�����G 
	DisplayResult(i,j,4,p4); //���4*4�����G 
	DisplayResult(i,j,5,p5); //���5*5�����G 
	DisplayResult(i,j,6,p6); //���6*6�����G 
	system("pause");
	return 0;
}
bool KnightTravel(int i,int j,int n,int **a){ //i,j���J�f,n�O�ѽL����ɪ�,a�����@�ӤG���}�C 
	if(i==0 && j==0) a[i][j]=1; //�N�J�f�]��1 
	int k,l;
	for(int i1=0;i1<8;i1++){ //�M���K�Ӥ�V 
		if(count==n*n && n!=1) return true; //�p�G������,�^��true 
		k=i+directionY[i1];
		l=j+directionX[i1];
		if(k>=0 && k<n && l>=0 && l<n && a[k][l]==0){ //�p�G�U�@�Ӧ�m�i�H�� 
			count++; //�B�ƥ[1 
			a[k][l]=count;
			KnightTravel(k,l,n,a); //�~�� 
		}
	}
	if(count==n*n && n!=1) return true;
	count--; //�K�Ӥ�V�����ਫ��,�B�ƴ�1 
	a[i][j]=0; //��e��m�]��0 
	return false;
}
void DisplayResult(int i,int j,int n,int **a){ //i,j���J�f,n�O�ѽL����ɪ�,a�����@�ӤG���}�C 
	if(KnightTravel(i,j,n,a)){ //�p�G�M�h������ 
		for(int i1=0;i1<n;i1++){ //�L�X�M�h�������| 
			for(int i2=0;i2<n;i2++){
				cout<<a[i1][i2]<<" ";
			}
			cout<<'\n';
		}
	}else cout<<"no solution"<<endl;
	count=1;
	cout<<endl;
}
