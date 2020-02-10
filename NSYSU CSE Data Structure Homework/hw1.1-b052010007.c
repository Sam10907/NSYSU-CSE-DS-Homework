
//Author:王昱翔 B052010007
//Date:Sep. 14,2019
//Purpose:魔方陣 
#include <stdio.h>
#include <stdlib.h>
void print_magic_array(int);
int main(void){
	print_magic_array(1);//一階魔方陣 
	printf("\n");
	print_magic_array(3);//三階魔方陣
	printf("\n");
	print_magic_array(5);//五階魔方陣 
	printf("\n");
	print_magic_array(7);//七階魔方陣 
	printf("\n");
	print_magic_array(9);//九階魔方陣 
	system("pause");
	return 0;
}
void print_magic_array(int num){ //num為階數 
	int magic_array[num][num]; //宣告一個魔方陣 
	int i,i1; //控制迴圈的變數 
	for(i=0;i<num;i++){
		for(i1=0;i1<num;i1++){
			magic_array[i][i1]=0; //將陣列所有元素初始化為0 
		}
	}
	int m=(num+1)/2-1; //第一行的中點 
	int x,y=(0,m);//起始點 
	magic_array[x][y]=1; //起始點為1 
	for(i=2;i<=num*num;i++){
		x--;
		y--;
		if(x<0 && y>=0){
			x=num-1;
			magic_array[x][y]=i;
		}
		else if(x>=0 && y<0){
			y=num-1;
			magic_array[x][y]=i;
		}
		else if(x<0 && y<0){
			x=x+1+1;
			y=y+1;
			magic_array[x][y]=i;
		}
		else if(magic_array[x][y]!=0){
			x=x+1+1;
			y=y+1;
			magic_array[x][y]=i;
		}
		else{
			magic_array[x][y]=i;
		}
	}
	for(i=0;i<num;i++){
		for(i1=0;i1<num;i1++){
			printf("%d ",magic_array[i][i1]); //印出魔方陣 
		}
		printf("\n");
	}
}
