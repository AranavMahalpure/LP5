#include <iostream>
#include <omp.h>
using namespace std;

void bubbleSort(int arr[], int n, bool parallel) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        #pragma omp parallel for if(parallel) shared(arr, first)
        for (int j = first; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int arr1[n], arr2[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
        arr2[i] = arr1[i];  // Copy for parallel sort
    }

    double t1 = omp_get_wtime();
    bubbleSort(arr1, n, false);  // Sequential
    double t2 = omp_get_wtime();

    double t3 = omp_get_wtime();
    bubbleSort(arr2, n, true);   // Parallel
    double t4 = omp_get_wtime();

    cout << "\nSorted Array (Sequential): ";
    for (int i = 0; i < n; i++) cout << arr1[i] << " ";
    cout << "\nTime (Sequential): " << t2 - t1 << " seconds";

    cout << "\n\nSorted Array (Parallel): ";
    for (int i = 0; i < n; i++) cout << arr2[i] << " ";
    cout << "\nTime (Parallel): " << t4 - t3 << " seconds\n";

    return 0;
}
