//Ithamar Baron 19/10/24
//Note, I actually made a TicTacToe about a week ago in C# so this one is based on the same code, (thats why the input differs from the requestd one)
//You can find the C# code here: https://github.com/IthamarBaron/boredTicTacToe


#pragma warning(disable : 4996)
#include <stdio.h>

#define N 3
#define GRN  "\x1B[32m"
#define WHT  "\x1B[37m"
#define CYN  "\x1B[36m"
#define MAG  "\x1B[35m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

void ConsoleClear()
{
    printf("\033[H\033[J");
}

void RestartGame(char mat[N][N])
{
    char slot = '0';
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat[i][j] = slot++;
        }
    }
}

void DrawBoard(char mat[N][N])
{
    ConsoleClear();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(WHT);
            if (mat[i][j] == 'O')
                printf(GRN);
            else if (mat[i][j] == 'X')
                printf(RED);
            printf(" %c", mat[i][j]);
            printf(CYN);
            if (j < N - 1)
                printf(" |");
        }
        if (i < N - 1)
            printf("\n---+---+---\n");
    }
    printf("\n\n");
    printf(WHT);
}

char CheckWin(char mat[N][N])
{
    char first;
    int counter;

    // Check rows
    for (int i = 0; i < N; i++)
    {
        first = mat[i][0];
        counter = 0;
        for (int j = 0; j < N; j++)
        {
            if (first == mat[i][j])
                counter++;
            if (counter == N)
                return first;
        }
    }

    // Check columns
    for (int i = 0; i < N; i++)
    {
        first = mat[0][i];
        counter = 0;
        for (int j = 0; j < N; j++)
        {
            if (first == mat[j][i])
                counter++;
            if (counter == N)
                return first;
        }
    }

    // Check diagonals
    int dcounter = 0;
    char dfirst = mat[0][0];
    for (int i = 0; i < N; i++)
    {
        if (dfirst == mat[i][i])
            dcounter++;
        if (dcounter == N)
            return dfirst;
    }

    dcounter = 0;
    dfirst = mat[0][N - 1];
    for (int i = 0; i < N; i++)
    {
        if (dfirst == mat[i][N - 1 - i])
            dcounter++;
        if (dcounter == N)
            return dfirst;
    }

    // Check for draw
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] >= '0' && mat[i][j] <= '9')
                return '0'; // Game not finished
        }
    }

    return 'E'; // Draw
}

void SelectMove(char turn, char mat[N][N])
{
    if (turn == 'X')
        printf(RED);
    else if (turn == 'O')
        printf(GRN);

    printf("\tIts %c's Turn!\n", turn);
    printf(WHT);
    printf("===============================\n");

    int slot;
    printf(YEL "Enter your move: " WHT);

    while (1)
    {
        scanf("%d", &slot);
        int j = slot % N;
        int i = slot / N;

        if (slot < 0 || slot >= N * N || (mat[i][j] == 'X' || mat[i][j] == 'O'))
        {
            printf(RED "WHAT ARE YOU DOING?!\n" WHT);
            printf("Please try again...\n");
            continue; // Prompt again
        }

        mat[i][j] = turn; // Place the move
        break; // Exit the loop
    }
}

void DeclareWinner(char mat[N][N], char winner)
{
    ConsoleClear();
    printf(CYN "===================================\n");

    if (winner != 'E')
    {
        printf(YEL "\t WE HAVE A WINNER!\n");
        if (winner == 'X')
            printf(RED);
        else
            printf(GRN);
        printf("\t %c HAS WON THE GAME\n", winner);
    }
    else
    {
        printf(MAG "\t GAME ENDED IN A DRAW\n");
    }

    printf(CYN "===================================\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(WHT); 
            if (mat[i][j] == winner)
                printf(YEL); 
            printf(" %c", mat[i][j]); 
            printf(WHT); 
            if (j < N - 1)
                printf(" |");
        }
        if (i < N - 1)
            printf("\n---+---+---\n");
    }
    printf("\n\n");
    printf(WHT);
}

int main()
{
    char mat[N][N];
    char win = ' ';
    char turn;
    int turnCounter = 0;

    RestartGame(mat);

    while (win != 'X' && win != 'O' && win != 'E')
    {
        turn = (turnCounter % 2 == 0) ? 'X' : 'O';
        DrawBoard(mat);
        SelectMove(turn, mat);
        win = CheckWin(mat);
        turnCounter++;
    }

    DeclareWinner(mat, win);
    return 0;
}
