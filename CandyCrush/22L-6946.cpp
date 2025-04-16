#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.graphics.h>
#include<stdio.h>
#include<Windows.h>
#include"22L-6946.h"
using namespace std;
int score = 0;

//Numbers print
//Number at Tens Place
void num1(int x) {
    int s = 0;
    if (x == 0)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 1)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 2)
    {
        name(1000 + s, 250, 1050, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
    }
    else if (x == 3)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 4)
    {
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 5)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 6)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 7)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);

    }
    else if (x == 8)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (x == 9)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);

    }

}
//Number at Units Place
void num2(int y)
{
    int s = 100;
    if (y == 0)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 1)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 2)
    {
        name(1000 + s, 250, 1050, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
    }
    else if (y == 3)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 4)
    {
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 5)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 6)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 7)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);

    }
    else if (y == 8)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 9)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);

    }

}
void num3(int y)
{
    int s = -120;
    if (y == 0)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 1)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 2)
    {
        name(1000 + s, 250, 1050, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
    }
    else if (y == 3)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 4)
    {
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 5)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 6)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 7)
    {
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);

    }
    else if (y == 8)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 300, 1000 + s, 350, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 300, 0, 0, 0);
        name(1050 + s, 300, 1050 + s, 350, 0, 0, 0);
    }
    else if (y == 9)
    {
        name(1000 + s, 250, 1050 + s, 250, 0, 0, 0);
        name(1050 + s, 250, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 300, 1050 + s, 300, 0, 0, 0);
        name(1000 + s, 350, 1050 + s, 350, 0, 0, 0);
        name(1000 + s, 250, 1000 + s, 300, 0, 0, 0);

    }

}

void scoretype()
{
    //SCORE TYPING
    name(800, 100, 850, 100, 255, 255, 0); //S
    name(800, 100, 800, 150, 255, 255, 0);
    name(800, 150, 850, 150, 255, 255, 0);
    name(850, 150, 850, 200, 255, 255, 0);
    name(800, 200, 850, 200, 255, 255, 0);

    name(900, 100, 950, 100, 255, 255, 0); //C
    name(900, 100, 900, 200, 255, 255, 0);
    name(900, 200, 950, 200, 255, 255, 0);

    name(1000, 100, 1050, 100, 255, 255, 0);//O
    name(1000, 200, 1050, 200, 255, 255, 0);
    name(1000, 100, 1000, 200, 255, 255, 0);
    name(1050, 100, 1050, 200, 255, 255, 0);

    name(1100, 100, 1150, 100, 255, 255, 0); //R
    name(1100, 150, 1150, 150, 255, 255, 0);
    name(1100, 100, 1100, 200, 255, 255, 0);
    name(1150, 100, 1150, 150, 255, 255, 0);
    name(1100, 150, 1150, 200, 255, 255, 0);

    name(1200, 100, 1200, 200, 255, 255, 0); //E
    name(1200, 100, 1250, 100, 255, 255, 0);
    name(1200, 150, 1250, 150, 255, 255, 0);
    name(1200, 200, 1250, 200, 255, 255, 0);
}

//function calling above two functions for numbers
void score_print(int num)
{
    scoretype();
    myRectangle(850, 245, 1200, 355, 77, 210, 255, 77, 210, 255);
    //Score counter
    int i = 0;
    int rem;
    rem = num % 10;
    num2(rem);
    num = num / 10;
    rem = num % 10;
    num1(rem);
    num = num / 10;
    rem = num % 10;
    num3(rem);
    name(1000 - 60, 250, 1050 - 60, 250, 77, 210, 255);
}


