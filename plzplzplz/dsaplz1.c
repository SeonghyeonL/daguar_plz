#include <stdio.h>
#include <stdlib.h> // for malloc, free
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
	int* insq; int LoS;
	printf("Length of Sequenece: ");
	scanf_s("%d", &LoS);    printf("length: %d\n", LoS);
	insq = (int*)malloc(sizeof(int) * LoS);
	printf("form: num1 num2 num3 ...\n");
	printf("Sequence: ");
	for (int i = 0;i < LoS;i++)    scanf_s("%d", &insq[i]);
	printf("input sequence: ");
	for (int i = 0;i < LoS;i++)    printf("%d ", insq[i]);
	printf("\n");
	int maxsum = MaxSubsequenceSum(insq, LoS);
	printf("MAXSUM: %d", maxsum);
	free(insq);
	return 0;
}

MaxSubsequenceSum(int A[], int N)
{
	int ThisSum, MaxSum, j;
	ThisSum = MaxSum = 0;
	for (j = 0;j < N;j++)
	{
		ThisSum += A[j];
		if (ThisSum > MaxSum)	MaxSum = ThisSum;
		else if (ThisSum < 0)	ThisSum = 0;
	}
	return MaxSum;
}