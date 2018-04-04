#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void input_scores(float score[], int n)
{
	int c;
	printf("\n\n");
	printf("점수를 입력하세요.\n");
	for (c = 0; c<n; c++)
	{
		scanf("%f", &score[c]);
	}
}


float max_score(float score[], int n)
{
	float max = 0;
	if (n == 1) {
		return score[n - 1];
	}
	max = max_score(score, n - 1);
		return (max > score[n - 1]) ? max : score[n - 1];

}



float min_score(float score[], int n)
{
	float min = 0;
	if (n == 1) {
		return score[n - 1];
	}
	min = min_score(score, n - 1);
	return (min < score[n - 1]) ? min : score[n - 1];

}



float sum_scores(float score[], int n)
{
	float sum;
	if (n == 1) {
		return score[n - 1];
	}
	sum = sum_scores(score, n - 1);
	return (sum += score[n - 1]);

}



void print_result(float max, float min, float sum, float mean)
{
	printf("**************************\n");
	printf("최고점수: %f\n", max);
	printf("최저점수: %f\n", min);
	printf("합계점수: %f\n", sum);
	printf("평균점수: %f\n", mean);
	printf("**************************\n");
}


void main()
{
	int n;
	float score[30];
	float max, min, sum, mean;

	printf("학생수? ");
	scanf("%d", &n);

	input_scores(score, n);

	max = max_score(score, n);
	min = min_score(score, n);
	sum = sum_scores(score, n);
	mean = sum / (float)n;

	print_result(max, min, sum, mean);

}
