
//Author:���R�� B052010007
//Date:Sep. 14,2019
//Purpose:�]��} 
#include <stdio.h>
#include <stdlib.h>
void print_magic_array(int);
int main(void){
	print_magic_array(1);//�@���]��} 
	printf("\n");
	print_magic_array(3);//�T���]��}
	printf("\n");
	print_magic_array(5);//�����]��} 
	printf("\n");
	print_magic_array(7);//�C���]��} 
	printf("\n");
	print_magic_array(9);//�E���]��} 
	system("pause");
	return 0;
}
void print_magic_array(int num){ //num������ 
	int magic_array[num][num]; //�ŧi�@���]��} 
	int i,i1; //����j�骺�ܼ� 
	for(i=0;i<num;i++){
		for(i1=0;i1<num;i1++){
			magic_array[i][i1]=0; //�N�}�C�Ҧ�������l�Ƭ�0 
		}
	}
	int m=(num+1)/2-1; //�Ĥ@�檺���I 
	int x,y=(0,m);//�_�l�I 
	magic_array[x][y]=1; //�_�l�I��1 
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
			printf("%d ",magic_array[i][i1]); //�L�X�]��} 
		}
		printf("\n");
	}
}
