#ifndef __SEQUENCE_LIST__
#define __SEQUENCE_LIST__

#include "iostream"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Max 100

typedef int Status;
typedef int Elem;

typedef struct {
	Status *element;    //the structural base address
	int listsize;   //note the listsize of list_space
	int length;     //note the data number
}SqList;
/*------------------------Function declaration----------------------*/
void Create_List(SqList *LIST);
int Insert_List(SqList *LIST, Elem e,int i);
void Clear_List(SqList *LIST);
void Destroy_List(SqList *LIST);
bool List_Empty(SqList *LIST);
int List_Length(SqList *LIST);
Elem GetElem(SqList *LIST, int i);
Elem Locate_Elem(SqList *LIST, Elem e);
int Traverse_List(SqList *LIST, bool(*p)(Elem, Elem));

Elem* generateRandomArray(int n, int rangL, int rangR);		//随机数发生器
bool compare_Char(Elem e1, Elem e2);
bool Visit(Elem e1, Elem e2);


#endif
