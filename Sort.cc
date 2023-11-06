//
// Created by H on 2023/11/01.
//

#include "Sort.h"

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

void mergeSort(int *arr, int len) {
  int *newArr = new int[len];
  for (int unitLen = 1; unitLen < len; unitLen *= 2) {
    int parts = len / unitLen + len % unitLen ? 1 : 0;
    int pairs = (parts + 1) / 2;

    int index = 0;

    for (int i = 0; i < pairs; ++i) {
      int st1 = index;
      int st2 = index + unitLen;

      if (st2 >= len) {
        break;
      }

      bool flag = true;
      while (flag) {
        if (arr[st1] < arr[st2]) {
          newArr[index] = arr[st1];
          ++st1;
        } else {
          newArr[index] = arr[st2];
          ++st2;
        }
        ++index;

        if (st1 >= unitLen || st2 > unitLen || index == len) {
          flag = false;
        }
      }
    }
  }
}

void heapSort(int *arr, int len) {}

void radixSort(int *arr, int len) {}
