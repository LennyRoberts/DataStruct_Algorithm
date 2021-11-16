#ifndef __LINKLIST__
#define __LINKLIST__

#include "iostream"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

#define TURE 1
#define FALSE 0
#define OK 1
#define OVER 0

typedef int status;
typedef int Elem;

/*-------------------Struct&&Class---------------------*/
typedef struct LNode {
	Elem Data;
	struct LNode *Next;
}LNode,*LinkList;

/*-------------------Function declaration---------------------*/
void Creat_Link(LinkList* LINK);
void Grow_Link(LinkList* LINK, Elem e);
int Length_Link(LinkList LINK);
int Insert_Link(LinkList* LINK,int i,Elem e);

#endif
