/*
    Jogo das Pedras | Trabalho final de Fundamentos de Programação
    Discente: Victor Gabriel Lucio
    Docente: Luciano Tadeu Esteves Pansanato
    Instituição: Universidade Tecnólogica Federal do Paraná
*/

#include <stdio.h>
#include <stdlib.h>

#define boardSize 8
#define stones '*'
#define empty '-'

// Function to show a title screen
void titleScreen(int decision)
{
    if(decision == 1)
    {
        printf("\n");
    }

    else if(decision == 2)
    {
        printf("\nRegras:\n");
        printf("Um salto consiste sempre em deslocar uma pedra qualquer para uma casa que esteja vazia;\n");
        printf("A casa de destino da pedra no salto deve estar na diagonal da sua casa de origem;\n");
        printf("Para atingir a casa vazia, a pedra não pode passar por outras casas vazias.\n");

        printf("\nDificuldades:\n");
        printf("Extremamente fácil: eliminar até 29 pedras;\n");
        printf("Fácil: eliminar de 30 a 39 pedras;\n");
        printf("Difícil: eliminar de 40 a 44 pedras;\n");
        printf("Extremamente difícil: eliminar de 45 a 47 pedras.\n");
    }
    else if(decision == 3)
    {
        printf("\nCriador: Victor Gabriel Lucio\n");
        printf("Professor: Luciano Tadeu Esteves Pansanato\n");
        printf("Universidade: UTFPR-CP\n");
        printf("Curso: Analise e Desenvolvimento de Sistemas\n");
    }
}

// Fuction to start the board
void boardStart (char s[boardSize][boardSize])
{
    // Setting the stone spots
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            s[i][j] = stones;
        }
    }

    // Setting the empty spots
    for (int i = 2; i < 6; i++)
    {
        for (int j = 2; j < 6; j++)
        {
            s[i][j] = empty;
        }
    }
}

// Function to display the board on the screen
void boardDisplay (char s[boardSize][boardSize])
{
    printf("  ");
    for (int i = 0; i < boardSize; i++)
    {
        printf("%d ", i+1);
    }
    printf("\n");

    for (int i = 0; i < boardSize; i++)
    {
        printf("%d ", i+1);
        for (int j = 0; j < boardSize; j++)
        {
            printf("%c ", s[i][j]);
        }
        printf("\n");
    }
}
// Fuction to check if the movement selected is diagonal
int isDiagonal (int originLine, int originCol, int destLine, int destCol)
{
    // Auxiliary Variable Declaration
    int diffL, diffC;

    // Processing
    diffL = abs(originLine - destLine);
    diffC = abs(originCol - destCol);

    if(diffL == diffC)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

// Error msg function if necessary.
int errorMsg (int originLine, int originCol, int destLine, int destCol, char board[boardSize][boardSize])
{
    // If the entry leaves the board space
    if(originLine-1 > boardSize || originCol-1 > boardSize || destLine-1 > boardSize || destCol-1 > boardSize)
    {
        printf("Entrada Invalida! (Fora dos limites do tabuleiro).\n\n");
        return 1;
    }
    else if(originLine-1 < 0 || originCol-1 < 0 || destLine-1 < 0 || destCol-1 < 0)
    {
        printf("Entrada Invalida! (Fora dos limites do tabuleiro).\n\n");
        return 1;
    }

    // If the entry is invalid by rules
    else if(board[originLine-1][originCol-1] != '*')
    {
        printf("Entrada Invalida! (A casa de origem nao e uma pedra).\n\n");
        return 1;
    }

    else if(board[destLine-1][destCol-1] != '-')
    {
        printf("Entrada Invalida! (A casa de destino nao esta vazia).\n\n");
        return 1;
    }

    else if(isDiagonal(originLine, originCol, destLine, destCol) == 0)
    {
        printf("Entrada Invalida! (A jogada deve ser feita na diagonal).\n\n");
        return 1;
    }

    // if there are no errors the game runs normally
    else
    {
        return 0;
    }
}

// Function to process the play
void playProc (char board[boardSize][boardSize],int originLine, int originCol, int destLine, int destCol, int *jumps)
{
    // Variable to count the remaining stones
    int remaining = 0;

    // Play processing  & variable declaration (Elimination)
    int diffLine = destLine - originLine;
    int diffCol = destCol - originCol;
    int stepLine = (diffLine > 0) ? 1 : -1;
    int stepCol = (diffCol > 0) ? 1 : -1;

    int i = originLine + stepLine;
    int j = originCol + stepCol;

    while (i != destLine)
    {
        if (board[i][j] == empty)
        {
            printf("Entrada Invalida. (A pedra nao pode passar por uma casa vazia)\n\n");
            return; // Terminates the function without making the move
        }

        i += stepLine;
        j += stepCol;
    }

    // Play processing (Elimination and Movement)
    i = originLine + stepLine;
    j = originCol + stepCol;

    while (i != destLine)
    {
        board[i][j] = empty;
        i += stepLine;
        j += stepCol;
    }

    // Play processing (Movement)
    board[destLine][destCol] = stones;
    board[originLine][originCol] = empty;

    // Counting the remaining stones
    for (i = 0; i < boardSize; ++i)
    {
        for (j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == stones)
            {
                remaining++;
            }
        }
    }

    // Increment the number os jumps if the play is valid.
    (*jumps)++;

    // Data output (informations)
    printf("Salto de (%d, %d) para (%d, %d).\n", originLine+1, originCol+1, destLine+1, destCol+1);
    printf("Pedras eliminadas: %d\n", abs(48 - remaining));
    printf("Restam %d pedras no tabuleiro\n\n", remaining);

}

