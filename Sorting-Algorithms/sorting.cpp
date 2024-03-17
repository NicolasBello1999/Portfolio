#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <chrono>

using namespace std;

#define ALGOS 6

// prototypes
void swap(int *x, int *y);
void intiateArr(int ***arr, int max);

void bubbleSort(int arr[], int size);
void bubbleSortModified(int arr[], int size);
void insertionSort(int arr[], int size);
void selectionSort(int arr[], int size);

void mergeSort(int arr[], int begin, int end);
void merge(int arr[], int left, int mid, int right);
void heapSort(int arr[], int size);
void heapify(int arr[], int size, int i);

int main(int argc, char **argv) {
    int **arr, max, i, j, opt;
    bool m_flag = false;

    srand((unsigned) time(NULL));
    while ((opt = getopt(argc, argv, ":m")) != -1) {
        switch (opt) {
            case 'm':
                m_flag = true;
                break;
        }
    }

    if (!m_flag)
        max = 80000;
    else {
        if (optind < argc)
            max = atoi(argv[optind]);
    }

    try {
        intiateArr(&arr, max);

        printf("\nRuntime of Each Algorithm w/(%d) integers:\n", max);
        printf("===================================================\n")
        for (int algo = 0; algo < ALGOS; algo++) {
            auto start = chrono::high_resolution_clock::now();
            
            switch (algo) {
                case 0:
                    bubbleSort(arr[algo], max);
                    printf("Bubble Sort: ");
                    break;
                case 1:
                    bubbleSortModified(arr[algo], max);
                    printf("Modified Bubble Sort: ");
                    break;
                case 2:
                    insertionSort(arr[algo], max);
                    printf("Insertion Sort: ");
                    break;
                case 3:
                    selectionSort(arr[algo], max);
                    printf("Selection Sort: ");
                    break;
                case 4:
                    mergeSort(arr[algo], 0, max - 1);
                    printf("Merge Sort: ");
                    break;
                case 5:
                    heapSort(arr[algo], max);
                    printf("Heap Sort: ");
                    break;
            }

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            printf("%d ms\n", duration);
        }
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl; // print the exception
    }

    return 0;
}

// methods

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void intiateArr(int ***arr, int max) {
    int i, j;

    *arr = (int**)malloc(sizeof(int*) * ALGOS);
    for (i = 0; i < ALGOS; i++) {
        (*arr)[i] = (int*)malloc(sizeof(int) * (max + 1));

        for (j = 0; j < max; j++)
            (*arr)[i][j] = (rand() % 100) + 1;
    }
}

void bubbleSort(int arr[], int size) {
    int i, j;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSortModified(int arr[], int size) {
    int i, j;
    bool swapped;

    for (i = 0; i < size - 1; i++) {
        swapped = false;

        for (j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void insertionSort(int arr[], int size) {
    int i, j, key;

    for (i = 0; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size) {
    int i, j, min_idx;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
            swap(arr[i], arr[min_idx]);
    }
}

void mergeSort(int arr[], int begin, int end) {
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void merge(int arr[], int left, int mid, int right) {
    int i, j;
    int const n1 = mid - left + 1;
    int const n2 = right - mid;
 
    // Create temp arrs
    int *leftarr = new int[n1];
    int *rightarr = new int[n2];
 
    // Copy data to temp arrs leftarr[] and rightarr[]
    for (i = 0; i < n1; i++)
        leftarr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightarr[j] = arr[mid + 1 + j];
 
    auto x = 0, y = 0;
    int key = left;
 
    // Merge the temp arrs back into arr[left..right]
    while (x < n1 && y < n2) {
        if (leftarr[x] <= rightarr[y])
            arr[key] = leftarr[x++];
        else
            arr[key] = rightarr[y++];
        key++;
    }
 
    // Copy the remaining elements of left[], if there are any
    while (x < n1)
        arr[key++] = leftarr[x++];
 
    // Copy the remaining elements of right[], if there are any
    while (y < n2)
        arr[key++] = rightarr[y++];

    delete[] leftarr;
    delete[] rightarr;
}

void heapSort(int arr[], int size) {
    int i;
    // Build heap (rearrange array)
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
 
    // One by one extract an element from heap
    for (i = size - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int size, int i) {
    int largest = i; // initialize largest as root
    int l = 2 * i + 1; // left = (2*i) + 1
    int r = 2 * i + 2; // right = (2*i) + 2
 
    // if left child is larger than root
    if (l < size && arr[l] > arr[largest])
        largest = l;
 
    // if right child is larger than largest so far
    if (r < size && arr[r] > arr[largest])
        largest = r;
 
    // if largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
 
        // recursively heapify the affected sub-tree
        heapify(arr, size, largest);
    }
}