#ifndef ADVANCESORT_H
#define ADVANCESORT_H
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <string>

/*---------------------------------MergeSort----------------------------------------------*/
// 将arr[l...mid]和arr[mid+1...r]两部分进行归并;（这个函数很重要）
template<typename T>
void __Merge(T arr[],int left,int mid,int right){
    T *aux=new T[right-left+1];
    for(int i = left;i <= right;i++)     //表示将一个数组拷贝一份供判断使用
        aux[i-left]=arr[i];
    int i=left;
    int j=mid+1;
    for(int k=left;k<=right;++k){
        if(i>mid){                      //表示当左边的数据处理完成后直接把右边的值赋给arr
            arr[k] = aux[j-left];
            j++;
        }else if(j>right) {             //表示当右边的数据处理完成后直接把左边边的值赋给arr
            arr[k] = aux[i-left];
            i++;
        }else if(aux[i-left]<aux[j-left]){//取左半部分和右半部分中小的值赋给当前的arr
            arr[k]=aux[i-left];
            i++;
        }else{
            arr[k]=aux[j-left];
            j++;
        }
    }
    delete [] aux;
    return;
}

template<typename T>
void __MergeSort2WayOfRecursion(T arr[],int left,int right){
    if(left >= right)
        return;
    int mid=(right - left)/2+left;
    //这里的递归调用会在每一层形成三叉树的形式，但每一层只有两边的结点才有子结点
    __MergeSort2WayOfRecursion(arr,left,mid);
    __MergeSort2WayOfRecursion(arr,mid+1,right);
    __Merge(arr,left,mid,right);
    return;
}

template<typename T>
void MergeSort1(T arr[],int n){
    __MergeSort2WayOfRecursion(arr,0,n-1);
    return;
}

/*------------------------MergeSort的优化-----------------------------------
 优化思路一：对于小于一定数据量的阈值，可以用插入排序
 优化思路二：在正序排序中，对于左半部分已经小于右半部分的不再调用__Merge();
----------------------------------------------------------------------------*/
template<typename T>
void __InsertionSortOfMerge(T arr[],int left,int right){
        //遍历所有的元素
        for(int i=left+1;i<=right;i++){
            T e=arr[i];         //将当前位置的元素记录下来
            int j;              //j保存元素e应该插入的位置
            for(j=i;j>0 && arr[j-1]>e;j--)
                arr[j]=arr[j-1];
            arr[j]=e;
        }
        return;
}


template<typename T>
void __MergeSort2WayOptimizied(T arr[],int left,int right){
//    if(right <= 30){      //在数据量小于一定阈值的时候来调用插入排序算法
//        __InsertionSortOfMerge(arr,left,right);
//        return;
//    }
    if(left >= right)
        return;
    int mid=(right-left)/2+left;
    __MergeSort2WayOptimizied(arr,left,mid);
    __MergeSort2WayOptimizied(arr,mid+1,right);
    /*在排正序时，对于左半部分已经小于右半部分不调用重新排序；这对于
     近乎有序的数组非常有效，但在一般情况下会有一定的性能损失，（有失健壮性）*/
    if(arr[mid] > arr[mid+1])
        __Merge(arr,left,mid,right);
    return;
}

template<typename T>
void MergeSort2(T arr[],int n){
    __MergeSort2WayOptimizied(arr,0,n-1);
    return;
}

