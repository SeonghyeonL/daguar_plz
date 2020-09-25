#include <stdio.h>
#include <stdlib.h> // for malloc, free
#define _CRT_SECURE_NO_WARNINGS // prevent scanf error

int main(void)
{
	// *** 총 몇 개 배열 받는지 입력 부분 필요 ***

	// 주의사항 출력 (모든 경우에 정수만 입력할 것)
	printf("please use integer only\n");

	// 미리 선언할 변수들
	int cntN, NoS; // for number of sequence
	
	// 총 입력 받을 배열의 개수 얻기
	printf("Number of Sequence (1~10) : ");
	scanf_s("%d", &NoS);
	while (1) // 배열의 개수(NoS)를 최대 10개로 제한
	{
		if (NoS < 1 || NoS > 10)
		{
			printf("%d is wrong input\n", NoS);
			printf("Number of Sequence (1~10) : ");
			scanf_s("%d", &NoS);
		}
		else
		{
			printf("input num of seq : %d\n", NoS);
			break;
		}
	}

	// LoS 배열 생성 (크기 = NoS)
	int* LoS = (int*)malloc(sizeof(int) * NoS);

	// NoS번째 배열의 길이 및 값 입력 받기
	for (cntN = 0;cntN < NoS;cntN++)
	{
		printf("Length of Sequence(%d) (1~20) : ", cntN+1);
		scanf_s("%d", &LoS[cntN]);
		while (1) // 배열의 길이(LoS)를 최대 20개로 제한
		{
			if (LoS[cntN] < 1 || LoS[cntN] > 20)
			{
				printf("%d is wrong input\n", LoS[cntN]);
				printf("Length of Sequence(%d) (1~20) : ", cntN + 1);
				scanf_s("%d", &LoS[cntN]);
			}
			else
			{
				printf("input len of seq(%d) : %d\n", cntN+1, LoS[cntN]);
				break;
			}
		}
	}

	// 주의사항 출력 (숫자와 숫자는 띄어쓰기로 구별할 것)
	printf("form: num1 num2 num3 ...\n");

	// 배열 내용 입력 받기
	int insq[10][20]; // maxNoS=10, maxLoS=20
	int cntL; // for counting LoS
	for (cntN = 0;cntN < NoS;cntN++)
	{
		printf("Sequence(%d) : ", cntN+1);
		for (cntL = 0;cntL < LoS;cntL++)
		{
			scanf_s("%d", &insq[cntN][cntL]);
		}
		printf("input seq(%d) : ", cntN+1);
		for (cntL = 0;cntL < LoS;cntL++)
		{
			printf("%d ", insq[cntN][cntL]);
		}
		printf("\n");
	}

	// *** 여기부터 ***
	int maxsum = MaxSubsequenceSum(insq, LoS);
	printf("MAXSUM: %d\n", maxsum);
	int* subseq = MaxSubSeqSum(insq, LoS, maxsum);
	printf("SUBSEQ: ");
	int subseqlen = *subseq; // because subseq[0]=subseqlen
	for (int i = 0;i < subseqlen;i++)
	{
		printf("%d ", subseq[i + 1]);
	}
	printf("\n");
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