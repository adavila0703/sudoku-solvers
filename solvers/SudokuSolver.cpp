#include <iostream>
#include <string>
#include <tuple>
#include <chrono>

using namespace std;


class Console {
	//C# style console methods
public:
	static void WriteLine(string str) {
		cout << str << endl;
	}
	static void WriteLine(bool bol) {
		if (bol == true) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}
	static void WriteLine(int num) {
		cout << num << endl;
	}
	static void Write(string str) {
		cout << str;
	}
	static void Write(int num) {
		cout << num;
	}
};

class Array {
	//C# style array methods
public:
	static bool IndexOf(int arr[], int num) {
		for (int i = 0; i < 9; i++) {
			if (arr[i] == num) {
				return true;
			}
		}
		return false;
	}
};


string Slot(int num) {
	return "| " + to_string(num) + " |";
}

void DrawBoard(int arr[][9]) {
	int cutOff[2] = { 2, 5 };
	Console::WriteLine(string(45, '-'));
	for (int row = 0; row < 9; row++){
		for (int col = 0; col < 9; col++){
			Console::Write(Slot(arr[row][col]));
		}
		Console::Write("\n");
		if (Array::IndexOf(cutOff, row) == true){
			Console::WriteLine(string(45, '-'));
		}
	}
	Console::WriteLine(string(45, '-'));
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
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (arr[i + startingRow][j + startingCol] == num)
			{
				return false;
			}
		}
	}
}

tuple<int, int> FindEmpty(int arr[][9]) {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++){
			if (arr[row][col] == 0) {
				return make_tuple(row, col);
			}
		}
	}
	return make_tuple(-1, -1);
}


bool Solver(int arr[][9]) {
	int replaceNum[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	tuple<int, int> cord = FindEmpty(arr);
	if (get<0>(cord) == -1) {
		return true;
	}
	for (int i = 0; i < 9; i++) {
		if (CheckValid(arr, get<0>(cord), get<1>(cord), replaceNum[i])) {
			arr[get<0>(cord)][get<1>(cord)] = replaceNum[i];
			if (Solver(arr)) {
				return true;
			}
			arr[get<0>(cord)][get<1>(cord)] = 0;
		}
	}
	return false;
}


int main()
{
	auto startTime = chrono::steady_clock::now();
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
	auto endTime = chrono::steady_clock::now();
	
	cout << "Solve Time -> " << chrono::duration_cast<chrono::seconds>(endTime - startTime).count()
		<< "s:" << chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count()
		<< "m:" << chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() << "us";
}
