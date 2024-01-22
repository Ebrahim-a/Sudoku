#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int v[11];

typedef struct
{
    int row;
    int column;
} parameters;

int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}};

void *ValidRow(void *param)
{
    parameters *params = (parameters *)param;
    int row = params->row;
    int col = params->column;
    int ArrVal[9] = {0};
    int i;
    for (i = 0; i < 9; i++)
    {
        int n = sudoku[row][i];
        if (n < 1 || n > 9 || ArrVal[n - 1] == 1)
        {
            pthread_exit(NULL);
        }
        else
        {
            ArrVal[n - 1] = 1;
        }
    }
    v[1] = 1;
    pthread_exit(NULL);
}

void *ValidCol(void *param)
{
    parameters *params = (parameters *)param;
    int row = params->row;
    int col = params->column;
    int ArrVal[9] = {0};
    int i;
    for (i = 0; i < 9; i++)
    {
        int n = sudoku[i][col];
        if (n < 1 || n > 9 || ArrVal[n - 1] == 1)
        {
            pthread_exit(NULL);
        }
        else
        {
            ArrVal[n - 1] = 1;
        }
    }
    v[0] = 1;
    pthread_exit(NULL);
}


void *SubValid(void *param)
{
    parameters *params = (parameters *)param;
    int row = params->row;
    int col = params->column;
    if (row > 6 || row % 3 != 0 || col > 6 || col % 3 != 0)
    int ArrVal[9] = {0};
    int i, j;
    for (i = row; i < row + 3; i++)
    {
        for (j = col; j < col + 3; j++)
        {
            int n = sudoku[i][j];
            if (n < 1 || n > 9 || ArrVal[n - 1] == 1)
            {
                pthread_exit(NULL);
            }
            else
            {
                ArrVal[n - 1] = 1;
            }
        }
    }
    v[2 + row / 3 * 3 + col / 3] = 1;
    pthread_exit(NULL);
}

int main()
{
    pthread_t col_thread, row_thread, thread_one, thread_two, thread_three, thread_four, thread_five, thread_six, thread_seven, thread_eight, thread_nine;

    parameters *rowCheck = (parameters *)malloc(sizeof(parameters));
    rowCheck->row = 0;
    rowCheck->column = 0;

    parameters *colCheck = (parameters *)malloc(sizeof(parameters));
    colCheck->row = 0;
    colCheck->column = 0;

    parameters *first3by3 = (parameters *)malloc(sizeof(parameters));
    first3by3->row = 0;
    first3by3->column = 0;

    parameters *second3by3 = (parameters *)malloc(sizeof(parameters));
    second3by3->row = 0;
    second3by3->column = 3;

    parameters *third3by3 = (parameters *)malloc(sizeof(parameters));
    third3by3->row = 0;
    third3by3->column = 6;

    parameters *fourth3by3 = (parameters *)malloc(sizeof(parameters));
    fourth3by3->row = 3;
    fourth3by3->column = 0;

    parameters *fifth3by3 = (parameters *)malloc(sizeof(parameters));
    fifth3by3->row = 3;
    fifth3by3->column = 3;

    parameters *sixth3by3 = (parameters *)malloc(sizeof(parameters));
    sixth3by3->row = 3;
    sixth3by3->column = 6;

    parameters *seventh3by3 = (parameters *)malloc(sizeof(parameters));
    seventh3by3->row = 6;
    seventh3by3->column = 0;

    parameters *eighth3by3 = (parameters *)malloc(sizeof(parameters));
    eighth3by3->row = 6;
    eighth3by3->column = 3;

    parameters *ninth3by3 = (parameters *)malloc(sizeof(parameters));
    ninth3by3->row = 6;
    ninth3by3->column = 6;

    void *rows;
    void *cols;
    void *first_grid;
    void *second_grid;
    void *third_grid;
    void *fourth_grid;
    void *fifth_grid;
    void *sixth_grid;
    void *seventh_grid;
    void *eighth_grid;
    void *ninth_grid;

    pthread_create(&col_thread, NULL, ValidCol, (void *)colCheck);
    pthread_create(&row_thread, NULL, ValidRow, (void *)rowCheck);
    pthread_create(&thread_one, NULL, SubValid, (void *)first3by3);
    pthread_create(&thread_two, NULL, SubValid, (void *)second3by3);
    pthread_create(&thread_three, NULL, SubValid, (void *)third3by3);
    pthread_create(&thread_four, NULL, SubValid, (void *)fourth3by3);
    pthread_create(&thread_five, NULL, SubValid, (void *)fifth3by3);
    pthread_create(&thread_six, NULL, SubValid, (void *)sixth3by3);
    pthread_create(&thread_seven, NULL, SubValid, (void *)seventh3by3);
    pthread_create(&thread_eight, NULL, SubValid, (void *)eighth3by3);
    pthread_create(&thread_nine, NULL, SubValid, (void *)ninth3by3);

    pthread_join(col_thread, &cols);
    pthread_join(row_thread, &rows);
    pthread_join(thread_one, &first_grid);
    pthread_join(thread_two, &second_grid);
    pthread_join(thread_three, &third_grid);
    pthread_join(thread_four, &fourth_grid);
    pthread_join(thread_five, &fifth_grid);
    pthread_join(thread_six, &sixth_grid);
    pthread_join(thread_seven, &seventh_grid);
    pthread_join(thread_eight, &eighth_grid);
    pthread_join(thread_nine, &ninth_grid);

    int c = 0;

    while (c < 11)
    {
        if (v[c] == 1)
        {
            c++;
        }
        else
        {
            printf("Solved \n");
            exit(0);
        }
    }
    printf("Wrong Solution \n");

    return 0;
}