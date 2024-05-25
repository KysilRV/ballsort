#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
 
void generator(const int rows, const int columns, char field[rows][columns])
{
    int col1, col2;
    col1 = rand() % columns;
    col2 = rand() % columns;
    while (col1 == col2) {
        col2 = rand() % columns;
    }
 
    for (int i = 0; i < rows; i++) {
        field[i][col1] = ' ';
        field[i][col2] = ' ';
    }
 
    char symbols[10] = {'*', '&', '+', '^', '$', '#', '%', '-', '=', '@'};
    int countArr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == col1 || j == col2) {
                continue;
            }
 
            int index = rand() % (columns - 2);
            if (countArr[index] < rows) {
                field[i][j] = symbols[index];
                countArr[index]++;
            } else {
                while (countArr[index] >= rows) {
                    index = rand() % (columns - 2);
                }
                field[i][j] = symbols[index];
                countArr[index]++;
            }
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    if (x == y || x > columns || y > columns || x < 1 || y < 1)
    {
        printf("Error\n");
    }
    else
    {
        char tmp = '\0';
        int getIndex = -1;
        for (int i = 0; i < rows; i++)
        {
            if (field[i][x - 1] != ' ')
            {
                tmp = field[i][x - 1];
                field[i][x - 1] = ' ';
                getIndex = i;
                break;
            }
        }
        if (tmp == '\0') {
            printf("Column for get is empty\n");
        } else {
            if (field[rows-1][y-1] == ' ') {
                // full column is empty
                field[rows-1][y-1] = tmp;
            } else if (field[0][y-1] != ' ') {
                printf("Column for set is full\n");
                field[getIndex][x - 1] = tmp;
                //
            } else {
                for (int i = 1; i < rows; i++) {
                    if (field[i][y-1] != ' ' && field[i][y-1] == tmp) {
                        field[i-1][y-1] = tmp;
                        break;
                    } else if (field[i][y-1] != ' ' && field[i][y-1] != tmp) {
                        field[getIndex][x - 1] = tmp;
                        break;
                    }
                }
            }
        }
    }
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < columns; j++) {
            printf(" %c |", field[i][j]);
        }
        printf("\n");
    }
    printf("   ");
    for (int i = 0; i < columns; i++) {
        printf("--- ");
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < columns; i++) {
        printf(" %d  ", i + 1);
    }
    printf("\n");
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    for (int i = 0; i < columns; i++) {
        for (int j = 1; j < rows; j++) {
            if (field[j][i] != field[0][i]) {
                return 0;
            }
        }
    }
    return 1;
}

void ball_sort_puzzle() {
    int rows, cols, flag = 1;
    printf("Enter rows: ");
    scanf("%d", &rows);

    printf("Enter cols: ");
    scanf("%d", &cols);

    printf("\n");

    char field[rows][cols];

    generator(rows, cols, field);
    game_field(rows, cols, field);
    if (check(rows, cols, field) == true) {
        printf("\nYou won!\n");
        flag = 0;
    } else {
        int x, y;
        while(flag) {
            printf("Enter what: ");
            scanf("%d", &x);
            printf("Enter where: ");
            scanf("%d", &y);    
            printf("\n");

            down_possible(rows, cols, field, x, y);
            if (check(rows, cols, field) == true) {
                game_field(rows, cols, field);
                printf("\nYou won!\n");
                break;
            }
            game_field(rows, cols, field);
        }
    }

    
}