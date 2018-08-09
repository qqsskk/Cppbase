#pragma once

//算法来源:http://www.cnblogs.com/eniac12/p/5329396.html
//把原有的int改为模板可以使用多种类型

template <class T>
int getArrayLen(T& a) { return (sizeof(a) / sizeof(*a)); }

template <class T>
void printArray(T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

//冒泡排序法
template <class T>
void bubbleSort(T a[], int n)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n - 1 - j; i++) // 依次比较相邻的两个元素,使较大的那个向后移
		{
			if (a[i] > a[i + 1])            // 如果条件改成A[i] >= A[i + 1],则变为不稳定的排序算法
			{
				std::swap(a[i], a[i + 1]);
			}
		}
	}
}

//鸡尾酒排序，也叫定向冒泡排序
template <class T>
void CocktailSort(T a[], int n)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		for (int i = left; i < right; i++)   // 前半轮,将最大元素放到后面
		{
			if (a[i] > a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
			}
		}
		right--;
		for (int i = right; i > left; i--)   // 后半轮,将最小元素放到前面
		{
			if (a[i - 1] > a[i])
			{
				std::swap(a[i - 1], a[i]);
			}
		}
		left++;
	}
}

//选择排序
template <class T>
void SelectionSort(T a[], int n) 
{
	for (int i = 0; i < n - 1; i++)         // i为已排序序列的末尾
	{
		int min = i;
		for (int j = i + 1; j < n; j++)     // 未排序序列
		{
			if (a[j] < a[min])              // 找出未排序序列中的最小值
			{
				min = j;
			}
		}
		if (min != i)
		{
			std::swap(a[min], a[i]);    // 放到已排序序列的末尾，该操作很有可能把稳定性打乱，所以选择排序是不稳定的排序算法
		}
	}
}

//插入排序
template <class T>
void InsertionSort(T a[], int n) {

	for (int i = 1; i < n; i++)         // 类似抓扑克牌排序
	{
		int get = a[i];                 // 右手抓到一张扑克牌
		int j = i - 1;                  // 拿在左手上的牌总是排序好的
		while (j >= 0 && a[j] > get)    // 将抓到的牌与手牌从右向左进行比较
		{
			a[j + 1] = a[j];            // 如果该手牌比抓到的牌大，就将其右移
			j--;
		}
		a[j + 1] = get; // 直到该手牌比抓到的牌小(或二者相等)，将抓到的牌插入到该手牌右边(相等元素的相对次序未变，所以插入排序是稳定的)
	}
}

//二分插入排序
template <class T>
void InsertionSortDichotomy(T a[], int n) {

	for (int i = 1; i < n; i++)         // 类似抓扑克牌排序
	{
		int get = a[i];                 // 右手抓到一张扑克牌
		int j = i - 1;                  // 拿在左手上的牌总是排序好的
		while (j >= 0 && a[j] > get)    // 将抓到的牌与手牌从右向左进行比较
		{
			a[j + 1] = a[j];            // 如果该手牌比抓到的牌大，就将其右移
			j--;
		}
		a[j + 1] = get; // 直到该手牌比抓到的牌小(或二者相等)，将抓到的牌插入到该手牌右边(相等元素的相对次序未变，所以插入排序是稳定的)
	}
}

//希尔排序法
template <class T>
void ShellSort(T a[], int n)
{
	int h = 0;
	while (h <= n)// 生成初始增量
	{
		h = 3 * h + 1;
	}
	while (h >= 1)
	{
		for (int i = h; i < n; i++)
		{
			int j = i - h;
			int get = a[i];
			while (j >= 0 && a[j] > get)
			{
				a[j + h] = a[j];
				j = j - h;
			}
			a[j + h] = get;
		}
		h = (h - 1) / 3;// 递减增量
	}
}


