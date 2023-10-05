#include <fstream>

//схема разбиения Хоара
int partitionHoare(int* data, int l, int r) {
    int k = data[l + (r - l) / 2];
    int i = l - 1;
    int j = r + 1;
    int tmp = 0;

    while (true) {
        do {
            i++;
        } while (data[i] < k);
 
        do {
            j--;
        } while (data[j] > k);
 
        if (i >= j) {
            return j;
        }

        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
}

void QuickSelect(int* data, int left, int right, int k1, int k2) {
    if (left >= right) {
        return;
    }

    int pivot = partitionHoare(data, left, right);
    if (pivot >= k1 - 1) {
        QuickSelect(data, left, pivot, k1, k2);
    }
    if (pivot < k2 - 1) {
        QuickSelect(data, pivot + 1, right, k1, k2);
    }
}


int main(int argc, char* argv[]){
    if (argc != 3) {
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    }
    std::ofstream fout(argv[2]);
    if (!fout.is_open()) {
        return 1;
    }

    int n, k1, k2, A, B, C, x1, x2;
    fin >> n >> k1 >> k2 >> A >> B >> C >> x1 >> x2;
    int* data = new int[n];
    int* tmp = new int[n];
    data[0] = x1;
    data[1] = x2;
    for (int i = 2; i < n; ++i) {
        data[i] = A*data[i-2] + B*data[i-1] + C;
    }

    QuickSelect(data, 0, n - 1, k1, k2);
    for (int i = k1 - 1; i < k2 - 1; ++i) {
        fout << data[i] << ' ';
    }
    fout << data[k2 - 1];

    delete[] data;
    delete[] tmp;
    fin.close();
    fout.close();

    return 0;
}

//схема разбиения Ломуто (через случайный элемент)
//int partitionLomuto(int* data, int l, int r) {
//    int tmp = 0;
//    int num = 0;
//    if (l != r) {
//        num = l + rand() % (r - l);
//        tmp = data[r];
//        data[r] = data[num];
//        data[num] = tmp;
//    }
//    int k = data[r];
//    int res = l;
//    for (int i = l; i <= r; ++i) {
//        if (data[i] <= k) {
//            tmp = data[res];
//            data[res] = data[i];
//            data[i] = tmp;
//            res++;
//        }
//    }
//    return res - 1;
//}