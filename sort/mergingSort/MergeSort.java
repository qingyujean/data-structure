//package sort.mergingSort;
public class MergeSort {
	/**
	 * @param args
	 */
	public static void merge(int[] L, int s, int m, int n){
		//将有序的L[s...m]和L[m+1...n]归并为有序的L[s...n],借用临时数字（额外的辅存）
		int i=s, j=m+1, k=0;
		int[] tmp = new int[L.length];
		for(k = s; i<=m && j<=n; k++){
			if(L[i] <= L[j])
				tmp[k] = L[i++];
			else
				tmp[k] = L[j++];
		}
		//复制剩余的元素
		while(i <= m)
			tmp[k++] = L[i++];
		while(j <= n)
			tmp[k++] = L[j++];
		
		//将临时数组里的已经排好序的元素返回给L
		for(k=s; k <= n; k++ )
			L[k] = tmp[k];
	}
	//将L[]归并排序
	public static void mergeSort(int[] L, int start, int end){
		if(start < end){
			int m = (start+end)/2;//整个子序列会逐渐一分为2，然后2分为4，4分为8....，主要依赖于L的长度，
			//直至每个子序列仅含有一个元素，就开始合并
			mergeSort(L, start, m);//递归的将L[start...m]归并为有序的L[start...m]
			mergeSort(L, m+1, end);//递归的将L[m+1...end]归并为有序的L[m+1...end]
			merge(L, start, m, end);//将有序的L[start...m]和L[m+1...end]归并到L[start...end]
		}
		//当start == end时，说明此时子序列中只有一个元素，即在此后，每2个单元素将会合并成含有2个元素的子序列
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 46, 55, 13, 42, 94, 5, 17, 70}; //0号单元未使用
		mergeSort(test, 1, test.length-1);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
