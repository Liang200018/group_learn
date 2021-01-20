#include<stdio.h>
#include<stdlib.h>
struct Dnode {
	int data;
	struct Dnode *pre;
	struct Dnode *next;
}; 
typedef struct Dnode Dnode;

void PrintDLinkList(Dnode *head) {
	Dnode *p;
	p = head->next;
	if(p == NULL) {
		return ;
	}
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}
Dnode* CreateDLinkList(Dnode *head) {
	//create double linklist by inserting into the head of linklist
	//ͷ�巨����˫���� 
	Dnode *p; 
	head = (Dnode*)malloc(sizeof(Dnode));
	head->pre = NULL; head->next = NULL;
	for(int i=1; i<10 ;i++) {
		p = (Dnode*)malloc(sizeof(Dnode));
		p->data = i; //input
		p->next = head->next; 
		if(head->next != NULL) {
			head->next->pre = p;//update the next node's pre value 		
		}
		p->pre = head; 
		head->next = p;
	}
	return head;
}
Dnode* CreateDLinkListByTail(Dnode *head) {
	//create double linklist by inserting into the tail of linklist
	//β�巨����˫���� 
	Dnode *p, *tail; 
	head = (Dnode*)malloc(sizeof(Dnode));
	head->pre = NULL; head->next = NULL;
	tail = head; 
	for(int i=1; i<10 ;i++) {
		p = (Dnode*)malloc(sizeof(Dnode));
		p->data = i;
		p->next = NULL; 
		p->pre = tail; tail->next = p; //�޸����һ���ڵ��pre��ǰһ������next 
		tail = tail->next;
	}
	return head;
}
bool ListInsert(Dnode *head, int k, int e) {
	//�ڵ�i��λ�ò���ڵ�,���ҵ�i���ڵ㣬��ǰ�����ڵ� 
	int i=0;
	Dnode *p; Dnode *s;
	p = head; 
	for(i = 0; i < k; ) {
		p = p->next;
		i++;
		if(p == NULL) break;
	}
	if(p == NULL || p == head) //i=0ʱ��pΪhead���޷����� 
		return false;
	s = (Dnode*)malloc(sizeof(Dnode));
	s->data = e;
	s->pre = p->pre; 
	p->pre->next = s; //����ǰ��Ľڵ��nextֵ 
	s->next = p; p->pre = s;
	return true; 
}
bool ListDelete(Dnode *head, int k) {
	//ɾ����i��λ�õĽڵ� 
	int i=0;
	Dnode *p; Dnode *s;
	p = head; 
	for(i = 0; i < k; ) {
		p = p->next;
		i++;
		if(p == NULL) break;
	}
	if(p == NULL || p == head) //i=0ʱ��pΪhead���޷�ɾ�� 
		return false;
	p->pre->next = p->next;
	if(p->next != NULL) {//p�������һ���ڵ� 
		p->next->pre = p->pre; 
	}
	free(p); 
	return true; 
}
int main() {
	Dnode *head; 
	//head = CreateDLinkList(head);
	head = CreateDLinkListByTail(head);
	PrintDLinkList(head);
	ListInsert(head,5,50); printf("\n"); PrintDLinkList(head);
	/*����k=1 
	ListInsert(head,1,10); printf("\n"); PrintDLinkList(head);
	ListInsert(head,12,120); printf("\n"); PrintDLinkList(head);
	����k=12��β��
	*/ 
	//ListDelete(head, 10); printf("\n"); PrintDLinkList(head);
	
}
