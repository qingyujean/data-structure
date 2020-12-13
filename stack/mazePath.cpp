#include<stdio.h>
#define mazeRowNum 10//迷宫行数
#define mazeColNum 10//迷宫列数
#define MAXSIZE 100//栈大小

//迷宫中的坐标位置
typedef struct{
	int x;//行号
	int y;//列号
}PosType;

//栈的元素类型
typedef struct{
	//int ord;//通道块在路径上的“序号”
	PosType seat;//通道块在迷宫中的“坐标位置”
	int direction;//从此通道块走向下一通道块的方向,di=1,2,3,4分别表示东，南，西，北
}SElemType;

///////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////

//定义迷宫，' '表示通道块，'#'表示墙壁，在后面的执行过程中，迷宫的元素可能变成'*'表示路径，'@'表示曾经走过但是无法到达出口
static char maze[mazeRowNum][mazeRowNum] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
	{'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
	{'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

PosType start = {1, 1};//设置迷宫起点
PosType end = {8, 8};//设置迷宫终点



//对曾经走过的通道块留下痕迹，以防止所求路径不是简单路径
void footPrint(PosType curpos){
	maze[curpos.x][curpos.y] = '*';//表示到达了该通道块
}
//曾走过的通道块但是无法到达出口，是“不通的”路，标记以免陷入“死胡同”
void markPrint(PosType curpos){
	maze[curpos.x][curpos.y] = '@';//表示该通道块虽然不是墙壁，但是它仍然不通
}

PosType nextPos(PosType curpos, int direction){
	switch(direction){
		case 1: curpos.y++;break;//向东走，行号不变，列号加1
		case 2: curpos.x++;break;//向南走，行号加1，列号不变
		case 3: curpos.y--;break;//向西走，行号不变，列号减1
		case 4: curpos.x--;break;//向北走，行号减1，列号不变
	}
	return curpos;
}
//判断当前位置是否可通,即为' ',而不是'#'、'*'（已走过）、'@'（已走过但不通）
bool pass(PosType curpos){
	if(maze[curpos.x][curpos.y] == ' ')
		return true;
	else
		return false;
}
//bool mazePath(char maze[][mazeColNum], PosType start, PosType end){
//若迷宫中存在从入口start到出口end的通道，则求得一条路径存放在栈中（从栈底到栈顶），并返回TRUE,否则返回FALSE
bool mazePath(PosType start, PosType end){
	SqStack s;
	initStack(s);
	PosType curpos = start;//设定当前位置为“入口”位置
	//int curstep = 0;  //探索的第一步，用于表示路径序号
	do{
		if(pass(curpos)){//当前路径可通（是未曾到达过的通道块）
			footPrint(curpos);//留下"到此一游"的标记，为了求得的路径是简单路径
			//SElemType e = {curpos, 1};
			SElemType e;
			e.seat = curpos;
			e.direction = 1;
			push(s, e);  //加入路径
			if(curpos.x == end.x && curpos.y == end.y)  //到达出口
				return true;
			curpos = nextPos(curpos, 1);//下一位置是当前位置的东边
			//curstep++;   //探索下一步
		}else{//当前位置不能通过，则栈顶元素出栈，因为栈顶位置是当前位置的“来向”通道块，即当前位置的前一个位置
			SElemType e;
			pop(s, e);
			//如果弹出的栈顶位置的四周均不可通，则继续往“来路”通道块回退
			while(e.direction == 4 && !isEmpty(s)){
				markPrint(e.seat);//标记此通道块已经走过且不可通，标记是为了避免陷入死胡同
				pop(s, e);
			}
			//弹出的栈顶位置尚有其他方向的方块未探索，则切换到下一个方向的方块为当前位置
			if(e.direction < 4){
				e.direction++;
				push(s, e);
				curpos = nextPos(e.seat, e.direction);
			}
		}//end else
	}while(!isEmpty(s));//栈不为空则循环继续
	return false;
}

//打印迷宫
void printMaze(){
	for(int i = 0; i < mazeRowNum; i++){
		for(int j = 0; j < mazeColNum; j++){
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
//仅打印迷宫中的路径
void printPath(){
	for(int i = 0; i < mazeRowNum; i++){
		for(int j = 0; j < mazeColNum; j++){
			if(i == 0 || j == 0 || i == mazeRowNum-1 || j == mazeColNum-1 || maze[i][j] == '*'){
				printf("%c ", maze[i][j]);
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");		
}
int main(){
	printf("迷宫的初始状态：\n");
	printMaze();
	if(mazePath(start, end)){
		printf("存在通路！\n");
		printf("迷宫的现态：\n");
		printMaze();
		printf("迷宫里的路径：\n");
		printPath();
	}else
		printf("不存在通路！\n");	

	return 0;	
}