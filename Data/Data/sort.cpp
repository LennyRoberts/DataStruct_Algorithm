#if 0
#include "sort.h"


using namespace std;

void Selection_Sort() {
	int i, j, n = 10;
	int arr[] = { 1,2,3,5,4,7,6,8,9,19 };
	for (i = 0; i < n-1; i++) {
		int index = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] > arr[index])index = j;
			if (index != i) {
				int temp = arr[i];
				arr[i] = arr[index];
				arr[index] = temp;
			}
		}
	}
	for (int m = 0; m < 10; m++) {
		cout << arr[m] << "  ";
	}
	cout << endl;
}

/**********************************************************************************/

int main() {
	int n = 10;
	//int *arr = Sort::generateRandomArray(n, 0, n);
	//int arr[] = { 1,2,3,5,4,7,6,8,9,19 };
	Selection_Sort();


	//delete[] arr;
	system("pause");
	return 0;
}
#endif