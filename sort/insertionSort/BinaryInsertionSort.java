//package sort.insertionSort;

public class BinaryInsertionSort {

	/**
	 * @param args
	 */
	//对顺序表L做折半插入排序,利用折半查找快速找到要插入的位置
	public static void binaryInsertSort(int[] L){
		for(int i = 2; i <= L.length-1; i++){		
			//利用折半查找找到要插入的位置
			int low = 1, high = i-1;//在1->i-1的有序子序列中插入第i个元素，使之成为1->i的有序子序列
			L[0] = L[i];//暂存要插入的元素
			while(low <= high){
				int mid = (low+high)/2;
				if(L[0] < L[mid])
					high = mid -1;
				else
					//L[0] >= L[mid]
					low = mid+1;//等于当成大于处理，这样后出现的相等值就会排在后面，从而到达“稳定”
			}
			//此时high = low-1，且high+1即low的位置即为要插入的位置
			for(int j = i-1; j >= low; j--)
				L[j+1] = L[j];
			L[low] = L[0];
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 53, 27, 36, 15, 69, 42}; //0号单元未使用
		binaryInsertSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
