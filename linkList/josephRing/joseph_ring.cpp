#include<stdio.h>
#include<stdlib.h>
#define NULL 0
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	ElemType sequence;
	LNode *next;
}LNode,*LinkList;

//创建一个不带头节点的循环单向链表
void createCircularList(LinkList &L, int n){
	printf("依次输入数据元素：\n");

	//输入第一个元素，即头节点
	LinkList head = (LinkList)malloc(sizeof(LNode));
	head->sequence = 1;
	head->next = NULL;
	scanf("%d", &head->data);
	L = head;

	LinkList p = head;
	int i = 2;
	while(i <= n){
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->sequence = i;
		s->next = NULL;
		scanf("%d", &s->data);

		p->next = s;
		p = s;
		i++;
	}
	p->next = L;
}

//打印输出单项循环链表
void printCircularList(LinkList L){
	printf("打印单项循环链表：");
	LinkList head = L;
	LinkList p = L->next;
	printf("%d ",head->data);
	while(p!=head){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//约瑟夫环的实现
void josephRing(LinkList L, int m, int n){
	int *outNum = new int[n], num=0;//按退出顺序记录编号
	
	int count = 1;//报数
	LinkList p = L, q = L;	
	while(p->next!=p){
		if(count%m == 0){
			q->next = p->next;
			outNum[num] = p->sequence;
			num++;

			free(p);
			p = q->next;
			count = 1;
		}else{
			q = p;
			p = p->next;
			count++;
		}
	}
	outNum[num] = p->sequence;

	printf("退出的编号顺序是：");
	for(int i = 0; i < n; i++){
		printf("%d ", outNum[i]);
	}
	printf("\n");
}

//实例：设m=20，n=7，7个人的密码依次是3，1，7，2，4，8，4，
//则退席的人的编号依次为6，1，7，5，3，2，4。
int main(){
	LinkList L;
	createCircularList(L, 7);
	printCircularList(L);

	josephRing(L, 20, 7);
	
	return 0;
}