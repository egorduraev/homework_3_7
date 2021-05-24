#include<stdio.h>
#include<stdlib.h>

//TASK 1:
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void fillRandom(int* arr, int len, int border) {
    for (int i = 0; i < len; ++i) {
        *(arr + i) = rand() % border;
    }
}

void printArray(int* arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortInserts(int arr[], int low, int n) {
    for(int i = low + 1; i < n + 1; i++) {
        int val = arr[i] ;
        int j = i ;
        while (j > low && arr[j-1] > val) {
            arr[j] = arr[j-1] ;
            j -= 1;
        }
        arr[j] = val ;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high] ;
    int i ,j;
    i = low;
    j = low;
    for (int i = low; i < high; i++) {
        if(arr[i] < pivot) {
            swap(&arr[i], &arr[j]);
            j += 1;
        }
    }
    swap(&arr[j], &arr[high]);
    return j;
}

void qs(int arr[], int low,int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        qs(arr, low, pivot-1) ;
        qs(arr, pivot + 1, high) ;
    }
}

void qsAdvanced(int arr[], int low, int high) {
    while (low < high) {
        if (high - low + 1 < 10)
        {
            sortInserts(arr, low, high);
            break;
        }
        else
        {
            int pivot = partition(arr, low, high) ;
            if (pivot - low < high - pivot)
            {
                qsAdvanced(arr, low, pivot - 1);
                low = pivot + 1;
            }
            else
            {
                qsAdvanced(arr, pivot + 1, high);
                high = pivot-1;
            }
        }
    }
}

// TASK 2:

void bucketSort(int* arr, int len) {
    const int max = len;
    const int b = 10;

    int buckets[b][max + 1];
    for (int i = 0; i < b; ++i) {
        buckets[i][max] = 0;
    }

    for (int digit = 1; digit < 1000000000; digit *= 10) {
        for (int i = 0; i < max; ++i) {
            if ((arr[i] % 2) != 0) continue;
            int d = (arr[i] / digit) % b;
            int counter = buckets[d][max];
            buckets[d][counter] = arr[i];
            counter++;
            buckets[d][max] = counter;
        }
        int idx = 0;
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < buckets[i][max]; ++j) {
                while ((arr[idx] % 2) != 0) {
                    idx++;
                }
                if (buckets[b][max] == 0) continue;
                arr[idx] = buckets[i][j];
                idx++;

            }
            buckets[i][max] = 0;
        }
    }
}

int main() {
    const int SZ = 30;
    int arr[SZ];
    printf("TASK 1 \n");
    fillRandom(arr, SZ, 100);
    printArray(arr, SZ);
    qs(arr, 0, SZ);
    printf("Hoare quicksort: \n");
    printArray(arr, SZ);
    qsAdvanced(arr, 0, SZ);
    printf("Advanced quicksort: \n");
    printArray(arr, SZ);
    printf("\n\n");
    printf("TASK 2 \n");
    fillRandom(arr, SZ, 30);
    printArray(arr, SZ);
    bucketSort(arr, SZ);
    printArray(arr, SZ);

}

