//以无向图的邻接表作为存储结构，实现图深度优先遍历算法
#include<stdio.h>
#include<stdlib.h>
/*
图的表示方法
DG（有向图）或者DN（有向网）：邻接矩阵、邻接表（逆邻接表--为求入度）、十字链表
UDG（无向图）或者UDN（无向网）：邻接矩阵、邻接表、邻接多重表
*/
#define MAX_VERTEX_NUM 10//最大顶点数目
#define NULL 0
//typedef int VRType;//对于带权图或网，则为相应权值
typedef int VertexType;//顶点类型
//typedef enum GraphKind {DG, DN, UDG, UDN};  //有向图：0，有向网：1，无向图：2，无向

typedef struct ArcNode{	
	int adjvex;//该弧所指向的顶点的在图中位置
	//VRType w;//弧的相应权值
	struct ArcNode *nextarc;//指向下一条边的指针
}ArcNode;//弧结点信息

typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}VNode, AdjVexList[MAX_VERTEX_NUM];//顶点结点信息

typedef struct{
	AdjVexList vexs;//顶点向量
	int vexnum, arcnum;//图的当前顶点数和弧数
	//GraphKind kind;//图的种类标志
}ALGraph;//邻接表表示的图


//若图G中存在顶点v，则返回v在图中的位置信息，否则返回其他信息
int locateVex(ALGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//图中没有该顶点
}


//采用邻接表表示法构造无向图G
void createUDN(ALGraph &G){
	printf("输入顶点数和弧数如:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//构造顶点向量,并初始化
	printf("输入%d个顶点（以空格隔开如：v1 v2 v3）:", G.vexnum);
	getchar();//吃掉换行符
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstarc = NULL;//初始化为空指针////////////////重要！！！
		getchar();//吃掉空格符
	}

	//构造邻接表
	VertexType v1, v2;//分别是一条弧的弧尾和弧头（起点和终点）
	//VRType w;//对于无权图或网，用0或1表示相邻否；对于带权图或网，则为相应权值	
	printf("\n每行输入一条弧依附的顶点（先弧尾后弧头）（如：v1v2）:\n");
	fflush(stdin);//清除残余后，后面再读入时不会出错
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//清除残余后，后面再读入时不会出错
		i = locateVex(G, v1);//弧起点
		j = locateVex(G, v2);//弧终点
		
		//采用“头插法”在各个顶点的弧链头部插入弧结点
		ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));//构造一个弧结点，作为弧vivj的弧头（终点）
		p1->adjvex = j;
		//p1->w = w;
		p1->nextarc = G.vexs[i].firstarc;
		G.vexs[i].firstarc = p1;
		ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));//构造一个弧结点，作为弧vivj的弧尾（起点）
		p2->adjvex = i;
		//p2->w = w;
		p2->nextarc = G.vexs[j].firstarc;
		G.vexs[j].firstarc = p2;
	}
}

//打印邻接表
void printAdjList(ALGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("依附顶点v%d的弧为：", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstarc;
		while(p){
			printf("v%dv%d ", G.vexs[i].data, G.vexs[p->adjvex].data);
			p = p->nextarc;
		}
		printf("\n");
	}
	printf("\n");
}


int visited[MAX_VERTEX_NUM];//访问标识数组

void DFS(ALGraph G, int ivex){
	//从第i个顶点出发递归的深度优先遍历图G
	visited[ivex] = 1;
	printf("v%d ", G.vexs[ivex].data);//打印（访问）该顶点
	for(ArcNode *p = G.vexs[ivex].firstarc; p; p = p->nextarc){//对于第ivex个顶点的每个未被访问的邻接点递归调用DFS
		if(!visited[p->adjvex]){
			DFS(G, p->adjvex);
		}
	}
}