//归并排序
template <class T>
void Merge(T a[], int left, int mid, int right)// 合并两个已排好序的数组A[left...mid]和A[mid+1...right]
{
	int len = right - left + 1;
	int *temp = new T[len];       // 辅助空间O(n)
	int index = 0;
	int i = left;                   // 前一数组的起始元素
	int j = mid + 1;                // 后一数组的起始元素
	while (i <= mid && j <= right)
	{
		temp[index++] = a[i] <= a[j] ? a[i++] : a[j++];  // 带等号保证归并排序的稳定性
	}
	while (i <= mid)
	{
		temp[index++] = a[i++];
	}
	while (j <= right)
	{
		temp[index++] = a[j++];
	}
	for (int k = 0; k < len; k++)
	{
		a[left++] = temp[k];
	}
}

template <class T>
void MergeSortIteration(T a[], int len)    // 非递归(迭代)实现的归并排序(自底向上)
{
	int left, mid, right;// 子数组索引,前一个为A[left...mid]，后一个子数组为A[mid+1...right]
	for (int i = 1; i < len; i *= 2)        // 子数组的大小i初始为1，每轮翻倍
	{
		left = 0;
		while (left + i < len)              // 后一个子数组存在(需要归并)
		{
			mid = left + i - 1;
			right = mid + i < len ? mid + i : len - 1;// 后一个子数组大小可能不够
			Merge(a, left, mid, right);
			left = right + 1;               // 前一个子数组索引向后移动
		}
	}
}

//堆排序
template <class T>
void Heapify(T a[], int i, int size)  // 从A[i]向下进行堆调整
{
	int left_child = 2 * i + 1;         // 左孩子索引
	int right_child = 2 * i + 2;        // 右孩子索引
	int max = i;                        // 选出当前结点与其左右孩子三者之中的最大值
	if (left_child < size && a[left_child] > a[max])
		max = left_child;
	if (right_child < size && a[right_child] > a[max])
		max = right_child;
	if (max != i)
	{
		std::swap(a[i], a[max]);		// 把当前结点和它的最大(直接)子节点进行交换             
		Heapify(a, max, size);          // 递归调用，继续从当前结点向下进行堆调整
	}
}

template <class T>
int BuildHeap(T a[], int n)           // 建堆，时间复杂度O(n)
{
	int heap_size = n;
	for (int i = heap_size / 2 - 1; i >= 0; i--) // 从每一个非叶结点开始向下进行堆调整
		Heapify(a, i, heap_size);
	return heap_size;
}

template <class T>
void HeapSort(T a[], int n)
{
	int heap_size = BuildHeap(a, n);    // 建立一个最大堆
	// 堆（无序区）元素个数大于1，未完成排序
	while (heap_size > 1)   
	{
		// 将堆顶元素与堆的最后一个元素互换，并从堆中去掉最后一个元素
		// 此处交换操作很有可能把后面元素的稳定性打乱，所以堆排序是不稳定的排序算法
		std::swap(a[0], a[--heap_size]);
		Heapify(a, 0, heap_size);     // 从新的堆顶元素开始向下进行堆调整，时间复杂度O(logn)
	}
}

//快速排序
template <class T>
int Partition(T a[], int left, int right)  // 划分函数
{
	int pivot = a[right];               // 这里每次都选择最后一个元素作为基准
	int tail = left - 1;                // tail为小于基准的子数组最后一个元素的索引
	for (int i = left; i < right; i++)  // 遍历基准以外的其他元素
	{
		if (a[i] <= pivot)              // 把小于等于基准的元素放到前一个子数组末尾
		{
			std::swap(a[++tail], a[i]);
		}
	}
	std::swap(a[tail + 1], a[right]);   // 最后把基准放到前一个子数组的后边，剩下的子数组既是大于基准的子数组
										// 该操作很有可能把后面元素的稳定性打乱，所以快速排序是不稳定的排序算法
	return tail + 1;                    // 返回基准的索引
}

template <class T>
void QuickSort(T a[], int left, int right)
{
	if (left >= right)
		return;
	int pivot_index = Partition(a, left, right); // 基准的索引
	QuickSort(a, left, pivot_index - 1);
	QuickSort(a, pivot_index + 1, right);
}

template <class T>
void QuickSort(T a[], int n) {
	QuickSort(a, 0, n - 1);
}