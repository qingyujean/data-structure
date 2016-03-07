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
	int ivex, jvex;//该边所依附的2个顶点的在图中位置
	struct ArcNode *ivexNextarc, *jvexNextarc;//分别指向该边所依附的两个顶点下一条边
}ArcNode;//弧结点信息

typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstedge;//指向第一条依附该顶点的弧的指针
}VNode, AdjMuitiVexList[MAX_VERTEX_NUM];//顶点结点信息

typedef struct{
	AdjMuitiVexList vexs;//顶点向量
	int vexnum, arcnum;//图的当前顶点数和弧数
	//GraphKind kind;//图的种类标志
}AMLGraph;//邻接表表示的图


//若图G中存在顶点v，则返回v在图中的位置信息，否则返回其他信息
int locateVex(AMLGraph G, VertexType v){
	for(int i = 0; i < G.vexnum; i++){
		if(G.vexs[i].data == v)
			return i;
	}
	return -1;//图中没有该顶点
}

//采用邻接多重表表示法构造无向图G
void createUDG(AMLGraph &G){
	printf("输入顶点数和弧数如:(5,3):");
	scanf("%d,%d", &G.vexnum, &G.arcnum);

	//构造顶点向量,并初始化
	printf("输入%d个顶点（以空格隔开如：v1 v2 v3）:", G.vexnum);
	getchar();//吃掉换行符
	for(int m = 0; m < G.vexnum; m++){
		scanf("v%d", &G.vexs[m].data);
		G.vexs[m].firstedge = NULL;//初始化为空指针////////////////重要！！！
		getchar();//吃掉空格符
	}

	//构造邻接多重表
	VertexType v1, v2;//分别是一条的两个顶点
	printf("\n每行输入一条边依附的顶点（如：v1v2）:\n");
	fflush(stdin);//清除残余后，后面再读入时不会出错
	int i = 0, j = 0;
	for(int k = 0; k < G.arcnum; k++){
		scanf("v%dv%d",&v1, &v2);
		fflush(stdin);//清除残余后，后面再读入时不会出错
		i = locateVex(G, v1);//边依附的两个顶点的在图中的位置
		j = locateVex(G, v2);
		
		//采用“头插法”在各个顶点的边链头部插入边结点
		ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));//构造一个边结点，它依附于vivj两个顶点
		p->ivex = i;
		p->ivexNextarc = G.vexs[i].firstedge;
		G.vexs[i].firstedge = p;
		p->jvex = j;
		p->jvexNextarc = G.vexs[j].firstedge;
		G.vexs[j].firstedge = p;
	}
}

//打印邻接多重表
void printAdjMultiList(AMLGraph G){
	printf("\n");
	for(int i = 0; i < G.vexnum; i++){
		printf("依附顶点v%d的边为：", G.vexs[i].data);
		ArcNode *p = G.vexs[i].firstedge;

		while(p){
			if(p->ivex == i){
				printf("v%dv%d ", G.vexs[i].data, G.vexs[p->jvex].data);
				p = p->ivexNextarc;
			}else if(p->jvex == i){
				printf("v%dv%d ", G.vexs[i].data, G.vexs[p->ivex].data);
				p = p->jvexNextarc;
			}
		}
		printf("\n");
	}
	printf("\n");
}


/*
测试：
4,3
v1 v2 v3 v4

  v1v2
  v1v3
  v2v4
*/
void main(){
	AMLGraph G;
	createUDG(G);
	printAdjMultiList(G);
}