//Нахождение минимального остовного дерева с помощью Disjoint-set

#include <iostream>
#include <fstream>

struct Edge {
    int x0_;
    int x_;
    int w_;
};

void Merge(Edge* arr, Edge* tmp, int l, int mid, int r) {
    int i = l;
    int j = mid + 1;
    int k = l;
    while ((i <= mid) && (j <= r)) {
        if (arr[i].w_ <= arr[j].w_) {
            tmp[k++] = arr[i++];
        }
        else {
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
}

void MergeSort(Edge* arr, Edge* tmp, int l, int r) {
    if (r <= l) {
        return;
    }
    int mid = l + (r - l) / 2;

    MergeSort(arr, tmp, l, mid);
    MergeSort(arr, tmp, mid + 1, r);
    Merge(arr, tmp, l, mid, r);
}

class DisjointSet {
    int* id_;
    int* size_;
public:
    DisjointSet() {
        id_ = nullptr;
        size_ = nullptr;
    }

    DisjointSet(int n) {
        id_ = new int[n];
        size_ = new int[n];
        for (int i = 0; i < n; ++i) {
            id_[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            size_[i] = 1;
        }
    }

    ~DisjointSet() {
        delete[] id_;
        delete[] size_;
    }

    int find(int X) {
        if (id_[X] == X) {
            return X;
        }

        return id_[X] = find(id_[X]);
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return;
        }
        if (size_[px] < size_[py]) {
            id_[px] = py;
            size_[py] += size_[px];
        } else {
            id_[py] = px;
            size_[px] += size_[py];
        }
    }
};



int main(int argc, char* argv[]){
    if (argc != 2) {
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        return 1;
    }
    int numberOfEdges = 0; 
    int numberOfVertices = 0;
    fin  >> numberOfVertices >> numberOfEdges;
    Edge* edges = new Edge[numberOfEdges];
    Edge* tmp = new Edge[numberOfEdges];
    int tmp1 = 0;
    int tmp2 = 0;
    for (int i = 0; i < numberOfEdges; ++i) {
        fin >> tmp1 >> tmp2 >> edges[i].w_;
        if (tmp1 < tmp2) {
            edges[i].x0_ = tmp1;
            edges[i].x_ = tmp2;
        } else {
            edges[i].x0_ = tmp2;
            edges[i].x_ = tmp1;
        }
        tmp[i].x0_ = edges[i].x0_;
        tmp[i].x_ = edges[i].x_;
        tmp[i].w_ = edges[i].w_;
    }
    MergeSort(edges, tmp, 0, numberOfEdges - 1);
    int res = 0;
    DisjointSet dsu(numberOfVertices);
    for (int i = 0; i < numberOfEdges; ++i) {
        if (dsu.find(edges[i].x0_) != dsu.find(edges[i].x_)) {
            dsu.unite(edges[i].x0_, edges[i].x_);
            res += edges[i].w_;
        }

    }
    std::cout << res;

    delete[] tmp;
    delete[] edges;
    fin.close();
    return 0;
} 