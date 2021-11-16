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

#define Max 50											//����ֵ������ݳ���

/*///////////////////////////////////////////////////////////////////-����������-/////////////////////////////////////////////////////////////////////*/
int Addition(char a[], char b[], int sum[]);
int Subtraction(char a[], char b[], int sub[]);
int Multiplication(char a[], char b[], int mul[]);
void Division(char a[], char b[], int div[]);

long long poow(int a, int b);							//����������
long long Num_to_Dec(char a[], int B);					//32�����������תʮ����
void Dec_to_Num(long long Dec, int B);					//ʮ����ת32�����������


/*///////////////////////////////////////////////////////////////////-����ʵ����-/////////////////////////////////////////////////////////////////////*/
/*********************************-Addition-***********************************
1.��ȡ�����ַ����鳤��strlen()��											  *
2.���ַ���������洢������������,(��Ϊsum�ĳ����㹻����û��Ҫ����������ת��)  *
3.�ӵ�λ��ӣ����н�λ����һλ +1											  *
4.�жϵ�ǰ���λ�ĺ�һλ�Ƿ�Ϊ�㣬����Ϊ��������λ����������				  *
5.ѭ����� �� ����Чλ�����ɸ�λ(��)���λ(ǰ)�ĵ�һ����Ϊ�������ʼ		  *
					������ + ���� = ��										  *
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

	for (i = 0; i <= len_s; ++i) {					//(�������λ����Ҫ���е���ǰ���λ�ĺ�һλ))
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
1. ����Ҫ�жϼ����ͱ������Ĵ�С��ϵ��1��λ����Ĵ�2����λ����Ĵ�			*
2. �������С�ڱ�����Ҫ��������λ�úͳ��ȣ�����sign��ǲ�ķ��ţ�			*
3.���ַ�����ת��Ϊ�����������򱣴���ڼ���								    *
4.����������ת����������������洢���������								*
5.�ӵ�λ��ʼ���㣬															*
6.�����λ��Ƿ��ţ������ж����λʱ���������								*
				������-����=��												*
*****************************************************************************/
int Subtraction(char a[], char b[], int sub[]) {
	int len_a = (int)strlen(a);						//��������λ��
	int len_b = (int)strlen(b);						//������λ�� 
	int len_sub = 0;								//���λ��
	int len_temp = 0;
	int sign = 1;
	int i = 0, j = 0, k = 0;						//��������� 
	int tempb[Max] = { 0 };
	char *temp = NULL;

	if (len_a < len_b) {							//���������λ�����ڼ���λ���ͽ������������������Ǹ��� 
		sign = -1;
		temp = a;
		a = b;
		b = temp;
		len_temp = len_a;
		len_a = len_b;
		len_b = len_temp;
	}
	else if (len_a == len_b) {						//��������������λ����ͬ 
		for (i = 0; i < len_a; ++i) {
			if (a[i] == b[i])	continue;			//��ȼ��� 
			if (a[i] > b[i])	break;				//���������ڼ������� 
			if (a[i] < b[i]) {						//������С�ڼ����򽻻�λ�ò���Ǹ��� 
				sign = -1;
				temp = a;
				a = b;
				b = temp;
				break;
			}
		}
	}
	len_sub = len_a;

	for (i = 0, j = len_a - 1; j >= 0; --j, ++i)	//������������ת�������ʹ洢���������� 
		sub[i] = a[j] - '0';
	for (i = 0, j = len_b - 1; j >= 0; --j, ++i)	//����������ת�������ʹ洢����ʱ������ 
		tempb[i] = b[j] - '0';

	for (k = 0; k <= len_sub; ++k) {
		sub[k] -= tempb[k];							//��Ӧλ��������ڲ������� 
		if (sub[k] < 0) {							//�����λ�ı�����С�ڼ��������������һ����һ������ 
			sub[k] += 10;							//����Ҫ������ǰ��һλ���� +10 ��(a+10)-b=(a-b)+10�� 
			sub[k + 1]--;							//����ĸ�һλҪ -1 
		}
	}

	for (i = len_a; sub[i] == 0 && i >= 0; --i);	//�������� sub[i]==0&&i>=0������λ��һλ��Ϊ����ѭ������
	len_sub = i + 1;								//i�����óɸĺ�����ȫ�ֱ������κθú����ĺ������������󶼻ᱣ��i��ֵ

	if (sign == -1) {								//�����ڸ��ţ��򽫲�����λ��ǰһλ���渺�� 
		sub[len_sub] = -1;
		len_sub++;									//������Ҫռ���ȵ� 
	}

	if (sub[len_sub - 1] == -1) {					//��� ������λ��ǰһλ�Ƿ��Ǹ���
		cout << "-";
		len_sub--;									//��������ȡ������Ҫ��ȥ������ռ�ĳ��� 
	}

	return len_sub;
}

/**********************-Multiplication-**************************
1.��ȡ�����ַ����鳤�ȣ��µĳ���Ϊ������֮��					*
2.�����������ַ�����ֱ����򱣴���������ʱ����������			*
3.�ӵ�λ��ʼ����												*
4.����һ��ѭ���˳���������mul�жϽ�λ���						*
5.ѭ���ó�����λ��												*
			������ * ���� = ��									*
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
			mul[i + j] += temp_a[i] * temp_b[j];		//ÿһλѭ������ۼӵ�����������

	for (i = 0; i <= len_m + 1; ++i) {					//�����ͳ�ƽ�λ����
		if (mul[i] >= 10) {
			mul[i + 1] += mul[i] / 10;
			mul[i] %= 10;
		}
	}

	for (i = len_m + 1; mul[i] == 0 && i >= 0; --i);
	len_m = i + 1;										//ͳ�ƻ���λ�� (i������Ϊ�ú�����ȫ�ֱ���)

	return len_m;
}

/****************************-Division********************************


				������ / ���� = ��......����
**********************************************************************/
void Division(char a[], char b[], int div[]) {
	int lena = (int)strlen(a);						//������λ��
	int len_b = (int)strlen(b);						//��������λ��
}

/*----------------------------------------����������---------------------------------------------*/
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

/*----------------------------------32λ��������ƻ�ʮ����-------------------------------------*/
long long Num_to_Dec(char a[], int B) {
	int len, i;
	long long sum = 0, num = 0;
	len = (int)strlen(a);							//strlen��cstring�� 
	for (i = 0; i < len; ++i) {
		if (a[i] >= '0'&&a[i] <= '9')
			num = a[i] - '0';
		else if (a[i] >= 'A'&&a[i] <= 'V')
			num = a[i] - 'A' + 10;
		sum = sum * B + num;
	}
	return sum;
}

/*---------------------------------ʮ���ƻ�32λ���������-------------------------------------*/
void Dec_to_Num(long long Dec, int B) {
	long long n;
	if (Dec) {
		Dec_to_Num(Dec / B, B);						//���õݹ���ʵ�֣�������ĵ������ⶼ�����
		n = Dec % B;
		if (n < 10)
			printf("%lld", n);
		else
			printf("%lld", n + 55);
	}
}

/*///////////////////////////////////////////////////////////////////-����ʵ����-/////////////////////////////////////////////////////////////////////*/


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