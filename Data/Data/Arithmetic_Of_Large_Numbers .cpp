#if 0
#ifndef ARITHMETICOFLARGENUMBERS 
#define ARITHMETICOFLARGENUMBERS 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <math.h>

#pragma warning (disable: 4996)

using namespace std;

#define Max 50											//计算值最大数据长度

/*///////////////////////////////////////////////////////////////////-函数声明区-/////////////////////////////////////////////////////////////////////*/
int Addition(char a[], char b[], int sum[]);
int Subtraction(char a[], char b[], int sub[]);
int Multiplication(char a[], char b[], int mul[]);
void Division(char a[], char b[], int div[]);

long long poow(int a, int b);							//快速幂运算
long long Num_to_Dec(char a[], int B);					//32以下任意进制转十进制
void Dec_to_Num(long long Dec, int B);					//十进制转32以下任意进制


/*///////////////////////////////////////////////////////////////////-代码实现区-/////////////////////////////////////////////////////////////////////*/
/*********************************-Addition-***********************************
1.获取两个字符数组长度strlen()，											  *
2.将字符数组逆序存储到整型数组中,(因为sum的长度足够，故没必要做两个数的转换)  *
3.从低位相加，若有进位则下一位 +1											  *
4.判断当前最高位的后一位是否不为零，若不为零则增加位数计数长度				  *
5.循环求出 和 的有效位数，由高位(后)向低位(前)的第一个不为零的数开始		  *
					被加数 + 加数 = 和										  *
*******************************************************************************/
int Addition(char a[], char b[], int sum[]) {
	int i, j;
	int temp[Max] = { 0 };
	int len_a = (int)strlen(a);
	int len_b = (int)strlen(b);
	int len_s = (len_a > len_b) ? len_a : len_b;

	for (i = 0, j = len_a - 1; j >= 0; ++i, --j)
		sum[i] = a[j] - '0';
	for (i = 0, j = len_b - 1; j >= 0; ++i, --j)
		temp[i] = b[j] - '0';

	for (i = 0; i <= len_s; ++i) {					//(会产生进位，故要进行到当前最高位的后一位))
		sum[i] += temp[i];
		if (sum[i] >= 10) {
			sum[i] -= 10;
			sum[i + 1]++;
		}
	}

	for (i = len_s; sum[i] == 0 && i >= 0; --i);
	len_s = i + 1;

	return len_s;
}

/****************************-Subtraction-***********************************
1. 首先要判断减数和被减数的大小关系；1：位数多的大，2；高位数大的大			*
2. 如果减数小于被减数要交换数据位置和长度，并用sign标记差的符号，			*
3.将字符数组转换为整型数组逆序保存便于计算								    *
4.将减数数组转换到差数组中逆序存储做计算基础								*
5.从低位开始计算，															*
6.在最高位标记符号，并在判断最高位时输出正负号								*
				被减数-减数=差												*
*****************************************************************************/
int Subtraction(char a[], char b[], int sub[]) {
	int len_a = (int)strlen(a);						//被减数的位数
	int len_b = (int)strlen(b);						//减数的位数 
	int len_sub = 0;								//差的位数
	int len_temp = 0;
	int sign = 1;
	int i = 0, j = 0, k = 0;						//标记正负号 
	int tempb[Max] = { 0 };
	char *temp = NULL;

	if (len_a < len_b) {							//如果被减数位数少于减数位数就交换被减数与减数并标记负号 
		sign = -1;
		temp = a;
		a = b;
		b = temp;
		len_temp = len_a;
		len_a = len_b;
		len_b = len_temp;
	}
	else if (len_a == len_b) {						//如果被减数与减数位数相同 
		for (i = 0; i < len_a; ++i) {
			if (a[i] == b[i])	continue;			//相等继续 
			if (a[i] > b[i])	break;				//被减数大于减数结束 
			if (a[i] < b[i]) {						//被减数小于减数则交换位置并标记负号 
				sign = -1;
				temp = a;
				a = b;
				b = temp;
				break;
			}
		}
	}
	len_sub = len_a;

	for (i = 0, j = len_a - 1; j >= 0; --j, ++i)	//将被减数逆序转换成整型存储到差数组中 
		sub[i] = a[j] - '0';
	for (i = 0, j = len_b - 1; j >= 0; --j, ++i)	//将减数逆序转换成整型存储到临时数组中 
		tempb[i] = b[j] - '0';

	for (k = 0; k <= len_sub; ++k) {
		sub[k] -= tempb[k];							//对应位相减保存在差数组中 
		if (sub[k] < 0) {							//如果该位的被减数小于减数，则减出来的一定是一个负数 
			sub[k] += 10;							//则需要，将向前借一位，即 +10 （(a+10)-b=(a-b)+10） 
			sub[k + 1]--;							//被借的高一位要 -1 
		}
	}

	for (i = len_a; sub[i] == 0 && i >= 0; --i);	//当不满足 sub[i]==0&&i>=0，即高位第一位不为零则循环结束
	len_sub = i + 1;								//i被设置成改函数的全局变量，任何该函数的函数或语句结束后都会保存i的值

	if (sign == -1) {								//若存在负号，则将差的最高位的前一位保存负号 
		sub[len_sub] = -1;
		len_sub++;									//负号是要占长度的 
	}

	if (sub[len_sub - 1] == -1) {					//检测 差的最高位的前一位是否是负号
		cout << "-";
		len_sub--;									//将负号提取出来后，要消去负号所占的长度 
	}

	return len_sub;
}

