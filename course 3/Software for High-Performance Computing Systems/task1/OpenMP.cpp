#include <omp.h>
#include <iostream>

int main() {
    int num_threads = 4; 

#pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        std::cout << "from process " << thread_id << std::endl;
    }

    return 0;
}
