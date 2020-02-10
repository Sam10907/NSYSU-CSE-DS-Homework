//Author:王昱翔 B052010007
//Date:Dec. 8,2019
//Purpose:測試排序演算法的執行效率 
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
void insertion_sort(int*,int); //插入排序法 
void merge_sort(int*,int); //合併排序法 
void quick_sort(int*,int,int); //快速排序法 
void merge(int*,int*,int,int*,int); //將left sublist與right sublist合併  
int cmpfunc(const void*,const void*); //C語言的qsort會用到 
void random(int); //產生亂數 
int *data_set;
int main(void){
	fstream file;
	//產生input.txt的資料 
	/*file.open("input.txt",ios::out);
	if(file.fail()) cout<<"The file can not be opened.\n";
	else{
		int num=10;
		file<<num<<endl;
		srand(time(NULL));
		for(int i=1;i<=num;i++) file<<rand()<<endl;
		file.close();
	}*/ 
	//產生outputA~E.txt排序過後的資料 
	file.open("input.txt",ios::in);
	if(file.fail()) cout<<"The file can not be opened.\n";
	else{
		int num;
		file>>num; //資料量 
		int number[num];
		int i=0;
		while(!file.eof()){
			file>>number[i];
			i++;
		}
		insertion_sort(number,num);
		fstream file0;
		file0.open("outputA.txt",ios::out);
		if(!file0) cout<<"The file can not be opened.\n";
		else{
			file0<<"Insertion Sort"<<endl;
			for(int i=0;i<num;i++) file0<<number[i]<<endl;
			file0.close();
		}
		
		merge_sort(number,num);
		fstream file1;
		file1.open("outputB.txt",ios::out);
		if(!file1) cout<<"The file can not be opened.\n";
		else{
			file1<<"Merge Sort"<<endl;
			for(int i=0;i<num;i++) file1<<number[i]<<endl;
			file1.close();
		}
		
		quick_sort(number,0,num);
		fstream file2;
		file2.open("outputC.txt",ios::out);
		if(!file2) cout<<"The file can not be opened.\n";
		else{
			file2<<"Quick Sort"<<endl;
			for(int i=0;i<num;i++) file2<<number[i]<<endl;
			file2.close();
		}
		
		qsort(number,num,sizeof(int),cmpfunc);
		fstream file3;
		file3.open("outputD.txt",ios::out);
		if(!file3) cout<<"The file can not be opened.\n";
		else{
			file3<<"C qsort()"<<endl;
			for(int i=0;i<num;i++) file3<<number[i]<<endl;
			file3.close();
		}
		
		sort(number,number+num);
		fstream file4;
		file4.open("outputE.txt",ios::out);
		if(!file4) cout<<"The file can not be opened.\n";
		else{
			file4<<"C++ sort()"<<endl;
			for(int i=0;i<num;i++) file4<<number[i]<<endl;
			file4.close();
		}
		file.close();
	}
	//統計各個排序演算法的時間 
	double sum[5]; 
	int n;
	cout<<"輸入測試的資料量:";
	cin>>n; //輸入欲產生的資料量 
	for(int i=1;i<=10;i++){ //產生10組資料 
		int original[n]; //用來存放原始未經排序的資料 
		random(n); //一次產生一組資料,供接下來的五種排序演算法使用 
		for(int i=0;i<n;i++) original[i]=data_set[i]; //先將原始資料存放進original陣列 
		double t1,t2,t3,t4,t5,t6,t7,t8,t9,t10; //為了計算各個排序演算法的執行時間 
		t1=clock();
		insertion_sort(data_set,n);
		t2=clock();
		cout<<(t2-t1)/1000<<endl; //印出時間 
		sum[0]+=(t2-t1)/1000;
		for(int i=0;i<n;i++) data_set[i]=original[i];
		
		t3=clock();
		merge_sort(data_set,n);
		t4=clock();
		cout<<(t4-t3)/1000<<endl;
		sum[1]+=(t4-t3)/1000;
		for(int i=0;i<n;i++) data_set[i]=original[i];
		
		t5=clock();
		quick_sort(data_set,0,n-1);
		t6=clock();
		cout<<(t6-t5)/1000<<endl;
		sum[2]+=(t6-t5)/1000;
		for(int i=0;i<n;i++) data_set[i]=original[i];
		
		t7=clock();
		qsort(data_set,n,sizeof(int),cmpfunc);
		t8=clock();
		cout<<(t8-t7)/1000<<endl;
		sum[3]+=(t8-t7)/1000;
		for(int i=0;i<n;i++) data_set[i]=original[i];
		
		t9=clock();
		sort(data_set,data_set+n);
		t10=clock();
		cout<<(t10-t9)/1000<<endl;
		sum[4]+=(t10-t9)/1000;
		cout<<"-----------------------"<<endl;
	}
	for(int i=0;i<5;i++) cout<<sum[i]/10<<endl; //印出各個排序演算法的平均執行時間(insertion->merge->quick->qsort->sort) 
	return 0; 
}
void insertion_sort(int *l,int n){
	for(int i=1;i<n;i++){
		for(int j=i-1;j>=0;j--){
			if(l[j+1]<l[j]){
				int temp=l[j];
				l[j]=l[j+1];
				l[j+1]=temp;
			}
			else break;
		}
	} 
}
void merge_sort(int *l,int n){
	int mid,i,*L,*R;
	if(n<2) return;
	mid=n/2;
	L = new int[mid];
	R = new int [n - mid];
	for(i=0;i<mid;i++) L[i]=l[i];
	for(i=mid;i<n;i++) R[i-mid]=l[i];
	merge_sort(L,mid);
	merge_sort(R,n-mid);  
	merge(l,L,mid,R,n-mid);
	delete [] R;
	delete [] L;
}
void merge(int *l,int *L,int Lcount,int *R,int Rcount){
	int i,j,k;
	i=0; j=0; k=0;
	while(i<Lcount && j<Rcount) {
		if(L[i]<R[j]) l[k++]=L[i++];
		else l[k++]=R[j++];
	}
	while(i<Lcount) l[k++]=L[i++];
	while(j<Rcount) l[k++]=R[j++];
}
void quick_sort(int *l,int left,int right){
	if(left<right){
		int i=left,j=right+1,pivot=l[left];
		do{
			do i++; while(l[i]<pivot);
			do j--; while(l[j]>pivot);
			if(i<j){
				int temp=l[i];
				l[i]=l[j];
				l[j]=temp;
			}
		}while(i<j);
		int temp=l[left];
		l[left]=l[j];
		l[j]=temp;
		quick_sort(l,left,j-1);
		quick_sort(l,j+1,right);
	}
}
int cmpfunc(const void *a, const void *b){
  return (*(int*)a-*(int*)b);
}
void random(int n){
	srand(time(NULL));
	data_set=new int[n];
	for(int i=0;i<n;i++) data_set[i]=rand();
}
