#include <stdio.h>

int main() {
	int number;
	float score[30];
	float highScore = 0, lowScore = 0, sumScore = 0, avargeScore = 0;

	printf("학생수? ");
	scanf("%d", &number);

	printf("점수를 입력하세요.");

	for (int i = 0; i < number; i++) {
		scanf("%f", &score[i]);
	}

	// Sum Score
	for (int i = 0; i < number; i++) {
		sumScore = sumScore + score[i];
	}


	// Avarge Score
	for (int i = 0; i < number; i++) {
		avargeScore = sumScore / number;
	}


	//Highest Score
	highScore = score[0];
	for (int i = 0; i < number; i++) {
		if (score[i] > highScore) {
			highScore = score[i];
		}
	}



	//Lowest Score
	lowScore = score[0];
	for (int i = 0; i < number; i++) {
		if (score[i] < lowScore) {
			lowScore = score[i];
		}
	}




	printf("***********************\n");
	printf("Highest Score = %f\n", highScore);
	printf("Lowest Socre = %f\n", lowScore);
	printf("Sum Score = %f\n", sumScore);
	printf("Avarge  Score = %f\n", avargeScore);
	printf("***********************\n");

}
