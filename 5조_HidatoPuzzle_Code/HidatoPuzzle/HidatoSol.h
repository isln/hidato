#ifndef __HidatoSol_H__
#define __HidatoSol_H__

#include "Hidato.h"

//�� ��ü�� ���� �ϳ��� ��ü�� ������ִ� pairŸ������ �������� �����صӴϴ�.
pair<int, int> startPoint;

//������ ���� ������ ������ ����� �����Դϴ�.
vector<vector<int>> hidatoBoard;
//input���� �Էµ� ���ڵ��� �����صδ� �����Դϴ�.
vector<int> inputNum;
void initHidato(vector<string>& input, int row, int col)
{
	//������ ��,�� ũ�� 
	int nRows = row;
	int nCols = col;

	//��Ʈ�� Ÿ���� ��� ���͸� ���ҷ� ���� puzzle�� �����մϴ�. �� ���� ������ ���ҷ� ��� �ֽ��ϴ�
	vector<vector<string>> puzzle(nRows);

	for (int i = 0; i < nRows; i++)
	{
		//��Ʈ���� �Է¹޾� �ٸ� �������� �ٲ��ִ� istringstream�� �����մϴ�
		istringstream ss(input[i]);
		string str;
		//input������ 1����� str�� �޾� ��� puzzle�� push�մϴ�.
		while (ss >> str)
			puzzle[i].push_back(str);
	}

	//������ �׵θ� ���� ǥ�� �ϱ� ���� �����¿� ���پ��� �߰����ݴϴ�.
	vector<int> boardCol;
	boardCol.resize(nCols + 2);
	hidatoBoard.resize(nRows + 2, boardCol);

	for (vector<int>& row : hidatoBoard)
	{
		for (int& col : row)
			col = -1;
	}

	for (int r = 0; r < nRows; r++)
	{
		//puzzle�� ��� r��° ����(�� ����)�� row�� ��Ƴ����ϴ�
		vector<string> row = puzzle[r];

		for (int c = 0; c < nCols; c++)
		{
			//r�� c�� 1�� ���ϴ� ������ �׵θ� ������ ���� �ȿ� ���带 ä��� �����Դϴ�
			//�ش� ���� ��Ʈ�� ���� ���ڸ� element�� ����ϴ�
			string element = row[c];
			//�ش� ��Ʈ���� -1�̶�� ������������ Ǯ��� �� ��ĭ�Դϴ�
			if (element == "-1")
				hidatoBoard[r + 1][c + 1] = 0;
			//0�̶�� ������ �����մϴ�
			else if (element == "0")
				continue;
			//���� ���� �̿ܿ� �ٸ� ���ڶ�� ��Ʈ���� int�� ��ȯ�Ͽ� �����亸��迭�� �ش� ���ڸ� ����ֽ��ϴ�.
			else
			{
				int val = stoi(element);
				hidatoBoard[r + 1][c + 1] = val;
				//input���Ͽ��� �־��� ���ڸ� ��Ƴ��� ������ inputNum�� �ش� ���ڸ� ��Ƴ����ϴ�.
				inputNum.push_back(val);
				//�ش� ���ڰ� 1�̶�� �� ���� ������������ ���������� �����մϴ�.
				if (val == 1)
				{
					startPoint.first = r + 1;
					startPoint.second = c + 1;
				}
			}
		}
	}

	sort(inputNum.begin(), inputNum.end());
	// input���Ͽ� ����ִ� ���ڵ��� �����س����ϴ�.
}
// ������ ������ Ǯ �� �ִ��� 8�������� Ž���մϴ�.
   // ���� ó������ ������ (���ڰ� 1�� ����)���� Ž���� �����մϴ�.
bool solveHidato(int r, int c, int n, int next)
{
	//���� ���ڰ� �־��� ������ max������ ũ�� Ž�� ����
	if (n > inputNum[inputNum.size() - 1])
		return true;
	//Ž���Ϸ��� ���� 0(��ĭ)�� �ƴϰ� ������ ���ڰ� �ƴ϶�� �ش� ĭ���δ�
	   //Ž�� �Ұ�
	if (hidatoBoard[r][c] != 0 && hidatoBoard[r][c] != n)
		return false;
	//Ž���Ϸ��� ���� 0(��ĭ)�̰�, �־��� ���� ������ next��°�� ���� ���ڶ��
	//Ž���Ұ�
	if (hidatoBoard[r][c] == 0 && inputNum[next] == n)
		return false;

	//Ž���Ϸ��� ���� lastPoint�� �����صӴϴ�
	int lastPoint = hidatoBoard[r][c];
	//Ž���Ϸ��� ���� ���� ���ڰ� ���ٸ� ���� Ž�������� Ž��.
	if (lastPoint == n)
		next++;
	//�ش� ���� ���� ǥ��
	hidatoBoard[r][c] = n;
	//8�������� ���� ������ recursive�ϰ� ȣ���ؼ� Ȯ���մϴ�.
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			//������ �����ٸ� ��
			if (solveHidato(r + i, c + j, n + 1, next))
				return true;
	//8������ �ƹ������ε� �� ���� �������� �����ص� lastPoint�� ���ư��ϴ�
	hidatoBoard[r][c] = lastPoint;

	return false;
}
// ������ ���� board�� ����ϴ� �Լ��Դϴ�. ��ǲ������ �Է¹��� ���Ŀ� �����ߴٸ�
   // Ǯ������ ������ ������ ����ϰ�, solveHidato���� ���Ŀ� �� �Լ��� �����Ѵٸ� 
   // �ַ���� ��µ˴ϴ�.
void printPuzzle() {
	for (vector<int>& row : hidatoBoard) {
		for (int &c : row) {
			if (c == -1)
				cout << " + ";
			else
				printf(c > 0 ? "%2d " : "__ ", c);
		}
		cout << endl;
	}
}

#endif
#pragma once
