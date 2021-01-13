#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h> //sleep�۲���ͣ 

struct Student {
	char no[10];
	char name[20];
	float grade;
};
struct SNode {
	char no[10];
	char name[20];
	float grade;
	struct SNode *next;
};
typedef struct SNode SNode;
typedef struct Student Student;

SNode * GetStudent(SNode *head, int n);
void Print(SNode *head);
void search_by_name(SNode *head, char name[20]);
void search_by_loc(SNode *head, int k);
void insert_by_loc(SNode *head, int k, Student *s);
void delete_by_loc(SNode *head, int k);
int get_length(SNode *head);
SNode * test_get(); //���Ժ��� 
void test_search_by_name();
SNode* m(int n);
int main();

SNode * GetStudent(SNode *head, int n){
	//����ѧ����Ϣ 
	int i = 0;
	SNode *s;
	while(i<n){
		s = (SNode*)malloc(sizeof(SNode));
		scanf("%s %s %f", &s->no, &s->name, &s->grade);
		s->next = NULL; 
		//printf("%s %s %f\n", s->no, s->name, s->grade);
		i = i + 1;
		s->next = head->next;
		head->next = s;
	}
	return head;
}
void Print(SNode *head) {
	//��������е�ѧ����Ϣ 
	SNode *p;
	int i=1;
	printf("%-6s%-10s%-10s%-10s\n","����", "ѧ��", "����", "�ɼ�");
	for(p=head->next; p != NULL; ){
		printf("%-6d%-10s%-10s%-0.2f\n", i++, p->no, p->name, p->grade);
		p = p->next;
	}
}
SNode * test_get(){
	//���ڸ��Ĳ��Խű� 
	int i=0;
	SNode *p, *head;
	head = (SNode*)malloc(sizeof(SNode));
	head->next = NULL;
	SNode s[5] = {
					{"2011", "lzy", 81},
					{"2012", "lzy", 82},
					{"2013", "lzc", 83},
					{"2014", "lzy", 84},
					{"2015", "lzy", 85}
				};
	while(i<5){
		p = (SNode*)malloc(sizeof(SNode));
		strcpy(p->no,s[i].no); strcpy(p->name,s[i].name); p->grade = s[i].grade;
		p->next = NULL; 
		i = i + 1;
		p->next = head->next;
		head->next = p;
	}
	Print(head);
	return head;
}
void test_search_by_name() {
	//���԰����ֲ��� 
	SNode *head, *p;
	char ch[20] = "lzy";
	head = test_get();
	for(p = head->next; p != NULL; ) {
		if(strcmp(p->name, ch) == 0){
			printf("%s:%s %0.2f\n", p->name, p->no, p->grade);
			break;
		}
		p = p->next;
	}
	if(p == NULL)
		printf("û���ҵ�%s����Ϣ", ch); 
}
void test_insert_delete() {
	SNode *head, *p; 
	char ch[20] = "lzy";
	int number;
	head = test_get();
	search_by_name(head, ch);
	search_by_loc(head, 2);
	//Sleep(5000);
	Student s = {"2018", "��־��", 100};
	puts("����"); 
	number = get_length(head);
	printf("%d\n", number);
	insert_by_loc(head, 4, &s);
	Print(head);
	puts("ɾ��");
	number = get_length(head);
	printf("%d\n", number);
	delete_by_loc(head,4);
	Print(head);
} 
SNode* m(int n) {
	//������ѧ����Ϣ 
	int i=0;
	SNode *s; SNode *p, *head;
	head = (SNode*)malloc(sizeof(SNode));
	head->next = NULL;
	GetStudent(head, n);
	//Print(head);
	return head;
}
void search_by_name(SNode *head, char name[20]) {
	SNode *p;
	int number=0;
	for(p = head->next; p != NULL; ) {
		if(strcmp(p->name, name) == 0){
			printf("%s:%s %0.2f\n", p->name, p->no, p->grade);
			number++;
		}
		p = p->next;
	}
	printf("����%s��%d�ɼ���¼\n", name, number); 
	
}
void search_by_loc(SNode *head, int k) {
	//����ָ����λ�ý��в��� 
	SNode *p;
	int i=1;
	for(p = head->next; p != NULL; i++) {
		if(i == k){
			printf("%s:%s %0.2f\n", p->name, p->no, p->grade);
			break;
		}
		p = p->next;
	}
	if(p == NULL)
		printf("û���ҵ���%d������Ϣ", k); 
}
void insert_by_loc(SNode *head, int k, Student *s) {
	//���뵽����ĵ�k��λ�ã�k=[1, k] 
	SNode *p, *q, *newnode;
	int i=1;
	for(p = head; p != NULL; i++) {
		if(i <= k-1){
			p = p->next;	
		}
		else if(i=k){
			newnode = (SNode*)malloc(sizeof(SNode));
			strcpy(newnode->no, s->no); strcpy(newnode->name, s->name); newnode->grade = s->grade;
			newnode->next = p->next;
			p->next = newnode;
			break;			
		}
	}	 
	if(p == NULL)
		printf("��%d��λ��û���ҵ�", k);
} 

