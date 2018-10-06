#include <iostream>
#include <cstring>
#include <set>

using namespace std;

bool isUnknown(int value) {
	return (value == 0);
}

void initialize(set<int> &possibilities) {
	for(int i = 1; i <= 9; i++) 
		possibilities.insert(i);
}

void removeInconsistenciesFromLine(int line, set<int> &possibilities, int matrix[][11]) {
	for(int j = 0; j < 9; j++)
		possibilities.erase(matrix[line][j]);
}

void removeInconsistenciesFromColumn(int column, set<int> &possibilities, int matrix[][11]) {
	for(int i = 0; i < 9; i++) 
		possibilities.erase(matrix[i][column]);
}

void removeInconsistenciesFromSubregion(int line, int column, set<int> &possibilities, int matrix[][11]) {
	int initialLine, initialColumn;

	initialLine = 3 * (line / 3);
	initialColumn = 3 * (column / 3);

	for(int i = initialLine; i < initialLine + 3; i++) {
		for(int j = initialColumn; j < initialColumn + 3; j++) 
			possibilities.erase(matrix[i][j]);
	}
}

void showResultingMatrix(int matrix[][11]) {
	cout << "Resulting matrix is: " << endl;

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(j != 0) cout << " ";
			cout << matrix[i][j];
		}

		cout << endl;
	}
}

void removeAllInconsistencies(int line, int column, set<int> &possibilities, int matrix[][11]) {
	removeInconsistenciesFromLine(line, possibilities, matrix);
	removeInconsistenciesFromColumn(column, possibilities, matrix);
	removeInconsistenciesFromSubregion(line, column, possibilities, matrix);
}

void tryMethod1(int matrix[][11], int line, int column) {
	set<int> possibilities;
	initialize(possibilities);
	removeAllInconsistencies(line, column, possibilities, matrix);

	if( possibilities.size() == 1 ) {
		matrix[line][column] = *possibilities.begin();
	}
}

void tryMethod2(int matrix[][11], int line, int column) {
	if( isUnknown(matrix[line][column]) ) {
		int frequencyColumn[10], frequencyLine[10];
		set<int> possLine, possColumn, possibilities;

		memset(frequencyLine, 0, sizeof frequencyLine);
		memset(frequencyColumn, 0, sizeof frequencyColumn);

		for(int j = 0; j < 9; j++) {
			if( isUnknown( matrix[line][j] ) ) {
				possLine.clear();
				initialize(possLine);

				removeAllInconsistencies(line, j, possLine, matrix);
				for(int e : possLine) frequencyLine[e]++;
			}
		}

		for(int i = 0; i < 9; i++) {
			if( isUnknown( matrix[i][column] ) ) {
				possColumn.clear();
				initialize(possColumn);

				removeAllInconsistencies(i, column, possColumn, matrix);
				for(int e : possColumn) frequencyColumn[e]++;
			}
		}

		initialize(possibilities);
		removeAllInconsistencies(line, column, possibilities, matrix);

		for(int e : possibilities) {
			if(frequencyColumn[e] == 1 or frequencyLine[e] == 1) {
				matrix[line][column] = e;
				break;
			}
		}
	}
}

void tryMethod3(int matrix[][11], int line, int column) {
	if( isUnknown( matrix[line][column] ) ) {
		set<int> possSubregion, possibilities;
	
		int initialLine, initialColumn, frequency[10];
		memset(frequency, 0, sizeof frequency);

		initialLine = 3 * (line / 3);
		initialColumn = 3 * (column / 3);

		for(int i = initialLine; i < initialLine + 3; i++) {
			for(int j = initialColumn; j < initialColumn + 3; j++) {
				if(isUnknown( matrix[i][j] )) {
					possSubregion.clear();
					initialize(possSubregion);

					removeAllInconsistencies(i, j, possSubregion, matrix);
					for(int e : possSubregion) frequency[e]++;
				}
			}
		}

		initialize(possibilities);
		removeAllInconsistencies(line, column, possibilities, matrix);

		for(int e : possibilities) {
			if(frequency[e] == 1) {
				matrix[line][column] = e;
				break;
			}
		}
	}
}

int main() {
	bool endFilling;
	int matrix[11][11];

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) cin >> matrix[i][j];
	}

	endFilling = false;
	while(not endFilling) {
		endFilling = true;

		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if( isUnknown(matrix[i][j]) ) {
					endFilling = false;

					tryMethod1(matrix, i, j);
					tryMethod2(matrix, i, j);
					tryMethod3(matrix, i, j);
				} 
			}
		}
	}

	showResultingMatrix(matrix);
	return 0;
}