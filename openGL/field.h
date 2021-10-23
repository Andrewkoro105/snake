#pragma once


class Field
{
public:
	Field();
	void Rendering();
	int Save();
	bool logic();
	void del();

	int length = 2;

private:
	struct cell
	{
		int x = 0;
		int y = 0;
	};
	const int FWidth = 10;
	const int FHeight = 10;
	cell snake[100];
	int field[10][10];
	cell direction;

	void Input();
	bool checkingSpawnFood(int x, int y);
};

