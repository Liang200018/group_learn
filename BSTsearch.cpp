#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
struct node {
	int key;
	struct node *left;
	struct node *right;
};
struct AVLNode {
	int key;
	struct AVLNode *left;
	struct AVLNode *right;
	int height; 
};
typedef struct node Node;
typedef struct AVLNode AVLNode;
int InsertBST(Node *&p, int k) {
	if(p == NULL ) {
		p = (Node *)malloc(sizeof(Node));
		p->key = k; p->left = p->right = NULL;
		return 1;
	}
	else {
		if(k == p->key){
			return 0;
		}
		else if(k < p->key) {
			return InsertBST(p->left, k);
		}
		else {
			return InsertBST(p->right, k);	
		}
	}
}
int GetNodeHeight(AVLNode *&p)
{
    if (p != NULL)    //若不为空子树
    {
        if (p->left == NULL && p->right == NULL)    //若为叶子节点
        {
        	p->height = 1;
            return 1;    
        }
        else {
        	int a, b;
        	a = GetNodeHeight(p->left);
			b = GetNodeHeight(p->right);
			if (a < b) {
				p->height = p->right->height + 1;
            	return b + 1;
        	}
	        else {
	        	p->height += p->left->height + 1;
	            return a + 1;
	        }
		}
    }
    else    //若为空子树
    {
        return 0;
    }
}
void LL_Rotation(AVLNode *&p) {
	AVLNode *temp;
	temp = p;
	p = p->left; //p保存失衡节点的左子树 
	temp->left = p->right;
	p->right = temp; 
	p->height = GetNodeHeight(p);
}
void RR_Rotation(AVLNode *&p) {
	AVLNode *temp;
	temp = p; //
	p = p->right; //p保存失衡节点的右子树 
	temp->right = p->left;
	p->left = temp; 
	p->height = GetNodeHeight(p);
}
void LR_Rotation(AVLNode *&p) {
	AVLNode *temp;
	temp = p;
	p = p->left->right;
	temp->left->right = p->left;
	p->left = temp->left; //新节点的左子树是旧节点的左子树 
	temp->left = p->right;
	p->right = temp; 
	p->height = GetNodeHeight(p);
}
void RL_Rotation(AVLNode *&p) {
	AVLNode *temp;
	temp = p;
	p = p->right->left;
	temp->right->left = p->right;
	p->right = temp->right;
	temp->right = p->left;
	p->left = temp;
	p->height = GetNodeHeight(p);
}
int InsertAVL(AVLNode *&p, int k) {
	if(p == NULL) {
		p = (AVLNode*)malloc(sizeof(AVLNode));
		p->key = k; p->left = p->right = NULL;
		p->height = GetNodeHeight(p);
	}
	else if(k < p->key) {
		InsertAVL(p->left, k); //插入左子树
		p->height = GetNodeHeight(p);  
		//找到失衡节点 
		if(GetNodeHeight(p->left) - GetNodeHeight(p->right) > 1) {
			printf("失衡点：%d ", p->key);
			if(GetNodeHeight(p->left->left) - GetNodeHeight(p->left->right) == 1) {
				LL_Rotation(p); printf("LL\n");
			}
			else {
				LR_Rotation(p); printf("LR\n");
			}
		}
		return 1; 
	}
	else if(k > p->key) {
		InsertAVL(p->right, k); 
		p->height = GetNodeHeight(p);  
		if(GetNodeHeight(p->right) - GetNodeHeight(p->left) > 1) {
			printf("失衡点：%d ", p->key);
			if(GetNodeHeight(p->right->right) - GetNodeHeight(p->right->left) == 1) {
				RR_Rotation(p); printf("RR\n");
			}
			else {
				RL_Rotation(p); printf("RL\n");
			}
		}
		return 1; 		
	}
	else if(k == p->key) {
		return 0;
	}
}
Node *CreateBST(int data[], int n) {
	int i;
	Node *root = NULL;
	for(i = 0; i < n; i++)
		InsertBST(root, data[i]);
	return root;
}
void print(Node *&p) {
	if(p == NULL)
		return;
	print(p->left);
	printf("%d ", p->key);
	print(p->right);
}
void print_height(AVLNode *&p) {
	if(p == NULL)
		return;
	print_height(p->left);
	p->height = GetNodeHeight(p);
	printf("key = %d, height = %d\n", p->key, p->height);
	print_height(p->right);
}
void Delete(Node *&p) { 
	Node *q;
	if(p->left == NULL && p->right == NULL) {
		free(p);
	}
	if (p->left == NULL && p->right != NULL) { 
		q = p; p = p->right; 
		free(q);
	}
	if (p->left != NULL && p->right == NULL) { 
		q = p; p = p->left; 
		free(q);
	}
	//既有左子树，也有右子树 
	else {
		q = p;
		p = p->left;
		while(p->right != NULL) {
			p = p->right;
		} 
		q->key = p->key;
		Delete(p);
	}
}
int BSTDelete(Node *&p, int k) {
	if(p == NULL) {
		return 0;
	}
	if(p->key == k) {
		Delete(p);
		return 1;
	}
	else if (k < p->key) {
		BSTDelete(p->left, k);
	}
	else {
		BSTDelete(p->right, k);
	}
}
void test_BST() {
	int data[7] = {5, 4, 3, 2, 9, 11, 56};
	Node *root=NULL;
	root = CreateBST(data, 7);
	print(root); printf("\n");
	BSTDelete(root, 4);
	print(root);
}

void test_InsertAVL() {
	int data[7][MAXSIZE] = {
							{16, 3, 7, 11, 9, 26, 18, 14, 15},
							{5, 4, 2}, //LL
							{4, 2, 6, 5, 8, 9}, //RR
							{16, 3, 7}, //LR
							{7, 3, 11, 9, 16, 8}, //RL
							{1}, 
							{6, 4, 8, 3, 5, 7, 9},
						};
	int i, j; int len[7] = {9, 3, 6, 3, 6, 1, 7};
	for(j = 0; j < 1; j++) {
		AVLNode *p = NULL;
		for(i = 0; i < len[j]; i++) {
			printf("插入：%d\n", data[j][i]);
			InsertAVL(p, data[j][i]);
			print_height(p); printf("\n");	
		}
		print_height(p); printf("\n");
	}
	
}
int main() {
	test_InsertAVL();
} 