//深度优先遍历无向图G（相当于树的先序遍历）（递归算法）
void DFSTraverseGraph(ALGraph G){
	//初始化访问标志数组
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0表示未被访问，1表示已被访问
	}
	printf("请输入遍历的起始顶点（如：v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("一条深度优先遍历序列为：");
	if(!visited[startVexPos])
		DFS(G, startVexPos);
	printf("\n");
	/*
	for(i = 0; i < G.vexnum; i++){//图中每个顶点至多调用一次DFS函数
		if(!visited[i]){//对还未访问过的顶点调用DFS
			DFS(G, i);
		}
	}
	*/
}


//深度优先遍历无向图G（相当于树的先序遍历）（非递归算法）
void DFSTraverseGraph2(ALGraph G){
	int stack[MAX_VERTEX_NUM];//维护一个栈来存储访问图的顶点的（位置）信息
	int top = 0;//初始化栈顶指针，为空栈

	//初始化访问标志数组
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0表示未被访问，1表示已被访问
	}
	printf("请输入遍历的起始顶点（如：v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("一条深度优先遍历序列为：");

	ArcNode *p;// = G.vexs[startVexPos].firstarc;
	int ivex = startVexPos;
	while(!visited[ivex] || top!=-1){//栈不为空
		if(!visited[ivex]){//第vex结点没有被访问过
			visited[ivex] = 1;
			printf("v%d ", G.vexs[ivex].data);
			stack[top++] = ivex;
		}
			
		p = G.vexs[ivex].firstarc;
		while(p && visited[p->adjvex])//p不为空且p已经被访问过，就跳过
			p = p->nextarc;
		//此时p指向以当前顶点为头的且未被访问第一个尾顶点
		if(p){//如果p不为空
			ivex = p->adjvex;
		}else{//如果p为空，说明当前顶点的所有和他有路径相通的顶点均已访问，则栈顶元素出栈，查找下一个尚未被访问的顶点
			ivex = stack[--top];//栈顶元素出栈
		}
	}
	printf("\n");
}


//广度优先遍历无向图G（相当于树的按层次遍历）（非递归算法）
void BFSTraverseGraph(ALGraph G){
	int queue[MAX_VERTEX_NUM];//维护一个队列来存储访问图的顶点的（位置）信息
	int front = 0, rail = 0;//初始化队头、队尾指针，为空队列

	//初始化访问标志数组
	for(int i = 0; i < G.vexnum; i++){
		visited[i] = 0;//0表示未被访问，1表示已被访问
	}

	printf("请输入遍历的起始顶点（如：v1):");
	VertexType startVex;
	scanf("v%d", &startVex);
	int startVexPos = locateVex(G, startVex);
	printf("一条广度优先遍历序列为：");

	queue[rail++] = startVexPos;//起点先入队
	int ivex;// = startVexPos;
	ArcNode *p;
	while(front != rail){//不是空队列
		ivex = queue[front++];//队头元素出队
		if(!visited[ivex]){
			visited[ivex] = 1;
			printf("v%d ", G.vexs[ivex].data);
		}
		p = G.vexs[ivex].firstarc;
		while(p){//p指向与ivex的邻接的（同一个层次的）还未被顶点
			if(!visited[p->adjvex])
				queue[rail++] = p->adjvex;//入队
			p = p->nextarc;
		}
	}	
	printf("\n");	
}

/*测试：8,9
v1 v2 v3 v4 v5 v6 v7 v8 v9

v1v2
v1v3

v2v4
v2v5

v3v6
v3v7

v4v8
v5v8
v6v7
*/
void main(){
	ALGraph G;
	createUDN(G);
	//printAdjList(G);

	printf("\n深度优先遍历（递归算法）：\n");
	DFSTraverseGraph(G);
	fflush(stdin);//清除残余后，后面再读入时不会出错

	printf("\n深度优先遍历（非递归算法）：\n");
	DFSTraverseGraph2(G);
	fflush(stdin);//清除残余后，后面再读入时不会出错

	printf("\n广度优先遍历（非递归算法）：\n");
	BFSTraverseGraph(G);
}