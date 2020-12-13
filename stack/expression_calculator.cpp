//表达式求值
/*
分析：操作符栈op栈    操作数栈num栈
op栈里不可能出现')'，只可能有'+'、'-'、'*'、'/'、'('、'#'，设ch为当前字符，假设输入都合法
1.op栈顶为'('或'#'，则ch为操作符的话入op栈，为数字入num栈;即总是入栈操作
2.op栈顶为'*'、'/'，则ch为'*'或'/'或')'或'*'或'/'或'#'，则栈顶元素出栈进行计算，否则若ch为操作符则入op栈，为数字则入num栈；即如果ch是'('或数字则入栈，否则总是运算操作
3.op栈顶为'+'、'-'，则ch为'+'或'-'或')'或'#'，则栈顶元素出栈进行计算，否则若ch为操作符则入op栈，为数字则入num栈
4.op栈顶为'#'，计算结束，取出num栈栈顶元素为计算结果
其中ch若为')'，则进行计算直至栈顶出现'('并弹出
其中ch若为'#',则进行计算直至栈顶出现'#'则运算结束，弹出num栈栈顶元素为运算结果

 
1.ch为'+'、'-'，则op栈顶为'('时入栈，否则进行运算直至op栈顶为'('
2.ch为'*'、'/'，则op栈顶为'('、'+'、'-'入栈，否则op为'*'、'/'进行运算
3.ch为数字，入栈
4.ch为'('，则入栈
5.ch为')'，则循环计算直至出现'(',并弹出'('
5.ch为'#'，则输入结束结束，此时应继续循环计算至op栈为空，那么弹出num栈栈顶元素即为运算结果
*/


//实例：(5*(12-3)+4)/2;4+2*3-10/5;
void dealExpression(){
	SqStack op, num;
	initStack(op);
	initStack(num);
	printf("请输入简单表达式(以#号结束)：");
	char currentChar;
	scanf("%c", currentChar);
	while(currentChar!='#'){
		switch(currentChar){
			case '+':
			case '-':
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					while(e != '('){//op栈不为空且栈顶元素不为'('，即为'+'、'-'、'*'、'/'，都应该进行运算
						calculate();						
					}
					//此时e为'('，则应入栈
					push(op, currentChar);
					scanf("%c", currentChar);
				}				
				break;
			case '*':
			case '/':
				if(!isEmpty(op)){
					SElemType e;
					getTopElem(op, e);
					if(e == '*'||e == '/'){//则应进行计算
						calculate();
					}
					push(op, currentChar);
					scanf("%c", currentChar);
				}
				break;
			case '(':
				push(op, currentChar);
				scanf("%c", currentChar);
				break;
			case ')':
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
				}
				break;
			default://currentChar为数字，则入num栈
				int opNum = 0;
				do{
					opNum = opNum*10 + currentChar-'0';
					scanf("%c", currentChar);
				}while(currentChar>='0'&&currentChar<='9');
				push(num, opNum);
				break;
		}//end switch
	}
	//while结束，说明表达式已经输入结束，则只要op栈不为空，就应进行计算
	//当op栈为空时，则弹出num栈栈顶元素即为运算结果
	//SElemType e;
	//getTopElem(op, e);
	while(isEmpty()){
		calculate();
	}
	SElemType result;
	getTopElem(op, result);
	printf("计算结果是%d\n", result);
}

void calculate(SqStack op, SqStack num){
	SElemType op1, op2;
	SElemType opf;
	pop(num, op2);
	pop(num, op1);
	pop(op, opf);

	SElemType tmpResult;
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
	push(num, tmpResult);
}