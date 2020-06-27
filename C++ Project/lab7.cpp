#pragma warning(disable : 4703)
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h> 
#include <locale.h>
#include <conio.h>
#define N 5 
void input_matr_file(int a[][N])
{
	int i, j;
	FILE* fp;
	fp = fopen("in.txt", "r");
	if (fp)
	{
		for (i = 0;i < N;i++)
			for (j = 0;j < N;j++)
				fscanf(fp, "%d", &a[i][j]);
	}
	else printf("Входной файл отсутствует\n");
}

void input_matr(int a[N][N])
{
	int i, j;
	printf("Введите элементы матрицы А: \n");
	for (i = 0;i < N;i++)
		for (j = 0;j < N;j++)
			scanf("%d", &a[i][j]);
}

void output(const int x[], const int a[N][N])
{
	int i, j;
	FILE* fp;
	printf("Матрица А:\n");
	for (i = 0;i < N;i++)
	{
		for (j = 0;j < N;j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
	printf("Массив Х:\n");
	for (i = 0; i < N; i++)
		printf("%d ", x[i]);
	printf("\n");
	fp = fopen("out.txt", "w");
	for (i = 0;i < N;i++)
		fprintf(fp, "%5d", x[i]);
	fclose(fp);
}

int* mas_max(int(*a)[N], int* x, void (*pfunc)(int[N][N])) 
{
	int i, j, max, abs_max, n1, n2;
	bool flag = false;
	pfunc(a);  
	max = a[0][0];
	abs_max = a[0][0];
	for (i = 0; i < N; i++)  
		for (j = 0; j < N; j++)
		{
			if (a[i][j] > max)
			{
				max = a[i][j];
				n1 = j;
			};
			if (abs(a[i][j]) > abs_max)
			{
				abs_max = abs(a[i][j]);
				n2 = j;
			}
		}
	printf("max = %d\n", max); 
	printf("abs_max = %d\n", abs_max);
	if (n1 == n2)
	{
		printf("max и abs_max находятся в одном столбце: %d\n", n1);
		for (i = 0; i < N; i++)
			x[i] = a[i][n1];
	}
	else
	{
		printf("max и abs_max находятся в разных столбцах\n");
		for (i = 0; i < N; i++)
			x[i] = a[N - i - 1][i];
	};
	return x;
}

void multiply_recurs(int x[N], int i, int& s) 
{
	if (i < N)  
		if (x[i] < 0)
		{
			s = s * x[i];   
			return multiply_recurs(x, i + 1, s); 
		}
		else 
			return multiply_recurs(x, i + 1, s);
}

int multiply(int x[N])
{
	int s, i; 
	s = 1; 
	i = 0;
	while ((i < N) && (x[i]<0))  
		i++;
	i++; 
	multiply_recurs(x, i, s); 
	return s;
}

int main() 
{
	setlocale(LC_CTYPE, "");
	int a[N][N], x[N], c;
	void (*pfunc)(int[N][N]);
	do
	{
		printf("Ввод матрицы:\n1 - с клавиатуры\n2- из файла\n");
		scanf("%d", &c);
	} while (c != 1 && c != 2);
	switch (c)
	{
	case 1: pfunc = &input_matr;
		break;
	case 2: pfunc = &input_matr_file;
	}
	output(mas_max(a, x, pfunc), a);
	printf("Y = %d", multiply(x));
	_getch();
}