#include <iostream>
#include <string>
using namespace std;

// prototypes
void swap(int *x, int *y);
int *bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);

void bubbleSort(string arr[], int n);
void insertionSort(string arr[], int n);
void selectionSort(string arr[], int n);

int main(int argc, char *argv) {

    return 0;
}

// methods

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int *bubbleSort(int arr[], int n) {
    int x, y, temp;

    for (x = 0; x < n - 1; x++) {
        for (y = 0; y < n - 1 - x; y++) {
            if (arr[x] > arr[x + 1]) {
                swap(arr[x], arr[x + 1]);
            }
        }
    }

    return arr;
}

void insertionSort(int arr[], int n) {

}

void selectionSort(int arr[], int n) {

}