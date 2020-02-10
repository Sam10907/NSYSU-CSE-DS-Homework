//Author:王昱翔 B052010007
//Date:Oct. 19,2019
//Purpose:西洋騎士走訪(遞迴) 
#include <iostream>
using namespace std;
bool KnightTravel(int,int,int,int**); //判斷騎士是否能夠走完棋盤 
void DisplayResult(int,int,int,int**); //顯示1*1~6*6棋盤的結果 
int array1[1][1]={0}; //1*1 
int array2[2][2]={{0},{0}}; //2*2 
int array3[3][3]={{0},{0},{0}}; //3*3 
int array4[4][4]={{0},{0},{0},{0}}; //4*4 
int array5[5][5]={{0},{0},{0},{0},{0}}; //5*5 
int array6[6][6]={{0},{0},{0},{0},{0},{0}}; //6*6 
int directionX[8]={1,2,2,1,-1,-2,-2,-1}; //八個騎士可以走的方向(用directionX和directionY表示) 
int directionY[8]={-2,-1,1,2,2,1,-1,-2};  
int count=1; //用來計算走過的路 
int main(void){	
	int i=0,j=0; //騎士一開始走的入口 
	int *p1[1],*p2[2],*p3[3],*p4[4],*p5[5],*p6[6]; //配置可傳入函式的二維陣列 
	p1[0]=array1[0];
	p2[0]=array2[0],p2[1]=array2[1];
	p3[0]=array3[0],p3[1]=array3[1],p3[2]=array3[2];
	p4[0]=array4[0],p4[1]=array4[1],p4[2]=array4[2],p4[3]=array4[3];
	p5[0]=array5[0],p5[1]=array5[1],p5[2]=array5[2],p5[3]=array5[3],p5[4]=array5[4];
	p6[0]=array6[0],p6[1]=array6[1],p6[2]=array6[2],p6[3]=array6[3],p6[4]=array6[4],p6[5]=array6[5];
	DisplayResult(i,j,1,p1); //顯示1*1的結果 
	DisplayResult(i,j,2,p2); //顯示2*2的結果 
	DisplayResult(i,j,3,p3); //顯示3*3的結果 
	DisplayResult(i,j,4,p4); //顯示4*4的結果 
	DisplayResult(i,j,5,p5); //顯示5*5的結果 
	DisplayResult(i,j,6,p6); //顯示6*6的結果 
	system("pause");
	return 0;
}
bool KnightTravel(int i,int j,int n,int **a){ //i,j為入口,n是棋盤的邊界長,a接受一個二維陣列 
	if(i==0 && j==0) a[i][j]=1; //將入口設為1 
	int k,l;
	for(int i1=0;i1<8;i1++){ //遍歷八個方向 
		if(count==n*n && n!=1) return true; //如果走的完,回傳true 
		k=i+directionY[i1];
		l=j+directionX[i1];
		if(k>=0 && k<n && l>=0 && l<n && a[k][l]==0){ //如果下一個位置可以走 
			count++; //步數加1 
			a[k][l]=count;
			KnightTravel(k,l,n,a); //繼續走 
		}
	}
	if(count==n*n && n!=1) return true;
	count--; //八個方向都不能走時,步數減1 
	a[i][j]=0; //當前位置設為0 
	return false;
}
void DisplayResult(int i,int j,int n,int **a){ //i,j為入口,n是棋盤的邊界長,a接受一個二維陣列 
	if(KnightTravel(i,j,n,a)){ //如果騎士走的完 
		for(int i1=0;i1<n;i1++){ //印出騎士走的路徑 
			for(int i2=0;i2<n;i2++){
				cout<<a[i1][i2]<<" ";
			}
			cout<<'\n';
		}
	}else cout<<"no solution"<<endl;
	count=1;
	cout<<endl;
}