/**********************-Multiplication-**************************
1.获取两个字符数组长度，新的长度为其两个之和					*
2.将两个两个字符数组分别逆序保存在两个临时整型数组中			*
3.从低位开始计算												*
4.将第一次循环乘出来的数组mul判断进位情况						*
5.循环得出积的位数												*
			被乘数 * 乘数 = 积									*
*****************************************************************/
int Multiplication(char a[], char b[], int mul[]) {
	int i, j;
	int len_a, len_b, len_m;
	int temp_a[Max] = { 0 };
	int temp_b[Max] = { 0 };

	len_a = (int)strlen(a);
	len_b = (int)strlen(b);
	len_m = len_a + len_b;

	for (i = 0, j = len_a - 1; j >= 0; ++i, --j)
		temp_a[i] = a[j] - '0';
	for (i = 0, j = len_b - 1; j >= 0; ++i, --j)
		temp_b[i] = b[j] - '0';

	for (i = 0; i <= len_a; ++i)
		for (j = 0; j <= len_b; ++j)
			mul[i + j] += temp_a[i] * temp_b[j];		//每一位循环相乘累加到积的数组中

	for (i = 0; i <= len_m + 1; ++i) {					//乘完后统计进位处理
		if (mul[i] >= 10) {
			mul[i + 1] += mul[i] / 10;
			mul[i] %= 10;
		}
	}

	for (i = len_m + 1; mul[i] == 0 && i >= 0; --i);
	len_m = i + 1;										//统计积的位数 (i被定义为该函数的全局变量)

	return len_m;
}

/****************************-Division********************************


				被除数 / 除数 = 商......余数
**********************************************************************/
void Division(char a[], char b[], int div[]) {
	int lena = (int)strlen(a);						//除数的位数
	int len_b = (int)strlen(b);						//被除数的位数
}

/*----------------------------------------快速幂运算---------------------------------------------*/
long long poow(int a, int b) {
	int ans = 1;
	int base = a;
	while (b != 0) {
		if ((b & 1) != 0)ans *= base;
		base *= base;
		b >>= 1;
	}
	return ans;
}

/*----------------------------------32位下任意进制化十进制-------------------------------------*/
long long Num_to_Dec(char a[], int B) {
	int len, i;
	long long sum = 0, num = 0;
	len = (int)strlen(a);							//strlen在cstring里 
	for (i = 0; i < len; ++i) {
		if (a[i] >= '0'&&a[i] <= '9')
			num = a[i] - '0';
		else if (a[i] >= 'A'&&a[i] <= 'V')
			num = a[i] - 'A' + 10;
		sum = sum * B + num;
	}
	return sum;
}

/*---------------------------------十进制化32位下任意进制-------------------------------------*/
void Dec_to_Num(long long Dec, int B) {
	long long n;
	if (Dec) {
		Dec_to_Num(Dec / B, B);						//运用递归来实现，连输出的倒序问题都解决了
		n = Dec % B;
		if (n < 10)
			printf("%lld", n);
		else
			printf("%lld", n + 55);
	}
}

/*///////////////////////////////////////////////////////////////////-代码实现区-/////////////////////////////////////////////////////////////////////*/


void Handle_1() {
	int i = 0, j = 0, len = 0;
	int c[Max * 2 + 10] = { 0 };
	char a[Max];
	char b[Max];
	scanf("%s", &a);
	scanf("%s", &b);
	len = Multiplication(a, b, c);

	for (i = len - 1; i >= 0; --i)
		cout << c[i];
	cout << endl;
	cout << "Data length is:" << len << endl;
}

void Handle_2() {}


/*--------------------------MAIN--------------------------------------*/
int main() {
	clock_t start, finish;
	start = clock();
	Handle_1();
	finish = clock();
	cout << "Run_Time:" << finish - start << "ms" << endl;
	system("pause");
	return 0;
}
/*--------------------------MAIN--------------------------------------*/
#endif
#endif