//#pragma once
#ifndef DATA_SORT
#define DATA_SORT

#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <cstring>

namespace Sort {
	//������n��Ԫ�ص�������飬ÿ��Ԫ�ص������ΧΪ[rangL,rangR]
	int* generateRandomArray(int n, int rangL, int rangR) {
		assert(rangL <= rangR);
		int *arr = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; ++i)
			arr[i] = rand() % (rangR - rangL + 1) + rangL;
		return arr;
	}
}

void maopaoSort(int arr[], int n);

#endif