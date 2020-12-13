/*顺序循环队列：少用一个元素空间，约定以“队列头指针在队列尾指针的下一位置（环状的下一位置）上”作为队列“满”状态的标志
即，队满：Q.f == (R.r + 1)%MAXSIZE
    对空：Q.f == Q.r
	队长：(Q.r - Q.f + MAXSIZE)%MAXSIZE
	入队时尾指针后移：Q.r = (Q.r + 1)%MAXSIZE
	出队时头指针后移：Q.f = (Q.f + 1)%MAXSIZE
*/
#include<stdio.h>
#define MAXSIZE 30
typedef char QElemType;
typedef struct{
	QElemType data[MAXSIZE];
	int f;//头指针
	int r;//尾指针
}SqQueue;

//初始化一个空队列
void initQueue(SqQueue &Q){
	Q.f = Q.r = 0;
}

//求队列长度
int getQueueLength(SqQueue Q){
	return (Q.r - Q.f + MAXSIZE)%MAXSIZE;
}

//入队操作，尾指针后移
void enQueue(SqQueue &Q, QElemType e){
	//先判断队列是否已满
	if(Q.f == (Q.r + 1)%MAXSIZE){
		printf("队列已满，入队操作失败！\n");
		return;
	}
	Q.data[Q.r] = e;
	Q.r = (Q.r + 1)%MAXSIZE;
}

//出队操作，头指针后移,e返回出队元素值
void deQueue(SqQueue &Q, QElemType &e){
	//先判断队列是否为空
	if(Q.f == Q.r){
		printf("队列已空，出队操作失败！\n");
		return;
	}
	e = Q.data[Q.f];
	printf("元素%c出队\n", e);
	Q.f = (Q.f + 1)%MAXSIZE;
}

//利用入队操作创建一个队列，他含有n个元素
void createQueue(SqQueue &Q, int n){
	int i = 0;
	printf("请输入%d个字符队列元素：\n", n);
	while(i < n){
		QElemType e;
		scanf("%c", &e);
		enQueue(Q, e);
		i++;
		getchar();//吃掉回车符
	}
}

void printQueue(SqQueue Q){
	printf("打印队列：");
	int i = Q.f;
	while(i%MAXSIZE != Q.r){
		printf("%c ", Q.data[i]);
		i++;
	}
	printf("\n\n");
}

int main(){
	SqQueue Q;
	initQueue(Q);
	createQueue(Q, 5);
	printQueue(Q);

	printf("执行入队操作：");
	printf("请输入您要入队的字符元素：");
	QElemType e;
	scanf("%c", &e);
	enQueue(Q, e);
	printQueue(Q);

	printf("执行出队操作：");
	deQueue(Q, e);
	printQueue(Q);

	return 0;
}