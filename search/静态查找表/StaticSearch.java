package search;

public class StaticSearch {

	/**
	 * @param args
	 */
	//在顺序表ST中顺序查找其关键字等于key的数据元素，若找到，则函数值为该元素在表中的位置，否则返回0
	public static int searchSeq(int[] st, int key){//st表的0号单元不使用
		//从后往前找，并在0号单元设置"监视哨"	
		int i = st.length - 1;
		st[0] = key;//设置监视哨
		while(st[i] != key){
				i--;
		}
		return i;
	}
	
	//在有序表st中折半查找其关键字等于key的数据元素，若找到，则函数值为该元素在表中的位置，否则返回0
	public int searchBin(int[] st, int key){//st表的0号单元不使用
		int low = 1, high = st.length - 1, mid = (low + high)/2;
		while(low <= high){
			if(st[mid] == key)
				return mid;
			else if(st[mid] > key)
				high = mid - 1;
			else
				//st[mid] < key
				low = mid + 1;
		}
		return 0;//low > high时表明查找失败
	}
	
	public static int searchIndex(int[][] index, int[] st, int key){//为方便，index[],st[]均使用0号单元
		//折半查找索引表
		int low = 0, high = index[0].length - 1;
		int block = index[0].length, elemsInBlock = st.length / block;
		int start, mid = 0;
		while(low < high){
			mid = (low + high)/2;		
			if(index[0][mid] == key){
				start = mid;
				break;
			}else if(index[0][mid] > key)
				high = mid;
			else
				//index[0][mid] < key
				low = mid + 1;
		}
		start = index[1][low];
		
		//从start位置开始顺序查找
		int i = 0;
		while(i < elemsInBlock && st[start+i] != key){
			i++;
		}
		if(i == elemsInBlock)
			return -1;
		else
			return start+i;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		//顺序查找测试
		int st[] = {0, 10, 20, 40, 80, 30, 60, 25};//0号单元不使用
		int key = 75;
		int result = searchSeq(st, key);
		if(result > 0)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
		
		key = 80;
		result = searchSeq(st, key);
		if(result > 0)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
		*/
		
		/*
		//有序表的二分查找测试
		int st[] = {0, 8, 17, 25, 44, 68, 77, 98, 100, 115, 125};//0号单元不使用
		int key = 17;
		int result = searchSeq(st, key);
		if(result > 0)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
		
		key = 120;
		result = searchSeq(st, key);
		if(result > 0)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
		*/
		
		
		
		//索引顺序查找，又叫分块查找，是顺序查找的一种改进方法，块间可使用折半查找，块内只能是顺序查找
		int[][] index = {{20, 53, 89},
				         {0, 5, 10}
		};//索引表
		int[] st = {18, 12, 8, 5, 20, 51, 36, 22, 29, 53, 89, 60, 72, 66, 76};//查找表
		int key = 22;
		int result = searchIndex(index, st, key);
		if(result > -1)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
		key = 6;
		result = searchIndex(index, st, key);
		if(result > -1)
			System.out.println("查找" + key + "成功,在查找表中的位置是" + result);
		else
			System.out.println("查找" + key + "失败");
	}

}
