// Tic Tac Toe game
// User chooses x or o
// Board is empty, random gen for player or cpu go first
// Board seen before and updated after each play
// Cpu chooses random spot first, then more advanced where cpu 
// calculates every time theres 2 in a row, they place in front of those
// Also they try to play multiple in a row
// When theres a winner figure out how to highlight the row, some sort of celebration
// After a player has 3 turns start checking for wins

// Need to change how board displays using loops

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// Builds the game board
void buildBoard()
{
    printf("\n        %d   |   %d   |   %d \n", 1, 2, 3);
    printf("     -----------------------\n");
    printf("        %d   |   %d   |   %d \n", 4, 5, 6);
    printf("     -----------------------\n");
    printf("        %d   |   %d   |   %d\n\n", 7, 8, 9);
}

// Update game matrix and print
void updateBoard(char board[3][3])
{
    printf("\n");

    // Loop over game matrix, first part of each row needs extra spaces, otherwise same format
    // Last part of each row needs no |
    // After each row except the last, need --- for formatting board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
            {
                if (j == 0)
                {
                    printf("        %c   |", board[i][j]);
                }
                else
                {
                    printf("   %c   |", board[i][j]);
                }
            }
            else
            {
                printf("   %c   ", board[i][j]);
            }
            
        }
        if (i != 2)
        {
            printf("\n     -----------------------\n");
        }
    }
    printf("\n\n");
}

// Take chosen space as argument and update matrix, then use to update visible board
void updateGameMatrix(int space, char marker, char board[3][3], int spaceEmpty[1])
{
    int spaceCount = 0;
    spaceEmpty[0] = 1;
    // Loop through and insert players value into correct spot
    // When correct spot reached, place marker or flag it as full
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            spaceCount = spaceCount + 1;
            if (spaceCount == space)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = marker;
                }
                else
                {
                    spaceEmpty[0] = 0;
                }
                
                break;
            }
        }
    }

}

// Function not entering
void playerPlay(char marker, char board[3][3])
{
    int space;
    int spaceEmpty[1] = {0};
    bool validEntry = false;
    float divided; 
    // Stores getchar stuff for clearing stdin
    int c;

    // Want this to loop until player has valid space
    // Loop while space is full and entry is invalid
    while (spaceEmpty[0] == 0 || validEntry == false )
    {
        printf("Choose space: ");
        scanf("%d", &space);

        // getchar() for clearing stdin buffer, this is needed
        // when char or string entered into int data type
        while ((c = getchar()) != '\n'){}
        
        // This works
        divided = (float)space / 9.0f;

        // Catch invalid space entry
        // When string or char entered into int scan, a huge number is stored
        // Any number less then 9 divided by 9 is < or = 1, a large number
        // caught is either invalid number or a char/string
        if (divided > 1 || space < 1)
        {
            printf("Invalid Entry. Try again.\n");
        }
        else 
        {
            validEntry = true;
            updateGameMatrix(space, marker, board, spaceEmpty);
            if (spaceEmpty[0] == 0)
            {
                printf("That space was already taken. Try again.\n");
            }
        }
    }
}

// Want to return coord to make play at, 2D array
// If no match for 2 return empty and show this to mean there isn't 2 back in cpu func
void checkFor2(char board[3][3], char playerMarker, char cpuMarker, int horizontalArr[2], int verticalArr[2], int diagonalArr[2])
{
    int count = 0;
    
    // This misses 2 diagonals?

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j+2 < 3)
            {
                // to the right horizontal
                if (board[i][j] == playerMarker && board[i][j+1] == playerMarker && board[i][j+2] != cpuMarker)
                {
                    // Want to return coords as array to easily update board in cpu func
                    // If no coords returned handle this in cpu func to say that there isn't 2 in a row
                    horizontalArr[0] = i;
                    horizontalArr[1] = j+2;
                }
            }
            if (j-2 > -1)
            {
                // to the left horizontal
                if (board[i][j] == playerMarker && board[i][j-1] == playerMarker && board[i][j-2] != cpuMarker)
                {
                    horizontalArr[0] = i;
                    horizontalArr[0] = j-2;
                }
            }
            if (i+2 < 3)
            {
                // to the top vertical
                if (board[i][j] == playerMarker && board[i+1][j] == playerMarker && board[i+2][j] != cpuMarker)
                {
                    verticalArr[0] = i+2;
                    verticalArr[1] = j;
                }
            }
            if (i-2 > -1)
            {
                // down vertical
                if (board[i][j] == playerMarker && board[i-1][j] == playerMarker && board[i-2][j] != cpuMarker)
                {
                    verticalArr[0] = i-2;
                    verticalArr[1] = j;
                }
            }
            if (i+2 < 3 && j+2 < 3)
            {
                // bottom right diagonal
                if (board[i][j] == playerMarker && board[i+1][j+1] == playerMarker && board[i+2][j+2] != cpuMarker)
                {
                    diagonalArr[0] = i+2;
                    diagonalArr[1] = j+2;
                }
            }
            if (i-2 > -1 && j-2 > -1)
            {
                // top right diagonal
                if (board[i][j] == playerMarker && board[i-1][j-1] == playerMarker && board[i-2][j-2] != cpuMarker)
                {
                    diagonalArr[0] = i-2;
                    diagonalArr[1] = j-2;
                }
            }
        }
    }
}

