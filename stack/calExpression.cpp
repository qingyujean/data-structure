//实例：(5*(12-3)+4)/2=24;4+2*3-10/5=8;
#include<stdio.h>
#define MAXSIZE 30
char op[MAXSIZE], num[MAXSIZE];//全局变量
int opTop, numTop;
//void calculate(SqStack op, SqStack num){
void calculate(){
	/*
	SElemType op1, op2;
	SElemType opf;
	pop(num, op2);
	pop(num, op1);
	pop(op, opf);

	SElemType tmpResult;
	*/
	char op1, op2;
	int opf;
	op2 = num[numTop-1];
	numTop--;
	op1 = num[numTop-1];
	numTop--;
	opf = op[opTop-1];
	opTop--;

	int tmpResult = 0;
	switch(opf){
		case '+':
			tmpResult = op1 + op2;			
			break;
		case '-':
			tmpResult = op1 - op2;
			break;
		case '*':
			tmpResult = op1 * op2;
			break;
		case '/':
			tmpResult = op1 / op2;
			break;
	}
	//push(num, tmpResult);
	num[numTop] = tmpResult;
	numTop++;
}



//处理简单表达式
void dealExpression(){
	//SqStack op, num;
	//initStack(op);
	//initStack(num);
	//初始化op栈和num栈:栈为空：top=0;栈满：top=MAXSIZE
	opTop = 0, numTop = 0;

	printf("请输入简单表达式(以#号结束)：");
	char currentChar;
	scanf("%c", &currentChar);
	//printf("currentChar=%c", currentChar);
	while(currentChar!='#'){
		//printf("test1");
		//printf("currentChar=%c", currentChar);
		switch(currentChar){
			case '+':
			case '-':
				/*
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					while(e != '('){//op栈不为空且栈顶元素不为'('，即为'+'、'-'、'*'、'/'，都应该进行运算
						calculate();						
					}
					//此时e为'('，则应入栈
					push(op, currentChar);
					scanf("%c", currentChar);
				}*/
				//printf("test4");
				while(opTop&&op[opTop-1]!='('){
					calculate();
				}								
				
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case '*':
			case '/':
				/*
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					if(e == '*'||e == '/'){//则应进行计算
						calculate();
					}
					push(op, currentChar);
					scanf("%c", currentChar);
				}*/
				if(opTop&&(op[opTop-1]=='*'||op[opTop-1]=='/')){
					calculate();
				}
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case '(':
				op[opTop] = currentChar;
				opTop++;
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			case ')':
				/*
				if(!isEmpty(op)){//栈不为空
					SElemType e;
					getTopElem(op, e);
					while(e!='('){
						calculate();
					}
					//此时op栈顶元素e为'('，应该弹出左括号
					SElemType popElem;
					pop(op, popElem);
					scanf("%c", currentChar);
				}*/
				while(op[opTop-1]!='('){//当前是'('，则op栈一定能有'('匹配到,即op栈一定不为空
					calculate();
				}
				opTop--;//出栈，弹出左括号
				scanf("%c", &currentChar);
				//printf("currentChar=%c", currentChar);
				break;
			default://currentChar为数字，则入num栈
				//printf("testNum");
				int opNum = 0;
				do{
					opNum = opNum*10 + currentChar-'0';
					//printf("%d",opNum);
					scanf("%c", &currentChar);
					//printf("%c",currentChar);
				}while(currentChar>='0'&&currentChar<='9');
				//push(num, opNum);
				//printf("%d",opNum);
				num[numTop] = opNum;
				numTop++;
				//scanf("%c", currentChar);
				break;
		}//end switch
		//printf("test3");
	}
	//while结束，说明表达式已经输入结束，则只要op栈不为空，就应进行计算
	//当op栈为空时，则弹出num栈栈顶元素即为运算结果
	//SElemType e;
	//getTopElem(op, e);
	/*
	while(isEmpty()){
		calculate();
	}
	SElemType result;
	getTopElem(op, result);
	printf("计算结果是%d\n", result);
	*/
	while(opTop){
		calculate();
	}
	int result = num[numTop-1];
	printf("计算结果是%d\n", result);
}



void main(){
	dealExpression();
}