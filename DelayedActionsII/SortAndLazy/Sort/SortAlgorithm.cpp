#include "SortAlgorithm.h"

void Swap(int& left, int& right)
{
	int tmp = left;
	left = right;
	right = tmp;
}

Operations InsertionSort(int* elements, int elementCount)
{
	Operations op{};
	for(int k = 1; k < elementCount; k++)
	{
		++op.numberComparisons;
		if(elements[k] < elements[k-1])
		{		
			int x = elements[k];
			int i = 0;
			for(i = k; ((i > 0) && (elements[i-1] > x)); i--)
			{
				++op.numberComparisons;
				++op.numberSwaps;
				elements[i] = elements[i-1];
			}
			elements[i] = x;
		}
	}
	return op;
}

Operations BubbleSort(int* elements, int elementCount)
{
	Operations op{};
	for(int k = elementCount - 1; k > 0; k--)
    {
        bool noSwap = true;
        for(int i = 0; i < k; i++)
        {
			++op.numberComparisons;
        	if(elements[i] > elements[i + 1])
            {
				++op.numberSwaps;
				Swap(elements[i], elements[i + 1]);
                noSwap = false;
            }
        }
        if(noSwap)
			break;
    }
	return op;
}

Operations SelectionSort(int* elements, int elementCount)
{
	Operations op{};
	for(int k = 0; k < elementCount - 1; k++)
	{
		int min = k;
		for(int i = k+1; i < elementCount; i++)
		{
			++op.numberComparisons;
			if(elements[i] < elements[min])
				min=i;
		}
		++op.numberComparisons;
		if(min != k)
		{
			++op.numberSwaps;
			Swap(elements[k], elements[min]);
		}
	}
	return op;
}

Operations QuickSort(int* elements, int left, int right);
int QuickSortPartition(int* elements, int left, int right);
Operations QuickSort(int* elements, int elementCount)
{
	return QuickSortRecursive(elements, 0, elementCount - 1);
}

Operations QuickSortRecursive(int* elements, int left, int right)
{
	Operations op{};
	if(right <= left) 
		return op;
    
    int middle = QuickSortPartition(elements, left, right, &op);
    Operations opL = QuickSortRecursive(elements, left, middle - 1);
    Operations opR = QuickSortRecursive(elements, middle + 1, right);
	return {op.numberComparisons + opL.numberComparisons + opR.numberComparisons, op.numberSwaps + opL.numberSwaps + opR.numberSwaps};
	
}
int QuickSortPartition(int* elements, int left, int right, Operations* op)
{
    int pivot = elements[right]; // letztes Element als Pivotelement
    int i = left;
    int j = right - 1;
    
    while(1)
    {
        while(elements[i] <= pivot && i < right)
		{
			++op->numberComparisons;
            i++;
		}
        
        
        while(elements[j] >= pivot && j >= left)
		{
			++op->numberComparisons;
			j--;
		}
        
		++op->numberComparisons;
        if(i < j)
        {
			++op->numberSwaps;
			Swap(elements[i], elements[j]);
        }
        else
			break;
    }
	++op->numberSwaps;
	Swap(elements[i], elements[right]);
    return i;
}