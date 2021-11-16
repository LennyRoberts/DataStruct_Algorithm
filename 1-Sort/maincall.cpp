#include "sorttesthelper.h"
#include "basicsort.h"
#include "advancesort.h"
#include "heapsort.h"
#include <ctime>
#include <cstdio>

int main(){
    int n=100;            //Data Size
    int SwapTimes=10;    //SwapTimes
    int *arr=SortTestHelper::GenerateRandomArray(n,0,n);
    int *arr2=SortTestHelper::CopyIntArray(arr,n);
    int *arr3=SortTestHelper::CopyIntArray(arr,n);
    int *arr4=SortTestHelper::CopyIntArray(arr,n);

    int *array=SortTestHelper::GenerateNearlyOrderedArray(n,SwapTimes);
    int *array2=SortTestHelper::CopyIntArray(array,n);
    int *array3=SortTestHelper::CopyIntArray(array,n);

//    SortTestHelper::TestSort("Insert Sort",InsertSort,arr2,n);
//    SortTestHelper::TestSort("Insert Sort Advance",InsertSortAdvance,arr3,n);
//    SortTestHelper::TestSort("BinaryInsertionSort",BinaryInsertion,arr,n);
//    SortTestHelper::TestSort("Shell Sort",ShellSort,arr,n);

//    SortTestHelper::TestSort("Bubble Sort",BubbleSort,arr,n);
//    SortTestHelper::TestSort("Bubble Sort",OptimizedBubbleSort,arr2,n);
//    SortTestHelper::TestSort("Quick Sort",QuickSort,arr,n);
//    SortTestHelper::TestSort("Quick Sort2",QuickSort2,arr2,n);
//    SortTestHelper::TestSort("QuickSort3Ways",QuickSort3Ways,arr3,n);

//    SortTestHelper::TestSort("Merge Sort",MergeSort1,arr,n);
//    SortTestHelper::TestSort("MergeOp Sort",MergeSort2,arr2,n);
//    SortTestHelper::TestSort("MergeBU Sort",MergeSort3,arr3,n);

//    SortTestHelper::TestSort("Selection Sort",SelectSort,arr,n);
//    SortTestHelper::TestSort("Selection Sort Advance",OptimizedSelectSort,arr2,n);
//    srand(time_t(nullptr));

//    heapSort1(arr,n);
//    for(int i=1;i<n;i++)
//        cout<<arr[i]<<" ";

//    heapsort2(arr,n);

//    MaxHeap<int> heapmax=MaxHeap<int>(arr,n);
//    //heapmax.print();
//    cout<<endl;
//    heapmax.Heapify(n);
//    heapmax.print();


    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete [] array;
    delete [] array2;
    delete [] array3;


    return 0;
}
