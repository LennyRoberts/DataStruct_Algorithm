#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

//二分查找
template <typename T>
int __BinarySearch(T arr[],T tract,int left,int right){
    int mid=0;
    while(mid>0){
        mid=(right-left)/2+left;
        if(arr[mid]==tract)
            return mid;
        if(arr[mid] < tract)
            left=mid+1;
        if(arr[mid] > tract)
            right=mid;
    }
    return -1;
}
//二分查找的递归实现
template <typename T>
int __BinarySearchRecursion(T arr[],T tract,int left,int right){
    if(left>right)
        return -1;
    int mid=(right-left)/2+left;
    if(arr[mid]==tract)
        return mid;
    if(arr[mid] > tract)
        return BinarySearchRecursion(arr,tract,left,mid-1);
    if(arr[mid] < tract)
        return BinarySearchRecursion(arr,tract,mid+1,right);
}

template <typename T>
void BinarySearch(string BinarySearchName,T arr[],T tract,int n){
    if(BinarySearchName == "BSR")
        __BinarySearchRecursion(arr,tract,0,n-1);
    else
        __BinarySearch(arr,tract,0,n-1);
}

#endif // BINARY_SEARCH_H