/*-----------------------------------MergeSortBottomUp------------------------------------------*/
/****************************************************************************************
    1）Merge Sort BU 也是一个O(nlogn)复杂度的算法，虽然使用两重for循环
        但Merge Sort BU也可以在1秒之内轻松处理100万数量级的数据
    2）注意：不要轻易根据循环层数来判断算法的复杂度，Merge Sort BU就是一个反例
        关于这部分陷阱，推荐看《玩转算法面试》课程，第二章：《面试中的复杂度分析》
    3）该算法没有使用到数组索引来直接获取元素的特性，所以可以更好地使用O(nlogn)
        的时间复杂度对链表等这样的数据结构进行排序
    4）思考：构造一个链表，用该算法进行排序
***********************************************************************************
1）比较MergeSort和MergeSortBottomUp两种排序算法的性能效率整体而言, 
     两种算法的效率是差不多的。但是如果进行仔细测试, 自底向上的归并排序会略胜一筹。
3）思考？（有递归的归并排序相比自底向上的实现多了函数压栈和出栈的操作，怎么才能更快呢？）
*****************************************************************************************/
int min(int x,int y){
    return x<y?x:y;
}
// 使用自底向上的归并排序算法
template<typename T>
void __MergeSort2WayOfBottomUp(T arr[],int right){
    for (int size=1;size<right+1;size+=size) {
        for(int i=0; i<=right-size; i+=size+size)
            if(arr[i+size-1] > arr[i+size])
                __Merge(arr,i,i+size-1,min(i+size+size-1,right));
    }
    return;
    /*--------------------------------------------------------------------------------------------------
        1)外层循环是要确定每次的增量的大小,即确定每次要划分多少元素为每两组进行__Merge
        （注意：这里传的是最后一个的数组下标进来，而这里的Size是判断元素的个数，故要+1
        2）内层循环是确定每次每次按照Size的大小来往后推，
           将整个数组分成Size大小的每两部分进行Merge的部分（注意：这里的i要取到最后一个元素
        3）边界问题：1）i+size-1>right,令i<=right-size；mid指向最后剩余<=size的部分，
           right'=i+size+size-1中刚好弥补；注意：当在传入下标时，要使i能够取到最后一个元素
           2）i+size+size-1>right,取i+size+size-1>right和right-1的最小值解决
        4）对于arr[mid] <= arr[mid+1]的情况,不进行merge
        5）由(i+size+size-1)-(i+size-1)!=(i+size-1)-i =>在每次分组的左半部分和右半部分元素个数都不一定相同
    -----------------------------------------------------------------------------------------------------*/
}

template<typename T>
void MergeSort3(T arr[],int n){
    __MergeSort2WayOfBottomUp(arr,n-1);
    return;
}


/*****************************************---QuickSort---*******************************/
template<typename T>
int __Partition(T arr[],int left,int right){
    swap(arr[left],arr[rand()%(right-left+1)+left]);
    T e=arr[left];
    int j=left;
    for (int i=j+1;i<=right;i++)
       if(arr[i] < e)
           swap(arr[++j],arr[i]);
    swap(arr[j],arr[left]);
    return j;
    /*------------------------------------------------------------------
     1）for循环：进行arr[left+1...j]<e和arr[j+1...i)>e的划分；
     2）索引i是对数组自左向右进行一次遍历，在遍历时考察每一个元素与键值e的大小；
        索引j处于左半部分最后一个满足条件的位置(从left+1到j内是小于键值的部分)，
        类似BubbleSort，当索引i指向的元素<or<=键值时就交换i，j的值，并将索引指向下一位置。
        -------------------------------------------
         left          j->         i->       right
         | e |<e |<e |<e |>e |>e |>e |   |   |   |
           0   1   2   3   4   5   6   7   8   9
        -------------------------------------------
     3）当对于近乎有序的数组，还选用第一个元素作为分界值时，在最坏的
        情况下会被分成只有右半部分（或左半部分），算法退化为O(n^2)级别；
     4）改进思路：用随机种子在数组中随机挑选一个元素作为分界值e；
        这对于近乎有序的数组的效果是十分明显的,退化为O(n^2)级别的概率极低。
     -------------------------------------------------------------------*/
}
template<typename T>
void __QuickSort(T arr[],int left,int right){
    if(left>=right)
        return;
    srand(time_t(nullptr));
    int p=__Partition(arr,left,right);
    __QuickSort(arr,left,p-1);
    __QuickSort(arr,p+1,right);
}

template<typename T>
void QuickSort(T arr[],int n){
    __QuickSort(arr,0,n-1);
    return;
}

