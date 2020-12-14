//package sort.swampSort;

public class BubbleSort {
	/**
	 * @param args
	 */
	//冒泡排序
	public static void bubbleSort(int[] L){
		for(int i = L.length-1; i > 1; i--){//i控制比较的趟数，比较n-1趟
			for(int j = 1; j < i; j++){
				if(L[j] > L[j+1]){//交换
					L[0] = L[j+1];
					L[j+1] = L[j];
					L[j] = L[0];
				}			
			}
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] test = {0, 25, 56, 49, 78, 11, 65, 41, 36}; //0号单元未使用
		bubbleSort(test);
		for(int i = 1; i <= test.length-1; i++)
			System.out.print(test[i]+" ");
	}

}
