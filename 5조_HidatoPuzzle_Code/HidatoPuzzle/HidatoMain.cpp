#include "HidatoSol.h"
#include "HidatoGen.h"

int main() {

	// Generator
	ifstream input;
	input.open("input.txt");

	ofstream output;
	output.open("output.txt");

	MapIn(input);
	GeneratePuzzle();
	MapOut(output);

	// Solver
	vector<string> inputtext;
	int row, col;
	string line;

	ifstream fin("output.txt");

	getline(fin, line);
	istringstream is(line);
	is >> row >> col;

	for (int i = 0; i < row; ++i)
	{
		getline(fin, line);
		inputtext.push_back(line);
	}
	
	initHidato(inputtext, row, col);

	cout << ("Puzzle Input:") << endl;
	printPuzzle();

	solveHidato(startPoint.first, startPoint.second, 1, 0);

	cout << ("\nSolution Found:") << endl;
	printPuzzle();

	system("pause");
	return 0;
}