#include <iostream>

long long partition(int n, int k);

int main() {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	std::cout << partition(n, k);
	return 0;
}

long long partition(int n, int k) {
	int tmp_n_ = n;
	int size_ = 0;
	do {
		size_ += tmp_n_;
		--tmp_n_;
	} while (tmp_n_ != 0);
 
	int tmp_k_ = k;
	tmp_n_ = n;
	int idx = 0;
	do {
		idx += tmp_n_;
		--tmp_n_;
		--tmp_k_;
	} while (tmp_k_ != 0);

    //Значения функции p(n,k) = p(n-1, k-1) + p(n-k, k)
	//- количество возможных разбиений n на k слагаемых
	long long* funcVal;
	if (size_ != 0) {
		funcVal = new long long[size_];
		for (int i = 0; i < size_; ++i) {
			funcVal[i] = 0;
		}
	}

	//Количество различных разбиений чисел от 1 по n
	long long* parts = new long long[n + 1];
	parts[0] = 1;
	for (int i = 1; i < (n + 1); ++i) {
		parts[i] = 0;
	}

	//Находим количество разбиений,
	//где каждое новое слагаемое является значением функции p(n,k)
	int r = 0;
	for (int i = 1; i < (n + 1); ++i) {
		for (int j = i; j < (n + 1); ++j) {
			parts[j] += parts[j - i];
			funcVal[r] = parts[j - i];
			++r;
		}
	}

	long long res = 0;
	if (idx > 0) {
		res = funcVal[idx - 1];
	}
	
	delete[] parts;
	delete[] funcVal;

	return res;
}

//n = 5, size_ = 15
//k = 3: idx = 12
// funcVal: 1 1 1 1 1|1 1 2 2|1 1 *2|1 1|1
// parts:
//0| 1         | = 1
//1| 1         | = 1
//2| 1 1       | = 2
//3| 1 1 1     | = 3
//4| 1 2 1 1   | = 5
//5| 1 2 *2 1 1 | = 7