#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>

using namespace std;

// prototypes
void swap(int *x, int *y);
int *bubbleSort(int arr[], int size);
int *insertionSort(int arr[], int size);
int *selectionSort(int arr[], int size);

void bubbleSort(string arr[], int size);
void insertionSort(string arr[], int size);
void selectionSort(string arr[], int size);

int *fillArrRand(int arr[], int size);

int main(int argc, char *argv) {
    int **arr, max, i;
    bool m_flag = false;
    extern char *optarg; // used for getopt() to return the option argument value
    extern char optind;  // used by getopt() to communicate how far it scanned the command line
    char opt;

    while ((opt = getopt(argc, argv, ":m")) != -1) {
        switch (opt) {
            case 'm':
                m_flag = true;
                break;
            default:
                break;
        }
    }

    if (!m_flag)
        max = 100000;

    arr = new int[4][max];
    for (i = 0; i < 4; i++) {
        arr[i] = fillArrRand(arr[i], max);
    }

    return 0;
}

// methods

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int *bubbleSort(int arr[], int size) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - x; j++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
    }

    return arr;
}

int *insertionSort(int arr[], int size) {
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

    return arr;
}

int *selectionSort(int arr[], int size) {
    int i, j, min_idx;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < size; j++) {
            if (arr[j] <  arr[min_idx])
                min_idx = j;
            swap(arr[i], arr[min_idx]);
        }
    }

    return arr;
}

int *fillArrRand(int arr[], int size) {
    int i;
    
    srand((unsigned) time(NULL));
    for (i = 0; i < size; i++)
        arr[i] = (rand() % max) + 1;
    
    return arr;
}