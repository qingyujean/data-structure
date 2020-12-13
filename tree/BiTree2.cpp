#include<stdio.h>
#define MAXSIZE 20
typedef char TElemType;
typedef struct{
	int llink;
	TElemType data;
	int rlink;
}BiNode;
typedef BiNode BiTree[MAXSIZE+1];//下标为0的单元空出来

//按先序次序输入二叉树中结点的值（一个字符），点号字符表示空树，构造二叉链表表示的二叉树T
void createBiTree(BiTree &T, int &root, int &i){
	TElemType e;
	scanf("%c", &e);
	if(e!='#'){
		if(e!='.'){//输入的当前节点不是“空树”，是实结点
			T[i].data = e;
			//T[i].llink = 0;
			//T[i].rlink = 0;
			root = i;
			createBiTree(T, T[root].llink, ++i);
			createBiTree(T, T[root].rlink, ++i);
		}else{
			root = 0;//输入的当前节点是“空树”，是虚结点，则对应指向它的链为0
			i--;//静态链表下标回退，因为空树没有进表，只有实节点进表了
		}
	}
}
//先序遍历二叉树（根、左、右）（递归算法）
void preOrderPrint(BiTree T, int root){
	if(root){//根节点不为空
		printf("%c ", T[root].data);
		preOrderPrint(T, T[root].llink);
		preOrderPrint(T, T[root].rlink);
	}
}

//先序遍历二叉树（根、左、右）（非递归算法）
void preOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//维护一个栈，用来记录遍历的节点
	int s[MAXSIZE];//维护一个栈，用来记录遍历的节点
	int top = 0;//指向栈顶元素的下一个位置，初始时top = 0
	int pointer = root;//pointer指向当前层的根节点
	while(pointer || top){
		if(pointer){//根节点不为空
			printf("%c ", T[pointer].data);
			//s[top++] = T[pointer];//根节点入栈
			s[top++] = pointer;//根节点入栈
			pointer = T[pointer].llink;//找根节点的左孩子
		}else{//根节点为空
			//BiNode topElem = s[--top];//栈顶元素出栈，即上一层的根节点		
			//pointer = topElem.rlink;
			int topElemPt = s[--top];//栈顶元素出栈，即上一层的根节点
			pointer = T[topElemPt].rlink;
		}
	}
}

//中序遍历二叉树（左、根、右）（递归算法）
void inOrderPrint(BiTree T, int root){
	if(root){//根节点不为空		
		inOrderPrint(T, T[root].llink);
		printf("%c ", T[root].data);
		inOrderPrint(T, T[root].rlink);
	}
}

//中序遍历二叉树（左、根、右）（非递归算法）
void inOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//维护一个栈，用来记录遍历的节点
	int s[MAXSIZE];//维护一个栈，用来记录遍历的节点
	int top = 0;//指向栈顶元素的下一个位置，初始时top = 0
	int pointer = root;//pointer指向当前层的根节点
	while(pointer || top){
		if(pointer){//根节点不为空
			//s[top++] = T[pointer];//根节点入栈
			s[top++] = pointer;//根节点入栈
			pointer = T[pointer].llink;//找根节点的左孩子
		}else{//根节点为空
			//BiNode topElem = s[--top];//栈顶元素出栈，即上一层的根节点
			//printf("%c ", topElem.data);
			//pointer = topElem.rlink;
			int topElemPt = s[--top];//栈顶元素出栈，即上一层的根节点
			printf("%c ", T[topElemPt].data);
			pointer = T[topElemPt].rlink;
		}
	}
}
//后序遍历二叉树（左、右、根）（递归算法）
void postOrderPrint(BiTree T, int root){
	if(root){//根节点不为空
		postOrderPrint(T, T[root].llink);
		postOrderPrint(T, T[root].rlink);
		printf("%c ", T[root].data);
	}
}

//后序遍历二叉树（左、右、根）（非递归算法）
void postOrderPrint2(BiTree T, int root){
	//BiNode s[MAXSIZE];//维护一个栈，用来记录遍历的节点
	int s[MAXSIZE];//维护一个栈，用来记录遍历的节点指针
	int top = 0;//指向栈顶元素的下一个位置，初始时top = 0
	int pointer = root;//pointer指向当前层的根节点

	while(pointer || top){
		if(pointer){//根节点不为空
			//s[top++] = T[pointer];//根节点入栈
			s[top++] = pointer;//根节点指针入栈
			pointer = T[pointer].llink;//找根节点的左孩子
		}else{//根节点为空
			//BiNode topElem = s[top-1];//取得栈顶元素，即上一层的根节点
			int topElemPt = s[top-1];//取得栈顶元素指针，即上一层的根节点指针
			if(topElemPt > 0){//当前层根节点的右子树还没有被访问过，则访问右子树，并赋“右子树已遍历”标志
				pointer = T[topElemPt].rlink;
				s[top-1] = -s[top-1];
			}else{
				//BiNode topElem = s[--top];//栈顶元素出栈，即上一层的根节点
				topElemPt = -topElemPt;//还原
				printf("%c ", T[topElemPt].data);
				top--;
			}
		}
	}
}


