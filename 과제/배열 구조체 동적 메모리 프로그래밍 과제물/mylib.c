#include "stdafx.h"
#include "mylib.h"

void input_scores_file(FILE *infile, float *score, int n) {
	int i;
	for (i = 0; i < n; i++) {
		fscanf(infile, "%f", &score[i]);
	}
}

float max_score(float *score, int n)
{
	float max = 0;
	if (n == 1) {
		return score[n - 1];
	}
	max = max_score(score, n - 1);
	return (max > score[n - 1]) ? max : score[n - 1];

}

float min_score(float *score, int n)
{
	float min = 0;
	if (n == 1) {
		return score[n - 1];
	}
	min = min_score(score, n - 1);
	return (min < score[n - 1]) ? min : score[n - 1];

}



float sum_scores(float *score, int n)
{
	float sum = 0;
	if (n == 1) {
		return score[n - 1];
	}
	sum = sum_scores(score, n - 1);
	return (sum += score[n - 1]);

}


float print_scores(float *score, int n) {
	float showScores;
	if (n == 0) {
		return score[n];
	}
	showScores = print_scores(score, n - 1);

	printf("%f�� �Էµ�\n", score[n - 1]);
	return (showScores = score[n - 1]);
}

float print_result(float max, float min, float sum, float mean) {
	printf("**************\n");
	printf("�ְ�����: %f\n", max);
	printf("��������: %f\n", min);
	printf("�հ�����: %f\n", sum);
	printf("�������: %f\n", mean);
	printf("**************\n");
	return max, min, sum, min;
}

float save_result_file(FILE *outfile, float max, float min, float sum, float mean) {
	fprintf(outfile, "�ְ�����: %f \n", max);
	fprintf(outfile, "��������: %f \n", min);
	fprintf(outfile, "�հ�����: %f \n", sum);
	fprintf(outfile, "�������: %f \n", mean);
	return max, min, sum, mean;
}