#include<stdio.h>
#include<stdlib.h>
//参考：
//http://www.2cto.com/kf/201410/347626.htmla

//线性表的两种存储结构：
//1.顺序表（动态数组实现、静态数组实现）
//2.链表（单链表、静态链表）
//本实例实现线性表的链式存储

#define NULL 0
typedef int ElemType;
//单链表存储结构节点定义
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;
//默认单链表都带有头节点


//在带头节点的单链表的第i(1<=i<=n+1)个位置之前插入元素e,有n+1个位置可供插入
//得找到前驱结点第i-1个节点
//时间复杂度：O(n)
void insertList(LinkList &L, int i, ElemType e){
	int j = 1;
	LinkList p = L;//p现在指向头节点
	while(j<i&&p){
		p = p->next;
		j++;
	}//顺利的话，j应该为插入的位置i,p为其前驱结点即i-1位置的节点
	//如果i大于表长+1，则会因为p=NULL而跳出循环，如果i<1,则会因为j<i不满足跳出循环
	if(j>i||!p){
		printf("插入位置参数不合法\n");
	}else{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
	}	
}

//在带头节点的单链表里删除第i(1<=i<=n)个元素，并由e返回
//需要找到第i个元素的前驱结点
//时间复杂度：O(n)
void delList(LinkList &L, int i, ElemType &e){
	int j = 1;
	LinkList p = L;
	while(j<i&&p->next){
		p = p->next;
		j++;
	}//顺利的话,j应该为插入的位置i,p为其前驱结点即i-1位置的节点
//如果i大于表长，则会因为p->next=NULL而跳出循环，如果i<1,则会因为j<i不满足跳出循环
	if(j>i||!p->next){
		printf("删除位置参数不合法\n");
	}else{
		LinkList s = p->next;
		e = s->data;
		p->next = s->next;
		free(s);
		printf("被删除的第%d个位置的数据是%d\n", i, e);
	}
}

//创建一个长度为n的线性单链表,使用尾插法（顺序建立），
//（若为头插法则为逆向建立，那么输入元素的顺序应该与线性表里的逻辑顺序相反）
void createList(LinkList &L, int n){
	//先建立一个带头节点的单链表L,即初始化
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	LinkList r = L;//r指针总是指向当前线性表的最后一个元素，即尾元素
	printf("请输入%d个数据:\n", n);
	for(int i = 0; i < n; i++){
		LinkList s = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &s->data);
		//getchar();
		s->next = NULL;
		r->next = s;
		r = s;
	}
}
//打印输出线性单链表
void printList(LinkList L){
	printf("打印线性链表：");
	LinkList p = L->next;
	while(p){//p为当前查访的元素
		printf("%d ", p->data);
		p=p->next;
	}
	printf("\n");
}

//已知线性表La和Lb中的数据元素按值非递减排列，现要求将La和Lb归并为一个新的线性表Lc，且Lc中的数据元素仍然按值非递减有序排列  
//实现：为保持Lc的非递减有序，则当a<=b时，c=a;当a>b时，c=b  
//时间复杂度：O(La.len+Lb.len)  
//实例：La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),Lc=(2,3,5,6,8,8,9,11,11,15,20),注意并没有去重，只是做了合并 
//注意：与线性顺序表的实现的区别之处：Lc可利用la和Lb的节点，即把La,Lb逐步链接到Lc中去
void mergeList(LinkList &La, LinkList &Lb, LinkList &Lc){
	Lc = La;//将La的头节点作为Lc的头节点
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc;//pc总是指向Lc的最后一个节点

	while(pa&&pb){
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;//插入剩余段
	free(Lb);//释放Lb的头节点
}

//利用两个线性表La,Lb分别表示两个集合A和B(线性表中的数据元素即为集合元素)，现要求一个新的集合A=AUB  
//实现：扩展线性表La,实现类似于merge操作，只是要去重，可以用2个指针同时从两个线性表出发并比较,这样求得的并集保持了合并前的顺序
//实例：La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),union以后的La=(2,3,5,6,8,9,11,15,20),La.len=9,注意有去重， 
//时间复杂度：O(La.len + Lb.len) 
void unionList(LinkList &La, LinkList &Lb){
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = La;//pc总是指向并集列表的最后一个节点

	while(pa&&pb){
		if(pa->data < pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else if(pa->data > pb->data){
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}else{//a==b，只插入其中之一
			LinkList s = pb;

			pc->next = pa;
			pc = pa;
			pa = pa->next;
			pb = pb->next;

			free(s);
		}
	}
	pc->next = pa?pa:pb;//插入剩余段
	free(Lb);//释放Lb的头节点
}
void main(){  	
	LinkList L;
	createList(L, 5);//初始化并创建一个线性单链表
	printList(L);	

	/*
	//完成插入功能  
    printf("您要插入的数据和位置(1~6)(如：在第2个位置插入10则输入：2,10)：");  
    int elem, pos;  
    scanf("%d,%d",&pos,&elem);  
    insertList(L,pos,elem);  
    printList(L);  
	*/
	
	
	/*
	//完成删除功能  
    printf("您要删除的数据的位置(1~5)(如：在第2个位置删除则输入：2)：");  
    int pos; 
	ElemType elem;
    scanf("%d",&pos);  
    delList(L,pos,elem); 
    printList(L); 
	*/

	/*
	//完成merge操作  
    LinkList La, Lb, Lc;   
    printf("创建线性表La:\n");  
    createList(La, 4);//初始化并创建线性表La  
    printList(La);  
    printf("创建线性表Lb:\n");  
    createList(Lb, 7);//初始化并创建线性表Lc  
    printList(Lb);  
    mergeList(La, Lb, Lc);  
    printf("merge以后得到的Lc:\n");  
    printList(Lc);  
	*/
	
	/*
	//完成union操作  
    LinkList La, Lb;   
    printf("创建线性表La:\n");  
    createList(La, 4);//初始化并创建线性表La  
    printList(La);  
    printf("创建线性表Lb:\n");  
    createList(Lb, 7);//初始化并创建线性表Lc  
    printList(Lb); 
    unionList(La, Lb);  
    printList(La); 
	*/
}