#ifndef __HidatoSol_H__
#define __HidatoSol_H__

#include "Hidato.h"

//두 객체를 묶어 하나의 객체로 취급해주는 pair타입으로 시작점을 저장해둡니다.
pair<int, int> startPoint;

//히다토 퍼즐 보드의 정보가 저장된 벡터입니다.
vector<vector<int>> hidatoBoard;
//input에서 입력된 숫자들을 저장해두는 벡터입니다.
vector<int> inputNum;
void initHidato(vector<string>& input, int row, int col)
{
	//퍼즐의 행,렬 크기 
	int nRows = row;
	int nCols = col;

	//스트링 타입을 담는 벡터를 원소로 갖는 puzzle을 생성합니다. 행 한줄 한줄을 원소로 담고 있습니다
	vector<vector<string>> puzzle(nRows);

	for (int i = 0; i < nRows; i++)
	{
		//스트링을 입력받아 다른 형식으로 바꿔주는 istringstream을 선언합니다
		istringstream ss(input[i]);
		string str;
		//input파일의 1행부터 str에 받아 모두 puzzle에 push합니다.
		while (ss >> str)
			puzzle[i].push_back(str);
	}

	//퍼즐의 테두리 벽을 표시 하기 위해 상하좌우 한줄씩을 추가해줍니다.
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
		//puzzle에 담긴 r번째 원소(행 한줄)을 row에 담아놓습니다
		vector<string> row = puzzle[r];

		for (int c = 0; c < nCols; c++)
		{
			//r과 c에 1씩 더하는 이유는 테두리 한줄을 빼고 안에 보드를 채우기 때문입니다
			//해당 줄의 스트링 한자 한자를 element에 담습니다
			string element = row[c];
			//해당 스트링이 -1이라면 히다토퍼즐을 풀어야 할 빈칸입니다
			if (element == "-1")
				hidatoBoard[r + 1][c + 1] = 0;
			//0이라면 벽으로 간주합니다
			else if (element == "0")
				continue;
			//앞의 숫자 이외에 다른 숫자라면 스트링을 int로 변환하여 히다토보드배열에 해당 숫자를 집어넣습니다.
			else
			{
				int val = stoi(element);
				hidatoBoard[r + 1][c + 1] = val;
				//input파일에서 주어진 숫자를 담아놓는 벡터인 inputNum에 해당 숫자를 담아놓습니다.
				inputNum.push_back(val);
				//해당 숫자가 1이라면 이 점을 히다토퍼즐의 시작점으로 설정합니다.
				if (val == 1)
				{
					startPoint.first = r + 1;
					startPoint.second = c + 1;
				}
			}
		}
	}

	sort(inputNum.begin(), inputNum.end());
	// input파일에 들어있는 숫자들을 정렬해놓습니다.
}
// 히다토 퍼즐을 풀 수 있는지 8방향으로 탐색합니다.
   // 가장 처음에는 시작점 (숫자가 1인 지점)부터 탐색을 시작합니다.
bool solveHidato(int r, int c, int n, int next)
{
	//현재 숫자가 주어진 숫자의 max값보다 크면 탐색 종료
	if (n > inputNum[inputNum.size() - 1])
		return true;
	//탐색하려는 곳이 0(빈칸)이 아니고 현재의 숫자가 아니라면 해당 칸으로는
	   //탐색 불가
	if (hidatoBoard[r][c] != 0 && hidatoBoard[r][c] != n)
		return false;
	//탐색하려는 곳이 0(빈칸)이고, 주어진 숫자 벡터의 next번째가 현재 숫자라면
	//탐색불가
	if (hidatoBoard[r][c] == 0 && inputNum[next] == n)
		return false;

	//탐색하려는 곳을 lastPoint에 저장해둡니다
	int lastPoint = hidatoBoard[r][c];
	//탐색하려는 곳과 현재 숫자가 같다면 다음 탐색지점을 탐색.
	if (lastPoint == n)
		next++;
	//해당 점에 숫자 표시
	hidatoBoard[r][c] = n;
	//8방향으로 위의 과정을 recursive하게 호출해서 확인합니다.
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			//퍼즐이 끝났다면 끝
			if (solveHidato(r + i, c + j, n + 1, next))
				return true;
	//8방향중 아무곳으로도 갈 수가 없을때는 저장해둔 lastPoint로 돌아갑니다
	hidatoBoard[r][c] = lastPoint;

	return false;
}
// 히다토 퍼즐 board를 출력하는 함수입니다. 인풋파일을 입력받은 직후에 실행했다면
   // 풀기전의 히다토 퍼즐을 출력하고, solveHidato실행 이후에 이 함수를 실행한다면 
   // 솔루션이 출력됩니다.
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