// Function to display the endgame informations.
void endGame(int jumps, char board[boardSize][boardSize])
{
    // Variable declaration
    int remaining = 0;

    // Counting the remaining stones
    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            if (board[i][j] == stones)
            {
                remaining++;
            }
        }
    }

    // Data output
    printf("Numero de saltos realizados: %d\n", jumps);
    printf("Pedras Eliminadas: %d\n", 48 - remaining);

    // Difficulty level reached
    if(48 - remaining <= 29)
    {
        printf("Nivel de dificuldade: Extremamente facil\n");
    }
    else if(48 - remaining <= 39)
    {
        printf("Nivel de dificuldade: Facil\n");
    }
    else if(48 - remaining <= 44)
    {
        printf("Nivel de dificuldade: Dificil");
    }
    else
    {
        printf("Nivel de dificuldade: Extremamente dificil\n");
    }
}

int main()
{
    // Initializing the board
    char board[boardSize][boardSize];

    // Variable declaration (move data)
    int originLine, originCol, destLine, destCol, decision, jumps = 0;

    // Title Screen
    do
    {
        printf("\n- Jogo das Pedras-\n\n");
        printf("[1] - Novo Jogo\n");
        printf("[2] - Regras e Info's\n");
        printf("[3] - Sobre\n\n");
        scanf("%d", &decision);

        // Data validation
        while(decision < 1 || decision > 3)
        {
            printf("\nEntrada Invalida!\n");
            printf("Digite novamente:");
            scanf("%d", &decision);
        }

        titleScreen(decision);
    }
    while(decision != 1);

    // Starting the board
    boardStart(board);

    // Gameplay
    do
    {
        // Displaying the board
        boardDisplay(board);
        printf("\n");

        // Data input (movement informations)
        do
        {
            printf("Digite [0] em uma das entradas para desistir!\n");

            printf("\nDigite a linha da casa de origem:");
            scanf("%d", &originLine);

            printf("Digite a coluna da casa de origem:");
            scanf("%d", &originCol);

            printf("\nDigite a linha da casa de destino:");
            scanf("%d", &destLine);

            printf("Digite a coluna da casa de destino:");
            scanf("%d", &destCol);

            printf("\n");

            // if the user wants to finish the game
            if(originLine == 0 || originCol == 0 || destLine == 0 || destCol == 0)
            {
                printf("\nFim de jogo!\n\n");
                break;
            }
        }
        while(errorMsg(originLine, originCol, destLine, destCol, board) == 1);

        // If the player wants to finish the game!
        if(originLine == 0 || originCol == 0 || destLine == 0 || destCol == 0)
        {
            char playAgain;
            endGame(jumps, board);

            printf("\nDeseja Jogar novamente? [S/N]:");
            scanf(" %c", &playAgain);

            // If the play wants to play again restart the board.
            if(playAgain == 's' || playAgain == 'S')
            {
                boardStart(board);
                jumps = 0;
                printf("\n");
            }

            // Else finish the programm.
            else
            {
                printf("\n- Obrigado por jogar! -");
                break;
            }
        }

        // Else process the play.
        else
        {
            playProc(board, originLine-1, originCol-1, destLine-1, destCol-1, &jumps);
        }

    }
    while(1);
}