#include <fstream>
#include <iostream>

void QuickSort(double* arr, int l, int r) {
    int left = l;
    int right = r;
    double pivot = arr[l + rand() % (r - l + 1)];
    double tmp = 0;
    do {
        while (arr[left] < pivot) {
            ++left;
        }
        while (arr[right] > pivot) {
            --right;
        }
        if (left <= right) {
            tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            ++left;
            --right;
        }
    } while (left <= right);

    if (l < right) {
        QuickSort(arr, l, right);
    }
    if (r > left) {
        QuickSort(arr, left, r);
    }
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    }
    int n = 0;
    fin >> n;
    double* M = new double[n];
    double* sorted = new double[n];
    for (int i = 0; i < n; ++i) {
        fin >> M[i];
        sorted[i] = M[i];
    }
    QuickSort(sorted, 0, n-1);
    int idxMin = 0;
    while (M[idxMin] != sorted[0]) {
        ++idxMin;
    }
    int idxMax = 0;
    while (M[idxMax] != sorted[n-1]) {
        ++idxMax;
    }
    int idxMid = 0;
    while (M[idxMid] != sorted[n/2]) {
        ++idxMid;
    }
    std::cout << idxMin+1 << ' ' << idxMid+1 << ' ' << idxMax+1;
    delete[] M;
    delete[] sorted;
    fin.close();
    return 0;
}

