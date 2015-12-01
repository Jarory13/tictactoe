/**
** A command line version of Tic Tac Toe
** By Erik Jarory de Jesus
** Complete Date: 10/02/15
**
** This is my own personal version of tic tac toe for 2 players.
** The function to update the board state is seperate so that
** it can be called multiple times. The checkwin function
** is kept as a seperate function to reduce clutter main function.
** To playUsers should input a number corresponding to a space on 
** the grid. Game ends when a player gets 3 in a row. 
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define COLS 3
#define ROWS 3

//set global variables 
int gameplay[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char unused = '*';
char player1icon = 'X';
char player2icon = 'O';
bool xwin = false;
bool owin = false;
char* promptmove = "Enter the number where you'd like to move \n"; 

//prototypes 
void updatedBoard(void);
bool checkwin(void);

//Play the game

int main(void){

    //seet needed variables 
    bool player1turn =true;
    int turncount = 0;

    //welcome player
    printf("Hello, Welcome to Tic Tac Toe. \n");
    
    //fetch and print instructions to screen.
    FILE* fp = fopen("instruct.txt", "r");
    
    //abort if error with file
    if (fp == NULL)
    {
        printf("something went wrong, please reload instructions");
        return 1;
    }
    
    //print instructions to screen from instruc.txt
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)){
        printf("%c", c);
    }
    
    //create the board and prompt first move
    updatedBoard();
    
    //begin game, game runs as long as gameover is false
    while(xwin != true && owin != true && turncount < 9){       
        
        //get move from user
        int move;
        scanf ("%d",&move);
        
        //if invalid, reprompt user
        if(move < 1 || move > 9 || gameplay[move-1] > 0) {
            printf("That's not a valid move. \n");
            printf("%s", promptmove);
            scanf ("%d",&move);
        }
        
        /**
        Set the value of the gameplay array, at the location equal
        to the user's input, equal to the value for the player.
        1 for player 1 or 2 for player 2.
        */
        if(player1turn == true) {
           gameplay[move-1] = 1;
           player1turn = false;
            
        }
        else{
            gameplay[move-1] = 5;
            player1turn = true;
        }
        
        //updated the board state and turn count
        updatedBoard();
        turncount++;
        
        //cheeck if a vicotry condition is met, if so end game and declare the victor
        checkwin();
        if(owin == true || xwin == true) {
            if(xwin == true) {
                printf("Player 1 wins. \n");
            }
            else if(owin == true){
                printf("Player 2 wins. \n");
            }
          
        }
        
    }
    
    //if draw, end game. 
    if(xwin != true && owin != true) {
        printf("It's a darw! \n");
    }
    
     //thank the user
     printf("Thank's for playing! \n");
    
    //close the instruction.txt file and terminate the program. 
    fclose(fp);
}

/** creates the 3x3 grid of characters
**  This function is also called to update the board
**  and print the "x", "o", and "*" characters.
**/
void updatedBoard(void) {
    //flag vairables
    int check = 0;
    char tmp;
    
    //make rows
    for(int i = 0; i < ROWS; i++) {
    
        //make columns
        for(int j = 0; j<  COLS; j++) {
        
            //add an "x" if player has placed one there
            if(gameplay[check] == 1) {
                tmp = player1icon;
                }
            //add a "o" if player has placed on there    
            else if (gameplay[check] == 5) {
                tmp = player2icon;
                }
            
            //add a "*" if unused    
            else{
                tmp = unused;
                } 
            printf("%i.%c", check+1,tmp);
            printf(" ");
            check++;
            }
        printf("\n");    
        }
        
   printf("\n");
   //prompt user to move     
   printf("%s",promptmove);    
}

/** checks to see if vicotry condition is met
**  If a victory conditions is found for either x or o, it'll 
**  change the corressponding bool to true. 
**  variables checker 1 and 2 will examine rows and columns.
**  Special cases are made for diagnoal victory conditions.
**  will return false if no victory condition is met. 
**/
bool checkwin(void){
   
    //set all the variable to check vicotyr against
    int checker1 = 0;
    int checker2 = 0;
    int checkdag1 = 0;
    int checkdag2 = 0;
    
    //check for win conditions 
    for(int i = 0; i < ROWS; i++) {

            //check columns
            checker1 = gameplay[i] + gameplay[i+3] + gameplay[i+6];
            
            //check rows
            checker2 = gameplay[i*3] + gameplay[(i*3)+1] + gameplay[(i*3)+2];
      
            //check diagnoals
            checkdag1 = gameplay[0] + gameplay[4] + gameplay[8];
            checkdag2 = gameplay[2] + gameplay[4] + gameplay[6];
      
            //if any check equates to three, victory goes to player 1
            if(checker1 == 3 || checker2 == 3  || checkdag1 == 3 || checkdag2 == 3) {
                xwin = true;
                return true;
            }
            
            //if any check equates to 15, victory goes to player 2
            else if (checker1 == 15 || checker2 == 15  || checkdag1 == 15 || checkdag2 == 15) {
                owin = true;
                return true;
            }   
    }
    
    //victory not found, return false. 
    return false;
    
}




