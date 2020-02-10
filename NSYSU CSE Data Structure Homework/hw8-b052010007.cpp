//Author:���R�� B052010007
//Date:Dec .22,2019
//Purpose:�Q��huffman�t��k��@���Y�n�� 
#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <algorithm>
#include <bitset>
#include <cstring>
using namespace std;
class Node{ //huffman��`�I 
	public:
		int val;
		int freq;
		Node *lchild;
		Node *rchild;
		Node(char _val,int _freq,Node *_lchild,Node *_rchild){
			val=_val;
        	freq=_freq;
        	lchild=_lchild;
        	rchild=_rchild;
		}
};
class Table{ //�s�X���� 
	public:
		unsigned char c;
		string s;
		Table(unsigned char _c,string _s){
			c=_c;
			s=_s;
		}
};
deque<Node*> forest; //�x�s�U�Ӹ`�I������
deque<Table> table; //�x�s�s�X��
deque<unsigned char> file_c; //�s���l�ɮ׸�T
bool comp(Node*,Node*); //sort() 
bool comp1(Node*,Node*); //stable_sort()
void printCode(Node*,string); //�N�s�X�s�J�s�X�� 
deque<unsigned long> encode(); //�N��l�ɮ׽s�X���Y 
void decode(long long,bitset<8>,string&,long long&); //�N���Y�ɸѽX���٭� 
int main(int argc,char *argv[]){
	if(!strcmp(argv[2],"-c")){
		//�[���Y 
		int ascii[256]={0};
		ifstream fin(argv[4],ios::binary);
		//Ū���ɮת��� 
		fin.seekg(0,fin.end);
		long long length=fin.tellg(); 
		fin.seekg(0,fin.beg);
		
		unsigned char *buffer=new unsigned char[length];
		fin.read((char*)buffer,length);
		for(long long i=0;i<length;i++){
			file_c.push_back(buffer[i]);
			int index=buffer[i];
			ascii[index]++; //�p��r���X�{�W�v 
		}
		delete [] buffer;
		for(int i=0;i<256;i++){
			if(ascii[i]!=0){
				forest.push_back(new Node(i,ascii[i],NULL,NULL));
			}
		}
		fin.close();
		int size=forest.size();
		for(int i=0;i<size-1;i++){ //�s�@huffman�� 
			sort(forest.begin(),forest.end(),comp);
			stable_sort(forest.begin(),forest.end(),comp1);
			Node *ptr=forest.front(); forest.pop_front();
			Node *ptr1=forest.front(); forest.pop_front();
			if(ptr->val<ptr1->val){
				Node *parent=new Node(ptr->val,ptr->freq+ptr1->freq,ptr,ptr1);
				forest.push_back(parent);
			}
			else{
				Node *parent=new Node(ptr1->val,ptr->freq+ptr1->freq,ptr1,ptr);
				forest.push_back(parent);
			}
		}
		printCode(forest.front(),""); //�x�s�s�X��
		int code_table=table.size(); //�s�X��j�p 
		long long original_byte=file_c.size(); //��l�ɮפj�p 
		deque<unsigned long> d=encode(); //�N�s�X�᪺�줸�զs�Jd 
		int num=0;
		for(int i=0;i<table.size();i++) num+=sizeof(table[i].c)+table[i].s.size()+sizeof(char)*2; //�p��s�X���줸�ռ� 
		long long compress_byte=d.size()+num+sizeof(int)+sizeof(int)+sizeof(long long)*2; //���Y�ɤj�p 
		int ratio=original_byte/compress_byte; //���Y�v 
		ofstream fout(argv[6],ios::binary);
		fout.write((char*) &original_byte,sizeof(long long)); 
		fout.write((char*) &compress_byte,sizeof(long long));
		fout.write((char*) &ratio,sizeof(int));
		fout.write((char*) &code_table,sizeof(int));
		for(int i=0;i<table.size();i++){ //�g�J�s�X�� 
			string s1='='+table[i].s+'\n';
			unsigned char *buffer=new unsigned char[s1.length()+1];
			for(int j=0;j<s1.length()+1;j++){
				if(j==0) buffer[j]=table[i].c;
				else buffer[j]=s1[j-1];
			}
			fout.write((char*)buffer,s1.length()+1);
			delete [] buffer;	
		}
		for(long long i=0;i<d.size();i++){ //�g�J�s�X�᪺�줸�� 
			char cb=d[i]; fout.write(&cb,sizeof(char));
		}
		fout.close();
		cout<<d.size(); //�L�X�s�X�᪺�줸�դj�p 
	}
	else if(!strcmp(argv[2],"-u")){
		//�����Y 
		ifstream fin1(argv[4],ios::binary);
		fin1.seekg(0,fin1.end);
		long long length=fin1.tellg(); 
		fin1.seekg(0,fin1.beg);
		long long original_byte,compress_byte; int ratio,code_table;
		fin1.read((char*) &original_byte,sizeof(long long));
		cout<<original_byte<<endl; //��l�ɦ줸�ռ� 
		fin1.read((char*) &compress_byte,sizeof(long long));
		cout<<compress_byte<<endl; //���Y�ɦ줸�ռ� 
		fin1.read((char*) &ratio,sizeof(int));
		cout<<ratio<<endl; //���Y�v
		fin1.read((char*) &code_table,sizeof(int));
		length=length-24;
		unsigned char *buffer=new unsigned char [length];
		int i=0;
		fin1.read((char*)buffer,length);
		deque<unsigned char> aline;
		Table t(' ',""); 
		while(i<length){ //��X�s�X��
			if(buffer[i]=='=' || buffer[i]=='\n' || buffer[i]=='0' || buffer[i]=='1') cout<<(char)buffer[i];
			else if(0 <= int(buffer[i]) && 127 >= int(buffer[i])) cout<<(char)buffer[i];
			else cout<<+buffer[i];
			aline.push_back(buffer[i]);
			if(buffer[i]=='\n'){
				t.c=aline[0];
				if(aline.size()==1){
					i++;
					continue;
				}
				for(int i1=2;i1<aline.size()-1;i1++){
					t.s+=aline[i1];
				}
				table.push_back(t);
				t.s="";
				aline.clear();
			}
			i++;
			if(table.size()==code_table) break;
		}
		string s("");
		long long count=0;
		while(i<length){ //�ѽX 
			bitset<8> b(buffer[i]);
			decode(original_byte,b,s,count);
			i++;
		}
		fin1.close();
		cout<<file_c.size()<<endl;
		delete [] buffer;
		//��X�s�X���ɮ�
		ofstream fout("code_table.txt",ios::binary);
		for(int i=0;i<table.size();i++){
			string s1='='+table[i].s+'\n';
			unsigned char *buffer=new unsigned char[s1.length()+1];
			for(int j=0;j<s1.length()+1;j++){
				if(j==0) buffer[j]=table[i].c;
				else buffer[j]=s1[j-1];
			}
			fout.write((char*)buffer,s1.length()+1);
			delete [] buffer;	
		}
		fout.close();
		//��X�����Y�᪺�ɮ� 
		ofstream fout1(argv[6],ios::binary);
		unsigned char *file=new unsigned char[file_c.size()];
		for(long long i=0;i<file_c.size();i++) file[i]=file_c[i]; 
		fout1.write((char*)file,sizeof(char)*file_c.size());
		delete [] file; 
		fout1.close();
	}
	return 0;
}
bool comp(Node *a,Node *b){
	return a->val < b->val;
}
bool comp1(Node *a,Node *b){
	return a->freq < b->freq;
}
void printCode(Node *ptr,string s){
	if(ptr->lchild==NULL || ptr->rchild==NULL){
        unsigned char c=ptr->val;
        Table t(c,s);
        table.push_back(t);
        return;
    }
    if(ptr->lchild) printCode(ptr->lchild,s+"0");
    if(ptr->rchild) printCode(ptr->rchild,s+"1");
}
deque<unsigned long> encode(){
	bitset<8> byte;
	deque<unsigned long> db;
	int index=7;
	for(long long j=0;j<file_c.size();j++){
		for(int j1=0;j1<table.size();j1++){
			if(file_c[j]==table[j1].c){
				for(int k=0;k<table[j1].s.size();k++){
					byte[index]=table[j1].s[k]-'0';
					index--;
					if(index<0){
						db.push_back(byte.to_ulong());
						index=7;
					}
				}
				break;
			}
		}
	}
	if(index!=7){
		while(index>-1){
			byte[index]=0;
			index--;
		}
		db.push_back(byte.to_ulong());
	}
	return db;
}
void decode(long long ori,bitset<8> b,string& s,long long& c){
	string sb=b.to_string();
	for(int i=0;i<8;i++){
		s+=sb[i];
		if(c<ori){
			for(int j=0;j<table.size();j++){
				if(s==table[j].s){
					file_c.push_back(table[j].c);
					c++;
					s="";
					break;
				}
			}
		}else break;
	}
}
