#ifndef __HidatoGen_H__
#define __HidatoGen_H__

#include "Hidato.h"

typedef struct Point {
	int x, y;
}point;

// 8 방향 포인트 구조체 배열입니다.
point direction[8] = { { -1, -1 },{ 1, -1 },{ 1, -1 },{ 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 },{ -1, 0 } };

int puzzle[MAXSIZE][MAXSIZE], path[MAXSIZE][MAXSIZE];
int arr[MAXN];
int N = 0;
int width, height;
point start;

void SetStartingPoint();
int Generate(int width, int height, point pos, int cnt, int N);

// 파일스트림을 통해 너비, 길이 및 벽 데이터 입력받습니다.
void MapIn(ifstream& input)
{
	input >> width >> height;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			input >> puzzle[i][j];
			//만약 1(숫자가 들어갈 수 있는 자리)이라면, 숫자 카운트 N 증가시킵니다.
			if (puzzle[i][j] == 1)
				N++;
			//방문했는지 아닌지를 표시하는 path 2차원 배열은 0으로 초기화 합니다.
			path[i][j] = 0;
		}
	}

	//arr은 입력해야하는 수의 sequence 범위를 저장하는 배열입니다.
	for (int i = 0; i <= N; i++)
		arr[i] = 1;

	//임의의 시작점을 설정하는 메소드를 호출합니다.
	SetStartingPoint();

}

void SetStartingPoint()
{

	//난수를 생성합니다
	srand(time(NULL));

	while (true)
	{
		//width * height 크기의 퍼즐판에서 임의의 좌표  x,y를 선택, 만약 그 자리가 1이라면(숫자를 넣을 수 있는 칸이면) 반복문을 종료합니다.
		start.x = rand() % width;
		start.y = rand() % height;
		if (puzzle[start.x][start.y] == 1)
			break;
	}
}

void GeneratePuzzle()
{
	//퍼즐판에 몇개의 빈칸을 남길지를 랜덤으로 범위를 제한합니다.
	int index = 1;
	while (index < N)
	{
		int ranNum = rand() % 4 + 1; // 1~4
		for (int i = 1; i <= ranNum; i++)
		{
			index++;
			if (index >= N)
				break;
			arr[index] = 0;
		}
		index++;
	}


	//출발점에 숫자 1을 넣고, 체크를 위한 path에 1을 표시합니다.
	path[start.x][start.y] = 1;
	puzzle[start.x][start.y] = 1;

	//1부터 N까지 숫자를 채워나가는 함수를 호출합니다.
	Generate(width, height, start, 1, N);
}

int Generate(int width, int height, point pos, int count, int N)
{
	int i;
	point next;

	//N까지의 모든숫자가 퍼즐판에 들어갔다면 return 1
	if (count == N)
		return 1;

	for (i = 0; i < 8; i++)
	{
		//next point는 주위 8방향으로 이동하였을 때 좌표입니다.
		next.x = pos.x + direction[i].x;
		next.y = pos.y + direction[i].y;

		//next point는 width와 height을 벗어나서는 안되고, 해당 좌표의 path가 1이면 안되며(이미 방문한 칸이 아니며), 해당 좌표에는 벽이 없어야 합니다.
		if (next.x >= 0 && next.x < width &&
			next.y >= 0 && next.y < height &&
			path[next.x][next.y] != 1 &&
			puzzle[next.x][next.y] != 0)
		{
			//그렇다면 path에 방문했음을 표시합니다.
			path[next.x][next.y] = 1;

			// 다음에 들어가야 할 숫자의 arr 값이 0이라면 해당 카운트 숫자는 퍼즐판에 넣지않고 숫자가 들어가는 빈칸으로 남겨둡니다 (-1)
			if (arr[count + 1] == 0)
				puzzle[next.x][next.y] = -1;

			// 만약 1이라면 , 그 자리에는 해당하는 숫자를 채워넣어줍니다.
			else
				puzzle[next.x][next.y] = count + 1;

			//다음 next point에 대해 recusrive하게 generate를 호출하고, true가 리턴되었다면 count == N이라는 뜻이므로 return 후 함수 종료합니다.
			if (Generate(width, height, next, count + 1, N))
				return 1;

			//위의 식에서 true가 리턴되지 않았다면 false라는 뜻이므로 이 path에 다시 방문할 수 있게 방문표시를 지워줍니다.
			path[next.x][next.y] = 0;
		}
	}
	return 0;
}

void MapOut(ofstream& output)
{
	// 완성된 맵 형식을 파일로 출력합니다.
	output << width << ' ' << height << endl;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			output << puzzle[i][j] << " ";
		}
		output << endl;
	}
}

#endif
#pragma once