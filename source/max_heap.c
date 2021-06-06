#include <stdio.h>
#include "../headers/max_heap.h"

  // Function to swap the the position of two elements
  void swap(int a, int b, int freq[],int years[]) {

    int temp = freq[a];
    freq[a] = freq[b];
    freq[b] = temp;

    temp = years[a];
    years[a] = years[b];
    years[b] = temp;
  }

  void heapify(int freq[],int years[], int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && freq[left] > freq[largest])
      largest = left;

    if (right < n && freq[right] > freq[largest])
      largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(i, largest,freq,years);
      heapify(freq,years, n, largest);
    }
}


  // Main function to do heap sort
  void heapSort(int freq[],int years[],  int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(freq,years, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
     swap(0, i,freq,years);

      // Heapify root element to get highest element at root again
      heapify(freq,years, i, 0);
    }
  }
