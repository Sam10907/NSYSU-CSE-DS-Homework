//Author:���R�� B052010007
//Date:Sep. 14,2019
//Purpose:�L�X1��N�����Ҧ���Ƥ����� (factorial)�AN<=50
#include <stdio.h>
#include <stdlib.h>
int print_answer(int);
int main(void){
	/*int enter; //����J��N 
	int x[10]; //�x�s��J��N�� 
	int i=0; //��x�}�C������ 
	while(1){
		scanf("%d",&enter);
		if(enter==0){
			break;
		}
		x[i]=enter;
		i++;
	}
	int j; //�M��x�}�C���w��J��N�� 
	int j1; //����C�L 1~N �����Ҧ���Ƥ����� 
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
int print_answer(int num){ //num�����1~N�������䤤�@�Ӽ� 
	if(num==1){ //��num��1��,1!=1 
		printf("%d",num);
		printf("\n");
		return 1;
	}
	int array[100]={0}; //��l���x�s�j�ƪ��}�C 
	int m=0; //�����i��
	int carry=0; //�����i�쪺��
	array[0]=1;
	int i,i1; //����j�骺�y�{ 
	for(i=2;i<=num;i++){
		for(i1=0;i1<=m;i1++){
			array[i1]=array[i1]*i;
			array[i1]=array[i1]+carry;
			if(array[i1]/10){ //�p�G�������ƭȤj��10 
				if(i1>=m){ //�p�G�̰�����Ƥj��10,�h�i�@�� 
					m++;	
				}
				carry=array[i1]/10; //�N�i�쪺�ƽ�ȵ�carry 
				array[i1]=array[i1]%10; //�N�Ӧ���x�s��ثe����� 
			}
			else{
				carry=0;
			}
		}
	}
	for(i=m;i>=0;i--){
		printf("%d",array[i]); //�L�X�j�ư}�C 
	}
	printf("\n");
	return 0; 
}
