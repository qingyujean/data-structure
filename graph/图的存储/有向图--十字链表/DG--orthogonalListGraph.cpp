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
	int tailvex, headvex;//该弧的弧尾（起点）和弧头（终点）所指向的顶点的在图中位置
	struct ArcNode *tailNextarc, *headNextArc;//分别为指向弧尾（起点）相同的弧的下一条弧的指针、弧头（终点）相同的弧的下一条弧的指针
}ArcNode;//弧结点信息

typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstIn;//指向第一条以该顶点为弧尾（起点）的指针
	ArcNode *firstOut;//指向第一条以该顶点的弧头（终点）的指针
}VNode, VexList[MAX_VERTEX_NUM];//顶点结点信息

typedef struct{
	VexList vexs;//顶点向量
	int vexnum, arcnum;//图的当前顶点数和弧数
	//GraphKind kind;//图的种类标志
}OLGraph;//邻接表表示的图

//若图G中存在顶点v，则返回v在图中的位置信息，否则返回其他信息
int locateVex(OLGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//图中没有该顶点
}


//采用十字链表表示法构造有向图G
void createDN(OLGraph &G){
	printf("输入顶点数和弧数如:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//构造顶点向量,并初始化
	printf("输入%d个顶点（以空格隔开如：v1 v2 v3）:", G.vexnum);
	getchar();//吃掉换行符
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstIn = NULL;//初始化为空指针////////////////重要！！！
		G.vexs[m].firstOut = NULL;
		getchar();//吃掉空格符
	}

	//构造十字链表
	VertexType v1, v2;//分别是一条弧的弧尾和弧头（起点和终点）
	printf("\n每行输入一条弧依附的顶点（先弧尾后弧头）（如：v1v2）:\n");
	fflush(stdin);//清除残余后，后面再读入时不会出错
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//清除残余后，后面再读入时不会出错
		i = locateVex(G, v1);//弧起点
		j = locateVex(G, v2);//弧终点
		
		//采用“头插法”在各个顶点的弧链头部插入弧结点
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));//构造一个弧结点，作为弧vivj的弧头（终点）
		p->tailvex = i;
		p->tailNextarc = G.vexs[i].firstOut;
		G.vexs[i].firstOut = p;
		p->headvex = j;
		p->headNextArc = G.vexs[j].firstIn;
		G.vexs[j].firstIn = p;
	}
}

//打印十字链表
void printOrthogonalList(OLGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("以顶点v%d为弧尾的弧有为：", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstOut;
		while(p){
			printf("v%dv%d ", G.vexs[i].data, G.vexs[p->headvex].data);
			p = p->tailNextarc;
		}
		printf("\n");
	}
	printf("\n");
}


/*测试：
4,7
v1 v2 v3 v4

v1v2
v1v3

v3v1
v3v4

v4v1
v4v2
v4v3
*/
int main(){
	OLGraph G;
	createDN(G);
	printOrthogonalList(G);

	return 0;
}

