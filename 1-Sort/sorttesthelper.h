#ifndef SORTTESTHELPER_H
#define SORTTESTHELPER_H
#include <iostream>
#include <assert.h>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;
namespace SortTestHelper {
/*生成有n个元素的随机数组，每个元素的随机分为[rangL，rangR]*/
int* GenerateRandomArray(int n,int rangL,int rangR){
    assert(rangL<=rangR);
    int *arr = new int[n];
    srand(time_t(nullptr));
    for(int i=0;i<n;i++)
        arr[i]=rand()%(rangR-rangL+1)+rangL;
    return arr;
}

/*先生成一个有序数组，然后再从该数组中用随机种子挑选出若干个进行交换*/
int* GenerateNearlyOrderedArray(int n,int swapTimes){
    int* arr=new int[n];
    for(int i=0;i<n;i++)
        arr[i]=i;
    srand(time_t(nullptr));
    for(int i=0;i<swapTimes;i++){
        int posx=rand()%n;
        int posy=rand()%n;
        swap(arr[posx],arr[posy]);
    }
    return arr;
}

/*逐个输出数组*/
template <typename T>
void PrinterArray(T arr,int n){
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

/*检查排序后的数组是否正确和完整*/
template <typename T>
bool isSort(T arr[],int n){
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1])
            return false;
    }
    return true;
}

/*测试排序算法*/
template <typename T>
void TestSort(string sortName,void(*sort)(T[],int),T arr[],int n){
    clock_t stratTime=clock();
    sort(arr,n);
    clock_t endTime=clock();
    assert(isSort(arr,n));
    cout<<sortName<<" cost time: "<<double(endTime-stratTime)/CLOCKS_PER_SEC<<"s"<<endl;
    return;
}

/*测试排序算法并逐个输出*/
template <typename T>
void TestAndPrintSort(string sortName,void(*sort)(T[],int),T arr[],int n){
    clock_t stratTime=clock();
    sort(arr,n);
    clock_t endTime=clock();
    assert(isSort(arr,n));
    cout<<sortName<<" cost time: "<<double(endTime-stratTime)/CLOCKS_PER_SEC<<"s"<<endl;
    PrinterArray(arr,n);
    return;
}

/*复制一个数组*/
int* CopyIntArray(int a[],int n){
    int* arr=new int[n];
    copy(a,a+n,arr);
    return arr;
}
}
#endif // SORTTESTHELPER_H
