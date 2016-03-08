package sort.insertionSort;
public class StraightSort {
	/**
	 * @param args
	 */
	//对顺序表L做直接插入排序
	public static void InsertSort(int[] L){
		//先将第一个元素看成是一个有序子序列
		for(int i = 2; i <= L.length-1; i++){
			//在已经有序的1->i-1的子序列中插入第i个元素，以保证仍然有序，成为一个1->i的有序子序列
			L[0] = L[i];//监视哨
			int j = i-1;
			/*
			for(; j > 0; j--){//没有利用监视哨，仍然用j>0作为条件以避免数组下标越界
				if(L[0] < L[j])
					L[j+1] = L[j];
				else
					break;
			}
			*/
			for(; L[0] < L[j]; j--)
				L[j+1] = L[j];//利用监视哨
			//当L[0] >= <[j]时跳出循环，由于j做了一次自减，所以是L[j+1] = L[0]，
			//当是因为=而跳出循环时（j后来没有自减），L[0]插在L[j]的后面以保证了“稳定” 
			L[j+1] = L[0];
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 53, 27, 36, 15, 69, 42}; //0号单元未使用
		InsertSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}

}