bool check3or4(int arr[][8], int p, int q)
{
    bool check = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] - 5 == arr[i + 1][j] && arr[i][j] - 5 == arr[i + 2][j])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;


                        if (arr[i + 1][j] == arr[i][j])
                        {
                            while (arr[i][j] == arr[i + 2][j])
                            {
                                arr[i + 2][j] = (rand() % 5) + 1;
                            }
                        }
                        check = 1;

                    }
                }
            }


            for (int i = 1; i < 7; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] - 5 == arr[i + 1][j] && arr[i][j] - 5 == arr[i - 1][j])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;
                        if (arr[i + 1][j] == arr[i][j])
                        {
                            while (arr[i - 1][j] == arr[i + 1][j])
                            {
                                arr[i - 1][j] = (rand() % 5) + 1;
                            }
                        }
                        check = 1;

                    }
                }
            }



            for (int i = 2; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] - 5 == arr[i - 1][j] && arr[i][j] - 5 == arr[i - 2][j])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;
                        if (arr[i][j] == arr[i - 1][j])
                        {
                            while (arr[i][j] == arr[i - 2][j])
                            {
                                arr[i - 2][j] = (rand() % 5) + 1;
                            }
                        }
                        check = 1;

                    }
                }
            }

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    if (arr[i][j] - 5 == arr[i][j + 1] && arr[i][j] - 5 == arr[i][j + 2])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;
                        if (arr[i][j + 1] == arr[i][j])
                        {
                            while (arr[i][j + 2] == arr[i][j])
                            {
                                arr[i][j + 2] = (rand() % 5) + 1;
                            }
                        }
                        check = 1;

                    }
                }
            }



            for (int i = 0; i < 8; i++)
            {
                for (int j = 1; j < 7; j++)
                {
                    if (arr[i][j] - 5 == arr[i][j + 1] && arr[i][j] - 5 == arr[i][j - 1])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;
                        if (arr[i][j + 1] == arr[i][j])
                        {
                            while (arr[i][j] == arr[i][j - 1])
                            {
                                arr[i][j] = (rand() % 5) + 1;
                            }
                        }

                        check = 1;

                    }
                }
            }



            for (int i = 0; i < 8; i++)
            {
                for (int j = 2; j < 8; j++)
                {
                    if (arr[i][j] - 5 == arr[i][j - 1] && arr[i][j] - 5 == arr[i][j - 2])
                    {
                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j - 1] = (rand() % 5) + 1;
                        arr[i - 1][j] = (rand() % 5) + 1;
                        arr[i - 1][j + 1] = (rand() % 5) + 1;
                        arr[i - 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 1][j - 1] = (rand() % 5) + 1;
                        arr[i + 1][j + 1] = (rand() % 5) + 1;
                        if (arr[i][j - 1] == arr[i][j])
                        {
                            while (arr[i][j - 2] == arr[i][j])
                            {
                                arr[i][j - 2] = (rand() % 5) + 1;
                            }
                        }
                        check = 1;

                    }
                }
            }



            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i][j + 3])
                    {
                        check = 1;
                        if (arr[i][j] == 1)
                        {
                            arr[p][q] = 6;
                        }
                        else if (arr[i][j] == 2)
                        {
                            arr[p][q] = 7;
                        }
                        else if (arr[i][j] == 3)
                        {
                            arr[p][q] = 8;
                        }
                        else if (arr[i][j] == 4)
                        {
                            arr[p][q] = 9;
                        }
                        else if (arr[i][j] == 5)
                        {
                            arr[p][q] = 10;
                        }
                        if (q != 0)
                        {
                            arr[i][0] = (rand() % 5) + 1;
                        }

                        if (q != 1)
                        {
                            arr[i][1] = (rand() % 5) + 1;
                        }
                        if (q != 2)
                        {
                            arr[i][2] = (rand() % 5) + 1;
                        }
                        if (q != 3)
                        {
                            arr[i][3] = (rand() % 5) + 1;
                        }
                        if (q != 4)
                        {
                            arr[i][4] = (rand() % 5) + 1;
                        }
                        if (q != 5)
                        {
                            arr[i][5] = (rand() % 5) + 1;
                        }
                        if (q != 6)
                        {
                            arr[i][6] = (rand() % 5) + 1;
                        }
                        if (q != 7)
                        {
                            arr[i][7] = (rand() % 5) + 1;
                        }
                        if (q != 8)
                        {
                            arr[i][8] = (rand() % 5) + 1;
                        }
                        if (arr[i][j + 1] == arr[i][j])
                        {
                            while (arr[i][j + 2] == arr[i][j])
                            {
                                arr[i][j + 2] = (rand() % 5) + 1;
                            }
                        }
                        score = score + 10;


                    }
                }
            }
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 6; j++)
                {

                    if (arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
                    {

                        check = 1;

                        arr[i][j] = (rand() % 5) + 1;
                        arr[i][j + 1] = (rand() % 5) + 1;
                        arr[i][j + 2] = (rand() % 5) + 1;
                        if (arr[i][j + 1] == arr[i][j])
                        {
                            while (arr[i][j + 2] == arr[i][j])
                            {
                                arr[i][j + 2] = (rand() % 5) + 1;
                            }
                        }

                        int n = j;


                        n = n - 1;
                        int a = n;
                        int b = n + 1;
                        int b1 = n + 1;
                        int c = n + 2;
                        int c1 = n + 2;
                        int temp = 0;

                        for (int l = 0; l < a; l++)
                        {
                            temp = arr[i][n];
                            arr[i][n] = arr[i][n - 1];
                            arr[i][n - 1] = temp;

                            n--;
                        }
                        for (int l = 0; l < b; l++)
                        {
                            temp = arr[i][b1];
                            arr[i][b1] = arr[i][b1 - 1];
                            arr[i][b1 - 1] = temp;

                            b1--;
                        }
                        for (int l = 0; l < c; l++)
                        {
                            temp = arr[i][c1];
                            arr[i][c1] = arr[i][c1 - 1];
                            arr[i][c1 - 1] = temp;

                            c1--;
                        }



                        score = score + 5;

                    }
                }
            }
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j] && arr[i][j] == arr[i + 3][j])
                    {
                        check = 1;
                        if (arr[i][j] == 1)
                        {
                            arr[p][q] = 6;
                        }
                        else if (arr[i][j] == 2)
                        {
                            arr[p][q] = 7;
                        }
                        else if (arr[i][j] == 3)
                        {
                            arr[p][q] = 8;
                        }
                        else if (arr[i][j] == 4)
                        {
                            arr[p][q] = 9;
                        }
                        else if (arr[i][j] == 5)
                        {
                            arr[p][q] = 10;
                        }
                        if (p != 0)
                        {
                            arr[0][j] = (rand() % 5) + 1;
                        }
                        if (p != 1)
                        {
                            arr[1][j] = (rand() % 5) + 1;
                        }
                        if (p != 2)
                        {
                            arr[2][j] = (rand() % 5) + 1;
                        }
                        if (p != 3)
                        {
                            arr[3][j] = (rand() % 5) + 1;
                        }
                        if (p != 4)
                        {
                            arr[4][j] = (rand() % 5) + 1;
                        }
                        if (p != 5)
                        {
                            arr[5][j] = (rand() % 5) + 1;
                        }
                        if (p != 6)
                        {
                            arr[6][j] = (rand() % 5) + 1;
                        }
                        if (p != 7)
                        {
                            arr[7][j] = (rand() % 5) + 1;
                        }
                        if (p != 8)
                        {
                            arr[8][j] = (rand() % 5) + 1;
                        }
                        if (arr[i + 1][j] == arr[i][j])
                        {
                            while (arr[i][j] == arr[i + 2][j])
                            {
                                arr[i + 2][j] = (rand() % 5) + 1;
                            }
                        }


                        score = score + 10;

                    }
                }
            }
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                {

                    if (arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
                    {

                        check = 1;


                        arr[i][j] = (rand() % 5) + 1;
                        arr[i + 1][j] = (rand() % 5) + 1;
                        arr[i + 2][j] = (rand() % 5) + 1;
                        if (arr[i + 1][j] == arr[i][j])
                        {
                            while (arr[i][j] == arr[i + 2][j])
                            {
                                arr[i + 2][j] = (rand() % 5) + 1;
                            }
                        }


                        int n = j + 1;


                        n = n - 1;
                        int a = n;
                        int b = n + 1;
                        int b1 = n + 1;
                        int c = n + 2;
                        int c1 = n + 2;
                        int temp = 0;

                        for (int l = 0; l < a; l++)
                        {
                            temp = arr[i][n];
                            arr[i][n] = arr[i][n - 1];
                            arr[i][n - 1] = temp;

                            n--;
                        }
                        for (int l = 0; l < b; l++)
                        {
                            temp = arr[i][b1];
                            arr[i][b1] = arr[i][b1 - 1];
                            arr[i][b1 - 1] = temp;

                            b1--;
                        }
                        for (int l = 0; l < c; l++)
                        {
                            temp = arr[i][c1];
                            arr[i][c1] = arr[i][c1 - 1];
                            arr[i][c1 - 1] = temp;

                            c1--;
                        }



                        score = score + 5;

                    }
                }
            }
        }
    }
    return check;

}

