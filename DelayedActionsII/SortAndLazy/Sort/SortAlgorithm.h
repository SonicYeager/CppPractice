#pragma once

struct Operations
{
	int numberComparisons = 0;
	int numberSwaps = 0;
};

Operations InsertionSort(int* elements, int elementCount);
Operations BubbleSort(int* elements, int elementCount);
Operations SelectionSort(int* elements, int elementCount);
Operations QuickSort(int* elements, int elementCount)