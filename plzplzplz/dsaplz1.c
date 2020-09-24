#include <stdio.h>
#include <stdlib.h> // for malloc, free
#define _CRT_SECURE_NO_WARNINGS // for scanf error

int main(void)
{
	// 총 몇 개 배열 받는지 입력 부분 필요
	int* insq; int LoS;
	printf("please use integer only\n");
	printf("Length of Sequence (1~20) : ");
	scanf_s("%d", &LoS);
	while (1) // limit Length of Sequence (1~20)
	{
		if (LoS < 1 || LoS > 20)
		{
			printf("%d is wrong input\n", LoS);
			printf("Length of Sequence (1~20) : ");
			scanf_s("%d", &LoS);
		}
		else
		{
			printf("input length: %d\n", LoS); break;
		}
	}
	insq = (int*)malloc(sizeof(int) * LoS);
	printf("form: num1 num2 num3 ...\n");
	printf("Sequence: ");
	for (int i = 0;i < LoS;i++)    scanf_s("%d", &insq[i]);
	printf("input sequence: ");
	for (int i = 0;i < LoS;i++)    printf("%d ", insq[i]);
	printf("\n");
	int maxsum = MaxSubsequenceSum(insq, LoS);
	printf("MAXSUM: %d\n", maxsum);
	int* subseq = MaxSubSeqSum(insq, LoS, maxsum);
	printf("SUBSEQ: ");
	int subseqlen = *subseq;
	for (int i = 0;i < subseqlen;i++)
	{
		printf("%d ", subseq[i + 1]);
	}
	printf("\n");
	// subseq의 크기 계산해서 subseq를 for문으로 출력
	free(insq); free(subseq);
	return 0;
}

// original - return 'sum'
MaxSubsequenceSum(int A[], int N)
{
	int ThisSum, MaxSum, j; int Amax, Anow;
	ThisSum = MaxSum = 0; Amax = -9999; Anow = 0;
	for (j = 0;j < N;j++)
	{
		ThisSum += A[j];
		if (ThisSum > MaxSum)    MaxSum = ThisSum;
		else if (ThisSum < 0)    ThisSum = 0;

		Anow = A[j];
		if (Anow > Amax)    Amax = Anow;
		// Amax is max num for x<0 only sequence
	}
	if (MaxSum == 0 && Amax < 0)    MaxSum = Amax;
	return MaxSum;
}

// edit - return 'subseq'
// 조건: max subseq는 각 원소의 합이 최대가 되는 subseq 중
//       구성 원소의 개수가 최소인 subseq라고 정의
// MaxSum이 0인 경우는 0과 음수로만 구성된 경우 (= 0 1개)
// MaxSum이 음수인 경우는 음수로만 구성된 경우 (= 최댓값인 1개)
// MaxSum이 양수인 경우는 나머지
MaxSubSeqSum(int A[], int N, int MaxSum)
{
	int thissum, maxsum, findsum;
	int j, k, i, startnum, endnum;
	int* SubSeq;
	if (MaxSum > 0)
	{
		thissum = maxsum = startnum = endnum = 0;
		for (j = 0;j < N;j++)
		{
			thissum += A[j];
			if (thissum > maxsum)
			{
				maxsum = thissum;
				if (A[j] != 0 && maxsum == MaxSum)    endnum = j;
			}
			else if (thissum < 0)    thissum = 0;
		}
		findsum = MaxSum;
		for (k = endnum;k >= 0;k--)
		{
			findsum -= A[k];
			if (A[k] != 0 && findsum == 0)    startnum = k;
		}
		int SubSeqLen = endnum - startnum + 1;
		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		for (i = 1;i <= SubSeqLen;i++)
		{
			SubSeq[i] = A[i + startnum - 1];
		}
		SubSeq[0] = SubSeqLen;
		return SubSeq;
	}
	else if (MaxSum <= 0) // MaxSum==0 && MaxSum<0
	{
		int SubSeqLen = 1; // "MaxSum"
		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		SubSeq[0] = SubSeqLen; SubSeq[1] = MaxSum;
		return SubSeq;
	}
}

// 문제점: 0과 음수로만 구성된 수열은 SubSeq가 음수로만 나옴