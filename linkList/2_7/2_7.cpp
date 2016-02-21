#include<stdio.h>
//顺序表：1.使用动态分配的一维数组
//        2.使用静态分配的一维数组
//本实例使用静态分配
#define LIST_INIT_SIZE 100
typedef int ElemType;

typedef struct SqList{
	ElemType data[LIST_INIT_SIZE];
	int len;
}SqList;

//在第i（1<=i<=n）个元素之前插入一个元素，需要向后移动n-i+1个元素，
//在最后插入则不需要移动任何元素，可供插入的位置有n+1个，
//从后往前找插入的位置，其中i表示位序,第i个元素的下标i-1,i的范围是1~n+1
//时间复杂度：O(n)
void insertSqList(SqList &L,int i, ElemType e){
	if(i>L.len+1||i<1){
		printf("插入位置参数不合法");
	}else if(L.len >= LIST_INIT_SIZE){
		printf("表已满，无法差插入");
	}else{
		int j = L.len-1;
		for(j;j>=i-1;j--){
			L.data[j+1] = L.data[j];//从后往前移动元素
		}
		L.data[i-1] = e;
		L.len++;
	}
}
//删除第i(1<=i<=L.len)个元素,并用e返回其值
//时间复杂度：O(n)
void delSqList(SqList &L, int i, ElemType &e){
	if(i>L.len||i<1){
		printf("删除位置参数不合法");
	}
	int j = i-1;//j是要被删除元素的下标
	e = L.data[j];
	printf("删除的第%d位置的数据是%d\n",i,e);
	for(j;j<L.len-1;j++){
		L.data[j] = L.data[j+1];
	}
	L.len--;
}


//打印输出顺序线性表
void printSqList(SqList L){
	printf("打印线性表:");
	for(int i = 0; i < L.len; i++){
		printf("%d ",L.data[i]);
	}
	printf("\n");
}

//创建一个长度为n的顺序线性表
void createSqList(SqList &L, int n){
	printf("请输入%d个数:\n", n);
	for(int i = 0; i < n; i++){
		scanf("%d",&L.data[i]);
	}
	L.len = n;
	//printSqList(L);
}

//创建一个线性表实际上也是不断往一个空表里插入元素的过程
//所以可利用插入算法实现线性表的创建
void createUseInsertSqList(SqList &L, int n){
	printf("请输入%d个数:\n", n);
	int x;
	for(int i = 0; i < n; i++){
		scanf("%d", &x);
		insertSqList(L,i+1,x);
	}
	L.len = n;
}
//已知线性表La和Lb中的数据元素按值非递减排列，现要求将La和Lb归并为一个新的线性表Lc，且Lc中的数据元素仍然按值非递减有序排列
//实现：为保持Lc的非递减有序，则当a<=b时，c=a;当a>b时，c=b
//时间复杂度：O(La.len+Lb.len)
//实例：La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),Lc=(2,3,5,6,8,8,9,11,11,15,20),注意并没有去重，只是做了合并
void mergeSqList(SqList La, SqList Lb, SqList &Lc){
	int i=0, j=0;
	Lc.len=La.len+Lb.len;//初始化Lc
	int k =0;
	while(i<La.len&&j<Lb.len){
		if(La.data[i]<=Lb.data[j]){
			Lc.data[k]=La.data[i];
			i++;
			k++;
		}else{
			Lc.data[k]=Lb.data[j];
			j++;
			k++;
		}
	}
	while(i<La.len){
		Lc.data[k]=La.data[i];
		i++;
		k++;
	}
	while(j<Lb.len){
		Lc.data[k]=Lb.data[j];
		j++;
		k++;	
	}
}

//利用两个线性表La,Lb分别表示两个集合A和B(线性表中的数据元素即为集合元素)，现要求一个新的集合A=AUB
//实现：扩展线性表La,即从Lb中依次取得每个数据元素，并依值在La中进行查访，若在La中不存在则插入之。
//实例：La=(3,5,8,11),Lb=(2,6,8,9,11,15,20),union以后La=(3,5,8,11,2,6,9,15,20),la.len=9,注意有去重，但不care求并集以后的顺序
//时间复杂度：O(La.len * Lb.len)
int locateElem(SqList L, ElemType e){//查找线性表L中第一个与数据元素e相等(也可以是其他比较方法)的元素的位置(1~L.len)，
									//若没找到则返回0，找到则返回位序,时间复杂度：O(L.len)
									
	int i = 1;//i表示位序
	while(i<=L.len&&L.data[i-1]!=e){
		i++;
	}
	if(i<=L.len)
		return i;
	else
		return 0;
}
void unionSqList(SqList &La, SqList Lb){
	for(int i = 0; i < Lb.len; i++){
		ElemType e = Lb.data[i];
		if(!locateElem(La, e)){//e在La中不存在//O(La.len)
			insertSqList(La,La.len+1, e);//由于总在表尾插入，所以插入操作的时间复杂度与表长无关
		}
	}
}

//将merge第一个循环体中以switch语句代替if语句，即分出3种情况，当a=b时，只将两者之一插入到Lc中，则此时算法完成的操作和
//union完全相同，而时间复杂度却不同，其原因有二：
//1.La,Lb中的元素都是依值递增（同一集合中元素不等），则对Lb中每个元素，不需要再La中从表头至表尾进行全程搜索
//2.由于用新表Lc表示“并集”，则插入操作实际上借助“复制”完成，而无须因插入导致移动一系列元素
//由此可见，若以线性表表示集合并进行集合的各种运算，应先对表中的元素进行排序，则可降低集合运算的时间复杂度

void main(){
	
	//初始化一个空的线性表
	SqList L;
	L.len=0;
	
	createSqList(L, 5);//创建一个线性表
	printSqList(L);
	//printf("%d\n",locateElem(L, 6));
	

	/*
	createUseInsertSqList(L, 5);
	printSqList(L);
	*/

	/*
	//完成插入功能
	printf("您要插入的数据和位置(1~%d)(如：在第2个位置插入10则输入：10，2)：",L.len+1);
	int elem, pos;
	scanf("%d,%d",&elem,&pos);
	insertSqList(L,pos,elem);
	printSqList(L);
	*/

	/*
	//完成删除功能
	printf("您要删除的数据的位置(如：要删除第2个位置的数据则输入(1~%d)：2)：",L.len);
	int pos;
	ElemType elem;
	scanf("%d",&pos);
	delSqList(L,pos,elem);
	printSqList(L);
	*/

	/*
	//完成merge操作
	SqList La, Lb, Lc;
	//初始化线性表
	La.len = Lb.len =Lc.len = 0;
	printf("创建线性表La:\n");
	createSqList(La, 4);//创建线性表La
	printSqList(La);
	printf("创建线性表Lb:\n");
	createSqList(Lb, 7);//创建线性表Lc
	printSqList(Lb);
	mergeSqList(La, Lb, Lc);
	printSqList(Lc);
	*/

	/*
	//完成union操作
	SqList La, Lb;
	//初始化线性表
	La.len = Lb.len = 0;
	printf("创建线性表La:\n");
	createSqList(La, 4);//创建线性表La
	printSqList(La);
	printf("创建线性表Lb:\n");
	createSqList(Lb, 7);//创建线性表Lc
	printSqList(Lb);
	unionSqList(La, Lb);
	printSqList(La);
	printf("La的长度为%d\n",La.len);
	*/
}