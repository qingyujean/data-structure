#include<stdio.h>
//#include<stdlib.h>
/*
图的表示方法
DG（有向图）或者DN（有向网）：邻接矩阵、邻接表（逆邻接表--为求入度）、十字链表
UDG（无向图）或者UDN（无向网）：邻接矩阵、邻接表、邻接多重表
*/

//1.数组表示法（邻接矩阵）：将以有向网为例
#define INFINITY 32767//最大值：假定为无穷大
#define MAX_VERTEX_NUM 10//最大顶点数目
//typedef enum GraphKind {DG, DN, UDG, UDN};  //有向图：0，有向网：1，无向图：2，无向网：3

typedef int VRType;//顶点关系类型，对于无权图或网，用0或1表示相邻否；对于带权图或网，则为相应权值
typedef int VertexType;//顶点类型
typedef VRType AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum, arcnum;//图的当前顶点数和弧数
	//GraphKind kind;//图的种类标志
}MGraph;//邻接矩阵表示的图

//若图G中存在顶点v，则返回v在图中的位置信息，否则返回其他信息
int locateVex(MGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i] == v)
			return i;
	}
	return -1;//图中没有该顶点
}

//采用邻接矩阵表示法构造有向网G
void createDN(MGraph &G){
	printf("输入顶点数和弧数如:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//构造顶点向量
	printf("输入%d个顶点（以空格隔开如：v1 v2 v3）:", G.vexnum);
	getchar();//吃掉换行符
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m]);
		getchar();//吃掉空格符
	}

	
	//初始化邻接矩阵
	int i=0, j=0;
	for(i = 0; i < G.vexnum; i++){
		for(j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = INFINITY;
	}

	//构造邻接矩阵
	VertexType v1, v2;//分别是一条弧的弧尾和弧头（起点和终点）
	VRType w;//对于无权图或网，用0或1表示相邻否；对于带权图或网，则为相应权值	
	printf("\n每行输入一条弧依附的顶点（先弧尾后弧头）和权值（如：v1 v2 3）:\n");
	fflush(stdin);//清除残余后，后面再读入时不会出错
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%d v%d %d",&v1, &v2, &w);
		fflush(stdin);//清除残余后，后面再读入时不会出错
		i = locateVex(G, v1);
		j = locateVex(G, v2);
		G.arcs[i][j] = w;
	}
}

//打印邻接矩阵
void printDN(MGraph G){
	printf("\n打印有向网G的邻接矩阵：\n");
	for(int i = 0; i < G.vexnum; i++){
		for(int j = 0; j < G.vexnum; j++)
		{
			if(G.arcs[i][j] != INFINITY)
				printf("%9d ", G.arcs[i][j]);
			else
				printf("INFINITY  ");
		}
		printf("\n");
	}
	printf("\n");
}



/*测试：
6,10
v1 v2 v3 v4 v5 v6

v1,v2,5
v1,v4,7

v2,v3,4

v3,v1,8
v3,v6,9

v4,v3,5
v4,v6,6

v5,v4,5

v6,v1,3
v6,v5,1
*/
void main(){
	MGraph G;
	createDN(G);	
	printDN(G);
}