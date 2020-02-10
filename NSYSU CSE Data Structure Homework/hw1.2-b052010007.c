//Author:王昱翔 B052010007
//Date:Sep. 14,2019
//Purpose:印出1到N之間所有整數之階乘 (factorial)，N<=50
#include <stdio.h>
#include <stdlib.h>
int print_answer(int);
int main(void){
	/*int enter; //為輸入值N 
	int x[10]; //儲存輸入的N值 
	int i=0; //為x陣列的索引 
	while(1){
		scanf("%d",&enter);
		if(enter==0){
			break;
		}
		x[i]=enter;
		i++;
	}
	int j; //遍歷x陣列中已輸入的N值 
	int j1; //控制列印 1~N 之間所有整數之階乘 
	for(j=0;j<=i;j++){
		for(j1=1;j1<=x[j];j1++){
			printf("%d!=",j1);
			print_answer(j1);		
		}
	}*/
	print_answer(15);
	system("pause");
	return 0;
}
int print_answer(int num){ //num為整數1~N之間的其中一個數 
	if(num==1){ //當num為1時,1!=1 
		printf("%d",num);
		printf("\n");
		return 1;
	}
	int array[100]={0}; //初始化儲存大數的陣列 
	int m=0; //紀錄進位
	int carry=0; //紀錄進位的數
	array[0]=1;
	int i,i1; //控制迴圈的流程 
	for(i=2;i<=num;i++){
		for(i1=0;i1<=m;i1++){
			array[i1]=array[i1]*i;
			array[i1]=array[i1]+carry;
			if(array[i1]/10){ //如果乘完的數值大於10 
				if(i1>=m){ //如果最高的位數大於10,則進一位 
					m++;	
				}
				carry=array[i1]/10; //將進位的數賦值給carry 
				array[i1]=array[i1]%10; //將個位數儲存於目前的位數 
			}
			else{
				carry=0;
			}
		}
	}
	for(i=m;i>=0;i--){
		printf("%d",array[i]); //印出大數陣列 
	}
	printf("\n");
	return 0; 
}
