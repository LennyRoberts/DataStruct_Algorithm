#if 1
#pragma warning (disable: 4996)

#include "LinkList.h"

using namespace std;

/*------------------------------------Function definition------------------------------------*/
void Creat_Link(LinkList* LINK) {//要使用二级指针来改变实参函数内存
	*LINK = (LinkList)malloc(sizeof(struct LNode));
	if (!LINK) exit(FALSE);
	(*LINK)->Next = NULL;
	(*LINK)->Data = 0;
}

void Grow_Link(LinkList* LINK, Elem e) {
	LinkList tempL = (LinkList)malloc(sizeof(struct LNode));
	if (!tempL)	exit(OVER);
	(*LINK)->Data = e;
	tempL->Next = *LINK;
	(*LINK) = tempL;
}

int Length_Link(LinkList LINK) {
	int length = 0;
	LinkList p = LINK->Next;
	while (p) {
		length++;
		p = p->Next;
	}
	return length;
}

int Insert_Link(LinkList* LINK, int i, Elem e) {
	int length = Length_Link(*LINK);
	int research = 0;
	if (i<1 || i>length-1)	return OVER;
	LinkList temp_L = (*LINK)->Next;
	while (temp_L && research < i-1) {
		temp_L = temp_L->Next;
	}
	LinkList temp_p = (LinkList)malloc(sizeof(struct LNode));
	if (!temp_p) return OVER;
	temp_p->Data = e;
	temp_p->Next = temp_L->Next;
	temp_L->Next = temp_p;
	length++;
	return OK;
}



/*-----Function call---------------------*/
void play() {
	LinkList LINK=NULL;
	Creat_Link(&LINK);
	for (int i = 0; i < 5; ++i)
		Grow_Link(&LINK,i);
	for (int j = 0; j < 5; ++j)
		Insert_Link(&LINK,1,j);
	LinkList p = LINK->Next;
	while (p) {
		cout << p->Data << endl;
		p = p->Next;
	}
}

/*-----------------------MAIN--------------------------*/
int main() {
	clock_t start, finish;
	start = clock();
	play();
	//play2();
	finish = clock();
	cout << "Run_Time:" << finish - start << "ms" << endl;
	system("pause");
	return 0;
}
#endif