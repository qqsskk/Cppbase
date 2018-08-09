#pragma once

//�㷨��Դ:http://www.cnblogs.com/eniac12/p/5329396.html
//��ԭ�е�int��Ϊģ�����ʹ�ö�������

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

//ð������
template <class T>
void bubbleSort(T a[], int n)
{
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n - 1 - j; i++) // ���αȽ����ڵ�����Ԫ��,ʹ�ϴ���Ǹ������
		{
			if (a[i] > a[i + 1])            // ��������ĳ�A[i] >= A[i + 1],���Ϊ���ȶ��������㷨
			{
				std::swap(a[i], a[i + 1]);
			}
		}
	}
}

//��β������Ҳ�ж���ð������
template <class T>
void CocktailSort(T a[], int n)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		for (int i = left; i < right; i++)   // ǰ����,�����Ԫ�طŵ�����
		{
			if (a[i] > a[i + 1])
			{
				std::swap(a[i], a[i + 1]);
			}
		}
		right--;
		for (int i = right; i > left; i--)   // �����,����СԪ�طŵ�ǰ��
		{
			if (a[i - 1] > a[i])
			{
				std::swap(a[i - 1], a[i]);
			}
		}
		left++;
	}
}

//ѡ������
template <class T>
void SelectionSort(T a[], int n) 
{
	for (int i = 0; i < n - 1; i++)         // iΪ���������е�ĩβ
	{
		int min = i;
		for (int j = i + 1; j < n; j++)     // δ��������
		{
			if (a[j] < a[min])              // �ҳ�δ���������е���Сֵ
			{
				min = j;
			}
		}
		if (min != i)
		{
			std::swap(a[min], a[i]);    // �ŵ����������е�ĩβ���ò������п��ܰ��ȶ��Դ��ң�����ѡ�������ǲ��ȶ��������㷨
		}
	}
}

//��������
template <class T>
void InsertionSort(T a[], int n) {

	for (int i = 1; i < n; i++)         // ����ץ�˿�������
	{
		int get = a[i];                 // ����ץ��һ���˿���
		int j = i - 1;                  // ���������ϵ�����������õ�
		while (j >= 0 && a[j] > get)    // ��ץ�����������ƴ���������бȽ�
		{
			a[j + 1] = a[j];            // ��������Ʊ�ץ�����ƴ󣬾ͽ�������
			j--;
		}
		a[j + 1] = get; // ֱ�������Ʊ�ץ������С(��������)����ץ�����Ʋ��뵽�������ұ�(���Ԫ�ص���Դ���δ�䣬���Բ����������ȶ���)
	}
}

//���ֲ�������
template <class T>
void InsertionSortDichotomy(T a[], int n) {

	for (int i = 1; i < n; i++)         // ����ץ�˿�������
	{
		int get = a[i];                 // ����ץ��һ���˿���
		int j = i - 1;                  // ���������ϵ�����������õ�
		while (j >= 0 && a[j] > get)    // ��ץ�����������ƴ���������бȽ�
		{
			a[j + 1] = a[j];            // ��������Ʊ�ץ�����ƴ󣬾ͽ�������
			j--;
		}
		a[j + 1] = get; // ֱ�������Ʊ�ץ������С(��������)����ץ�����Ʋ��뵽�������ұ�(���Ԫ�ص���Դ���δ�䣬���Բ����������ȶ���)
	}
}

//ϣ������
template <class T>
void ShellSort(T a[], int n)
{
	int h = 0;
	while (h <= n)// ���ɳ�ʼ����
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
		h = (h - 1) / 3;// �ݼ�����
	}
}


