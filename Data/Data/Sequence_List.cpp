#if 0
#pragma warning (disable: 4996)
#include "Sequence_List.h"

#define LIST_INIT_SIZE 10
#define LISTINCREASE 2

#define TRUE 1
#define OK 1
#define ERROR 0
#define OVER 0

using namespace std;

/*------------------------------------Function definition------------------------------------*/
void Create_List(SqList *LIST) {
	LIST->element = (Elem*)malloc(LIST_INIT_SIZE * sizeof(Elem));
	if (!LIST->element)
		exit(OVER);
	LIST->length = 0;
	LIST->listsize = LIST_INIT_SIZE;
}

bool List_Empty(SqList *LIST) {
	if (LIST->length == 0)return true;
	else
		return false;
}

int List_Length(SqList *LIST) {
	return LIST->length;
}

Elem GetElem(SqList *LIST, int i) {
	if (i<1 || i>LIST->length + 1)
		return ERROR;
	else
		return *(LIST->element + i - 1);
}

void Clear_List(SqList *LIST) {
	memset(LIST->element, 0, sizeof(LIST->length));
	LIST->length = 0;
}

void Destroy_List(SqList *LIST) {
	free(LIST->element);
	LIST->element = NULL;
	LIST->length = 0;
	LIST->listsize = 0;
}

bool compare_Char(Elem e1, Elem e2) {
	if (e1 == e2)return true;
	else
		return false;
}

Elem Locate_Elem(SqList *LIST, Elem e) {
	Elem *Prior_Point = LIST->element;
	int i = 0;
	while (i++ <= LIST->length && !compare_Char(*Prior_Point++, e));
	if (i <= LIST->length)
		return i;
	else
		return 0;
}

int Insert_List(SqList *LIST, Elem e, int i) {
	if (i<1 || i>LIST->length + 1)return ERROR;
	if (LIST->length >= LIST->listsize) {
		Elem *NewBase = (Elem*)realloc(LIST->element,
			(LIST->listsize + LISTINCREASE) * sizeof(Elem));
		if (!NewBase)exit(OVER);
		LIST->element = NewBase;
		LIST->listsize += LISTINCREASE;
	}
	//Elem *Later_Point = LIST->element+(LIST->length-1);
	//Elem *Prior_Point = LIST->element + i - 1;
	Elem *Later_Point = &(*LIST).element[LIST->length - 1];
	Elem *Prior_Point = &(*LIST).element[i - 1];
	for (Later_Point; Later_Point >= Prior_Point; --Later_Point) {
		*(Later_Point + 1) = *Later_Point;
	}
	*Prior_Point = e;
	//cout << (*LIST).element[i-1]<<endl;
	++LIST->length;

	return OK;
}

int Delete_List(SqList *LIST, int i) {
	if (i<1 || i>LIST->length + 1)return ERROR;
	Elem *Prior_Point = LIST->element + i - 1;
	Elem *Later_Point = LIST->element + LIST->length - 1;
	for (Prior_Point; Prior_Point < Later_Point; Prior_Point++) {
		*(Prior_Point) = *(Prior_Point + 1);
	}
	LIST->length--;
	return OK;
}

bool Visit(Elem e1, Elem e2) {
	if (e1 == e2)
		return true;
	else
		return false;
}

int Traverse_List(SqList *LIST, bool(*p)(Elem, Elem)) {
	Elem *Prior_Point = LIST->element;
	Elem *Later_Point = LIST->element + LIST->length - 1;
	int i = 1;
	while (Prior_Point <= Later_Point) {
		//此处的Visit()我用来判断LIST->element+k(k从0开始)与其后继元素的关系
		if ((*p)(*Prior_Point, *(Prior_Point + 1)))return i;
		Prior_Point++;
		i++;
	}
	return ERROR;
}

Elem* generateRandomArray(int n, int rangL, int rangR) {
	assert(rangL <= rangR);
	int *arr = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; ++i)
		arr[i] = rand() % (rangR - rangL + 1) + rangL;
	return arr;
}

//选择排序有问题？？？
void Sort_List(SqList *LIST) {
	Elem *Prior_Point;
	Elem *Later_Point;
	for (Prior_Point = LIST->element; Prior_Point < (LIST->element + LIST->length - 1); Prior_Point++) {
		Elem *Temp_Point = Prior_Point;
		for (Later_Point = Prior_Point + 1; Later_Point < (LIST->element + LIST->length - 1); Later_Point++) {
			if (*Prior_Point > *Later_Point)
				Temp_Point = Later_Point;
		}
		if (Temp_Point != Prior_Point) {
			Elem temp = *Temp_Point;
			*Temp_Point = *Prior_Point;
			*Prior_Point = temp;
		}
	}
}

/*------------------------------------Function definition------------------------------------*/
/*-------------------Function call---------------------*/
void Handle_1() {
	SqList SL;
	Create_List(&SL);
	Elem *arr = generateRandomArray(10, 0, 10);
	for (int i = 0; i < 10; i++) {
		Insert_List(&SL, arr[i], 1);
		//cout << SL.element[i] << "  ";//放在这里有什么问题？
		//注意Elem *Prior_Point = &(*LIST).element[i - 1];的插入的位置和此处的访问位置。
	}
	//Insert_List(&SL,1, 9);
	//Delete_List(&SL, 4);
	Sort_List(&SL);
	for (int j = 0; j < SL.length; j++) {
		cout << SL.element[j] << "\t";
	}
	//cout << "i="<<Traverse_List(&SL, Visit) << endl;

}

/*-------------------Function call---------------------*/
int main() {
	clock_t start, finish;
	start = clock();
	Handle_1();
	finish = clock();
	cout << endl << endl;
	cout << "Run_Time:" << finish - start << "ms" << endl << endl;
	system("pause");
	return 0;
}
#endif