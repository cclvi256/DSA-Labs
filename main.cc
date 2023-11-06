#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "Sort.h"

#define TEST

int main() {
  using namespace std;

#ifndef TEST
  string path;
  cout << "Please enter the path of the array to be sorted: ";
  cin >> path;
  ifstream ifs(path, ios::in);

  int arrLen;
  ifs >> arrLen;

  int *arr = new int[arrLen];
  int *arrCopy = new int[arrLen];

  for (int i = 0; i < arrLen; i++) {
    ifs >> arr[i];
    arrCopy[i] = arr[i];
  }
#else
  cout << "Please enter as required: ";

  int arrLen;
  cin >> arrLen;

  int *arr = new int[arrLen];
  int *arrCopy = new int[arrLen];

  for (int i = 0; i < arrLen; i++) {
    cin >> arr[i];
    arrCopy[i] = arr[i];
  }
#endif
  selectionSort(arr, arrLen);

  for (int i = 0; i < arrLen; i++) {
    arr[i] = arrCopy[i];
  }

  quickSort(arr, arrLen);

  for (int i = 0; i < arrLen; i++) {
    arr[i] = arrCopy[i];
  }

  mergeSort(arr, arrLen);

  return 0;
}
