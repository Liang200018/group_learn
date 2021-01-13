#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 50
struct node {
	char ch;
	struct node *lchild;
	struct node *rchild;
}; 
typedef node BTnode; 
struct ParentNode {
	BTnode bnode;//֮ǰ�Ķ�������� 
	struct ParentNode *f; //���ڵ�ĵ�ַ 
};
typedef struct ParentNode PNode;

BTnode* pre_order(BTnode *p) { 
	if(p == NULL) {
		return NULL; 
	}
	printf("%c -> ", p->ch);
	pre_order(p->lchild);
	pre_order(p->rchild);
}
BTnode* in_order(BTnode *p) { 
	//������� 
	if(p == NULL) {
		return NULL; 
	}
	in_order(p->lchild);
	printf("%c -> ", p->ch);
	in_order(p->rchild);
}
BTnode* post_order(BTnode *p) { 
	//������� 
	if(p == NULL) {
		return NULL; 
	}
	post_order(p->lchild);
	post_order(p->rchild);
	printf("%c -> ", p->ch);
}
char * save_order(BTnode *p) {
	//����������˳�� 
	//�ö��аѱ���˳�����һ���ַ����У�����ʹ�û��ζ��� 
	char ch[MAXSIZE];	 
	int i = 0;
	BTnode *q; //����ÿһ���ڵ� 
	BTnode *qu[MAXSIZE]; int front, tail;
	front = tail = -1;
	tail++;
	qu[tail] = p; 
	while(tail != front) {
		q = qu[++front];
		ch[i] = q->ch; i++;
		//�ѳ����еĽڵ����ڵ�����β 
		if(q->lchild != NULL) {
			tail++; qu[tail] = q->lchild;
		}
		if(q->rchild != NULL) {
			tail++; qu[tail] = q->rchild;
		}
	}
	return ch;
}
char * save_pre_order(BTnode *p) {
	//����ǰ�����˳�� 
	//�ѱ���˳�����һ���ַ����� 
	char ch[MAXSIZE];	 
	int i = 0;
	BTnode *q; //����ÿһ���ڵ� 
	BTnode *qu[MAXSIZE]; int front, tail;
	front = tail = -1;
	tail++;
	qu[tail] = p; 
	return ch;
}
int tree_depth(BTnode *p) {
	int left, right, depth;
	if(p == NULL) return 0;//ֻ��һ������ 
	if(p->lchild == NULL && p->rchild == NULL) {
		return 0;
	}
	left = tree_depth(p->lchild);
	right = tree_depth(p->rchild);
	depth = (left >= right) ? left+1 : right+1;
	return depth;
}
int node_number(BTnode *p) {
	//�ݹ���������
	int left, right;
	if(p == NULL) return 0;
	else {
		left = node_number(p->lchild);
		right = node_number(p->rchild);
		return left + right + 1;		
	}
}
int leafnode_number(BTnode *p) {
	//�ݹ����Ҷ�ӽ�����
	int leaf_number;
	if(p == NULL) return 0;
	else {
		if(p->lchild == NULL && p->rchild == NULL) {
			leaf_number = 1;
			}
		else leaf_number = leafnode_number(p->lchild) + leafnode_number(p->rchild);
		return leaf_number;
	}
} 
int get_one_degree(BTnode *p) {
	//��������ֻ��һ�����ӽ��Ľ�����
	int one_number;
	if(p == NULL) return 0;
	else {
		//Ҷ�ӽڵ� 
		if(p->lchild == NULL && p->rchild == NULL) {
			one_number = 1;
			}
		//ֻ��һ��Ҷ�ӽڵ�ĸ��ڵ� 
		else if(p->lchild == NULL || p->rchild == NULL) {
			one_number = 1;
		}
		//�������ڵ�ĸ��ڵ� 
		else one_number = get_one_degree(p->lchild) + get_one_degree(p->rchild);
		return one_number;
	} 
}
BTnode *copy_tree(BTnode *p, BTnode *copy) {
	if(p == NULL) {
		copy = NULL;
		return copy;
	}
	
	else {
		copy = (BTnode*)malloc(sizeof(BTnode));
		//��㸴�� 
		copy->ch = p->ch;
		copy->lchild = p->lchild;
		copy->rchild = p->rchild;		
		copy_tree(p->lchild, copy->lchild); //���������� 
		copy_tree(p->rchild, copy->rchild);
	}
	return copy;
}
void print_path(BTnode *p) {
	//����������д�ÿ��Ҷ�ӽ�㵽������·�� 
	//��ÿ������ָ��ת,��Ҫ����ǰһ����� 
}
BTnode* string_to_tree(BTnode *pt, char s[]) {
	//���ַ���ת��Ϊ�� 
	BTnode *qu[MAXSIZE];
	BTnode *p;
	int i=0; int top; int k;
	top = -1;
	pt = NULL;
	while(s[i] != '\0') {
		switch (s[i]) {
			case '(':  {
				top++; qu[top] = p;
				k = 1;
				break;
			}
			case ')':  top--; break; 
			case ',':  {
				k = 2;
				break;
			}
			default :  {
				p = (BTnode *)malloc(sizeof(BTnode)); p->ch = s[i];
				p->lchild = p->rchild =NULL; 
				if(pt == NULL) pt = p;
				else { 
					switch(k) {
						case 1: {
							qu[top]->lchild = p;//��һ���ڵ�Ϊ��β�Ľڵ�������
							break;
						}
						case 2: {
							qu[top]->rchild = p;
							break;
						}
						//printf("β����%c ", qu[top]->ch);
					} 
				}
			}
		}
		i++;
	}
	return pt;
}
void test_string_to_tree() {
	BTnode *pt[3];
	char s[5][MAXSIZE] = {
			"A(B(D,E),C(F,G))",
			"A(B(D,E),C(F,))", //û���ҽڵ� 
			"A(B(,E),C(F,G))" //û����ڵ� 
		};
	pt[0] = string_to_tree(pt[0], s[0]);
	pt[1] = string_to_tree(pt[1], s[1]);
	pt[2] = string_to_tree(pt[2], s[2]);
	pre_order(pt[0]); printf("\n");
	pre_order(pt[1]); printf("\n");
	pre_order(pt[2]); printf("\n");
}  
void test_tree_depth() {
	//����������� 
	int dept[5]; int count=0;
	BTnode *pt;
	char s[5][MAXSIZE] = {
			"A(B(D,E),C(F,G))",
			"A(B(D,E),C(F,))", //û���ҽڵ� 
			"A(B(,E),C(F,G))", //û����ڵ�
			"A(B(D,E(,H)),C(F,G(I(,J),)))" //û����ڵ� 
		};
	int real_dept[5] = {2, 2, 2, 4};
	//����������� 
	for(int i =0; i < 5; i++) {
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ��
		dept[i] = tree_depth(string_to_tree(pt, s[i]));
	} 
	for(int i = 0; i<5; i++){ 
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ�� 
		if (dept[i] != real_dept[i]) {
			//printf("%d\n", dept[i]);
			count++; 
			printf("%s failed to pass test! %d!=%d\n", s[i], dept[i], real_dept[i]);
		} 
		else {
			printf("%s %d=%d\n", s[i], dept[i], real_dept[i]);
		}
	}
	printf("%d tests failed to pass!\n", count);
} 
void test_node_number() {
	//���Խ����� 
	int number[5]; int count=0;
	BTnode *pt;
	char s[5][MAXSIZE] = {
			"A(B(D,E),C(F,G))",
			"A(B(D,E),C(F,))", //û���ҽڵ� 
			"A(B(,E),C(F,G))", //û����ڵ�
			"A(B(D,E(,H)),C(F,G(I(,J),)))" //û����ڵ� 
		};
	int real_number[5] = {7, 6, 6, 10};
	//����ڵ���� 
	for(int i =0; i < 5; i++) {
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ��
		number[i] = node_number(string_to_tree(pt, s[i]));
	} 
	for(int i = 0; i<5; i++){ 
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ�� 
		if (number[i] != real_number[i]) {
			count++; 
			printf("%s failed to pass test! %d!=%d\n", s[i], number[i], real_number[i]);
		} 
		else {
			printf("%s %d=%d\n", s[i], number[i], real_number[i]);
		}
	}
	printf("%d tests failed to pass!\n", count);
} 
void test_leafnode_number() {
	//����Ҷ�ӽ����� 
	int number[5]; int count=0;
	BTnode *pt;
	char s[5][MAXSIZE] = {
			"A(B(D,E),C(F,G))",
			"A(B(D,E),C(F,))", //û���ҽڵ� 
			"A(B(,E),C(F,G))", //û����ڵ�
			"A(B(D,E(,H)),C(F,G(I(,J),)))" //û����ڵ� 
		};
	int real_number[5] = {4, 3, 3, 4};
	//����ڵ���� 
	for(int i =0; i < 5; i++) {
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ��
		number[i] = leafnode_number(string_to_tree(pt, s[i]));
	} 
	for(int i = 0; i<5; i++){ 
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ�� 
		if (number[i] != real_number[i]) {
			count++; 
			printf("%s failed to pass test! %d!=%d\n", s[i], number[i], real_number[i]);
		} 
		else {
			printf("%s %d=%d\n", s[i], number[i], real_number[i]);
		}
	}
	printf("%d tests failed to pass!\n", count);
} 
void test_get_one_degree() {
	//����Ҷ�ӽ����� 
	int number[5]; int count=0;
	BTnode *pt;
	char s[5][MAXSIZE] = {
			"A(B(D,E),C(F,G))",
			"A(B(D,E),C(F,))", //û���ҽڵ� 
			"A(B(,E),C(F,G))", //û����ڵ�
			"A(B(D,E(,H)),C(F,G(I(,J),)))" //û����ڵ� 
		};
	int real_number[5] = {4, 3, 3, 4};
	//����ڵ���� 
	for(int i =0; i < 5; i++) {
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ��
		number[i] = get_one_degree(string_to_tree(pt, s[i]));
	} 
	for(int i = 0; i<5; i++){ 
		if (*s[i] == '\0') break; //ֻ�ж����е��ַ���ָ�� 
		if (number[i] != real_number[i]) {
			count++; 
			printf("%s failed to pass test! %d!=%d\n", s[i], number[i], real_number[i]);
		} 
		else {
			printf("%s %d=%d\n", s[i], number[i], real_number[i]);
		}
	}
	printf("%d tests failed to pass!\n", count);
} 
void test_copy_tree() {
	BTnode *pt, *copy;
	//���ַ���ת��Ϊ����A(B(D, E), C(F,)) 
	char s[MAXSIZE] = "A(B(D,E),C(F,G))";
	pt = string_to_tree(pt, s);
	pre_order(pt); printf("\n");
	copy = copy_tree(pt, copy);
	pre_order(copy); printf("\n");
}
int main() {
	BTnode *pt;
	//���ַ���ת��Ϊ����A(B(D, E), C(F,)) 
	char s[MAXSIZE] = "A(B(,E),C(F,G))";
	char save[MAXSIZE]; //�������˳�� 
	int depth;
	pt = string_to_tree(pt, s);
	//��֤
	pre_order(pt); printf("\n");
	in_order(pt); printf("\n");
	post_order(pt); printf("\n");
	depth = tree_depth(pt);
	test_tree_depth();
	test_node_number(); 
	test_leafnode_number();
	test_get_one_degree();
	test_copy_tree();
//�����α���˳�� 
//	strcpy(save,save_order(pt));
//	printf("%s", save);
	//test_string_to_tree(); 
} 
