#include <stdio.h>
#include <string.h>
#define MAX_ROW 7
#define MAX_COL 5
typedef char Str10[11];
/*
Purpose: initialize the values of the different character arrays
 set the initial positions of Alpha and Beta
Returns: void
@param : Position is a 2D character array that will store the positions of 
Alpha and Beta
 as well as the free spaces
@param : S is a 2D character array that will store the valid positions where 
players can eat
@param : Beta is a 2D character array that will store the initial position of
Beta
 @param : Alpha is a 2D character array that will store the initial position of 
Alpha
Pre-condition: the parameters do not contain values yet
*/
void Initialize(char Position[][MAX_COL], char S[][MAX_COL], char Beta[][MAX_COL], 
char Alpha[][MAX_COL]) {
    int i, j;
    for(i = 0; i < MAX_ROW; i++) // initialize every row
    {
        for(j = 0; j < MAX_COL; j++) // initialize every column
        {
            if((i+1) % 2 == (j+1) % 2) // check if (x,y) --> (i,j) passes the S set condition
            S[i][j] = 'S';
            
            if(i < 2) { // check if it passes the Y set condition (i <= 2) 
                // in this case the index starts with 0 so i should be from 0 to 1
                if((i+1) % 2 == (j+1) % 2) { 
                    Position[i][j] = 'X'; // X represents the pieces of BETA
                    Beta[i][j] = 'Y'; // Y represents the starting positions of BETA
                    Alpha[i][j] = ' '; // free space
                }
                else { // if it does not satisfy the S set condition, store a free space
                    Position[i][j] = ' ';
                    Beta[i][j] = ' ';
                    Alpha[i][j] = ' ';
                }
            }
            else if (i > 4) { // check if it passes the E set condition (i >= 6)
            // in this case i should be from 5 to 6
            if((i+1) % 2 == (j+1) % 2) { 
                Position[i][j] = 'O'; // O represents the pieces of ALPHA
                Alpha[i][j] = 'E'; // E represents the starting positions of ALPHA
                Beta[i][j] = ' '; // free space
            }
            else { // if it does not satisfy the S set condition, store a free space
                Position[i][j] = ' ';
                Alpha[i][j] = ' ';
                Beta[i][j] = ' ';
            }
            }
                else { // if it does not satisfy the Y and E set conditions then store a free space
                Position[i][j] = ' ';
                Beta[i][j] = ' ';
                Alpha[i][j] = ' ';
            }
        }
    }
}
/*
Purpose: prints the game board as well as the current positions of ALPHA and 
BETA including the free spaces
Returns: void
@param : Position is a 2D character array containing the current positions of
Alpha and Beta
 as well as the free spaces
Pre-condition: the parameter contains valid values
*/
void ShowBoard(char Position[][MAX_COL]) {
 int i, j;
 int k = 1;
 printf(" 1 2 3 4 5\n"); // print the column number
 printf(" _____________________\n");
 // loop for printing all values of the 2D array
 for(i = 0; i < MAX_ROW; i++)
 {
    printf(" | | | | | |\n");
    printf(" %d |", k);
    for(j = 0; j < MAX_COL; j++)
    {
        printf(" %c |", Position[i][j]);
    }
    k++;
    printf("\n");
    printf(" |___|___|___|___|___|\n");
 }
 printf("\n");
}
/*
Purpose: determine if the input prev and next row and columns are valid
Returns: (a) 0 if it is a valid next location
 (b) 1 if it is not a valid next location
 (c) 2 if player can't eat at next location
 (d) 3 if player successfully eats at next location
@param : prev is a 1D int array containing the input previous position (row 
and column) of a piece (ALPHA OR BETA)
@param : next is a 1D int array containing the input next position (row and 
column) of a piece (ALPHA OR BETA)
@param : Position is a 2D character array containing the current positions of
Alpha and Beta
 as well as the free spaces
 @param : aTurn is a int pointer formal parameter that stores either a 1 or 0 --
> indicating whose turn it is
 (a) 1 for BETA (b) 0 for ALPHA
 @param : S is a 2D character array containing the valid positions where players
can eat
Pre-condition: the parameters contain valid values
*/
int NextPlayerMove(int prev[], int next[], char Position[][MAX_COL], int *aTurn, 
char S[][MAX_COL]) {
 
int ok = 1; // 1 means false
int a = prev[0] - 1; // initialize value of a (prev row)
int b = prev[1] - 1; // initialize value of b (prew col)
int c = next[0] - 1; // initialize value of c (next row)
int d = next[1] - 1; // initialize value of d (next col)
// these variables will be used later in the if else conditions
int comp1 = a + 1; // previous row is less by 1
int comp2 = b + 1; // previous col is less by 1
int comp3 = c + 1; // next row is less by 1
int comp4 = d + 1; // next col is less by 1
/* if it's Alpha's turn && prev position (row & col) is valid && next row is 
less by 1 compared to prev row
&& next col is equal to prev col || prev col is higher by 1 compared to
next col || next col is higher by 1 compared to prev col */
if(*aTurn == 0 && Position[a][b] == 'O' && a == comp3 && (d == b || d == 
comp2 || b == comp4)) {
ok = (ok + 1) % 2; // ok = true
}
/* if it's Beta's turn && prev position (row & col) is valid && prev row is 
less by 1 compared to next row
&& next col is equal to prev col || prev col is higher by 1 compared to
next col || next col is higher by 1 compared to prev col */
else if(*aTurn == 1 && Position[a][b] == 'X' && c == comp1 && (d == b || d ==
comp2 || b == comp4)) {
ok = (ok + 1) % 2; // ok = true
}
else {
return 1;
}
if(ok == 0) { // if ok is true &&
    if(*aTurn == 0) { // if it's Alpha's turn &&
    if(Position[c][d] == ' ') { // if the next position contains a free space
    Position[a][b] = ' '; // replace previous position with a free space
    Position[c][d] = 'O'; // replace next position with Alpha piece 'O'
    *aTurn = (*aTurn + 1) % 2; // end Alpha's turn
    ok = (ok + 1) % 2; // ok = false
    return 0;
    }
    else if(Position[c][d] == 'X' && S[c][d] != 'S') { // if the next position contains a Beta piece 
    // BUT next position is not an 'S' position --> fail to eat
    ok = (ok + 1) % 2; // ok = false
    return 2;
    }
    else if(Position[c][d] == 'X' && S[c][d] == 'S') { // the next position contains a Beta piece 
    // && next position is an 'S' position --> eat 
    Position[a][b] = ' '; // replace previous position with a free space
    Position[c][d] = 'O'; // replace next position with Alpha piece 'O'
    *aTurn = (*aTurn + 1) % 2; // end Alpha's turn
    ok = (ok + 1) % 2; // ok = false
    return 3;
    }
    else 
    return 1;
    }
    else if(*aTurn == 1) { // if it's Beta's Turn
        if(Position[c][d] == ' ') { // if the next position contains a free space
        Position[a][b] = ' '; // replace previous position with a free space
        Position[c][d] = 'X'; // replace next position with Beta piece 'X'
        *aTurn = (*aTurn + 1) % 2; // end Beta's turn
        ok = (ok + 1) % 2; // ok = false
        return 0;
        }
        else if(Position[c][d] == 'O' && S[c][d] != 'S') { // The next position contains an Alpha piece 
            // BUT next position is not an 'S' position --> fail to eat
            ok = (ok + 1) % 2; // ok = false
            return 2;
        }
        else if(Position[c][d] == 'O' && S[c][d] == 'S') { // the next position contains an Alpha piece 
            // && next position is an 'S' position --> eat
            Position[a][b] = ' '; // replace previous position with a free space
            Position[c][d] = 'X'; // replace next position with Beta piece 'X'
            *aTurn = (*aTurn + 1) % 2; // end Beta's Turn
            ok = (ok + 1) % 2; // ok = false
            return 3;
        }
        else
        return 1;
    }
}
}
/*
Purpose: determine if Alpha or Beta wins
Returns: (a) 0 if winning conditions are met
 (b) 1 if winning conditions are not satisfied
@param : Position is a 2D character array containing the current positions of
Alpha and Beta
 as well as the free spaces
@param : Beta is a 2D character array containing the initial position of Beta
@param : ALpha is a 2D character array containing the initial position of 
Alpha
Pre-condition: the parameters contain valid values
*/
int GameOver(char Position[][MAX_COL], char Beta[][MAX_COL], char Alpha[][MAX_COL])
{
 Str10 result[2] = {"Beta Wins", "Alpha Wins"};
 int i, j;
 int over = 1; // game continues while over is equal to 1 (false)
 int ctr1 = 0; // counter for remaining Beta Pieces
 int ctr2 = 0; // counter for remaining Alpha Pieces
 int ctr3 = 0; // counter for Beta Pieces that are in Alpha's starting positions
 int ctr4 = 0; // counter for Alpha Pieces that are in Beta's starting positions
 for(i = 0; i < MAX_ROW; i++)
 for(j = 0; j < MAX_COL; j++) {
    if(Position[i][j] == 'X') {
    ctr1++; // add 1 for every Beta piece remaining
    if(Alpha[i][j] != 'E')
    ctr3++; // add 1 if Beta piece is not located on an Alpha starting point
    }
    else if(Position[i][j] == 'O') {
        ctr2++; // add 1 for every Alpha piece remaining
        if(Beta[i][j] != 'Y')
        ctr4++; // add 1 if Alpha piece is not located on a Beta starting point
    }
 }
 // if Beta has no players left || (Alpha still has players && All remaining pieces of Alpha are on the enemy starting point) --> Alpha Wins
 if(ctr1 == 0 || (ctr2 > 0 && ctr3 == 0)) {
    printf("%s\n", result[1]);
    over = 0; // end game
 }
 // if Alpha has no players left || (Beta still has players && All remaining pieces of Beta are on the enemy starting point) --> Beta Wins
 else if(ctr2 == 0 || (ctr1 > 0 && ctr4 == 0)) {
    printf("%s\n", result[0]);
    over = 0; // end game
 }
 
 
 return over;
}
int main () 
{
 int i, j, k = 0;
 int ctr = 0, ctr2 = 0;
 char Position[MAX_ROW][MAX_COL]; // ALpha, Beta, Free
 char S[MAX_ROW][MAX_COL]; // Valid row & col for eating
 char Beta[MAX_ROW][MAX_COL]; // Beta starting position
 char Alpha[MAX_ROW][MAX_COL]; // ALpha starting position
 int aTurn = 0; // Alpha plays first
 //int i, j;
 int prev[2]; // stores previous row and column
 int next[2]; // stores next row and column
 int end = 1; // games continues while end is equal to 1 (false)
 
 int valid = 0; // 0 if next move is valid
 int nChoice = 3;
 int nChoice2;
 Initialize(Position, S, Beta, Alpha);
 
 // welcome message to the player
 // choose 1 of the choices
 while (nChoice == 3){
 
    printf("======================================================================================================\n");
    printf("======================================================================================================\n");
    printf(" _____ _ _ _____ _ _ \n");
    printf("| |_____ ___ ___ ___ _ _|_|___ ___ _| | | | |_ ___ ___| |_ ___ ___ ___ \n");
    printf("|- -| | . | _| . | | | |_ -| -_| . | | --| | -_| _| '_| -_| _|_ -|\n");
    printf("|_____|_|_|_| _|_| |___| _/|_|___|___|___| |_____|_|_|___|___|_,_|___|_| |___|\n");
    printf(" |_| \n");
    printf("\n\n");
    nChoice = -1;
    while (nChoice == -1){ // so that choices loop under invalid choices
    printf("Start game? [1]\n");
    printf("Game Rules [2]\n");
    printf("Exit game [0]\n");
    printf("\n");
    scanf("%d", &nChoice); // assume the player will only input int values
    
    if (nChoice == 0)
    return 0;
    //for invalid inputs
    if ((nChoice > 2) || (nChoice < 0)){
    printf("Not valid option\n");
    nChoice = -1; //so that the code loops to choices since nChoice value was modified
    }
    }
    
    if(nChoice == 2){
    
        printf("======================================================================================================\n");
        
        printf("======================================================================================================\n");
        printf("\nRules\n"); 
        printf("!Movement : \n");
        printf("For Alpha - north, north east or north west\n");
        printf("For Beta - south, south east, or south west\n");
        printf("\n");
        printf("!Eating rules : \n");
        printf("A player can only eat its opponent when the enemy is on:\n");
        printf("- an odd row and column (ex row 1 column 5)\n");
        printf("- an even row and column (ex row 2 column 6)\n");
        printf("\n");
        printf("!Winning conditions\n");
        printf("- If there are no more players from the other team\n");
        printf("- the first team to reach each starting position of the opponent team wins\n");
        nChoice2 = 0;
        while(nChoice2 == 0) {
            printf("\nBack [1]\n");
            scanf("%d", &nChoice2);
            if (nChoice2 == 1)
            nChoice = 3;
            else if (nChoice>1 || nChoice<1){
                printf("Invalid option");
                nChoice2 = 0;
            }
        }
    }
}
if (nChoice == 1){
 
    printf("======================================================================================================\n");
    
    printf("======================================================================================================\n");
    do {
    ShowBoard(Position);
    
    switch (valid) {
        case 0:
        printf("Successfully Moved the Piece to Target Location!\n");
        if(aTurn == 0)
        printf("It's Alpha's Turn\n");
        else
        printf("It's Beta's Turn\n");
            break;
        case 1:
        printf("Invalid Move\n");
        if(aTurn == 0)
        printf("It's Alpha's Turn\n");
        else
        printf("It's Beta's Turn\n");
            break;
        case 2:
        printf("You Can't Eat There!\n");
        if(aTurn == 0)
        printf("It's Alpha's Turn\n");
        else
        printf("It's Beta's Turn\n");
            break;
        case 3:
        if(aTurn == 0) {
            printf("Successfully Captured Alpha Piece!\n");
            printf("It's Alpha's Turn\n");
        }
        else {
            printf("Successfully Captured Beta Piece!\n");
            printf("It's Beta's Turn\n");
        } 
    }
    // print piece positions [(x,y)]
    for(i = 0; i < MAX_ROW; i++)
    for(j = 0; j < MAX_COL; j++)
    if(Position[i][j] == 'O')
    ctr++;
    for(i = 0; i < MAX_ROW; i++)
    for(j = 0; j < MAX_COL; j++)
    if(Position[i][j] == 'X')
    ctr2++;
    
    printf("Alpha [O] (%d piece/s left): [", ctr);
    for(i = 0; i < MAX_ROW; i++) {
    for(j = 0; j < MAX_COL; j++) {
        if(Position[i][j] == 'O') {
            printf("(%d, %d)", i+1, j+1);
            k++;
            if(k != ctr)
            printf(", ");
            else
            printf("]\n");
            }
        }
    }
    k = 0; // reset
    printf("Beta [X] (%d piece/s left): [", ctr2);
    for(i = 0; i < MAX_ROW; i++) {
        for(j = 0; j < MAX_COL; j++) {
        if(Position[i][j] == 'X') {
            printf("(%d, %d)", i+1, j+1);
            k++;
            if(k != ctr2)
            printf(", ");
            else
            printf("]\n\n");
            }
        }
    }
    k = 0; // reset
    ctr = 0;
    ctr2 = 0;
    
    printf("Input current row of the piece: ");
    scanf("%d", &prev[0]);
    printf("Input current column of the piece: ");
    scanf("%d", &prev[1]);
    printf("Input row where you want the piece to move: ");
    scanf("%d", &next[0]);
    printf("Input column where you want the piece to move: ");
    scanf("%d", &next[1]);
    printf("\n");
    
    valid = NextPlayerMove(prev, next, Position, &aTurn, S);
    end = GameOver(Position, Beta, Alpha);
    } while (end != 0);
    return 0;
    }
}