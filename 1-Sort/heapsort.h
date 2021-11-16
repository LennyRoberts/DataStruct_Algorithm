#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

/*
  最大堆：堆中的每个结点的值总是不大于
        其父结点的值所表示的完全二叉树
  用数组表示：数组下标表示值的序号，从“1”开始，
        数组中的值就是结点的值。
           [1]=62
        /         \
   [2]=42         [3]=30
   /    \          /   \
[4]=20 [5]=16  [6]=22 [7]=13
------------------------------------------------------------
insert操作：1）在数组最后插入传入的值；
      2）进行shiftUp操作：1.当前结点值与其父节点值进行比较
         在最大堆中：2.若大于父节点则与父节点交换结点值
       “在最小堆中：2.若小于父节点则与父节点交换结点值”
         重复2直至到父节点大于当前子节点或到堆顶为止

extractMax操作：1）首先将堆顶元素与堆尾元素交换，count--；
    2）进行shiftDown操作：1.比较并取当前两个子节点中大的一个
                （这样才能保证交换后的父节点值大于子节点值）
         2.交换当前结点与较大子节点的值，并更新下标
         3.重复1.2.操作直至到最后一层或当前结点比两个子节点值大
同理可得extracMin操作。
-----------------------------------------------------------------------------------
1)heapSort1, 将所有的元素依次添加到堆中, 在将所有元素从堆中依次取出来, 即完成了排序
2)无论是创建堆的过程, 还是从堆中依次取出元素的过程, 时间复杂度均为O(nlogn)
3)整个堆排序的整体时间复杂度为O(nlogn)
-------------------------------------------------
 构造函数, 通过一个给定数组创建一个最大堆
 该构造堆的过程, 时间复杂度为O(n)
*/

template <typename Iterm>
class MaxHeap{
private:
    Iterm* data;
    int count;      //数据编号
    int capacity;   //数据容量

public:
    MaxHeap(Iterm capacity){
        data=new Iterm[capacity+1];
        this->capacity=capacity;
        count=0;
    }

    MaxHeap(Iterm arr[],int n){
        data=new Iterm[n+1];
        this->capacity=n;

        for(int i=0;i<n;i++)
            data[i+1]=arr[i];
        this->count=n;

        //        for(int j=count/2;j>=1;j--)
        //            shiftDown(j);
    }

    ~MaxHeap(){
        delete [] data;
    }

private:
    bool __isMaxOrder(int k){
        int i=2*k;
        if(i<count && data[i+1]>data[i])
            i++;
        if(data[k]<data[i])
            return false;
        return true;
    }

    bool __isMaxOrder(){
        for(int i=1;i<=count/2;i++)
            if(!__isMaxOrder(i)){
                cout<<"The HeapList:arr["<<i<<"] is disOrder"<<endl;
                return false;
            }else
                return true;
    }

public:
    bool isempty(){
        return count==0;
    }

    int size(){
        return capacity;
    }
    void print(){
        assert(__isMaxOrder());
        for (int i=1;i<=count;i++) {
            cout<<data[i]<<" ";
        }
    }

    Iterm getMax(){
        assert(count>0);
        return data[1];
    }
/*-----------------------------------------------------------------*/
private:
    void ShiftUp(int count){
        //元素向上移动寻找合适位置
        while( count > 1 && data[count/2] < data[count] ){
            swap( data[count/2], data[count] );
            count /= 2;
        }
        return;
        /*错在哪里？
        int temp=count;
        while( temp > 1 && data[temp/2] < data[count] )
            temp /= 2;
        swap( data[count], data[temp] );*/
    }

    void shiftDown(int k){
        //元素向下移动寻找合适位置
        while(2*k<=count){
            int j=2*k;
            //在两个子结点中寻找到较大的那个，注意边界条件
            if(data[j+1]>data[j] && j+1<=count)
                j++;
            if(data[k]>data[j])break;
            swap(data[k],data[j]);
            k=j;
        }
        return;
    }

/*
    1)将当前值保存下来，然后依次比较得到插入位置，多次比较一次移动；
    2)沿当前结点逐层向下遍历[for循环]
    3)在最大堆中：获取到两个子节点的大小，获取到较大的一个与当前节点交换；
    4)若当前节点已经大于了两个子节点中较大的一个，则不用再进行下去；
    5)多次比较后得到合适的插入位置，则将保存的值附给最终位置即可。
*/
    void Adjust(int k,int n){
        Iterm e=data[k];
        for(int i=k*2;i<=n;i*=2){
            if(i<n && data[i+1]>data[i])
                i++;
            if(data[i]<=e)
                break;
            else{
                data[k]=data[i];
                k=i;
            }
        }
        data[k]=e;
        return;
    }

public:
    void insert(Iterm e){
        //插入一个元素
        assert(count+1<=capacity);
        data[count+1]=e;
        count++;
        ShiftUp(count);
    }

    Iterm extractMax(){
        //取出堆顶元素
        assert(count>=1);
        Iterm tract=data[1];
        swap(data[1],data[count]);
        count--;
        shiftDown(1);
        return tract;
    }

/*data[n/2....1];
  也可以是data[1...n/2];上面的isOrder就是这么写的*/
    void Heapify(int n){
        for(int i=n/2;i>0;i--)
            Adjust(i,n);
    }

};

template <typename Iterm>
void heapSort1(Iterm arr[],int n){
    MaxHeap<int> maxheap=MaxHeap<int>(n);
    for(int i=1;i<n;i++)
        maxheap.insert(arr[i]);
    for(int j=1;j<n-1;j++)
        arr[j]=maxheap.extractMax();
    return;
}


/*
 * 思路：将排序数组复制给堆，然后每一次从堆中取出当前
 * 最大(最小)的元素赋值给原排序数组，这样就得到了排好序的数组
*/

template <typename Iterm>
void heapsort2(Iterm arr[],int n){
    MaxHeap<Iterm> maxheap = MaxHeap<Iterm>(arr,n);
    for( int i = n ; i > 0 ; i-- ){
        arr[i] = maxheap.extractMax();
    }
    return;
}


#endif // HEAPSORT_H






