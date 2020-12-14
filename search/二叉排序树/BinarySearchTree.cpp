#include<stdio.h>
#include<stdlib.h>
#define NULL 0
#define TRUE 1
#define FALSE 0
typedef int status; 
typedef int TElemType;
typedef int KeyType;
//动态二叉链表
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

bool isFind = false;//标识是否查找到

//在根指针T所指的二叉排序树中递归的查找其关键字等于key的数据元素，若查找成功，则指针p指向该数据元素的结点，并返回True，，否则返回False
//指针f总指向p的双亲，其初始值为NULL
status searchBST(BiTree T, KeyType key, BiTree &f, BiTree &p){
	if(!T){
		p = T;//使P指向NULL
		isFind = false;//标识没有查找到
		return FALSE;
	}
	if(T->data == key){
		p = T;
		isFind = true;//标识已经查找到
		return TRUE;
	}else if(T->data > key){
		f = T; 
		return searchBST(T->lchild, key, f, p);
	}else{
		f = T; 
		return searchBST(T->rchild, key, f, p);
	}
}

status insertBST(BiTree &T, KeyType key){
	BiTNode *p;
	BiTNode *f = NULL;
	if(searchBST(T, key, f, p)){//找到了
		return TRUE;
	}else{//没找到，即不存在，则要插入该值
		//printf("查找&d失败，则在原二叉排序树中插入该值\n");
		p = (BiTNode *)malloc(sizeof(BiTNode));
		p->data = key;
		p->lchild = p->rchild = NULL;
		if(!f){//f为NULL，说明二叉排序树还是一棵空树
			T = p;
		}else if(key > f->data){
			f->rchild = p;
		}else{
			f->lchild = p;
		}
		return TRUE;
	}
}

status deleteBST(BiTree &T, KeyType key){
	BiTNode *p, *q;//q将代替p在双亲f下的位置
	BiTNode *f = NULL;
	if(!searchBST(T, key, f, p)){//没找到
		return FALSE;
	}else{//找到了，则要执行删除操作
		if(!f){//f为NULL，说明要删除的是二叉排序树的根节点,示例：79
			if(p->lchild == NULL && p->rchild == NULL){//p是叶子结点，示例：5，68, 89，120
				T = NULL;
			}else if(p->lchild == NULL){//p只有右子树,示例:100,88
				T = p->rchild;
			}else if(p->rchild == NULL){//p只有左子树,示例:17
				T = p->lchild;				
			}else{//P的两棵子树均不为空
				//让p的左子树的根节点为新的根节点，右子树的根节点链接到左子树的最右下端
				T = p->lchild;
				q = T;
				while(q && q->rchild)
					q = q->rchild;
				//q指向p的左子树的最右下端
				if(q)
					q->rchild = p->rchild;
			}

		}else{
			if(p->lchild == NULL && p->rchild == NULL){//p是叶子结点，示例：5，68, 89，120
				q = NULL;
			}else if(p->lchild == NULL){//p只有右子树,示例:100,88
				q = p->rchild;
			}else if(p->rchild == NULL){//p只有左子树,示例:17
				q = p->lchild;				
			}else{//P的两棵子树均不为空,示例:62,90,
				//将p的左子树的根节点代替p，p的右子树到p的左子树的最右下端
				q = p->lchild;
				while(q->rchild){
					q = q->rchild;
				}
				q->rchild = p->rchild;//p的右子树移到左子树的最右下端
			}
			//重新指派p的双亲的孩子，并删除p结点
			if(f->lchild == p)
				f->lchild = q;
			else if(f->rchild == p)
				f->rchild = q;
			free(p);
		}//end else
	}//end else
	return TRUE;
}


//中序遍历打印二叉树的递归算法（左、根、右）
void inOrderPrint(BiTree T){
	if(T){
		inOrderPrint(T->lchild);
		printf("%d ", T->data);		
		inOrderPrint(T->rchild);
	}
	
}

int main(){
	BiTree T;
	T = NULL;//对树初始化：重要！！！

	//测试，按结定关键字序列79，62，68，90，88，89，17，5，100，120生成二叉排序树
	KeyType keyArray[] = {79, 62, 68, 90, 88, 89, 17, 5, 100, 120};
	for(int i = 0; i < 10; i++){
		insertBST(T, keyArray[i]);
	}
	printf("中序遍历该二叉树为：");
	inOrderPrint(T);
	printf("\n");

	/*
	//查找失败则插入
	int test = 1;
	while(test <= 3){//做2次测试
		printf("\n请输入要查找的关键字key=");
		KeyType key;
		scanf("%d", &key);
		insertBST(T, key);
		if(isFind){
			printf("查找%d成功\n", key);
		}else{
			printf("查找%d失败，则在原二叉排序树中插入该值\n", key);		
			printf("插入关键字%d后，中序遍历该二叉树为：", key);
			inOrderPrint(T);
			printf("\n");
		}
		test++;
	}
	*/

	
	//查找成功则删除
	int test = 1;
	while(test <= 3){//做3次测试
	    printf("\n请输入要查找的关键字key=");
		KeyType key;
		scanf("%d", &key);
		deleteBST(T, key);
		if(isFind){
			printf("查找%d成功,则删除该关键字\n", key);
			printf("删除关键字%d后，中序遍历该二叉树为：", key);
			inOrderPrint(T);
			printf("\n");
		}else{
			printf("查找%d失败\n", key);		
		}
		test++;
	}
	
	return 0;
}


