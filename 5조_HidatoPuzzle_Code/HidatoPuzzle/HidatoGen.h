#ifndef __HidatoGen_H__
#define __HidatoGen_H__

#include "Hidato.h"

typedef struct Point {
	int x, y;
}point;

// 8 ���� ����Ʈ ����ü �迭�Դϴ�.
point direction[8] = { { -1, -1 },{ 1, -1 },{ 1, -1 },{ 1, 0 },{ 1, 1 },{ 0, 1 },{ -1, 1 },{ -1, 0 } };

int puzzle[MAXSIZE][MAXSIZE], path[MAXSIZE][MAXSIZE];
int arr[MAXN];
int N = 0;
int width, height;
point start;

void SetStartingPoint();
int Generate(int width, int height, point pos, int cnt, int N);

// ���Ͻ�Ʈ���� ���� �ʺ�, ���� �� �� ������ �Է¹޽��ϴ�.
void MapIn(ifstream& input)
{
	input >> width >> height;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			input >> puzzle[i][j];
			//���� 1(���ڰ� �� �� �ִ� �ڸ�)�̶��, ���� ī��Ʈ N ������ŵ�ϴ�.
			if (puzzle[i][j] == 1)
				N++;
			//�湮�ߴ��� �ƴ����� ǥ���ϴ� path 2���� �迭�� 0���� �ʱ�ȭ �մϴ�.
			path[i][j] = 0;
		}
	}

	//arr�� �Է��ؾ��ϴ� ���� sequence ������ �����ϴ� �迭�Դϴ�.
	for (int i = 0; i <= N; i++)
		arr[i] = 1;

	//������ �������� �����ϴ� �޼ҵ带 ȣ���մϴ�.
	SetStartingPoint();

}

void SetStartingPoint()
{

	//������ �����մϴ�
	srand(time(NULL));

	while (true)
	{
		//width * height ũ���� �����ǿ��� ������ ��ǥ  x,y�� ����, ���� �� �ڸ��� 1�̶��(���ڸ� ���� �� �ִ� ĭ�̸�) �ݺ����� �����մϴ�.
		start.x = rand() % width;
		start.y = rand() % height;
		if (puzzle[start.x][start.y] == 1)
			break;
	}
}

void GeneratePuzzle()
{
	//�����ǿ� ��� ��ĭ�� �������� �������� ������ �����մϴ�.
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


	//������� ���� 1�� �ְ�, üũ�� ���� path�� 1�� ǥ���մϴ�.
	path[start.x][start.y] = 1;
	puzzle[start.x][start.y] = 1;

	//1���� N���� ���ڸ� ä�������� �Լ��� ȣ���մϴ�.
	Generate(width, height, start, 1, N);
}

int Generate(int width, int height, point pos, int count, int N)
{
	int i;
	point next;

	//N������ �����ڰ� �����ǿ� ���ٸ� return 1
	if (count == N)
		return 1;

	for (i = 0; i < 8; i++)
	{
		//next point�� ���� 8�������� �̵��Ͽ��� �� ��ǥ�Դϴ�.
		next.x = pos.x + direction[i].x;
		next.y = pos.y + direction[i].y;

		//next point�� width�� height�� ������� �ȵǰ�, �ش� ��ǥ�� path�� 1�̸� �ȵǸ�(�̹� �湮�� ĭ�� �ƴϸ�), �ش� ��ǥ���� ���� ����� �մϴ�.
		if (next.x >= 0 && next.x < width &&
			next.y >= 0 && next.y < height &&
			path[next.x][next.y] != 1 &&
			puzzle[next.x][next.y] != 0)
		{
			//�׷��ٸ� path�� �湮������ ǥ���մϴ�.
			path[next.x][next.y] = 1;

			// ������ ���� �� ������ arr ���� 0�̶�� �ش� ī��Ʈ ���ڴ� �����ǿ� �����ʰ� ���ڰ� ���� ��ĭ���� ���ܵӴϴ� (-1)
			if (arr[count + 1] == 0)
				puzzle[next.x][next.y] = -1;

			// ���� 1�̶�� , �� �ڸ����� �ش��ϴ� ���ڸ� ä���־��ݴϴ�.
			else
				puzzle[next.x][next.y] = count + 1;

			//���� next point�� ���� recusrive�ϰ� generate�� ȣ���ϰ�, true�� ���ϵǾ��ٸ� count == N�̶�� ���̹Ƿ� return �� �Լ� �����մϴ�.
			if (Generate(width, height, next, count + 1, N))
				return 1;

			//���� �Ŀ��� true�� ���ϵ��� �ʾҴٸ� false��� ���̹Ƿ� �� path�� �ٽ� �湮�� �� �ְ� �湮ǥ�ø� �����ݴϴ�.
			path[next.x][next.y] = 0;
		}
	}
	return 0;
}

void MapOut(ofstream& output)
{
	// �ϼ��� �� ������ ���Ϸ� ����մϴ�.
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