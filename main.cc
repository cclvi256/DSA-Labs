#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "Sort.h"

#define TEST

int main(int argc, char **argv) {
  using namespace std;

  if (argc == 2 && strcmp(argv[1], "-c") == 0) {
    cout << "Sorting Algorithms." << endl;
    cout << "1: Sorting data from user." << endl;

    string path;
    cout << "Please enter the path of the array to be sorted: ";
    cin >> path;
    ifstream ifs(path, ios::in);

    int arrLen;
    ifs >> arrLen;

    int *arr = new int[arrLen];
    int *arrCopy = new int[arrLen];

    for (int i = 0; i < arrLen; ++i) {
      ifs >> arr[i];
      arrCopy[i] = arr[i];
    }

    cout << "The initial array is: ";
    print(arr, arrLen);

    auto startS = chrono::system_clock::now();
    selectionSort(arr, arrLen);
    auto endS = chrono::system_clock::now();
    auto durS = chrono::duration_cast<chrono::microseconds>(endS - startS);

    cout << "Sorted by selection sort: ";
    print(arr, arrLen);
    cout << "Time consumption: " << durS.count() << " microseconds" << endl;

    for (int i = 0; i < arrLen; ++i) {
      arr[i] = arrCopy[i];
    }

    auto startQ = chrono::system_clock::now();
    quickSort(arr, arrLen);
    auto endQ = chrono::system_clock::now();
    auto durQ = chrono::duration_cast<chrono::microseconds>(endQ - startQ);

    cout << "Sorted by quick sort: ";
    print(arr, arrLen);
    cout << "Time consumption: " << durQ.count() << " microseconds" << endl;

    for (int i = 0; i < arrLen; ++i) {
      arr[i] = arrCopy[i];
    }

    auto startM = chrono::system_clock::now();
    mergeSort(arr, arrLen);
    auto endM = chrono::system_clock::now();
    auto durM = chrono::duration_cast<chrono::microseconds>(endM - startM);

    cout << "Sorted by merge sort: ";
    print(arr, arrLen);
    cout << "Time consumption: " << durM.count() << " microseconds" << endl;
  }

  else if (argc == 1 || (argc == 2 && strcmp(argv[1], "-t") == 0)) {
    cout << "2: Sorting speed comparison.";
    cout << "Enter parameters: Data scale, Repeating times, Algorithm" << endl;
    cout << "q for quick sort, m for merge sort, s for selection sort" << endl;
    int dataScale, repeat;
    char algorithm;

    cin >> dataScale >> repeat >> algorithm;
    int **arrSet = new int *[repeat];

    for (int i = 0; i < repeat; ++i) {
      arrSet[i] = new int[dataScale];
    }

    auto seed = chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> u(0, 2147483647);

    for (int i = 0; i < dataScale; ++i) {
      for (int j = 0; j < repeat; ++j) {
        arrSet[j][i] = u(e);
      }
    }

    auto start = chrono::system_clock::now();

    switch (algorithm) {
    case 'q':
      for (int i = 0; i < repeat; ++i) {
        quickSort(arrSet[i], dataScale);
      }
      break;
    case 'm':
      for (int i = 0; i < repeat; ++i) {
        mergeSort(arrSet[i], dataScale);
      }
      break;
    case 's':
      for (int i = 0; i < repeat; ++i) {
        selectionSort(arrSet[i], dataScale);
      }
      break;
    default:
      cout << "Invalid algorithm.";
      break;
    }

    auto end = chrono::system_clock::now();
    auto duration =
        duration_cast<chrono::microseconds>((end - start) * (1.0 / repeat));

    for (int i = 0; i < repeat; ++i) {
      delete[] arrSet[i];
    }

    delete[] arrSet;

    cout << "Time consumption: " << duration.count() << " microseconds" << endl;
  }

  else if (argc == 4) {
    string dataScaleS = argv[1];
    string repeatS = argv[2];
    string algorithmS = argv[3];
    int dataScale = stoi(dataScaleS);
    int repeat = stoi(repeatS);
    char algorithm = algorithmS[0];

    int **arrSet = new int *[repeat];

    for (int i = 0; i < repeat; ++i) {
      arrSet[i] = new int[dataScale];
    }

    auto seed = chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> u(0, 2147483647);

    for (int i = 0; i < dataScale; ++i) {
      for (int j = 0; j < repeat; ++j) {
        arrSet[j][i] = u(e);
      }
    }

    auto start = chrono::system_clock::now();

    switch (algorithm) {
    case 'q':
      for (int i = 0; i < repeat; ++i) {
        quickSort(arrSet[i], dataScale);
      }
      break;
    case 'm':
      for (int i = 0; i < repeat; ++i) {
        mergeSort(arrSet[i], dataScale);
      }
      break;
    case 's':
      for (int i = 0; i < repeat; ++i) {
        selectionSort(arrSet[i], dataScale);
      }
      break;
    default:
      cout << "Invalid algorithm.";
      break;
    }

    auto end = chrono::system_clock::now();
    auto duration =
        duration_cast<chrono::microseconds>((end - start) * (1.0 / repeat));

    for (int i = 0; i < repeat; ++i) {
      delete[] arrSet[i];
    }

    delete[] arrSet;

    cout << "Size: ";
    cout.width(12);
    cout << dataScale;
    cout << "Time: ";
    cout.width(12);
    cout << duration.count() << " microseconds" << endl;
  }

  return 0;
}