//to_check_randomized value firstly in the grid
void check_randomizedvalue(int candy[][8])
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (candy[i][j + 1] == candy[i][j])
            {
                while (candy[i][j + 2] == candy[i][j])
                {
                    candy[i][j + 2] = (rand() % 5) + 1;
                }
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (candy[i + 1][j] == candy[i][j])
            {
                while (candy[i + 2][j] == candy[i][j])
                {
                    candy[i + 2][j] = (rand() % 5) + 1;
                }
            }
        }
    }
}
//GRID MAKING
void grid()
{
    int x1 = 100, x2 = 175, y1 = 50, y2 = 125;
    myRectangle(100 - 30, 50 - 30, 700 + 30, 650 + 30, 0, 0, 0, 102, 51, 0); //Grid Outline
    myRectangle(100, 50, 175, 125, 0, 0, 0, 230, 255, 255);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            myRectangle(x1, y1, x2, y2, 0, 0, 0, 0, 0, 0);
            x1 = x1 + 75;
            x2 = x2 + 75;
        }
        y1 = y1 + 75;
        y2 = y2 + 75;
        x1 = 100, x2 = 175;
    }
}
//Candy Making
void draw_singlecandy(int candy[][8])
{
    int x = 120, y = 70;
    for (int i = 0, x = 120; i < 8; i++, x = x + 75)
    {

        for (int j = 0, y = 70; j < 8; j++, y = y + 75)
        {
            if (candy[i][j] == 1)
            {
                squarecandy(x, y, x + 35, y + 35, 0, 255, 255); //Cyan Candy(Square)
            }
            else if (candy[i][j] == 0)
            {
                squarecandy(x, y, x + 35, y + 35, 0, 0, 0); //Black Block
            }
            else if (candy[i][j] == 2)
            {
                myEllipse(x, y, x + 35, y + 35, 204, 0, 204, 0, 0, 0); //Purple Candy(Circle)
            }
            else if (candy[i][j] == 3)
            {
                ellipsecandy(x + 10, y, x + 25, y + 40, 255, 255, 0); //Yellow candy(Ellipse)
            }
            else if (candy[i][j] == 4)
            {
                myLine(x, y, x + 35, y + 35, 0, 255, 0);// Green candy(Cross)
                myLine(x + 35, y, x, y + 35, 0, 255, 0);
            }
            else if (candy[i][j] == 5)
            {
                mytriangle(x, y, x + 35, y + 35, 0, 0, 204, 0, 0, 0); //Blue candy(Triangle)
            }
            else if (candy[i][j] == 6)
            {
                squarecandy(x, y, x + 35, y + 35, 0, 255, 255); //Cyan candy(Special)
                myLine(x + 17.5, y, x, y + 17.5, 0, 255, 255);
                myLine(x + 17.5, y, x + 34, y + 17, 0, 255, 255);
                myLine(x, y + 17.5, x + 17.5, y + 34, 0, 255, 255);
                myLine(x + 34, y + 17.5, x + 17.5, y + 34, 0, 255, 255);
            }
            else if (candy[i][j] == 7)
            {
                myEllipse(x, y, x + 35, y + 35, 204, 0, 204, 0, 0, 0);
                myEllipse(x + 10, y + 10, x + 25, y + 25, 204, 0, 204, 0, 0, 0);//Purple Candy(Special)
            }
            else if (candy[i][j] == 8)
            {
                ellipsecandy(x - 5, y + 15, x + 40, y + 25, 255, 255, 0); //Yellow candy(Special)
                ellipsecandy(x + 10, y, x + 25, y + 40, 255, 255, 0);
            }
            else if (candy[i][j] == 9)
            {
                myLine(x, y, x + 35, y + 35, 0, 255, 0);// Green candy(Special)
                myLine(x + 35, y, x, y + 35, 0, 255, 0);
                myLine(x, y + 17.5, x + 35, y + 17.5, 0, 255, 0);
                myLine(x + 17.5, y, x + 17.5, y + 35, 0, 255, 0);
            }
            else if (candy[i][j] == 10)
            {
                mytriangle2(x, y + 10, x + 35, y + 40, 0, 0, 204, 0, 0, 0); //Blue candy(Special)
                mytriangle(x, y, x + 35, y + 35, 0, 0, 204, 0, 0, 0);
            }
        }
    }
}


