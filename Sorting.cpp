//
// Created by H on 2023/11/01.
//

#include "Sorting.h"

void Sorting::bubbleSort(int* arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = len - 1; j >= i; j++)
		{
			if (arr[j] < arr[j - 1])
			{
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

void Sorting::selectionSort(int* arr, int len)
{

}

void Sorting::insertionSort(int* arr, int len)
{

}

void Sorting::quickSort(int* arr, int len)
{

}

void Sorting::mergeSort(int* arr, int len)
{

}

void Sorting::heapSort(int* arr, int len)
{

}

void Sorting::radixSort(int* arr, int len)
{

}

void Sorting::quickSort(int* arr, int start, int len)
{

}
