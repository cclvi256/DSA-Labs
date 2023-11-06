#include <fstream>
#include <iostream>
#include <string>

int main() {
  using namespace std;

  string path;
  cout << "Please enter the path of the array to be sorted: ";
  cin >> path;
  ifstream ifs(path, ios::in);

  int arrLen;
  ifs >> arrLen;

  int *arr = new int[arrLen];

  for (int i = 0; i < arrLen; i++) {
  }

  return 0;
}