//to print board
void print_board(int candy[][8])
{
    grid();
    draw_singlecandy(candy);
    score_print(score);
}

//to move the marker and swap
void marker(int candy[][8])//(int& x1, int& x2, int& y1, int& y2, int candy[][8]/, int& score_marker)/
{
    time_t oldTime = time(0);

    int x1 = 100, x2 = 175, y1 = 50, y2 = 125;
    x1 = 101, y1 = 49, x2 = 175, y2 = 125;
    int r = 0;
    int c = 0;
    mySquare(x1, y1, x2, y2, 255, 0, 0);
    while ((time(0) - oldTime) <= 30)
    {
        _getch();
        int cursor = 0;
        if (isCursorKeyPressed(cursor))
        {
            if (x2 < 700)
            {
                if (cursor == 3) //Right
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1 + 75, y1, x2 + 75, y2, 255, 0, 0);
                    x1 = x1 + 75; //New position of Red Block after it's moved to right
                    x2 = x2 + 75;
                    r++;
                }
            }
            if (x1 > 101)
            {
                if (cursor == 1) //Left
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1 - 75, y1, x2 - 75, y2, 255, 0, 0);
                    x1 = x1 - 75; //New position of Red Block after it's moved to  left
                    x2 = x2 - 75;
                    r--;
                }
            }
            if (y2 < 650)
            {
                if (cursor == 4) //Down
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1 + 75, x2, y2 + 75, 255, 0, 0);
                    y1 = y1 + 75;
                    y2 = y2 + 75;
                    c++;
                }
            }
            if (y1 > 50)
            {
                if (cursor == 2) //Up
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1 - 75, x2, y2 - 75, 255, 0, 0);
                    y1 = y1 - 75;
                    y2 = y2 - 75;
                    c--;
                }
            }

            if (cursor == 5 && x1 > 101)//for a
            {

                swap(candy[r][c], candy[r - 1][c]);

                int g = 0;
                int h = 0;
                g = r - 1;
                h = c;


                if (check3or4(candy, g, r) == 1)
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    print_board(candy);
                    x1 = x1 - 75;
                    x2 = x2 - 75;
                    mySquare(x1, y1, x2, y2, 255, 0, 0);


                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    r--;
                }
                else
                {

                    swap(candy[r][c], candy[r - 1][c]);
                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);

                }
            }
            if (cursor == 6 && y1 > 50)//for w
            {

                swap(candy[r][c], candy[r][c - 1]);


                int g = 0;
                int h = 0;
                g = r;
                h = c - 1;
                if (check3or4(candy, g, h) == 1)
                {
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    print_board(candy);
                    y1 = y1 - 75;
                    y2 = y2 - 75;
                    mySquare(x1, y1, x2, y2, 255, 0, 0);

                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    c--;
                }
                else
                {

                    swap(candy[r][c], candy[r][c - 1]);
                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);

                }
            }
            if (cursor == 7 && x2 < 700)//for d
            {

                swap(candy[r][c], candy[r + 1][c]);
                int g = 0;
                int h = 0;
                g = r + 1;
                h = c;

                if (check3or4(candy, g, h) == 1)
                {
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    print_board(candy);
                    x1 = x1 + 75;
                    x2 = x2 + 75;
                    mySquare(x1, y1, x2, y2, 255, 0, 0);


                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    r++;
                }
                else
                {

                    swap(candy[r][c], candy[r + 1][c]);
                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);

                }
            }
            if (cursor == 8 && y2 < 650)//for s
            {

                swap(candy[r][c], candy[r][c + 1]);
                int g = 0;
                int h = 0;
                g = r;
                h = c + 1;

                if (check3or4(candy, g, h) == 1)

                {
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    print_board(candy);
                    y1 = y1 + 75;
                    y2 = y2 + 75;
                    mySquare(x1, y1, x2, y2, 255, 0, 0);


                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);
                    c++;

                }
                else
                {

                    swap(candy[r][c], candy[r][c + 1]);;
                    print_board(candy);
                    mySquare(x1, y1, x2, y2, 0, 0, 0);
                    mySquare(x1, y1, x2, y2, 255, 0, 0);

                }
            }

        }
    }

}

