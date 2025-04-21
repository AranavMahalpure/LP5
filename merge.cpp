#include <iostream>
#include <omp.h>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int temp[r - l + 1], i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (i = l, k = 0; i <= r; i++, k++) arr[i] = temp[k];
}

void mergesort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(arr, l, m);
            #pragma omp section
            mergesort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergesort(arr, 0, n - 1);
    }
    double end = omp_get_wtime();

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nTime taken: " << end - start << " seconds\n";

    return 0;
}
