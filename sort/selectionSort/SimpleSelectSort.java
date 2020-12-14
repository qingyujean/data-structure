//package sort.selectionSort;

public class SimpleSelectSort {

	/**
	 * @param args
	 */
	public static int selectMin(int[] L, int i){
		int min = L[i], min_k = i;
		for(int k = i+1; k <= L.length-1; k++)
			if(L[k] < min){
				min = L[k];
				min_k = k;
			}
		return min_k;
	}
	
	//对顺序表L做简单选择排序
	public static void selectSort(int[] L){
		//从i后面的子序列中(即从i->n中)选出一个min插入到i的位置上
		for(int i = 1; i < L.length-1; i++){//i的取值是1...n-1
			int j = selectMin(L, i);//从L[i...n]里选出一个min，并返回其下标
			if(j!=i){//交换L[i]与L[j]
				L[0] = L[i];
				L[i] = L[j];
				L[j] = L[0];
			}
				
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 8, 3, 9, 1, 6}; //0号单元未使用
		selectSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}

}