void cpuPlay(char cpuMarker, char board[3][3], int round, char playerMarker)
{
    int horizontalArr[2] = {-1,-1}; 
    int verticalArr[2] = {-1,-1}; 
    int diagonalArr[2] = {-1,-1};

    int cpuSpaceEmpty[1] = {0};
    int startMove;
    // int *horizontalArr;
    // int *verticalArr;
    // int *diagonalArr;
    bool twoHorizontal = false;
    bool twoVertical = false;
    bool twoDiagonal = false;
    int leftHorizontalMoveArr[2];
    int rightHorizontalMoveArr[2];
    int topVerticalMoveArr[2];
    int bottomVerticalMoveArr[2];
    int topLeftDiagonalMoveArr[2];
    int bottomRightDiagonalMoveArr[2];
    int topRightDiagonalMoveArr[2];
    int bottomLeftDiagonalMoveArr[2];
    // Array of valid moves instead?
    // Store array of arrays, each array being the move to be made
    // There are 8 possible moves with 2 coords each, each coord being a column
    int validMoves[8][2];
    int validCount = 0;
    int noTwoMove;
    // int leftHorizontalMove = 1;
    // int rightHorizontalMove = 2;
    // int topVerticalMove = 3;
    // int bottomVerticalMove = 4;
    // int topDiagonalMove = 5;
    // int bottomDiagonalMove = 6;


    srand(time(0));
    startMove = (rand()%9) + 1;

    // If round 1 or 2, cpu will play random location
    // Keep looping while cpu hasn't filled space, accounts for error of spaces
    // already full
    while (cpuSpaceEmpty[0] == 0)
    {
        // Cpus first move is a random gen
        if (round == 1 || round == 2)
        {
            updateGameMatrix(startMove, cpuMarker, board, cpuSpaceEmpty);
        }
        // Make check for 2 in a row function
        checkFor2(board, playerMarker, cpuMarker, horizontalArr, verticalArr, diagonalArr);
        // need check if arrays empty to know if cpu can go by seeing if 2nd index is still -1
        // When there isn't 2 in a row anywhere
        // Might need to account for possible spaces in here 
        if (horizontalArr[0] == -1 && verticalArr[0] == -1 && diagonalArr[0] == -1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // If there isn't 2 in a row want to random gen between 6 possible moves, 
                    // either place horizontal beside last cpu, up, or diagonal. 
                    // Want to assign numbers between each and use rand to decide
                    // Actually 6 possible moves to account for above or below, top diag or bottom, left or right side
                    // if one side not possible due to out of bounds then gen again
                    if (board[i][j] == cpuMarker)
                    {
                        // need arrays to store the move, int to keep track of number for random gen, 
                        // once random gen fill in the right move, might need to make a function
                        // Will need to change if statements as first loop j-1 is -1 but could still be right move, however 

                        // Have stored all possible moves, loop through the valid ones randomly to pick move
                        // If that space occupied by player then pick again till valid choice, when 
                        if (j + 1 < 3)
                        {
                            // leftHorizontalMoveArr[0] = i;
                            // leftHorizontalMoveArr[1] = j+1;
                            // store all moves even though some invalid, because thats decided later
                            // Not right because could be 2 possible moves with same value of count
                            // count row of array stores i in first column and j + 1 in 2nd column
                            validMoves[validCount][0] = i;
                            validMoves[validCount][1] = j+1;
                            validCount += 1;
                            // create a bunch of ints 1 or 0 
                        }
                        if (j - 1 > -1)
                        {
                            // rightHorizontalMoveArr[0] = i;
                            // rightHorizontalMoveArr[1] = j-1;
                            // The indice corresponds to amount of random moves to loop through
                            // The number corresponds to what move, 1 means its a left horizontal move
                            validMoves[validCount][0] = i;
                            validMoves[validCount][1] = j-1;
                            validCount += 1;
                        }
                        if (i - 1 > -1)
                        {
                            // topVerticalMoveArr[0] = i-1;
                            // topVerticalMoveArr[1] = j;
                            validMoves[validCount][0] = i-1;
                            validMoves[validCount][1] = j;
                            validCount += 1;
                        }
                        if (i + 1 < 3)
                        {
                            // bottomVerticalMoveArr[0] = i+1;
                            // bottomVerticalMoveArr[1] = j;
                            validMoves[validCount][0] = i+1;
                            validMoves[validCount][1] = j;
                            validCount += 1;
                        }
                        if (j - 1 > -1 && i - 1 > -1)
                        {
                            // topLeftDiagonalMoveArr[0] = i-1;
                            // topLeftDiagonalMoveArr[1] = j-1;
                            validMoves[validCount][0] = i-1;
                            validMoves[validCount][1] = j-1;
                            validCount += 1;
                        }
                        if (j + 1 < 3 && i + 1 < 3)
                        {
                            // bottomRightDiagonalMoveArr[0] = i+1;
                            // bottomRightDiagonalMoveArr[1] = j+1;
                            validMoves[validCount][0] = i+1;
                            validMoves[validCount][1] = j+1;
                            validCount += 1;
                        } 
                        if (j + 1 < 3 && i - 1 > -1)
                        {
                            // topRightDiagonalMoveArr[0] = i-1;
                            // topRightDiagonalMoveArr[1] = j+1;
                            validMoves[validCount][0] = i-1;
                            validMoves[validCount][1] = j+1;
                            validCount += 1;
                        }
                        if (j - 1 > -1 && i + 1 < 3)
                        {
                            // bottomLeftDiagonalMoveArr[0] = i+1;
                            // bottomLeftDiagonalMoveArr[1] = j-1;
                            validMoves[validCount][0] = i+1;
                            validMoves[validCount][1] = j-1;

                        }
                    }
                }
            }

            // Now should have 2D array with validCount being possible moves
            // want to gen random move from 1 to validCount + 1 - use associated columns for cpus move
            noTwoMove = (rand()%validCount) + 1;
            // pass in coords of the generated move to the board
            board[validMoves[noTwoMove][0]][validMoves[noTwoMove][1]] = cpuMarker;
        }

        // If player has 2 in a row block, either diagonal, horizontal or vertical
        // If player doesn't have 2 in a row then place beside other cpu marker
        // Random choice between placing vertical, horizontal, or diagonal
        // If space full random generate this again to another place
        // Also want to account for if theres 2 in a row, but cpu has 2 in a row, prioritize 
        // getting that 3 rather then blocking player
        
    }
}