void delete_by_loc(SNode *head, int k) {
	//���뵽����ĵ�k��λ�ã�k=[1, k] 
	SNode *p, *q;
	int i=1;
	for(p = head; p != NULL; i++) {
		if(i <= k-1){
			p = p->next;	
		}
		else break;
	}	 
	if(p == NULL)
		printf("��%d��λ��û���ҵ�", k);
	else{
		q = p->next;
		p->next = q->next;
		free(q);
	}
}
int get_length(SNode *head) {
	SNode *p;
	int i=0;
	for(p=head->next; p != NULL; ){
		i = i + 1;
		p = p->next;
	}
	return i;
}

int MenuSelect() {
	int choice;
	puts("********************");
	puts("ѧ���ɼ�����ϵͳ");
	puts("1������ѧ����Ϣ");
	puts("2������ѧ����Ϣ"); 
	puts("3��ɾ��ѧ����Ϣ");
	puts("4����ѯѧ����Ϣ");
	puts("5������ѧ����Ϣ"); 
	puts("6����ӡѧ����Ϣ");
	puts("7�����Ե�ѧ����Ϣ"); 
	puts("********************");
	printf("%s","ѡ��(1��2��3��4��5��6��7)��"); scanf("%d", &choice);
	return choice;
} 
SNode* PrintIn() {
	//1������ѧ����Ϣ 
	int choice, i=1, n;
	SNode *head; 
	puts("********************");
	puts("����ѧ����Ϣ");
	printf("%s", "step 1������ѧ������:"); scanf("%d", &n);
	puts("step 2������ѧ����Ϣ(ѧ�� ���� �ɼ�)"); 
	head = m(n); 
	puts("********************");
	return head;
} 
int PrintInsert(SNode *head) {
	//2������ѧ����Ϣ 
	int choice; int k; 
	Student s;
	puts("********************");
	puts("����ѧ����Ϣ"); 
	Print(head);
	printf("%s", "step 1����������ѧ����Ϣ(ѧ�� ���� �ɼ�):"); 
	scanf("%s %s %f", s.no, s.name, &s.grade);
	printf("%s", "step 2����������λ��:"); scanf("%d", &k);
	insert_by_loc(head, k, &s);
} 
void PrintDelete(SNode *head) {
	//3�� ɾ��ѧ����Ϣ
	int k;
	Print(head);
	printf("%s", "����ɾ����λ��:"); scanf("%d", &k);
	delete_by_loc(head, k); 
}
void PrintSearch(SNode *head) {
	//4�� ��ѯѧ����Ϣ
	int choice;
	printf("1�������ֲ�ѯ\t2����λ�ò�ѯ\tѡ�"); scanf("%d", &choice); 
	if(choice == 1){
		char name[20]; 
		printf("%s", "��������:"); scanf("%s", name);
		search_by_name(head, name); 
	}
	else if(choice == 2){
		int k; 
		printf("%s", "����λ��:"); scanf("%d", &k);
		search_by_loc(head, k);	
	}
 
}
int main()
{
	int choice; int count=1;
	SNode *s; SNode *p, *head, *re;
	printf("***��ʾ�������������ѧ����Ϣ����������[7], [1]Ϊ������Ϣ\n\n"); 
	while(1) {
		printf("IN[%d]\n",count);
		choice = MenuSelect(); printf("\n");
		printf("OUT[%d]\n",count);
		switch(choice) {
			case 1: head = PrintIn(); break;
			case 2: PrintInsert(head); break;
			case 3:	PrintDelete(head); break;
			case 4: PrintSearch(head); break;
			case 5: printf("�����ڴ�\n"); break;
			case 6: Print(head); break;
			case 7: head = test_get(); break;
		}
		printf("\n"); 
		count++;
	}
 } 