void FrontEnd()
{
    //FRONTEND OF THE GAME
    //sky
    myRectangle(0, 1000, 1500, 0, 0, 0, 0, 77, 210, 255);
    //grass
    myRectangle(0, 1000, 1500, 560, 0, 204, 68, 0, 204, 68);
    //son
    myEllipse(600, 110 + 30, 600 + 300 - 100 - 100, 80 - 30, 255, 255, 0, 255, 255, 51);
    //cloud 0
    myRectangle(500 - 300 - 150, 200 - 50, 650 - 300 - 150, 150 - 50 + 10, 225, 225, 255, 225, 225, 255); //1 block
    myRectangle(520 - 300 - 150, 110, 630 - 300 - 150, 80, 225, 225, 255, 225, 225, 255); //2 block
    myRectangle(550 - 300 - 150, 80, 600 - 300 - 150, 50, 225, 225, 255, 225, 225, 255); //3 block
    //cloud 1
    myRectangle(500 - 150, 200 - 50, 650 - 150, 150 - 50 + 10, 225, 225, 255, 225, 225, 255); //1 block
    myRectangle(520 - 150, 110, 630 - 150, 80, 225, 225, 255, 225, 225, 255); //2 block
    myRectangle(550 - 150, 80, 600 - 150, 50, 225, 225, 255, 225, 225, 255); //3 block
    //cloud 2
    myRectangle(500 + 300, 200 - 50, 650 + 300, 150 - 50 + 10, 225, 225, 255, 225, 225, 255); //1 block
    myRectangle(520 + 300, 110, 630 + 300, 80, 225, 225, 255, 225, 225, 255); //2 block
    myRectangle(550 + 300, 80, 600 + 300, 50, 225, 225, 255, 225, 225, 255); //3 block
    //cloud 3
    myRectangle(500 + 300 + 300, 200 - 50, 650 + 300 + 300, 150 - 50 + 10, 225, 225, 255, 225, 225, 255); //1 block
    myRectangle(520 + 300 + 300, 110, 630 + 300 + 300, 80, 225, 225, 255, 225, 225, 255); //2 block
    myRectangle(550 + 300 + 300, 80, 600 + 300 + 300, 50, 225, 225, 255, 225, 225, 255); //3 block
    //Candy Screen
    myRectangle(300 - 30, 160 + 40 - 30, 1000 + 30, 450 + 40 + 30, 255, 0, 0, 255, 0, 0); //Boarder
    myRectangle(300, 160 + 40, 1000, 450 + 40, 255, 112, 77, 255, 187, 153); //Orange
    //MINGLE
    int m = 50, n = 20;
    name(350 + m, 250, 350 + m, 350, 0, 0, 0); //M
    name(430 + m, 250, 430 + m, 350, 0, 0, 0);
    name(350 + m, 250, 390 + m, 300, 0, 0, 0);
    name(390 + m, 300, 430 + m, 250, 0, 0, 0);
    name(470 + m, 250, 470 + m, 350, 0, 0, 0); //I
    m = 40;
    name(470 + m + m + n, 250, 470 + m + m + n, 350, 0, 0, 0); //N
    name(470 + m + m + m + 30 + n, 250, 470 + m + n + m + m + 30, 350, 0, 0, 0);
    name(470 + m + m + n, 250, 470 + m + m + m + n + 30, 350, 0, 0, 0);
    name(470 + m + m + m + n + 30 + 30, 250, 470 + m + n + m + m + 30 + 30, 350, 0, 0, 0); //G
    name(470 + m + m + n + m + 30 + 30, 250, 470 + m + n + m + m + 30 + 30 + 50, 250, 0, 0, 0);
    name(470 + m + m + n + m + 30 + 30, 350, 470 + m + n + m + m + 30 + 30 + 50, 350, 0, 0, 0);
    name(470 + m + m + n + m + 30 + 30 + 50, 300, 470 + m + n + m + m + 30 + 30 + 50, 350, 0, 0, 0);
    name(470 + m + m + n + m + 75, 300, 470 + m + m + m + n + 30 + 30 + 50, 300, 0, 0, 0);
    name(470 + m + m + n + m + 90 + 50, 250, 470 + m + m + n + m + 90 + 50, 350, 0, 0, 0); //L
    name(470 + m + m + n + m + 90 + 50, 350, 470 + m + m + n + m + 90 + 50 + 50, 350, 0, 0, 0);
    name(470 + m + m + n + m + 90 + 130, 250, 470 + m + m + n + m + 90 + 130, 350, 0, 0, 0); //E
    name(470 + m + m + n + m + 90 + 130, 250, 470 + m + m + n + m + 90 + 130 + 50, 250, 0, 0, 0);
    name(470 + m + m + n + m + 90 + 130, 300, 470 + m + m + n + m + 90 + 130 + 50, 300, 0, 0, 0);
    name(470 + m + m + n + m + 90 + 130, 350, 470 + m + m + n + m + 90 + 130 + 50, 350, 0, 0, 0);
    //Play Button
    myRectangle(650 + m + n, 400 - 10, 500 + m + n + 20, 470 + 10, 51, 51, 204, 51, 51, 204); //pink block
    myRectangle(650 + m + n + 10, 400, 500 + m + n + 10, 470, 255, 187, 153, 51, 51, 204);
    name(630, 410, 630, 460, 255, 255, 255); //PLAY
    name(630, 410, 660, 435, 255, 255, 255);
    name(630, 460, 660, 435, 255, 255, 255);
    //Game 
}

