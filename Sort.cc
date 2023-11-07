//
// Created by H on 2023/11/01.
//

#include "Sort.h"
#include <iostream>

void selectionSort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < len; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }

    int temp = arr[i];
    arr[i] = arr[minIndex];
    arr[minIndex] = temp;
  }
}

void quickSort(int *arr, int len) {
  if (len < 2) {
    return;
  }

  int pivot = arr[0];
  int *newArr = new int[len];
  int index1 = 0, index2 = len - 1;

  for (int i = 1; i < len; i++) {
    if (arr[i] < pivot) {
      newArr[index1] = arr[i];
      ++index1;
    } else {
      newArr[index2] = arr[i];
      --index2;
    }
  }

  newArr[index1] = pivot;

  for (int i = 0; i < len; i++) {
    arr[i] = newArr[i];
  }

  delete[] newArr;

  quickSort(arr, index1);
  quickSort(arr + index1 + 1, len - index2 - 1);
}

void heapSort(int *arr, int len) {}

void radixSort(int *arr, int len) {}

void print(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    std::cout << arr[i] << ' ';
  }
  std::cout << std::endl;
}

void mergeSort(int *arr, int len) {
  for(int unit=1;unit< len;unit*=2){
    int *newArr = new int[len];

    int index = 0;

    for (int i = 0; i < len; i += 2 * unit) {
      if (i + unit >= len) {
        break;
      }

      int c1 = 0, c2 = 0;
      while (c1 < unit || (c2 < unit && i + unit + c2 < len)) {
        if (c1 == unit) {
          newArr[index] = arr[i + unit + c2];
          c2++;
        }

        else if (c2 == unit || i + unit + c2 >= len) {
          newArr[index] = arr[i + c1];
          c1++;
        }

        else if (arr[i + c1] < arr[i + unit + c2]) {
          newArr[index] = arr[i + c1];
          c1++;
        }

        else {
          newArr[index] = arr[i + unit + c2];
          c2++;
        }

        index++;
      }
    }

    for (int i = 0; i < index; i++) {
      arr[i] = newArr[i];
    }

    delete[] newArr;
    newArr = nullptr;
  }
}
