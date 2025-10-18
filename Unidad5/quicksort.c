#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low;            

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]);
    return i;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    int data[] = {6, 2, 4, 1, 5, 8, 10, 3, 9, 7};
    int n = sizeof(data) / sizeof(data[0]);

    quickSort(data, 0, n - 1);

    printf("Arreglo ordenado con QuickSort:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }

    printf("\n");
    return 0;
}
