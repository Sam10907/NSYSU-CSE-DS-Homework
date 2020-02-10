//Author:B052010007 ���R��
//Date:Nov. 2,2019
//Purpose:�ϥ��쵲��C��@�h�����B�� 
#include <iostream>
using namespace std;
class ChainNode{
	friend class Polynomial;
	public:
		ChainNode(float c,float e,ChainNode *l=0) //c���h�������Y��,e������� 
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
class Polynomial{ //�h�������� 
	public:
		Polynomial(){first=0;}
		void insert(float c,float e); //���J�`�I 
		Polynomial operator +(Polynomial& p);
		Polynomial operator *(Polynomial& p);
		void output(); //��X��C�����e 
		void Simplification_Sort(); //�h��������²�M�Ƨ� 
	private:
		ChainNode *first;
		ChainNode *x;
};
int main(void){
	int p=1,q=1,Case=1;
	while(p!=0 || q!=0){
		cout<<"�h����P������:";
		cin>>p; //��J�h����P������ 
		float c; //�Y�� 
		float e; //���� 
		Polynomial A,B,C,D;
		for(int i=1;i<=p;i++){ //�̧ǿ�J�Y�ƩM���� 
			cin>>c>>e;
			A.insert(c,e);
		}
		cout<<"�h����Q������:";
		cin>>q; //��J�h����Q������ 
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
	Simplification_Sort(); //����²�M�Ƨ� 
	p.Simplification_Sort();
	Polynomial c;
	ChainNode *x=first;
	ChainNode *y=p.first;
	float f;
	while(x!=0 || y!=0){
		if(x==0){ 
			f=y->coefficient;
			if(f) c.insert(f,y->exponent); //�p�G�Y�Ƥ����s�h���J��C 
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
	//�h������² 
	ChainNode *y=first;
	ChainNode *y1=first->link;
	ChainNode *temp=y; //�Ȧs�e�@�Ӹ`�I�H�K����ݭn�R���Y�Ӹ`�I 
	while(y){
		while(y1){
			if(y->exponent==y1->exponent){ //�p�G����ۦP�h��² 
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
	//�h�����Ƨ�
	y=first;
	y1=first->link;
	while(y){ //�ϥο�ܱƧǪk�Ѥj��p�ƦC 
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
	c.Simplification_Sort(); //���������٭n�A��² 
	return c;
}
