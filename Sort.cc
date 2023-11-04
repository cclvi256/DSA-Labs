//
// Created by H on 2023/11/01.
//

#include "Sort.h"

namespace Sort
{
void bubbleSort(int* arr, int len)
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

void selectionSort(int* arr, int len)
{
}

void insertionSort(int* arr, int len)
{
}

void quickSort(int* arr, int len)
{
  if (len < 2)
  {
    return;
  }

  int pivot = arr[0];
  int* newArr = new int[len];
  int index1 = 0, index2 = len - 1;

  for (int i = 1; i < len; i++)
  {
    if (arr[i] < pivot)
    {
      newArr[index1] = arr[i];
      ++index1;
    }
    else
    {
      newArr[index2] = arr[i];
      --index2;
    }
  }

  newArr[index1] = pivot;

  for (int i = 0; i < len; i++)
  {
    arr[i] = newArr[i];
  }

  delete[] newArr;

  quickSort(arr, index1);
  quickSort(arr + index1 + 1, len - index2 - 1);
}

void heapSort(int* arr, int len)
{
}

void radixSort(int* arr, int len)
{
}

}// namespace Sort