//�鲢����
template <class T>
void Merge(T a[], int left, int mid, int right)// �ϲ��������ź��������A[left...mid]��A[mid+1...right]
{
	int len = right - left + 1;
	int *temp = new T[len];       // �����ռ�O(n)
	int index = 0;
	int i = left;                   // ǰһ�������ʼԪ��
	int j = mid + 1;                // ��һ�������ʼԪ��
	while (i <= mid && j <= right)
	{
		temp[index++] = a[i] <= a[j] ? a[i++] : a[j++];  // ���Ⱥű�֤�鲢������ȶ���
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
void MergeSortIteration(T a[], int len)    // �ǵݹ�(����)ʵ�ֵĹ鲢����(�Ե�����)
{
	int left, mid, right;// ����������,ǰһ��ΪA[left...mid]����һ��������ΪA[mid+1...right]
	for (int i = 1; i < len; i *= 2)        // ������Ĵ�Сi��ʼΪ1��ÿ�ַ���
	{
		left = 0;
		while (left + i < len)              // ��һ�����������(��Ҫ�鲢)
		{
			mid = left + i - 1;
			right = mid + i < len ? mid + i : len - 1;// ��һ���������С���ܲ���
			Merge(a, left, mid, right);
			left = right + 1;               // ǰһ����������������ƶ�
		}
	}
}

//������
template <class T>
void Heapify(T a[], int i, int size)  // ��A[i]���½��жѵ���
{
	int left_child = 2 * i + 1;         // ��������
	int right_child = 2 * i + 2;        // �Һ�������
	int max = i;                        // ѡ����ǰ����������Һ�������֮�е����ֵ
	if (left_child < size && a[left_child] > a[max])
		max = left_child;
	if (right_child < size && a[right_child] > a[max])
		max = right_child;
	if (max != i)
	{
		std::swap(a[i], a[max]);		// �ѵ�ǰ�����������(ֱ��)�ӽڵ���н���             
		Heapify(a, max, size);          // �ݹ���ã������ӵ�ǰ������½��жѵ���
	}
}

template <class T>
int BuildHeap(T a[], int n)           // ���ѣ�ʱ�临�Ӷ�O(n)
{
	int heap_size = n;
	for (int i = heap_size / 2 - 1; i >= 0; i--) // ��ÿһ����Ҷ��㿪ʼ���½��жѵ���
		Heapify(a, i, heap_size);
	return heap_size;
}

template <class T>
void HeapSort(T a[], int n)
{
	int heap_size = BuildHeap(a, n);    // ����һ������
	// �ѣ���������Ԫ�ظ�������1��δ�������
	while (heap_size > 1)   
	{
		// ���Ѷ�Ԫ����ѵ����һ��Ԫ�ػ��������Ӷ���ȥ�����һ��Ԫ��
		// �˴������������п��ܰѺ���Ԫ�ص��ȶ��Դ��ң����Զ������ǲ��ȶ��������㷨
		std::swap(a[0], a[--heap_size]);
		Heapify(a, 0, heap_size);     // ���µĶѶ�Ԫ�ؿ�ʼ���½��жѵ�����ʱ�临�Ӷ�O(logn)
	}
}

//��������
template <class T>
int Partition(T a[], int left, int right)  // ���ֺ���
{
	int pivot = a[right];               // ����ÿ�ζ�ѡ�����һ��Ԫ����Ϊ��׼
	int tail = left - 1;                // tailΪС�ڻ�׼�����������һ��Ԫ�ص�����
	for (int i = left; i < right; i++)  // ������׼���������Ԫ��
	{
		if (a[i] <= pivot)              // ��С�ڵ��ڻ�׼��Ԫ�طŵ�ǰһ��������ĩβ
		{
			std::swap(a[++tail], a[i]);
		}
	}
	std::swap(a[tail + 1], a[right]);   // ���ѻ�׼�ŵ�ǰһ��������ĺ�ߣ�ʣ�µ���������Ǵ��ڻ�׼��������
										// �ò������п��ܰѺ���Ԫ�ص��ȶ��Դ��ң����Կ��������ǲ��ȶ��������㷨
	return tail + 1;                    // ���ػ�׼������
}

template <class T>
void QuickSort(T a[], int left, int right)
{
	if (left >= right)
		return;
	int pivot_index = Partition(a, left, right); // ��׼������
	QuickSort(a, left, pivot_index - 1);
	QuickSort(a, pivot_index + 1, right);
}

template <class T>
void QuickSort(T a[], int n) {
	QuickSort(a, 0, n - 1);
}