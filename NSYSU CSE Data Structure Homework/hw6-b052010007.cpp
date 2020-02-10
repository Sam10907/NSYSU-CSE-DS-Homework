//Author:���R�� B052010007
//Date:Nov. 17,2019
//Purpose:�ϥΤG���j�M���X�X�{�_�Ʀ����Ʀr 
#include <iostream>
#include <vector>
using namespace std;
class TreeNode{ //�إ߾�`�I 
	friend class Tree;
	public:
		TreeNode(int d,TreeNode *l=0,TreeNode *r=0){
			data=d;
			left=l; 
			right=r;
		}
	private:
		int data;
		TreeNode *left;
		TreeNode *right;
};
class Tree{ //�إ߾𪫥� 
	public:
		Tree(){ root=0; }
		void setRoot(){ root=0; }
		void travel(int a); //�𪬨��X�ç�A����m���J�Ʀr 
		void output(TreeNode *r1); //��X�G���j�M�� 
		void deletion(); //�R���`�I 
		TreeNode *root; //�ګ��� 
};
TreeNode *y; //���V��e��m 
TreeNode *pre; //���V��e��m���e�@�Ӧ�m 
vector<int> leftNode; //�x�s���`�I 
vector<int> rightNode; //�x�s�k�`�I 
int main(void){
	Tree t;
	int i;
	while(cin>>i){
		if(i==-1){
			cout<<"node: ";
			t.output(t.root);
			cout<<endl;
			cout<<"left: ";
			for(int i=0;i<leftNode.size();i++) cout<<leftNode[i]<<" ";
			cout<<endl;
			cout<<"right: ";
			for(int i=0;i<rightNode.size();i++) cout<<rightNode[i]<<" ";
			cout<<endl;
			cout<<" "<<endl;
			t.setRoot();
			leftNode.clear();
			rightNode.clear();
			continue;
		}
		t.travel(i);
	}
	return 0;
}
void Tree::travel(int a){ //a����J���Ʀr 
	y=root;
	pre=0;
	if(!root){ //root=0 
		root=new TreeNode(a);
		return;
	} 
	while(y!=0){
		if(y->data==a){ //�p�G��e��m��data�����J���Ʀr,�h�R���Ӹ`�I 
			deletion();
			y=0;
		}
		else if(y->data>a){ //�����䨫�X 
			if(y->left==0){
				y->left=new TreeNode(a);
				y=0;
			}
			else{
				pre=y;
				y=y->left;
			}
		}
		else{ //���k�䨫�X 
			if(y->right==0){
				y->right=new TreeNode(a);
				y=0;
			}
			else{
				pre=y;
			 	y=y->right;
			}
		}
	}
}
void Tree::output(TreeNode *r1){ //�ϥλ��j�L�XBST,�@�}�l�ǤJroot 
	if(r1->left!=0) output(r1->left);
	if(r1->left==0 && r1->right==0){
		cout<<r1->data<<" ";
		leftNode.push_back(0);
		rightNode.push_back(0);
	}
	else if(r1->left!=0 && r1->right!=0){
		cout<<r1->data<<" ";
		leftNode.push_back(r1->left->data);
		rightNode.push_back(r1->right->data);
		output(r1->right);
	}
	else if(r1->left!=0 && r1->right==0){
		cout<<r1->data<<" ";
		leftNode.push_back(r1->left->data);
		rightNode.push_back(0);
	}
	else if(r1->left==0 && r1->right!=0){
		cout<<r1->data<<" ";
		leftNode.push_back(0);
		rightNode.push_back(r1->right->data);
		output(r1->right);
	}
}
void Tree::deletion(){
	if(y->left==0 && y->right==0){ //���R�����`�I�Oleaf node 
		delete y;
		if(pre==0){ //�R�����`�I�O�ڸ`�I 
			root=0;
			return;
		}
		if(pre->left==y) pre->left=0;
		else if(pre->right==y) pre->right=0;
	}
	else if(y->left==0 || y->right==0){ //���R�����`�I���@��son 
		if(pre==0){ //�R�����`�I�O�ڸ`�I
			if(y->left){
				root=y->left;
				delete y;
			}else{
				root=y->right;
				delete y;
			}
			return;
		}
		if(pre->left==y){
			if(y->left){
				pre->left=y->left;
				delete y;
			}else{
				pre->left=y->right;
				delete y;
			}
		}
		else if(pre->right==y){
			if(y->left){
				pre->right=y->left;
				delete y;
			}else{
				pre->right=y->right;
				delete y;
			}
		}
	}
	else{ //���R�����`�I��2��son,�ϥ�inorder predecessor 
		TreeNode *x=y->left;
		TreeNode *prex=y;
		while(x->right!=0){ //��̥k�䪺�`�I 
			prex=x;	
			x=x->right;
		}
		y->data=x->data;
		if(x->left==0 && x->right==0){ //�R���̥k�䪺�`�I�B�Ӹ`�I��leaf node 
			delete x;
			if(prex==y) y->left=0;
			else prex->right=0;
		}
		else{ //�R���̥k�䪺�`�I�B�Ӹ`�I���l�`�I 
			if(prex==y){
				y->left=x->left;
				delete x;
			}
			else{
				prex->right=x->left;
				delete x;
			}
		}
	}
}