typedef BiNode QElemType;
typedef struct{
	//QElemType data[20];
	QElemType data[20];
	int f;//指向队头元素
	int r;//指向对尾元素的下一个位置
}SqQueue;

//初始化一个空队列
void initQueue(SqQueue &Q){
	Q.f = Q.r = 0;
}

//按层次遍历二叉树（从上到下、从左到右）
void hierarchicalTraversePrint(BiTree T, int root){
	SqQueue Q;//维护一个队列，按层次从上到下、从左到右存放二叉树的各个节点（实际上是按广度优先搜索算法实现层次遍历）
	initQueue(Q);
	//BiNode queue[20];
	
	//根节点入队
	Q.data[Q.r] = T[root];
	Q.r++;
	while(Q.f != Q.r){
		//先降队头元素的左孩子（实节点）入队
		if(Q.data[Q.f].llink){
			Q.data[Q.r] = T[Q.data[Q.f].llink];
			Q.r++;
		}
		//将队头元素的右孩子（实节点）入队
		if(Q.data[Q.f].rlink){
			Q.data[Q.r] = T[Q.data[Q.f].rlink];
			Q.r++;
		}
		//打印（访问）队头元素，并将其出队
		printf("%c ", Q.data[Q.f].data);
		Q.f++;
	}
}
//求二叉树的深度
int getBiTreeDepth(BiTree T, int root){
	if(!root)//根节点为空树
		return 0;
	int leftTreeDepth = getBiTreeDepth(T, T[root].llink);
	int rightTreeDepth = getBiTreeDepth(T, T[root].rlink);
	return leftTreeDepth > rightTreeDepth ? (leftTreeDepth + 1) : (rightTreeDepth + 1);
}

//求二叉树的结点数
int getBiTreeSize(BiTree T, int root){
	if(!root)
		return 0;
	int leftTreeSize = getBiTreeSize(T, T[root].llink);
	int rightTreeSize = getBiTreeSize(T, T[root].rlink);
	return leftTreeSize + rightTreeSize + 1;
}

//先序遍历的方法求二叉树的叶子节点数
int getBiTreeLeafNodesNum(BiTree T, int root){
	if(!root)
		return 0;
	else{//根节点不为空树
		if(!T[root].llink && !T[root].rlink){//如果当前根节点的左右孩子均不为空
			return 1;
		}
		int leftTreeLeafNodesNum = getBiTreeLeafNodesNum(T, T[root].llink);
		int rightTreeLeafNodesNum = getBiTreeLeafNodesNum(T, T[root].rlink);
		return leftTreeLeafNodesNum + rightTreeLeafNodesNum;
	}
}

int main(){
	BiTree tree;
	int root = 1;//根节点的位置
	printf("请按先序次序输入二叉树各节点以#号结束，空树用点号代替：\n");
	int pos = 1;//控制加入静态数组的位置
	createBiTree(tree, root, pos);	

	
	printf("先序遍历打印二叉树(递归算法):\n");
	preOrderPrint(tree, root);
	printf("\n");
		

	printf("先序遍历打印二叉树(非递归算法):\n");
	preOrderPrint2(tree, root);
	printf("\n");
	

	printf("中序遍历打印二叉树(递归算法):\n");
	inOrderPrint(tree, root);
	printf("\n");

	printf("中序遍历打印二叉树(非递归算法):\n");
	inOrderPrint2(tree, root);
	printf("\n");
	
	
	printf("后序遍历打印二叉树(递归算法):\n");
	postOrderPrint(tree, root);
	printf("\n");

	printf("后序遍历打印二叉树(非递归算法):\n");
	postOrderPrint2(tree, root);
	printf("\n");
	
	
	printf("按层次遍历打印二叉树(非递归算法):\n");
	hierarchicalTraversePrint(tree, root);
	printf("\n");

	
	int depth = getBiTreeDepth(tree, root);
	printf("该二叉树的深度为:%d\n", depth);
	

	int size = getBiTreeSize(tree, root);
	printf("该二叉树的结点数为:%d\n", size);
	
	int leafNodesNum = getBiTreeLeafNodesNum(tree, root);
	printf("该二叉树的叶子结点数为:%d\n", leafNodesNum);
	
	return 0;
}
