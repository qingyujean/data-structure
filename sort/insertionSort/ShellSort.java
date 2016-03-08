package sort.insertionSort;

public class ShellSort {

	/**
	 * @param args
	 */
	//对顺序表L做一趟希尔排序，本算法和一趟直接插入排序相比，做了如下修改：
	//1.前后记录位置的增量式dk,而不是1
	//2.L[0]只是暂存单元，而不再是哨兵
	public static void shellInsert(int[] L, int dk){
		/*对于下面for循环的i = i+dk和i++的分析：
		一趟希尔排序里有L.length/dk个子序列，每个子序列要进行直接插入排序，即要进行L.length/dk个直接插入排序
		子序列轮着来（有点并发的感觉），即第一个子序列的第2个数排完序，然后是第2个子序列的第2个数排序，然后是第3个子序列。。。
		i继续自增，然后是第1个子序列的第3个数往第一个子序列的1->2的有序子序列里插入并排序，然后是第2个子序列的第3个数
		往第2个子序列的1->2的有序子序列里插入并排序，然后是第3个子序列的第3个数往第3个子序列的1->2的有序子序列里插入并排序。。。
		i继续自增，然后是第1个子序列的第4个数往第一个子序列的1->3的有序子序列里插入并排序，接着
		第2个子序列的第4个数往第2个子序列的1->3的有序子序列里插入并排序.。。。。。以此类推，直到所有的完成
		 */
		//相当于每个子序列的第一个数都被看成是每个子序列的有序子序列
		for(int i = 1+dk; i <= L.length-1; i++){
			L[0] = L[i];
			//找L[i]应该插入的位置
			int j = i-dk;
			for(; j>0&&L[0]<L[j]; j-=dk)
				L[j+dk] = L[j];
			L[j+dk] = L[0];
		}
	}
	//按增量dlta[0......len(dlta)-1]对顺序表L做希尔排序
	public static void shellSort(int[] L, int[] dlta){
		for(int i = 0; i < dlta.length; i++)
			shellInsert(L, dlta[i]);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 65, 49, 97, 25, 25, 13}; //0号单元未使用
		int[] dlta = {3, 2, 1};//应使增量序列中的值没有除1之外的公因子，并且最后一个增量值必须等于1。
		shellSort(test, dlta);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}
}
