//Author:B052010007 王昱翔
//Date:Nov. 2,2019
//Purpose:使用鏈結串列實作多項式運算 
#include <iostream>
using namespace std;
class ChainNode{
	friend class Polynomial;
	public:
		ChainNode(float c,float e,ChainNode *l=0) //c為多項式的係數,e為次方數 
		{
			coefficient=c;
			exponent=e;
			link=l;
		}
	private:
		float coefficient;
		float exponent;
		ChainNode *link;
};
class Polynomial{ //多項式物件 
	public:
		Polynomial(){first=0;}
		void insert(float c,float e); //插入節點 
		Polynomial operator +(Polynomial& p);
		Polynomial operator *(Polynomial& p);
		void output(); //輸出串列的內容 
		void Simplification_Sort(); //多項式的化簡和排序 
	private:
		ChainNode *first;
		ChainNode *x;
};
int main(void){
	int p=1,q=1,Case=1;
	while(p!=0 || q!=0){
		cout<<"多項式P的項數:";
		cin>>p; //輸入多項式P的項數 
		float c; //係數 
		float e; //次方 
		Polynomial A,B,C,D;
		for(int i=1;i<=p;i++){ //依序輸入係數和次方 
			cin>>c>>e;
			A.insert(c,e);
		}
		cout<<"多項式Q的項數:";
		cin>>q; //輸入多項式Q的項數 
		for(int i=1;i<=q;i++){
			cin>>c>>e;
			B.insert(c,e);
		}
		if(p==0 && q==0){
			cout<<"End!"<<endl;
			break; 
		}
		C=A+B;
		D=A*B;
		cout<<"Case "<<Case<<":"<<endl;
		cout<<"ADD"<<endl;
		C.output();
		cout<<"MULTIPLY"<<endl;
		D.output();
		Case++;
	}
	return 0;
}
void Polynomial::insert(float c,float e){
	if(first){
		x->link=new ChainNode(c,e);
		x=x->link;
	}else{
		first=new ChainNode(c,e);
		x=first;
	}
}
void Polynomial::output(){
	ChainNode *y=first;
	if(y==0) cout<<0<<" "<<0<<endl;
	while(y){
		cout<<y->coefficient<<" "<<y->exponent<<endl;
		y=y->link;
	}
}
Polynomial Polynomial::operator +(Polynomial& p)
{
	Simplification_Sort(); //先化簡和排序 
	p.Simplification_Sort();
	Polynomial c;
	ChainNode *x=first;
	ChainNode *y=p.first;
	float f;
	while(x!=0 || y!=0){
		if(x==0){ 
			f=y->coefficient;
			if(f) c.insert(f,y->exponent); //如果係數不為零則插入串列 
			y=y->link;
			continue;
		}
		if(y==0){
			f=x->coefficient;
			if(f) c.insert(f,x->exponent);
			x=x->link;
			continue;
		}
		else if(x->exponent == y->exponent){
			f=x->coefficient+y->coefficient;
			if(f) c.insert(f,x->exponent);
			x=x->link;
			y=y->link;
		}
		else if(x->exponent > y->exponent){
			f=x->coefficient;
			if(f) c.insert(f,x->exponent);
			x=x->link;
		}
		else if(x->exponent < y->exponent){
			f=y->coefficient;
			if(f) c.insert(f,y->exponent);
			y=y->link;
		}
	}
	return c;
}
void Polynomial::Simplification_Sort(){
	if(first==0 || first->link==0) return;
	//多項式化簡 
	ChainNode *y=first;
	ChainNode *y1=first->link;
	ChainNode *temp=y; //暫存前一個節點以便之後需要刪除某個節點 
	while(y){
		while(y1){
			if(y->exponent==y1->exponent){ //如果次方相同則化簡 
				y->coefficient=y->coefficient+y1->coefficient;
				temp->link=y1->link;
				delete y1;
				y1=temp->link;
				continue;
			}
			temp=y1;
			y1=y1->link;
		}
		y=y->link;
		if(y==0) continue;
		y1=y->link;
		temp=y;
	}
	//多項式排序
	y=first;
	y1=first->link;
	while(y){ //使用選擇排序法由大到小排列 
		while(y1){
			if(y->exponent < y1->exponent){
				float t=y->coefficient;
				float t1=y->exponent;
				y->exponent=y1->exponent;
				y->coefficient=y1->coefficient;
				y1->exponent=t1;
				y1->coefficient=t;
			}
			y1=y1->link;
		}
		y=y->link;
		if(y==0) continue;
		y1=y->link;
	} 
}
Polynomial Polynomial::operator *(Polynomial& p)
{
	Simplification_Sort();
	p.Simplification_Sort();
	Polynomial c;
	ChainNode *y=first;
	ChainNode *y1=p.first;
	float fc,fe;
	while(y){
		while(y1){
			fc=y->coefficient*y1->coefficient;
			fe=y->exponent+y1->exponent;
			if(fc!=0) c.insert(fc,fe);
			y1=y1->link;
		}
		y=y->link;
		y1=p.first;
	}
	c.Simplification_Sort(); //乘完之後還要再化簡 
	return c;
}
