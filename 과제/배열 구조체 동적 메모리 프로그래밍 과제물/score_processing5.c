#include <mylib.h>
#include <stdio.h>

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
