#include<stdio.h>
//串的定长顺序存储表示
#define MAXSTRLEN 50  // // 用户可在50以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];//0号单元存放串的长度

//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0。其中，T非空，1<=pos<=StrLength(S)。
int indexBF(SString S, SString T, int pos){
	int i = pos, j = 1;
	while(i <= S[0] && j <= T[0]){
		if(S[i] == T[j]){
			i++;
			j++;
		}else{
			i = i - j + 2;//i回到原位置是i - j + 1 ,所以i退到远位置的下一个位置是i - j + 1 + 1
			j = 1;
		}
	}
	if(j > T[0]){//如果j > len(T)，说明模式串T与S中某子串完全匹配
		return i - T[0];//因为i是已经自增过一次了，所以是i-len(T)而不是i-len(T)+1
	}else
		return 0;
}

//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0。其中，T非空，1<=pos<=StrLength(S)。
int indexKMP(SString S, SString T, int pos, int next[]){
	int i = pos, j = 1;
	while(i <= S[0] && j <= T[0]){
		if(j == 0 || S[i] == T[j]){
			i++;  //继续比较后续字符
			j++;
		}else{
			j = next[j];//模式串向右滑动
		}
	}
	if(j > T[0]){//如果j > len(T)，说明模式串T与S中某子串完全匹配
		return i - T[0];//因为i是已经自增过一次了，所以是i-len(T)而不是i-len(T)+1
	}else
		return 0;
}

//求模式串T的next函数（修正方法）值并存入next数组
void getNextVal(SString T, int next[]){
	next[1] = 0;
	int i = 1, j = 0;
	while(i < T[0]){
		if(j == 0 || T[i] == T[j]){
			i++;  //继续比较后续字符
			j++;
			if(T[i] == T[j])//若除去if(T[i] == T[j])：next[i] = next[j];这2句，则得到的就是修正之前的next求解算法
				next[i] = next[j];
			else
				next[i] = j;
		}else{
			j = next[j];//模式串向右滑动
		}
	}	
}

void init(SString &S, char str[]){
	int i = 0;
	while(str[i]!='\0'){
		S[i+1] = str[i];
		i++;
	}
	S[i+1] = '\0';
	S[0] = i;
}

void printStr(SString Str){
	for(int i = 1; i <= Str[0]; i++){
		printf("%c", Str[i]);
	}
	printf("\n");
}

int main(){
	SString S;
	init(S, "ababcabcacbab");
	printStr(S);

	SString T;
	init(T, "abcac");
	printStr(T);

	int index = indexBF(S, T, 1);
	printf("index is %d\n", index);

	int next[6] = {0};
	getNextVal(T, next);
	//打印next值
	printf("\n\nnext[]：");
	for(int k = 1; k <= T[0]; k++)
		printf("%d ", next[k]);
	printf("\n");

	index = indexKMP(S, T, 1, next);
	printf("index is %d\n", index);

	return 0;
}