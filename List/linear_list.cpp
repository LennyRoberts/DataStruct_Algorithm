#include "linear_list.h"

using namespace std;
#define List_Init_Size 10
#define List_Increment 2
#define OVER 0
#define ERROR 0
#define TRUE 1
#define OK 1

linear_list::linear_list()
{}
/************************************************************************/
void Create_list(SqList *SL){
    SL->element=(Elem*)malloc(List_Init_Size*sizeof(Elem));
    if(!SL->element)
        exit(OVER);
    SL->length=0;
    SL->listsize=List_Init_Size;
}

int Insert_list(SqList *SL,Elem e,int i){
    if(i<1||i>SL->length+1)return ERROR;
    if(SL->length>SL->listsize){
        int *newbase=(Elem*)realloc(SL->element,
                                    (List_Init_Size+List_Increment)*sizeof (Elem));
        SL->element=newbase;
        SL->listsize+=List_Increment;
    }
    Elem *prior=SL->element+i-1;
    Elem *q=SL->element+(SL->length-1);
    for(;prior>=q;--prior){
        *(prior+1)=*prior;
    }
    *q=e;
    ++SL->length;
    return OK;
}

/************************************************************************/
void play(){
    SqList *SL;
    Create_list(SL);
    for(int i=0;i<10;++i){
         Insert_list(SL,i,1);
         cout<<SL->element<<"   ";
    }

}

int main(){
    play();
    cout<<"hello"<<endl;
    return 0;
}
