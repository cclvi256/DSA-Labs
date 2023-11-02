//
// Created by H on 2023/11/01.
//

#ifndef SORTING_ALGORITHMS_SORTING_H
#define SORTING_ALGORITHMS_SORTING_H


class Sorting
{
public:
	static void bubbleSort(int *arr, int len);
	static void selectionSort(int *arr, int len);
	static void insertionSort(int *arr, int len);
	static void quickSort(int *arr, int len);
	static void mergeSort(int *arr, int len);
	static void heapSort(int *arr, int len);
	static void radixSort(int *arr, int len);
};


#endif //SORTING_ALGORITHMS_SORTING_H
