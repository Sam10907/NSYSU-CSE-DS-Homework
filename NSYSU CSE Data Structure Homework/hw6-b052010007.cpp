//Author:王昱翔 B052010007
//Date:Nov. 17,2019
//Purpose:使用二元搜尋樹找出出現奇數次的數字 
#include <iostream>
#include <vector>
using namespace std;
class TreeNode{ //建立樹節點 
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
class Tree{ //建立樹物件 
	public:
		Tree(){ root=0; }
		void setRoot(){ root=0; }
		void travel(int a); //樹狀走訪並找適當的位置插入數字 
		void output(TreeNode *r1); //輸出二元搜尋樹 
		void deletion(); //刪除節點 
		TreeNode *root; //根指標 
};
TreeNode *y; //指向當前位置 
TreeNode *pre; //指向當前位置的前一個位置 
vector<int> leftNode; //儲存左節點 
vector<int> rightNode; //儲存右節點 
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
void Tree::travel(int a){ //a為輸入的數字 
	y=root;
	pre=0;
	if(!root){ //root=0 
		root=new TreeNode(a);
		return;
	} 
	while(y!=0){
		if(y->data==a){ //如果當前位置的data等於輸入的數字,則刪除該節點 
			deletion();
			y=0;
		}
		else if(y->data>a){ //往左邊走訪 
			if(y->left==0){
				y->left=new TreeNode(a);
				y=0;
			}
			else{
				pre=y;
				y=y->left;
			}
		}
		else{ //往右邊走訪 
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
void Tree::output(TreeNode *r1){ //使用遞迴印出BST,一開始傳入root 
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
	if(y->left==0 && y->right==0){ //欲刪除的節點是leaf node 
		delete y;
		if(pre==0){ //刪除的節點是根節點 
			root=0;
			return;
		}
		if(pre->left==y) pre->left=0;
		else if(pre->right==y) pre->right=0;
	}
	else if(y->left==0 || y->right==0){ //欲刪除的節點有一個son 
		if(pre==0){ //刪除的節點是根節點
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
	else{ //欲刪除的節點有2個son,使用inorder predecessor 
		TreeNode *x=y->left;
		TreeNode *prex=y;
		while(x->right!=0){ //找最右邊的節點 
			prex=x;	
			x=x->right;
		}
		y->data=x->data;
		if(x->left==0 && x->right==0){ //刪除最右邊的節點且該節點為leaf node 
			delete x;
			if(prex==y) y->left=0;
			else prex->right=0;
		}
		else{ //刪除最右邊的節點且該節點有子節點 
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
