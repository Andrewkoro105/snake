#include "field.h"
#include <stdlib.h>
#include <math.h>
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <winuser.h>

Field::Field()
{
    for (int x = 0; x < FWidth; x++)
    {
        for (int y = 0; y < FHeight; y++)
        {
            field[x][y] = 0;
        }
    }
    direction.x = 1;

    field[1][1] = 1;

    snake[0].x = 1;
    snake[0].y = 1;
    ///////
    field[0][1] = 1;

    snake[1].x = 0;
    snake[1].y = 1;
    //////
    field[5][1] = 2;
}

void Field::Rendering()
{
    float unit = 0.2f;
    float unit2 = 0.02f;

    for (int x = 0; x <= FWidth; x++)
    {
        for (int y = 0; y <= FHeight; y++)
        {
            int i = field[x][y];
            if (i != 0)
            {
                glBegin(GL_TRIANGLE_FAN);

                switch (i)
                {
                case 1:
                    unit2 = 0.01f;
                    glColor3f(0, 1, 0);
                    break;
                case 2:
                    unit2 = 0.05f;
                    glColor3f(1, 0, 0);
                    break;
                }

                glVertex2f(-1 + x * unit + unit2, -1 + y * unit + unit2);
                glVertex2f(-1 + x * unit + unit2, -1 + y * unit + unit - unit2);
                glVertex2f(-1 + x * unit + unit - unit2, -1 + y * unit + unit - unit2);
                glVertex2f(-1 + x * unit + unit - unit2, -1 + y * unit + unit2);

                glEnd();
            }

        }
    }

}

void Field::Input()
{
         if (GetAsyncKeyState(VK_UP)    & 0x01) { direction.x =  0;  direction.y =  1; }
    else if (GetAsyncKeyState(VK_LEFT)  & 0x01) { direction.x = -1;  direction.y =  0; }
    else if (GetAsyncKeyState(VK_DOWN)  & 0x01) { direction.x =  0;  direction.y = -1; }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x01) { direction.x =  1;  direction.y =  0; }
}

bool Field::checkingSpawnFood(int x, int y)
{
    for (int i = 0; i < length; i++)
        if (snake[i].x == x && snake[i].y == y) return true;
    return false;
}

bool Field::logic()
{
        int x = 0;
        int y = 0;
    Input();

    if ((snake[0].x + direction.x == -1 || snake[0].x + direction.x == 10) || (snake[0].y + direction.y == -1 || snake[0].y + direction.y == 10))
        return false;

    switch (field[snake[0].x + direction.x][snake[0].y + direction.y])
    {
    case 2:
            x = rand() % 10;
            y = rand() % 10;
        while (checkingSpawnFood(x, y))
        {
            if (x == 9)
            {
                x = 0;
                y = ((y == 9) ? 0 : y + 1);
            }
            else
                x++;
        }

        length++;
        field[x][y] = 2;
        break;
    case 1:
        return false;
    }

    if (field[snake[0].x + direction.x][snake[0].y + direction.y] == 2)
    {
        
    }
    field[snake[length-1].x][snake[length-1].y] = 0;

    for (int i = length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    snake[0].x += direction.x;
    snake[0].y += direction.y;
    field[snake[0].x][snake[0].y] = 1;

    return true;
}