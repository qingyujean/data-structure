#include<stdio.h>
#include<stdlib.h>
//队列要在队头执行删除（出队）操作，早队尾执行插入（入队）操作，故需要知道队头位置和队尾位置即可唯一确定一个队列
//和线性表类似，也有2种存储表示：顺序队列和链队列
//本实例实现链队列
//判断队列是否为空：Q.f == Q.r
#define NULL 0
typedef char QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode;

typedef struct{
	QNode *f;//队头指针
	QNode *r;//队尾指针
}LinkQueue;

//初始化一个带有头节点的空队列
void initQueue(LinkQueue &Q){
	Q.f = Q.r = (QNode *)malloc(sizeof(QNode));
	Q.f->next = NULL;
}
//销毁队列
void destroyQueue(LinkQueue &Q){
	while(Q.f){
		QNode *p = Q.f->next;
		free(Q.f);
		Q.f = p;
	}
}

//入队操作,在队尾插入
void enQueue(LinkQueue &Q, QElemType e){
	QNode *p = (QNode *)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	Q.r->next = p;
	Q.r = p;
}

//出队操作，在队头删除,并用e返回删除的元素
void deQueue(LinkQueue &Q, QElemType &e){
	if(Q.f == Q.r){
		printf("队列为空，删除操作失败！\n");
		return;
	}
	QNode *p = Q.f->next;
	e = p->data;
	Q.f->next = p->next;
	//如果要删除的是尾指针(整个队列此时只有一个元素)，还需要修改尾指针
	if(p == Q.r)
		Q.r = Q.f;
	free(p);
	printf("元素%c出队\n", e);
}

//利用入队操作创建一个队列,他拥有n个元素
void createQueue(LinkQueue &Q, int n){
	int i = 0;
	printf("请输入%d个字符元素：\n", n);
	while(i < n){
		char dataTmp;
		scanf("%c", &dataTmp);
		enQueue(Q, dataTmp);
		i++;
		getchar();//吃掉换行符
	}
}

void printQueue(LinkQueue Q){
	QNode *p = Q.f->next;
	while(p){
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n\n");
}
void main(){
	LinkQueue Q;//定义一个队列
	initQueue(Q);
	createQueue(Q, 5);
	printQueue(Q);
	printf("执行入队操作：");
	printf("输入您要插入的字符串数据：");
	QElemType e;
	scanf("%c", &e);
	enQueue(Q, e);
	printQueue(Q);

	printf("执行出队操作：");
	deQueue(Q, e);	
	printQueue(Q);
}