// 50 50 chance of cpu or player starting
int chooseStart()
{
    // Seed and generate numbers from 1 to 2 inclusive
    srand(time(0));
    int random = (rand() % 2) + 1;

    // If random = 1 cpu starts, if random = 2 player starts
    if (random == 1)
    {
        printf("Its been decided that I will play first, let the games begin!\n\n");
        return 1;
    }
    else
    {
        printf("Its been decided that you will play first, let the games begin!\n\n");
        return 2;
    }
} 

// Error cpus turn it plays twice in a row when it starts, when i play then cpu goes again seg fault
// When i start cpu then goes twice, putting 2 spaces together
int main()
{
    char marker;
    char cpuMarker;
    bool validEntry = true;
    char board[3][3] = {{' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}};
    // Track which round
    int countPlay = 0;
    // When true the player last played, when false cpu last played
    bool playerPlayed = false;

    printf("Welcome to Tic Tac Toe! You will be playing against me, the Tic Tac Master!\n"); 
    printf("Chance will decide who will play first.\n");
    printf("Take a look at the grid below:\n");
    
    buildBoard();
    
    printf("On your turn, enter a coordinate from 1-9 to place your marker.\n");
    printf("Would you like to be X or O? Enter here: ");
    scanf("%s", &marker);
    if (marker != 'X' || marker != 'O')
    {
        validEntry = false;
    }
   
    while (validEntry == false)
    {
        if (marker != 'X' && marker != 'O')
        {
            //validEntry = false;
            printf("Invalid entry, try again: ");
            scanf("%s", &marker);
        }
        else
        {
            validEntry = true;
        }
    }

    printf("Well, looks like we should get started. Good luck %c!\n", marker);

    if (marker == 'X')
    {
        cpuMarker = 'O';
    }
    else
    {
        cpuMarker = 'X';
    }

    int starter = chooseStart();
    //printf("Starter: %d\n", starter);
    
    // When starter is 1, set it as player already played so when loop starts cpu 
    // will go first
    if (starter == 1)
    {
        playerPlayed = true;
    }

    // While loop for while board not empty
    // If board has blank spaces its not empty 
    while (countPlay < 9)
    {
        countPlay = countPlay + 1;
        //printf("Count: %d\n", countPlay);

        // Once games had 4 turns, possible someone won, keep checking from/a.
        // now on for each round
        // if (countPlay >= 4)
        // {
        //     // call function to check win
        //     printf("temp check win\n");
        // }

        // If player last played, cpu goes, vice versa
        if (playerPlayed == true)
        {
            cpuPlay(cpuMarker, board, countPlay, marker);
            // is there an issue here?
            updateBoard(board);
            playerPlayed = false;
        }
        else
        {
            playerPlay(marker, board);
            updateBoard(board);
            playerPlayed = true;
        }
    }

    return 0;
}