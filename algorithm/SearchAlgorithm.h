#pragma once

#include<iostream>
using namespace std;

//算法来源:http://www.cnblogs.com/eniac12/p/5329396.html
//把原有的int改为模板可以使用多种类型

//*********************************顺序查找(最简单的查找)*********************************//
template <class T>
int SequenceSearch(T a[], T value, int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (a[i] == value)
			return i;
	return -1;
}

//*********************************二分查找(元素必须是有序的，如果是无序的则要先进行排序操作)*********************************//

//二分查找（折半查找），版本1
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

//*********************************插值查找(元素必须是有序的，如果是无序的则要先进行排序操作)*********************************//
//二分查找的改进版本
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









