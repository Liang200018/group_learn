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
	//头插法创建双链表 
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
	//尾插法创建双链表 
	Dnode *p, *tail; 
	head = (Dnode*)malloc(sizeof(Dnode));
	head->pre = NULL; head->next = NULL;
	tail = head; 
	for(int i=1; i<10 ;i++) {
		p = (Dnode*)malloc(sizeof(Dnode));
		p->data = i;
		p->next = NULL; 
		p->pre = tail; tail->next = p; //修改最后一个节点的pre和前一个结点的next 
		tail = tail->next;
	}
	return head;
}
bool ListInsert(Dnode *head, int k, int e) {
	//在第i个位置插入节点,查找第i个节点，在前面插入节点 
	int i=0;
	Dnode *p; Dnode *s;
	p = head; 
	for(i = 0; i < k; ) {
		p = p->next;
		i++;
		if(p == NULL) break;
	}
	if(p == NULL || p == head) //i=0时，p为head，无法插入 
		return false;
	s = (Dnode*)malloc(sizeof(Dnode));
	s->data = e;
	s->pre = p->pre; 
	p->pre->next = s; //更改前面的节点的next值 
	s->next = p; p->pre = s;
	return true; 
}
bool ListDelete(Dnode *head, int k) {
	//删除第i个位置的节点 
	int i=0;
	Dnode *p; Dnode *s;
	p = head; 
	for(i = 0; i < k; ) {
		p = p->next;
		i++;
		if(p == NULL) break;
	}
	if(p == NULL || p == head) //i=0时，p为head，无法删除 
		return false;
	p->pre->next = p->next;
	if(p->next != NULL) {//p不是最后一个节点 
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
	/*测试k=1 
	ListInsert(head,1,10); printf("\n"); PrintDLinkList(head);
	ListInsert(head,12,120); printf("\n"); PrintDLinkList(head);
	测试k=12，尾部
	*/ 
	//ListDelete(head, 10); printf("\n"); PrintDLinkList(head);
	
}
