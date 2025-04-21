#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4};
    int min_val = arr[0], max_val = arr[0], sum = 0;

    #pragma omp parallel for reduction(min: min_val) reduction(max: max_val) reduction(+: sum)
    for (int i = 0; i < arr.size(); i++) {
        min_val = min(min_val, arr[i]);
        max_val = max(max_val, arr[i]);
        sum += arr[i];
    }

    cout << "Min: " << min_val << "\nMax: " << max_val << "\nSum: " << sum 
         << "\nAverage: " << (double)sum / arr.size() << endl;
    return 0;
}