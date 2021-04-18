#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool IndexOf(int arr[], int num) {
	for (int i = 0; i < 9; i++) {
		if (arr[i] == num) {
			return true;
		}
	}
	return false;
}

void DrawBoard(int arr[][9]) {
	int cutOff[2] = { 2, 5 };

	printf("\n----------------------------------------------------\n");
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			printf("%i ", arr[row][col]);
		}
		printf("\n");
		if (IndexOf(cutOff, row) == true) {
			printf("\n----------------------------------------------------\n");
		}

	}
	printf("\n----------------------------------------------------\n");
}


bool CheckValid(int arr[][9], int row, int col, int num) {
	int startingRow = row - row % 3;
	int startingCol = col - col % 3;

	for (int i = 0; i < 9; i++) {
		if (arr[row][i] == num) {
			return false;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (arr[i][col] == num) {
			return false;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[i + startingRow][j + startingCol] == num)
			{
				return false;
			}
		}
	}
}

int FindEmpty(int arr[][9], int num) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (arr[row][col] == 0) {
				if (num == 1) {
					return row;
				}
				else {
					return col;
				}
			}
		}
	}
	return -1;
}


bool Solver(int arr[][9]) {
	int replaceNum[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int cord[2];
	cord[0] = FindEmpty(arr, 1);
	cord[1] = FindEmpty(arr, 2);
	if (cord[0] == -1) {
		return true;
	}
	for (int i = 0; i < 9; i++) {
		if (CheckValid(arr, cord[0], cord[1], replaceNum[i])) {
			arr[cord[0]][cord[1]] = replaceNum[i];
			if (Solver(arr)) {
				return true;
			}
			arr[cord[0]][cord[1]] = 0;
		}
	}
	return false;
}


int main()
{
	clock_t startTime = clock();
	int boardArray[9][9] = {
		 { 5,3,0, 0,7,0, 0,0,0 }
		,{ 6,0,0, 1,9,5, 0,0,0 }
		,{ 0,9,8, 0,0,0, 0,6,0 }

		,{ 8,0,0, 0,6,0, 0,0,3 }
		,{ 4,0,0, 8,0,3, 0,0,1 }
		,{ 7,0,0, 0,2,0, 0,0,6 }

		,{ 0,6,0, 0,0,0, 2,8,0 }
		,{ 0,0,0, 4,1,9, 0,0,5 }
		,{ 0,0,0, 0,8,0, 0,7,9 } };

	DrawBoard(boardArray);
	Solver(boardArray);
	DrawBoard(boardArray);
	clock_t endTime = clock();
	float time_spent = (float)(endTime - startTime);
	printf("Solve Time -> %f\n", time_spent);
}