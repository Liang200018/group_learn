#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h> //sleep观察暂停 

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
SNode * test_get(); //测试函数 
void test_search_by_name();
SNode* m(int n);
int main();

SNode * GetStudent(SNode *head, int n){
	//输入学生信息 
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
	//输出链表中的学生信息 
	SNode *p;
	int i=1;
	printf("%-6s%-10s%-10s%-10s\n","计数", "学号", "姓名", "成绩");
	for(p=head->next; p != NULL; ){
		printf("%-6d%-10s%-10s%-0.2f\n", i++, p->no, p->name, p->grade);
		p = p->next;
	}
}
SNode * test_get(){
	//便于更改测试脚本 
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
	//测试按名字查找 
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
		printf("没有找到%s的信息", ch); 
}
void test_insert_delete() {
	SNode *head, *p; 
	char ch[20] = "lzy";
	int number;
	head = test_get();
	search_by_name(head, ch);
	search_by_loc(head, 2);
	//Sleep(5000);
	Student s = {"2018", "梁志宇", 100};
	puts("插入"); 
	number = get_length(head);
	printf("%d\n", number);
	insert_by_loc(head, 4, &s);
	Print(head);
	puts("删除");
	number = get_length(head);
	printf("%d\n", number);
	delete_by_loc(head,4);
	Print(head);
} 
SNode* m(int n) {
	//手输入学生信息 
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
	printf("共有%s的%d成绩记录\n", name, number); 
	
}
void search_by_loc(SNode *head, int k) {
	//按照指定的位置进行查找 
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
		printf("没有找到第%d个的信息", k); 
}
void insert_by_loc(SNode *head, int k, Student *s) {
	//插入到链表的第k个位置，k=[1, k] 
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
		printf("第%d个位置没有找到", k);
} 

void delete_by_loc(SNode *head, int k) {
	//插入到链表的第k个位置，k=[1, k] 
	SNode *p, *q;
	int i=1;
	for(p = head; p != NULL; i++) {
		if(i <= k-1){
			p = p->next;	
		}
		else break;
	}	 
	if(p == NULL)
		printf("第%d个位置没有找到", k);
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
	puts("学生成绩管理系统");
	puts("1、输入学生信息");
	puts("2、增加学生信息"); 
	puts("3、删除学生信息");
	puts("4、查询学生信息");
	puts("5、更改学生信息"); 
	puts("6、打印学生信息");
	puts("7、测试的学生信息"); 
	puts("********************");
	printf("%s","选项(1、2、3、4、5、6、7)："); scanf("%d", &choice);
	return choice;
} 
SNode* PrintIn() {
	//1、输入学生信息 
	int choice, i=1, n;
	SNode *head; 
	puts("********************");
	puts("输入学生信息");
	printf("%s", "step 1、输入学生个数:"); scanf("%d", &n);
	puts("step 2、输入学生信息(学号 姓名 成绩)"); 
	head = m(n); 
	puts("********************");
	return head;
} 
int PrintInsert(SNode *head) {
	//2、插入学生信息 
	int choice; int k; 
	Student s;
	puts("********************");
	puts("增加学生信息"); 
	Print(head);
	printf("%s", "step 1、输入插入的学生信息(学号 姓名 成绩):"); 
	scanf("%s %s %f", s.no, s.name, &s.grade);
	printf("%s", "step 2、输入插入的位置:"); scanf("%d", &k);
	insert_by_loc(head, k, &s);
} 
void PrintDelete(SNode *head) {
	//3、 删除学生信息
	int k;
	Print(head);
	printf("%s", "输入删除的位置:"); scanf("%d", &k);
	delete_by_loc(head, k); 
}
void PrintSearch(SNode *head) {
	//4、 查询学生信息
	int choice;
	printf("1、按名字查询\t2、按位置查询\t选项："); scanf("%d", &choice); 
	if(choice == 1){
		char name[20]; 
		printf("%s", "输入名字:"); scanf("%s", name);
		search_by_name(head, name); 
	}
	else if(choice == 2){
		int k; 
		printf("%s", "输入位置:"); scanf("%d", &k);
		search_by_loc(head, k);	
	}
 
}
int main()
{
	int choice; int count=1;
	SNode *s; SNode *p, *head, *re;
	printf("***提示：如果不想手输学生信息，可以体验[7], [1]为手输信息\n\n"); 
	while(1) {
		printf("IN[%d]\n",count);
		choice = MenuSelect(); printf("\n");
		printf("OUT[%d]\n",count);
		switch(choice) {
			case 1: head = PrintIn(); break;
			case 2: PrintInsert(head); break;
			case 3:	PrintDelete(head); break;
			case 4: PrintSearch(head); break;
			case 5: printf("敬请期待\n"); break;
			case 6: Print(head); break;
			case 7: head = test_get(); break;
		}
		printf("\n"); 
		count++;
	}
 } 
