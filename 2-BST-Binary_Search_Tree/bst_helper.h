#ifndef BST_HELPER_H
#define BST_HELPER_H

#include "iostream"
#include <assert.h>
#include <ctime>
#include <string>

using namespace std;

namespace BSTHelper {
int* GenerateRandomArray(int n,int rangeL,int rangeR){
    assert(rangeL<=rangeR);
    int* arr=new int[n];
    srand(time_t(nullptr));
    for(int i=0;i<n;i++)
        arr[i]=rand()%(rangeR-rangeL+1)+rangeL;
    return arr;
}

void print(int arr[],int left,int right){
    assert(right >= left);
    for(int i=left;i<=right;i++)
        cout<<arr[i]<<" ";
}

template <typename T>
bool isorder(T arr[],int left,int right){
    for(int i=left;i<right;i++)
        if(arr[i] > arr[i+1]){
            cout<<"The first disOrder: array "<<i<<" > "<<"array"<<i+1<<endl;
            return false;
        }
    return true;
}

template <typename T>
void TestOrder(string OrderName,void(*order)(T[],int,int),T arr[],int left,int right){
    clock_t startTime=clock();
    order(arr,left,right);
    clock_t endTime=clock();
    assert(isorder(arr,left,right));
    cout<<OrderName<<":"<<double(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
    return;
}

}

#endif // BST_HELPER_H





