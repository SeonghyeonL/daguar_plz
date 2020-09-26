#include <stdio.h>
#include <stdlib.h> // for using malloc, free
#define _CRT_SECURE_NO_WARNINGS // for preventing scanf error

int main(void)
{
	// 주의사항 출력 (모든 경우에 정수만 입력할 것, 띄어쓰기로 구분)
	printf("\nplease use integer only and check # of elements\n");
	printf("sequence input form : num1 num2 num3 ...\n");

	// INPUT 부분 시작 -----------------------------------
	printf("\n\n********* INPUT *********\n\n");

	// 미리 선언할 변수들
	int cntN, NoS; // for number of sequence
	int cntL; // for counting LoS
	
	// 총 입력 받을 배열의 개수 얻기
	printf("Number of Sequence (1~10) : ");
	scanf_s("%d", &NoS);
	while (1) // 배열의 개수(NoS)를 최대 10개로 제한
	{
		if (NoS < 1 || NoS > 10)
		{
			// 범위를 벗어난 경우 재입력 요청
			printf("%d is wrong input\n", NoS);
			printf("Number of Sequence (1~10) : ");
			scanf_s("%d", &NoS);
		}
		else
		{
			// 범위에 해당될 경우 입력값 확인시켜줌
			printf("input num of seq : %d\n\n", NoS);
			break; // while문 벗어나기
		}
	}

	// LoS 배열 생성 (크기 = NoS)
	int* LoS = (int*)malloc(sizeof(int) * NoS);

	// input sequence의 2차원 배열 (maxNoS=10, maxLoS=20)
	int insq[10][20]; // 정수형 배열, [행개수][열개수]

	// NoS번째 seq의 길이 및 값 입력 받기
	for (cntN = 0;cntN < NoS;cntN++)
	{
		printf("Length of Sequence(%d) (1~20) : ", cntN+1);
		scanf_s("%d", &LoS[cntN]);
		while (1) // 배열의 길이(LoS)를 최대 20개로 제한
		{
			// cntN+1번째 seq의 길이 입력받기
			if (LoS[cntN] < 1 || LoS[cntN] > 20)
			{
				// 범위를 벗어난 경우 재입력 요청
				printf("%d is wrong input\n", LoS[cntN]);
				printf("Length of Sequence(%d) (1~20) : ", cntN + 1);
				scanf_s("%d", &LoS[cntN]);
			}
			else
			{
				// 범위에 해당될 경우 입력값 확인시켜줌
				printf("input len of seq(%d) : %d\n", cntN+1, LoS[cntN]);
				break; // while문 벗어나기
			}
		}

		// cntN+1번째 seq의 값들 입력받기
		printf("Sequence(%d) : ", cntN + 1);
		for (cntL = 0;cntL < LoS[cntN];cntL++)
		{
			scanf_s("%d", &insq[cntN][cntL]); // 입력 값 저장
		}

		printf("\n");
	}

	// OUTPUT 부분 시작 -----------------------------------
	printf("\n********* OUTPUT *********\n\n");

	for (cntN = 0;cntN < NoS;cntN++)
	{
		// cntN+1번째 seq의 값들 출력
		printf("INPUT SEQ(%d) : ", cntN + 1);
		for (cntL = 0;cntL < LoS[cntN];cntL++)
		{
			printf("%d ", insq[cntN][cntL]);
		}
		printf("\n");

		// maxsum 변수에 합의 최댓값 저장 및 출력
		int maxsum = MaxSubsequenceSum(insq[cntN], LoS[cntN]);
		printf("MAXSUM(%d) : %d\n", cntN + 1, maxsum);

		// maxsum을 구성하는 값들(subseq) 출력 과정
		int* subseq = MaxSubSeqSum(insq[cntN], LoS[cntN], maxsum);
		printf("SUBSEQ(%d) : ", cntN + 1);
		int subseqlen = *subseq; // because subseq[0]=subseqlen
		for (int i = 0;i < subseqlen;i++)
		{
			printf("%d ", subseq[i + 1]);
		}
		printf("\n\n");

		free(subseq);
	}

	free(LoS);
	return 0;
}

// return 'maximum sum'
MaxSubsequenceSum(int A[], int N)
{
	int ThisSum, MaxSum, j; int Amax, Anow;
	ThisSum = MaxSum = 0;
	Amax = -9999; Anow = 0;
	// Anow는 0으로, Amax는 매우 작은 값(-9999)으로 초기화

	for (j = 0;j < N;j++)
	{
		ThisSum += A[j]; // 즉, 기존 합 + 현재의 배열 값
		if (ThisSum > MaxSum)    MaxSum = ThisSum;
		else if (ThisSum < 0)    ThisSum = 0;

		Anow = A[j]; // Anow = 현재의 배열 값
		if (Anow > Amax)    Amax = Anow;
		// Amax is max num for x<0 only sequence
	}

	if (MaxSum == 0 && Amax < 0)    MaxSum = Amax;
	// 값들이 모두 음수인 경우 MaxSum은 음수 중 최댓값

	return MaxSum; // MaxSum을 반환
}

// return 'maximum sum's seq (= subseq)'
// 조건: max subseq는 각 원소의 합이 최대가 되는 subseq 중
//       구성 원소의 개수가 최소인 subseq라고 정의
// MaxSum이 0인 경우는 0과 음수로만 구성된 경우 (= 0 1개)
// MaxSum이 음수인 경우는 음수로만 구성된 경우 (= 최댓값인 1개)
// MaxSum이 양수인 경우는 나머지 경우들
MaxSubSeqSum(int A[], int N, int MaxSum)
{
	int thissum, maxsum, findsum;
	int j, k, i, startnum, endnum;
	int* SubSeq;

	if (MaxSum > 0) // MaxSum이 양수인 경우
	{
		thissum = maxsum = startnum = endnum = 0;

		for (j = 0;j < N;j++)
		{
			thissum += A[j];
			if (thissum > maxsum)
			{
				maxsum = thissum;
				if (A[j] != 0 && maxsum == MaxSum)    endnum = j;
				// 더한 값이 0이 아니면서 합이 MaxSum과 일치할 때의
				// 순서(위치)를 마지막 위치로 설정
			}
			else if (thissum < 0)    thissum = 0;
		}

		findsum = MaxSum;
		for (k = endnum;k >= 0;k--)
		{
			findsum -= A[k]; // 뒤에서부터 빼가면서 시작 위치 찾기
			if (A[k] != 0 && findsum == 0)    startnum = k;
		}

		int SubSeqLen = endnum - startnum + 1; // subseq의 길이 계산
		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		for (i = 1;i <= SubSeqLen;i++)
		{
			SubSeq[i] = A[i + startnum - 1];
		}
		// return 값의 [0]은 전체 길이, [1]부터는 실제 값
		SubSeq[0] = SubSeqLen;

		return SubSeq; // SubSeq를 반환
	}
	else if (MaxSum <= 0) // MaxSum==0 && MaxSum<0
	{
		int SubSeqLen = 1; // "MaxSum"으로 원소가 1개뿐

		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		// return 값의 [0]은 전체 길이, [1]은 실제 값(= 1개뿐)
		SubSeq[0] = SubSeqLen; SubSeq[1] = MaxSum;

		return SubSeq; // SubSeq를 반환
	}
}
