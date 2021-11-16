#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include "iostream"
#include <algorithm>
#include <ctime>
#include <cassert>
#include <stdlib.h>

typedef int Elem;
typedef int status;

class linear_list
{
public:
    linear_list();
};
/*---------------------------------*/
typedef struct{
    status *element;    //the structural base address
    int listsize;   //note the listsize of list_space
    int length;     //note the data number
}SqList;

/***********************************************************/
void play();
void Create_list(SqList *SL);
int Insert_list(SqList *SL,Elem e,int i);


/***********************************************************/
namespace Test_Sort{
int* generateRandomArray(int n,int range_L,int range_R){
    assert(range_L<=range_R);
    int *arr=new int[n];
    srand(time(NULL));
    for(int i=0;i<n;++i){
        arr[i]=rand()%(range_R-range_L+1)+range_L;
    }
    return arr;
}
}


#endif // LINEAR_LIST_H
