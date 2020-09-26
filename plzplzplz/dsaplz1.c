#include <stdio.h>
#include <stdlib.h> // for using malloc, free
#define _CRT_SECURE_NO_WARNINGS // for preventing scanf error

int main(void)
{
	// ���ǻ��� ��� (��� ��쿡 ������ �Է��� ��, ����� ����)
	printf("\nplease use integer only and check # of elements\n");
	printf("sequence input form : num1 num2 num3 ...\n");

	// INPUT �κ� ���� -----------------------------------
	printf("\n\n********* INPUT *********\n\n");

	// �̸� ������ ������
	int cntN, NoS; // for number of sequence
	int cntL; // for counting LoS
	
	// �� �Է� ���� �迭�� ���� ���
	printf("Number of Sequence (1~10) : ");
	scanf_s("%d", &NoS);
	while (1) // �迭�� ����(NoS)�� �ִ� 10���� ����
	{
		if (NoS < 1 || NoS > 10)
		{
			// ������ ��� ��� ���Է� ��û
			printf("%d is wrong input\n", NoS);
			printf("Number of Sequence (1~10) : ");
			scanf_s("%d", &NoS);
		}
		else
		{
			// ������ �ش�� ��� �Է°� Ȯ�ν�����
			printf("input num of seq : %d\n\n", NoS);
			break; // while�� �����
		}
	}

	// LoS �迭 ���� (ũ�� = NoS)
	int* LoS = (int*)malloc(sizeof(int) * NoS);

	// input sequence�� 2���� �迭 (maxNoS=10, maxLoS=20)
	int insq[10][20]; // ������ �迭, [�ళ��][������]

	// NoS��° seq�� ���� �� �� �Է� �ޱ�
	for (cntN = 0;cntN < NoS;cntN++)
	{
		printf("Length of Sequence(%d) (1~20) : ", cntN+1);
		scanf_s("%d", &LoS[cntN]);
		while (1) // �迭�� ����(LoS)�� �ִ� 20���� ����
		{
			// cntN+1��° seq�� ���� �Է¹ޱ�
			if (LoS[cntN] < 1 || LoS[cntN] > 20)
			{
				// ������ ��� ��� ���Է� ��û
				printf("%d is wrong input\n", LoS[cntN]);
				printf("Length of Sequence(%d) (1~20) : ", cntN + 1);
				scanf_s("%d", &LoS[cntN]);
			}
			else
			{
				// ������ �ش�� ��� �Է°� Ȯ�ν�����
				printf("input len of seq(%d) : %d\n", cntN+1, LoS[cntN]);
				break; // while�� �����
			}
		}

		// cntN+1��° seq�� ���� �Է¹ޱ�
		printf("Sequence(%d) : ", cntN + 1);
		for (cntL = 0;cntL < LoS[cntN];cntL++)
		{
			scanf_s("%d", &insq[cntN][cntL]); // �Է� �� ����
		}

		printf("\n");
	}

	// OUTPUT �κ� ���� -----------------------------------
	printf("\n********* OUTPUT *********\n\n");

	for (cntN = 0;cntN < NoS;cntN++)
	{
		// cntN+1��° seq�� ���� ���
		printf("INPUT SEQ(%d) : ", cntN + 1);
		for (cntL = 0;cntL < LoS[cntN];cntL++)
		{
			printf("%d ", insq[cntN][cntL]);
		}
		printf("\n");

		// maxsum ������ ���� �ִ� ���� �� ���
		int maxsum = MaxSubsequenceSum(insq[cntN], LoS[cntN]);
		printf("MAXSUM(%d) : %d\n", cntN + 1, maxsum);

		// maxsum�� �����ϴ� ����(subseq) ��� ����
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
	// Anow�� 0����, Amax�� �ſ� ���� ��(-9999)���� �ʱ�ȭ

	for (j = 0;j < N;j++)
	{
		ThisSum += A[j]; // ��, ���� �� + ������ �迭 ��
		if (ThisSum > MaxSum)    MaxSum = ThisSum;
		else if (ThisSum < 0)    ThisSum = 0;

		Anow = A[j]; // Anow = ������ �迭 ��
		if (Anow > Amax)    Amax = Anow;
		// Amax is max num for x<0 only sequence
	}

	if (MaxSum == 0 && Amax < 0)    MaxSum = Amax;
	// ������ ��� ������ ��� MaxSum�� ���� �� �ִ�

	return MaxSum; // MaxSum�� ��ȯ
}

// return 'maximum sum's seq (= subseq)'
// ����: max subseq�� �� ������ ���� �ִ밡 �Ǵ� subseq ��
//       ���� ������ ������ �ּ��� subseq��� ����
// MaxSum�� 0�� ���� 0�� �����θ� ������ ��� (= 0 1��)
// MaxSum�� ������ ���� �����θ� ������ ��� (= �ִ��� 1��)
// MaxSum�� ����� ���� ������ ����
MaxSubSeqSum(int A[], int N, int MaxSum)
{
	int thissum, maxsum, findsum;
	int j, k, i, startnum, endnum;
	int* SubSeq;

	if (MaxSum > 0) // MaxSum�� ����� ���
	{
		thissum = maxsum = startnum = endnum = 0;

		for (j = 0;j < N;j++)
		{
			thissum += A[j];
			if (thissum > maxsum)
			{
				maxsum = thissum;
				if (A[j] != 0 && maxsum == MaxSum)    endnum = j;
				// ���� ���� 0�� �ƴϸ鼭 ���� MaxSum�� ��ġ�� ����
				// ����(��ġ)�� ������ ��ġ�� ����
			}
			else if (thissum < 0)    thissum = 0;
		}

		findsum = MaxSum;
		for (k = endnum;k >= 0;k--)
		{
			findsum -= A[k]; // �ڿ������� �����鼭 ���� ��ġ ã��
			if (A[k] != 0 && findsum == 0)    startnum = k;
		}

		int SubSeqLen = endnum - startnum + 1; // subseq�� ���� ���
		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		for (i = 1;i <= SubSeqLen;i++)
		{
			SubSeq[i] = A[i + startnum - 1];
		}
		// return ���� [0]�� ��ü ����, [1]���ʹ� ���� ��
		SubSeq[0] = SubSeqLen;

		return SubSeq; // SubSeq�� ��ȯ
	}
	else if (MaxSum <= 0) // MaxSum==0 && MaxSum<0
	{
		int SubSeqLen = 1; // "MaxSum"���� ���Ұ� 1����

		SubSeq = (int*)malloc(sizeof(int) * (SubSeqLen + 1));
		// return ���� [0]�� ��ü ����, [1]�� ���� ��(= 1����)
		SubSeq[0] = SubSeqLen; SubSeq[1] = MaxSum;

		return SubSeq; // SubSeq�� ��ȯ
	}
}
