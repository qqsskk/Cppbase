#pragma once

#include<iostream>
using namespace std;

//�㷨��Դ:http://www.cnblogs.com/eniac12/p/5329396.html
//��ԭ�е�int��Ϊģ�����ʹ�ö�������

//*********************************˳�����(��򵥵Ĳ���)*********************************//
template <class T>
int SequenceSearch(T a[], T value, int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (a[i] == value)
			return i;
	return -1;
}

//*********************************���ֲ���(Ԫ�ر���������ģ�������������Ҫ�Ƚ����������)*********************************//

//���ֲ��ң��۰���ң����汾1
template <class T>
int BinarySearch(T a[], T value, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == value)
			return mid;
		if (a[mid] > value)
			high = mid - 1;
		if (a[mid] < value)
			low = mid + 1;
	}
	return -1;
}

//*********************************��ֵ����(Ԫ�ر���������ģ�������������Ҫ�Ƚ����������)*********************************//
//���ֲ��ҵĸĽ��汾
template <class T>
int InsertionSearch(T a[], T value, int low, int high)
{
	int mid = low + (value - a[low]) / (a[high] - a[low])*(high - low);
	if (a[mid] == value)
		return mid;
	if (a[mid] > value)
		return InsertionSearch(a, value, low, mid - 1);
	if (a[mid] < value)
		return InsertionSearch(a, value, mid + 1, high);
}









