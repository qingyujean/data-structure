/*栈是操作受限的线性表，表头为栈顶，表尾为栈底
和线性表一样，栈也有两种存储表示方法：1.顺序栈（动态数组、静态数组）2.链栈（单链表、静态链表）
分析：
	1.顺序栈(top为栈顶元素的下一个位置)
	动态数组：
	#define STACK_INIT_SIZE 100//初始分配量
	#define STACKINCREAMENCE 10//分配增量
	typedef int SElemType;
	typedef struct SqStack{
		SElemType *base;
		SElemType *top;
		int stacksize;//当前已分配的存储空间，以元素为单位
	}SqStack;

		栈不存在：base = NULL
		空栈：top = base
		满栈：top-base >= stacksize

	静态数组：
	#define MAXSIZE 100
	typedef struct SqStack{
		SElemType data[MAXSIZE];
		int top;//指向栈顶元素
	}SqStack;

		空栈：top = 0
		满栈：top = MAXSIZE

	2.链栈(单链表式，top指向栈顶元素)
	typedef struct SqNode{
		SElemType data;
		struct SqNode *next;
	}SqNode, *LinkStack;
	LinkStack top;//栈顶指针

		空栈：StackNode *top = NULL
*/

//本实例以静态数组实现顺序栈，其中：top为栈顶元素的下一个位置
#include<stdio.h>
#define MAXSIZE 100
typedef char SElemType;
typedef struct SqStack{
	SElemType data[MAXSIZE];
	int top;//指向栈顶元素
}SqStack;

//初始化空栈
void initStack(SqStack &s){
	s.top = 0;
}

//判栈空
bool isEmpty(SqStack s){
	if(s.top == 0){
		printf("是空栈\n");//
		return true;
	}else{
		return false;
	}
}

//判栈满
bool isFull(SqStack s){
	if(s.top == MAXSIZE){
		return true;
	}
	else{
		return false;
	}
}

//取栈顶元素
void getTopElem(SqStack s, SElemType &e){
	if(!isEmpty(s))
		e = s.data[s.top-1];
	else
		printf("此栈为空栈，取栈顶元素失败\n");
}

//入栈
void push(SqStack &s, SElemType e){
	if(!isFull(s)){
		s.data[s.top] = e;
		s.top++;
	}else
		printf("此栈已满，入栈操作失败\n");
}

//出栈
void pop(SqStack &s, SElemType &e){
	if(!isEmpty(s)){
		e = s.data[s.top-1];
		s.top--;
	}
	else
		printf("此栈为空栈，出栈操作失败\n");
}

//利用入栈操作创建一个初始栈
void createStatck(SqStack &s, int n){
	printf("依次输入栈内元素：\n");
	for(int i = 0; i < n; i++){
		SElemType e;
		scanf("%c", &e);
		push(s, e);
		getchar();//吸入回车符
	}
	printf("\n");
}

//打印输出栈内元素
void printStack(SqStack s){
	int stackLen = s.top;//栈长
	printf("打印栈内元素：");
	for(int i = 0; i < stackLen; i++){
		printf("%c ", s.data[i]);
	}
	printf("\n");
}

int main(){
	SqStack s;
	initStack(s);
	
	createStatck(s, 5);//产生一个从栈顶到栈底为：a，c，e，g，i的栈
	printStack(s);

	//入栈新元素：j
	printf("输入一个新元素入栈（如字母j）:");
	SElemType pushElem;
	scanf("%c", &pushElem);
	push(s, pushElem);
	printStack(s);

	//出栈
	SElemType popElem;
	pop(s, popElem);
	printf("\n出栈元素为%c\n", popElem);
	printStack(s);

	return 0;
}