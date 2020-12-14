//package sort.swampSort;

public class QuickSort {

	/**
	 * @param args
	 */
	//交换顺序表L的字表L[low...high]的记录，枢轴记录到为，并返回枢轴应该所在的位置
	//此时，枢轴前面的记录均小于枢轴，枢轴后面的记录均大于枢轴
	//是一趟快排
	public static int partion(int[] L, int low, int high){
		L[0] = L[low];//L[0]暂存枢轴,字表中的第一个元素一般默认为是枢轴
		while(low < high){
			while(low < high && L[0] <= L[high])
				high--;
			//此时L[high]>L[0]
			L[low++] = L[high];
			while(low < high && L[0] >= L[low])
				low++;
			//此时L[low]>L[0]
			L[high--] = L[low];
		}
		//循环结束时，一定有low==high
		L[low] = L[0];
		return low;
	}
	
	//递归形似的快速排序
	public static void quickSort(int[] L, int low, int high){
		//对顺序表L的子序列L[low...high]做快速排序
		if(low < high){
			int m = partion(L, low, high);
			quickSort(L, low, m-1);
			quickSort(L, m+1, high);
		}
		//low==high时，说明子序列中仅有一个元素了，显然已经有序，应作为每一层递归的结束
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 46, 55, 13, 42, 94, 5, 17, 70}; //0号单元未使用
		quickSort(test, 1, test.length-1);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
