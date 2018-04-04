#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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

	printf("%f점 입력됨\n", score[n-1]);
	return (showScores = score[n-1]);
}

float print_result(float max, float min, float sum, float mean) {
	printf("**************\n");
	printf("최고점수: %f\n", max);
	printf("최저점수: %f\n", min);
	printf("합계점수: %f\n", sum);
	printf("평균점수: %f\n", mean);
	printf("**************\n");
}

float save_result_file(FILE *outfile, float max, float min, float sum, float mean) {
	fprintf(outfile, "최고점수: %f \n", max);
	fprintf(outfile, "최저점수: %f \n", min);
	fprintf(outfile, "합계점수: %f \n", sum);
	fprintf(outfile, "평균점수: %f \n", mean);
}

int main() {
	FILE *infile, *outfile;
	float max, min, mean, sum;
	int n;
	float *score;
	infile = (FILE *)fopen("scores.txt", "r");
	if (infile == NULL) {
		printf("에러: 입력 파일을 열 수 없음!!!\n\n");
		return;
	}
	outfile = (FILE *)fopen("result.txt", "w");
	printf("학생 수?: ");
	scanf("%d", &n);
	score = (float *)malloc(n * sizeof(float));
	if (score == NULL) {
		printf("에러: 동적 메모리 할당 실패!!!\n\n");
		return;
	}
	printf("scores.txt파일에 있는 학생 수는 %d명\n", n);

	input_scores_file(infile, score, n);
	print_scores(score, n);
	max = max_score(score, n);
	min = min_score(score, n);
	sum = sum_scores(score, n);
	mean = mean = sum / (float)n;

	print_result(max, min, sum, mean);
	save_result_file(outfile, max, min, sum, mean);
	fclose(infile);
	fclose(outfile);
	free(score);
}
