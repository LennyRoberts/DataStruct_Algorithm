#ifndef BASICSORT_H
#define BASICSORT_H
#include <iostream>
#include <string>
#include <algorithm>

/****************************-SelectionSort-**************************************
1)选择排序要每次都必须遍历完所有的元素；而插入排序可以在不满足条件的情况下提前终止
2)插入排序比选择排序运行时间长的原因是利用swap交换含有多次赋值操作；
3)改进的插入算法是利用减少赋值的思想，即采用多次比较、一次赋值的操作来减少运行时间.
***********************************************************************************/
template<typename T>
void SelectSort(T arr[],int n){
    //遍历所有的元素
    for(int i=0;i<n;i++){
        //在遍历中找到最小的元素并用索引MinIndex保存，MinIndex首先指向第一个元素
        int MinIndex=i;
        for(int j=i+1;j<n;j++)
            if(arr[MinIndex]>arr[j])
                MinIndex=j;
        //在找到第一个最小的元素后，把它与第一个元素交换，放到第一个位置上去
        swap(arr[MinIndex],arr[i]);
    }
    return;
}

/*
 * 改进思路:在每一轮中, 可以同时找到当前未处理元素的最大值和最小值。
首先要保证每次两端的元素是有序的，然后设置Min和Max索引指向该区域
的最大和最小值部分然后交换，然后两端向中间靠拢，形成夹逼的形式*/

template<typename T>
void OptimizedSelectSort(T arr[],int n){
    int left=0,right=n-1;

    while(left < right){
        int MinIndex = left;
        int MaxIndex = right;

        if(arr[left]>arr[right])
            swap(arr[left],arr[right]);

        for(int i= left+1;i < right; ++i){
            if(arr[i] < arr[MinIndex])
                MinIndex=i;
            else if(arr[i] > arr[MaxIndex])
                MaxIndex=i;
        }
        swap(arr[MinIndex],arr[left]);
        swap(arr[MaxIndex],arr[right]);
        left++;
        right--;
    }
    return;
}

/***********************************-InsertSort-****************************************/
/*每次将一个待排序的记录按其关键字大小插入到前面已经排好的子序列中，直到全部记录插入完成。
 * 直接插入排序和希尔排序是插入排序思想的排序方式*/
template<typename T>
void InsertSort(T arr[],int n){
    //遍历所有的元素
    for(int i=1;i<n;i++){
        //寻找元素arr[i]适合的插入位置
        for(int j=i;j>0 && arr[j]<arr[j-1];j--)
            swap(arr[j],arr[j-1]);
    }
    return;
}

/*
改进思路:将当前i所指向的值e保存下来，每次判断成立后直接向后赋值覆盖，然后再j记录
下来的位置再把i位置保存的值e赋到该位置上，这样就减少交换的操作即多次比较，一次赋值
*/
template<typename T>
void InsertSortAdvance(T arr[],int n){
    //遍历所有的元素
    for(int i=1;i<n;i++){
        T e=arr[i];         //将当前位置的元素记录下来，之后写覆盖
        int j;              //j保存元素e应该插入的位置
        for(j=i;j>0 && arr[j-1]>e;j--)
            arr[j]=arr[j-1];	//写覆盖
        arr[j]=e;			//将之前保存的数据位置放到遍历的位置，重新遍历
    }
    return;
}

template<typename T>
void BinaryInsertion(T arr[],int n){
    int left,right,mid,i,j;
    for(i=1;i<n;i++){
        left=0;
        right=i-1;
        T e=arr[i];
        while(left<=right){
            mid=left+(right-left)/2;
            if(e < arr[mid])
                right=mid-1;
            else
                left=mid+1;
        }
        for(j=i-1;j>right;j--)
            arr[j+1]=arr[j];
        arr[j+1]=e;
    }
//    int low,high,m,temp,i,j;
//    for(i = 1;i<n;i++){
//        //折半查找应该插入的位置
//        low = 0;
//        high = i-1;
//        while(low <= high){
//            m = (low+high)/2;
//            if(arr[m] > arr[i])
//                high = m - 1;
//            else
//                low = m + 1;
//        }
//        //统一移动元素，然后将这个元素插入到正确的位置
//        temp = arr[i];
//        for(j=i;j>high+1;j--){
//            arr[j] = arr[j-1];
//        }
//        arr[high+1] = temp;
//    }

    return;
}

template<typename T>
void ShellSort(T arr[], int n){
    // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    while( h < n/3 )
        h = 3 * h + 1;
    while( h >= 1 ){
        // h-sort the array
        for( int i = h ; i < n ; i ++ ){
            // 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
            T e = arr[i];
            int j;
            for( j = i ; j >= h && e < arr[j-h] ; j -= h )
                arr[j] = arr[j-h];
            arr[j] = e;
        }
        h /= 3;
    }
}

/*---------------------ExchangeSort-BubbleSort--------------------------*/
template<typename T>
void BubbleSort(T arr[],int n){
    bool tag;
    do{
        tag=false;
        for(int i=1;i<n;++i)
            if(arr[i] < arr[i-1]){
                swap(arr[i] , arr[i-1]);
                tag=true;
            }
    }while(tag);
    return;
}

/*改进思路：
    对于正序Bubble Sort，在每一次最后一个位置得到最大值(或最小值)之后，
下一次的遍历就不再需要遍历这个位置及其以后的位置的元素，所以每一次的
遍历次数减一，为n-1次、n-2次.....2次、1次
*/
template<typename T>
void OptimizedBubbleSort(T arr[],int n){
    int newtag;
    do{
        newtag=0;
        for(int i = 1;i < n; ++i)
            if(arr[i] < arr[i-1]){
                swap(arr[i],arr[i-1]);
                newtag=i;
            }
        n=newtag;
    }while(newtag!=0);
    return;
}

#endif // BASICSORT_H



















