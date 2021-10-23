
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <vector>
#include "field.h"
#include <Windows.h>
#include <winuser.h>
#include <stdio.h>

using namespace std;
const int Width = 600;
const int Height = 600;

char* toString(int Value);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit())
    {
        glfwTerminate();
        return -1;
    }

    Field pole;

    bool stop = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (!stop)
        {
            Sleep(300 * (-1 / 14000 * pow(pole.length - 1, 2) + 1));

            /* Render here */
            glClearColor(0, 0, 0, 0);

            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

            if (!pole.logic()) break;
            pole.Rendering();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            glfwSetWindowTitle(window, toString(pole.length - 2));

            
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x01) return 2;
        stop = GetAsyncKeyState(VK_RETURN) & 0x01? !stop : stop;
    }

    glfwTerminate();

    glfwSetWindowShouldClose(window, GL_TRUE);

    system("cls");


    std::cout << "delete a record -> d" << '\n' << "exit -> Esc" << "\n-------------\n" << "record: " << pole.Save() << '\n' << "result: " << pole.length - 2 << '\n' << "restart:" << '\n' ;

    Sleep(500);
    for (int i = 3; i >= 1; i--)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x01) return 2;
        else if (GetAsyncKeyState(VK_RETURN) & 0x01) break;
        else if (GetAsyncKeyState(0x44) & 0x01)
        {
            remove("record.txt");
            std::cout << "record deleted" << '\n';
        }
        std::cout << (char)(i + 48) << '\n';
        Sleep(1000);
    }

    main();
}


char* toString(int Value)
{
    char str[] = "snake -> 000";

    int Val1 = Value / 100 + 48;
    int Val2 = (Value % 100) / 10 + 48;
    int Val3 = Value % 10 + 48;

    str[9] = Val1;
    str[10] = Val2;
    str[11] = Val3;

    return str;
}

