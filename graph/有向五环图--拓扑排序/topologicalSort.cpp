/*
DAG 有向无环图的应用--拓扑排序：能否顺利完成工程，即检查是否存在环，
AOV网：顶点表示活动的网

除了拓扑排序检查环以外，还可以用DFS
当有向图中无环时，从图中某点进行深度优先遍历时，最先退出DFS函数的顶点即出度为0的顶点，是拓扑序列中的最后一个顶点，由此，按退出DFS函数的先后记录下来的顶点序列，即为逆向的拓扑有序序列
*/

//本次示例采用邻接表作为有向图的存储结构


#include<stdio.h>
#include<stdlib.h>
/*
图的表示方法
DG（有向图）或者DN（有向网）：邻接矩阵、邻接表（逆邻接表--为求入度）、十字链表
UDG（无向图）或者UDN（无向网）：邻接矩阵、邻接表、邻接多重表
*/
#define MAX_VERTEX_NUM 10//最大顶点数目
#define NULL 0
typedef int VRType;//对于带权图或网，则为相应权值
typedef int VertexType;//顶点类型
//typedef enum GraphKind {DG, DN, UDG, UDN};  //有向图：0，有向网：1，无向图：2，无向

typedef struct ArcNode{	
	int adjvex;//该弧所指向的顶点的在图中位置
	//VRType w;//弧的相应权值
	struct ArcNode *nextarc;//指向下一条弧的指针
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


//采用邻接表表示法构造有向图G
void createDG(ALGraph &G){
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
	printf("\n每行输入一条弧依附的顶点（先弧尾后弧头）如：v1v2:\n");
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
		/*因为是有向图，所以不必创建2个弧结点
		ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));//构造一个弧结点，作为弧vivj的弧尾（起点）
		p2->adjvex = i;
		//p2->w = w;
		p2->nextarc = G.vexs[j].firstarc;
		G.vexs[j].firstarc = p2;
		*/
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


#define OK 1
#define ERROR 0
typedef int status;

static int indegree[MAX_VERTEX_NUM] = {0};//存放各个顶点的入度的数组



void findInDegree(ALGraph G, int indegree[]){	
	ArcNode *p;
	for(int i = 0; i < G.vexnum; i++){
		for(p = G.vexs[i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]++;
		}
	}		
}

//如有向图无回路，则输出G的顶点的一个拓扑序列并返回OK，否则返回ERROR
status toplogicalSort(ALGraph G){
	//先初始化各个顶点的入度
	findInDegree(G, indegree);
	

	int stack[MAX_VERTEX_NUM];//维护一个栈来存放入度为0的顶点，当栈为空时，则说明图中不存在无前驱的顶点了（即没有入度为0的顶点了），说明图中无环
	//否则如果此时仍然存在顶点，而且这些顶点有前驱，则说明有环
	int top = 0;//栈顶指针

	//将入度为0的顶点入栈
	for(int i = 0; i < G.vexnum; i++){
		if(!indegree[i]){
			stack[top++] = i;
		}
	}

	int count = 0;//对输出的顶点计数
	ArcNode *p;
	while(top != 0){//栈不为空
		int topElemVex_i = stack[--top];//栈顶元素出栈，即第一个无前驱的顶点
		printf("v%d ", G.vexs[topElemVex_i].data);//输出当前结点
		count++;

		//去掉以该结点为前驱的点与他的弧，以将相关顶点的入度减1的操作来实现
		for(p = G.vexs[topElemVex_i].firstarc; p; p = p->nextarc){
			indegree[p->adjvex]--;
			if(!indegree[p->adjvex]){
				stack[top++] = p->adjvex;//入度为0者入栈
			}
		}
	}
	printf("\n");

	if(count < G.vexnum)//该有向图有回路
		return ERROR;
	else
		return OK;
}

/*测试：
6,8
v1 v2 v3 v4 v5 v6

v1v2
v1v3
v1v4

v3v2

v4v3
v4v5

v6v4
v6v5
*/
void main(){
	ALGraph G;
	createDG(G);
	//printAdjList(G);
	printf("该图的拓扑排序序列为：");
	toplogicalSort(G);		
}

