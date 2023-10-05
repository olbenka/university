#include <fstream>
#include <iostream>

struct Element {
    int x0;
    int x1;
};

unsigned long long Merge(int l, Element* arr, int mid, Element* tmp,  int r) {
    int i = l;
    int j = mid + 1;
    int k = l;
    unsigned long long count = 0;
    while ((i <= mid) && (j <= r)) {
        if (arr[i].x0 <= arr[j].x0) {
            if (arr[i].x0 == arr[j].x0) {
                count += mid - i + 1;
            }
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= r) {
        tmp[k++] = arr[j++];
    }
    for (i = l; i <= r; i++) {
        arr[i] = tmp[i];
    }
    return count;
}

unsigned long long MergeSort(Element* arr, int l, Element* tmp, int r) {
    if (r <= l) {
        return 0;
    }
    unsigned long long count = 0;
    int mid = l + (r - l) / 2;

    count += MergeSort(arr, l, tmp, mid);
    count += MergeSort(arr, mid + 1, tmp, r);
    count += Merge(l, arr,  mid, tmp, r);

    return count;
}

unsigned long long int InvMerge(int l, Element* arr, int mid, Element* tmp,  int r) {
    int k = l;
    int i = l;
    int j = mid + 1;
    unsigned long long int count = 0;
    while (i <= mid && j <= r) {
        if (arr[i].x1 < arr[j].x1) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            count += mid - i + 1;
        }
    }

    while (i <= mid) {
        tmp[k++] = arr[i++];
    }

    for (i = l; i <= r; ++i) {
        arr[i] = tmp[i];
    }

    return count;
}

unsigned long long int InvMergeSort(Element* arr, int l, Element* tmp, int r) {
    if (r <= l) {
        return 0;
    }

    int mid = (l + (r - l) / 2);
    unsigned long long int count = 0;

    count += InvMergeSort(arr, l, tmp, mid);
    count += InvMergeSort(arr, mid + 1, tmp, r);
    count += InvMerge(l, arr,  mid, tmp, r);

    return count;
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
    Element* data = new Element[n];
    Element* tmp = new Element[n];
    for (int i = 0; i < n; ++i) {
        fin >> data[i].x0;
        fin >> data[i].x1;
        tmp[i].x0 = data[i].x0;
        tmp[i].x1 = data[i].x1;
    }
    unsigned long long first = MergeSort(data, 0, tmp, n - 1);
    int num = 0;
    int add = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (data[i].x0 == data[i + 1].x0) {
            ++num;
        }
    }
    if (num == n - 1) {
        add = 1;
    }
    std::cout << add + first +  InvMergeSort(data, 0, tmp, n - 1) << std::endl;

    delete[] data;
    delete[] tmp;
    fin.close();
    return 0;
}