void Victory()
{
    //sky
    myRectangle(0, 1000, 1500, 0, 0, 0, 0, 77, 210, 255);
    //grass
    myRectangle(0, 1000, 1500, 560, 0, 204, 68, 0, 204, 68);
    //VICTORY
    Line(200 + 50, 150, 250 + 50, 350, 204, 51, 0); // V
    Line(250 + 50, 350, 300 + 50, 150, 230, 57, 0);
    Line(330 + 50, 150, 330 + 50, 350, 230, 57, 0); //I
    Line(370 + 50, 150, 370 + 50, 350, 204, 51, 0); //C
    Line(370 + 50, 150, 370 + 70 + 50, 150, 230, 57, 0);
    Line(370 + 50, 350, 370 + 70 + 50, 350, 230, 57, 0);
    Line(510 + 50, 150, 510 + 50, 350, 204, 51, 0); //T
    Line(470 + 50, 150, 550 + 50, 150, 230, 57, 0);
    O(560 + 50, 150, 660 + 50, 350, 204, 51, 0, 77, 210, 255); //O
    Line(700 + 50, 150, 700 + 50, 350, 204, 51, 0); //R
    Line(700 + 50, 150, 770 + 50, 150, 230, 57, 0);
    Line(770 + 50, 150, 770 + 50, 240, 204, 51, 0);
    Line(700 + 50, 240, 770 + 50, 240, 230, 57, 0);
    Line(700 + 50, 240, 780 + 50, 345, 230, 57, 0);
    Line(850 + 50, 240, 850 + 50, 350, 204, 51, 0); //Y
    Line(800 + 50, 150, 850 + 50, 240, 204, 51, 0);
    Line(900 + 50, 150, 850 + 50, 240, 230, 57, 0);
    Line(1000, 150, 1000, 350, 204, 51, 0);// !
    Line(1050, 150, 1050, 350, 204, 51, 0);
    // DOTS
    myEllipse(990, 365, 1010, 385, 230, 57, 0, 230, 57, 0);
    myEllipse(990 + 50, 365, 1010 + 50, 385, 230, 57, 0, 230, 57, 0);
}
void RIP()
{
    //sky
    myRectangle(0, 1000, 1500, 0, 0, 0, 0, 77, 210, 255);
    //grass
    myRectangle(0, 1000, 1500, 560, 0, 204, 68, 0, 204, 68);
    int s = 50;
    Line(700 - s - s - s - s, 150 + s, 700 - s - s - s - s, 350 + s, 204, 51, 0); //R
    Line(700 - s - s - s - s, 150 + s, 770 - s - s - s - s, 150 + s, 230, 57, 0);
    Line(770 - s - s - s - s, 150 + s, 770 - s - s - s - s, 240 + s, 204, 51, 0);
    Line(700 - s - s - s - s, 240 + s, 770 - s - s - s - s, 240 + s, 230, 57, 0);
    Line(700 - s - s - s - s, 240 + s, 780 - s - s - s - s, 345 + s, 230, 57, 0);
    Line(330 + 50 + s + s + s + s + s + 20, 150 + s, 330 + 50 + s + s + s + s + s + 20, 350 + s, 230, 57, 0); //I
    Line(700 + 50, 150 + s, 700 + 50, 350 + s, 204, 51, 0); //P
    Line(700 + 50, 150 + s, 770 + 50, 150 + s, 230, 57, 0);
    Line(770 + 50, 150 + s, 770 + 50, 240 + s, 204, 51, 0);
    Line(700 + 50, 240 + s, 770 + 50, 240 + s, 230, 57, 0);
}


//-------------------------------------MAIN----------------------------------------------

int main()
{

    FrontEnd();
    int start = 0;
    int candy[8][8] = { 0 };
    srand(time(0));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            candy[i][j] = rand() % 5 + 1;
        }
    }
    cin >> start;
    if (start == 1)
    {
        //sky
        myRectangle(0, 1000, 1500, 0, 0, 0, 0, 77, 210, 255);
        //grass
        myRectangle(0, 1000, 1500, 560, 0, 204, 68, 0, 204, 68);
        check_randomizedvalue(candy);
        print_board(candy);
        marker(candy);
    }
    if (score >= 150)
    {
        Victory();
    }
    else
    {
        RIP();
    }
    return 0;
}