//package sort.selectionSort;

public class HeapSort {

	/**
	 * @param args
	 */
	//已知H[s...m]中记录的关键字除H[s]之外其他关键字均满足大顶堆的定义，本函数则
	//实现调整H[s]以使得H[s...m]成为一个大顶堆
	public static void heapAdjust(int[] H, int s, int m){
		//s指向暂时的堆顶位置，但H[s]使得不满足大顶堆的定义，所以调整H[s],使得H[s...m]成为一个大顶堆
		//这个过程叫做一次“筛选”：从堆顶到叶子节点的调整
		for(int j = 2*s; j <= m; j *= 2){//j = j * 2，即从当前层往下一层考察
			if(j<m && H[j+1] >H[j])//j<m是为了防止H[j+1]的j+1越界
				j++;//j总指向s的2个孩子里大的那个
			if(H[j] > H[s]){
				H[0] = H[s];
				H[s] = H[j];
				H[j] = H[0];
			}else
				break;//如果新换上来的堆顶本身就并不破坏堆得定义，则无需继续调整，因为他下面的元素是一定满足堆的
			s = j;//s调整好后，往下一层考察，直至到叶子节点
		}
	}
	
	public static void heapSort(int[] H){
		int n = H.length-1;
		//建堆
		for(int i = n/2; i > 0; i--){//将H[1...n]建成大顶堆，从第n/2个元素开始调整，即“筛选”过程
			//即调整元素的顺序是第n/2个元素，第n/2 - 1个元素，...，第1个元素
			//每一次筛选都是一次从当前元素（局部的堆顶到叶子节点的调整）
			heapAdjust(H, i, n);//每一次调整，都使得H[i...n]满足大顶堆的定义，直至整个H[1...n]都满足大顶堆定义
		}
		
		//堆排序
		//总是将最后一个元素与堆顶互换，即越大的数慢慢往后排，互换以后要做调整使剩余的元素仍然满足大顶堆的定义
		for(int i = n; i > 0; i--){//i指向当前还未排好序的子序列的“最后一个元素”，而i后面的是已经排好序的，
			//即每次从堆顶输出的那个最大值，排到i指向的这个最后位置
			H[0] = H[i];
			H[i] = H[1];//H[1]是当前的堆顶元素，是当前最大值，排到最后面去
			H[1] = H[0];//由于H[i]跑到了堆顶位置可能破坏堆，需要调整
			heapAdjust(H, 1, i-1);//从堆顶调整到i-1对应的节点
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] testH = {0, 21, 25, 49, 25, 16, 8}; //0号单元未使用
		//堆采用顺序表存储
		heapSort(testH);
		for(int i = 1; i <= testH.length-1; i++)
			System.out.print(testH[i]+" ");
	}

}