/*-----------------------------------------------------------------------------*/
template<typename T>
int __Partition2(T arr[],int left,int right){
    swap(arr[left],arr[rand()%(right-left+1)+left]);
    T e=arr[left];
    int i=left+1;
    int j=right;
    // arr[l+1...i) <= v; arr(j...r] >= v
    while(true){
    // 注意这里的边界, arr[i] < e, 不能是arr[i] <= e,这是为什么？
        while(arr[i]<e && i<=right)i++;
    // 注意这里的边界, arr[j] > e, 不能是arr[j] >= e,这是为什么？
        while(arr[j]>e && j>=left+1)j--;
        if(i>j)
            break;
        swap(arr[i],arr[j]);
        i++;j--;
    }
    swap(arr[left],arr[j]);
    return j;
    /*-----------------------------------------------------------------
    1)随机种子选取一个数组中一个点作为键值，
    2)设置两个索引i和j分别从左端和右端开始向中间扫描
    3)当出现>=键值OR<=键值时交换两个元素的位置，并让索引指向下一个位置
     ------------------------------------------------------------------*/
    /*-------------------------------------------------------------------
    比如数组 1,0,0, ..., 0, 0
    a. 对于arr[i]<v和arr[j]>v的方式，
       第一次partition得到的分点是数组中间；
    b. 对于arr[i]<=v和arr[j]>=v的方式，
       第一次partition得到的分点是数组的倒数第二个。
    这是因为对于连续出现相等的情况，a方式会交换i和j的值；
    而b方式则会将连续出现的这些值归为其中一方，使得两棵子树不平衡
     ----------------------------------------------------------------*/
    /*----------------------------------------
    这是一段错误的代码：错误之处在于
    while(i<=j){
        while(arr[i]<e && i<=right)i++;
        while(arr[j]>e && j>=left+1)j--;
        swap(arr[i],arr[j]);
        i++;j--;
    }
    swap(arr[left],arr[j]);
     ---------------------------------------*/
}

template<typename T>
void __QuickSort2(T arr[],int left,int right){
    if(left>=right)
        return;
    srand(time_t(nullptr));
    int p=__Partition2(arr,left,right);
    __QuickSort2(arr,left,p-1);
    __QuickSort2(arr,p+1,right);
    return;
}

template<typename T>
void QuickSort2(T arr[],int n){
    __QuickSort(arr,0,n-1);
    return;
}

/*------------------------------------QuickSort3Ways------------------------------------------*/
template<typename T>
void insertionSort2(T arr[],int left,int right){
    //遍历所有的元素
    for(int i=left+1;i<=right;i++){
        T e=arr[i];         //将当前位置的元素记录下来
        int j;              //j保存元素e应该插入的位置
        for(j=i;j>0 && arr[j-1]>e;j--)
            arr[j]=arr[j-1];
        arr[j]=e;
    }
    return;
}

template<typename T>
void __QuickSort3Ways(T arr[],int left,int right){
    if( right - left <= 15 ){
        insertionSort2(arr,left,right);
        return;
    }
    swap(arr[left],arr[rand()%(right-left+1)+left]);
    T e=arr[left];
    int lt=left;        //arr[left+1...lt]<e
    int gt=right+1;     //arr[lt+1...i)=e
    int i=left+1;       //arr[gt...right]>e
    while(i<gt){
        if(arr[i]<e){
            swap(arr[lt+1],arr[i]);
            lt++;i++;
        }else if(arr[i]>e){
            swap(arr[gt-1],arr[i]);
            gt--;
        }else{
            i++;
        }
    }
    swap(arr[lt],arr[left]);
    lt--;

    __QuickSort3Ways(arr,left,lt);
    __QuickSort3Ways(arr,gt,right);
    return;
    /*------------------------------------------------------------------------------------------
    1)int gt=right+1;在所有元素都等于键值或者元素中没有大于键值的元素时，i可以取到最右端，
      但只能在这里使gt=right+1，而不能使用while(i<=gt) OR while(i<gt+1),因为gt的值是在变化的。
    2）这里使用在元素个数少于16个时调用插入排序(InsertionSort)并返回空作为递归调用的出口。
    --------------------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------------------
    三路快速排序对于存在大量重复键值的数组有明显的优势：
    a.将数组化为:<键值；=键值；>键值 三个部分;
    b.用索引lt维护<键值部分，起始位置指向起始位置left；
    c.用索引gt维护>键值部分，起始位置指向末端位置right；
    d.索引i指向当前正在考察的元素，起始位置指向left+1；
    e.考察当前i的元素，依据与键值的大于小于或等于关系分别到相应部分；
    f.看上去lt和gt是由两端向中间扫描，由i<gt,则gt和lt不会发生索引越界；
    g.完成一次排序后，只需对小于键值的部分和大于键值的部分递归，这里用insertionSort作为递归出口
    --------------------------------------------------------------------------------------------*/
}

template<typename T>
void QuickSort3Ways(T arr[],int n){
    srand(time_t(nullptr));
    __QuickSort3Ways(arr,0,n-1);
}

#endif // ADVANCESORT_H
