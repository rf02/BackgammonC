/*
This is to certify that this project is my/our own work, based on my/our personal efforts in studying and applying
the concepts learned. We have constructed the functions and their respective algorithms and corresponding codes
either individually or with my group mate. The program was run, tested, and debugged by my/our own efforts. I/We
further certify that I/we have not copied in part or whole or otherwise plagiarized the work of other students/groups
and/or persons.

Hiraya Buan                 Rulet Fulo
DLSU ID 12119113            DLSU ID 12179043

*/

//Description: Functions are mostly void or for checking validity 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define ENABLE 1

//global variables

char board[12][13]; // game board

int startCol, endCol; //to get the moves from the player

int edible = 0; //initialize edible pieces

int playerTurn = 1; //initialize player turn

int P1Main = 0;     //player 1 pieces in homeboard
int P2Main = 0;     //player 2 pieces in homeboard
int P1Winning = 0;  //+1 is winning condition for P1
int P2Winning = 0;  //+1 is winning condition for P2

//player profile
typedef struct player{

    char Name[25];
    int color;
    char piece;
    
}Player;

//get players' names
void getName(Player *P1, Player *P2){

    printf("Enter your name Player 1: ");
    fgets(P1->Name, 25, stdin);
    
    printf("Hello %s\n", P1->Name);
 
    //Player 2 name
    printf("Enter your name Player 2: ");
    fgets(P2->Name, 25, stdin);

    printf("Hello %s\n", P2->Name);

}

//remove color
void removeColor(){
    printf("\x1b[0m");
}

//put color
void inputColor(Player p){

    if(ENABLE){
        if(p.color == 1){
            printf("\x1b[38;5;196m");
        }
        else{
            printf("\x1b[38;5;247m");
        }
    }
}

//Return Dice Number
int DiceRandomizer(int count){
    int num = 0;

    for (int i = 0; i < count; i++) {
        num = (rand() % (6)) + 1;
    }
    return num;
}

//Return first player
int ReturnPlayer(){
    int FirstRes, SecondRes;
    int ret = 1; 

    srand(time(0));
    FirstRes = DiceRandomizer(3);
    SecondRes = DiceRandomizer(3);
    printf("Roll 1: %d\n", FirstRes);
    printf("Roll 2: %d\n\n", SecondRes);
    //loop if same number
    if(FirstRes == SecondRes){
        while(FirstRes == SecondRes){
            printf("Rolling Again.\n");
            FirstRes = DiceRandomizer(3);
            SecondRes = DiceRandomizer(3);
            printf("Roll 1: %d\n", FirstRes);
            printf("Roll 2: %d\n\n", SecondRes);
        };
    }

    if(FirstRes > SecondRes)
    ret = 0;

    return ret;
}

//roll dice to determine which player goes first
void determineOrder(Player *P1, Player *P2, Player *PTemp){

    if(ReturnPlayer() == 0){
        printf("First Move: %s", P1->Name);
        printf("Second Move: %s\n", P2->Name);
    }else{
        //swap Pname1 and Pname2 if first move is  Pname2
        strcpy(PTemp->Name, P2->Name);
        strcpy(P2->Name, P1->Name);
        strcpy(P1->Name, PTemp->Name);
    }
    
        printf("First Player: %s", P1->Name);
        printf("Second Player: %s\n", P2->Name);

}

//let the player choose their color
void chooseColor(Player *P1, Player *P2){

    char choice;

    printf("Choose your color, %s([R]ed or [G]rey): ", P1->Name);
    while(choice != 'r' && choice != 'R' && choice != 'g' && choice != 'G'){
    scanf("%c", &choice);
    	switch(choice){
        case 'r':
        case 'R': 
            P1->color = 1;
            P2->color = 2;
            inputColor(*P1);
            printf("\nred is %s", P1->Name);
            removeColor();
            inputColor(*P2);
            printf("grey is %s", P2->Name);
            removeColor();
            break;
        case 'g':
        case 'G': 
            P1->color = 2;
            P2->color = 1;
            inputColor(*P1);
            printf("\ngrey is %s", P1->Name);
            removeColor();
            inputColor(*P2);
            printf("red is %s", P2->Name);
            removeColor();
            break; 
		default: 
			printf("Try Again: ");
		}
    }
}

//initialize the starting pieces of player 1 and player 2
void initializeBoard(char board[][13], Player P1, Player P2, Player PTemp){
    int i,j; 

    for( i = 0; i < 12; i++){
        for( j = 0; j < 13; j++){
            board[i][j] = PTemp.piece;
            switch(i){
                case 0: 
                    board[i][0] = P1.piece;
                    board[i][4] = P2.piece;
                    board[i][6] = P2.piece;
                    board[i][11] = P1.piece; 
                        break;
                case 1: 
                    board[i][0] = P1.piece;
                    board[i][4] = P2.piece;
                    board[i][6] = P2.piece;
                    board[i][11] = P1.piece; 
                        break;
                case 2: 
                    board[i][0] = P1.piece;
                    board[i][4] = P2.piece;
                    board[i][6] = P2.piece; 
                        break;
                case 3: 
                    board[i][0] = P1.piece;
                    board[i][6] = P2.piece; 
                        break;
                case 4: 
                    board[i][0] = P1.piece;
                    board[i][6] = P2.piece; 
                        break;
                case 5:
                case 6: 
                    board[i][j] = '-'; 
                            break;
                case 7: 
                    board[i][0] = P2.piece;
                    board[i][6] = P1.piece; 
                        break;
                case 8: 
                    board[i][0] = P2.piece;
                    board[i][6] = P1.piece; 
                        break;
                case 9: 
                    board[i][0] = P2.piece;
                    board[i][4] = P1.piece;
                    board[i][6] = P1.piece; 
                        break;
                case 10: 
                    board[i][0] = P2.piece;
                    board[i][4] = P1.piece;
                    board[i][6] = P1.piece;
                    board[i][11] = P2.piece; 
                        break;
                case 11:
                    board[i][0] = P2.piece;
                    board[i][4] = P1.piece;
                    board[i][6] = P1.piece;
                    board[i][11] = P2.piece; 
                        break;
            }
        }
    }
}

//Display the board
void PrintTable(char board[][13], Player P1, Player P2, Player PTemp){
   
   int i, j;
   
    printf("\n|00||01||02||03||04||05||06||07||08||09||10||11|\n"); 
    printf("------------------------------------------------\n");
    for(i = 0; i < 12; i++){
        for(j = 0; j < 12; j++){   
                if(board[i][j] == P1.piece){
                    inputColor(P1);
                    printf("|%2c|", board[i][j]);
                    removeColor();
                }
                else if(board[i][j] == P2.piece){
                    inputColor(P2);
                    printf("|%2c|", board[i][j]);
                    removeColor();
                }
                else{
                    printf("|%2c|", board[i][j]);
                }
                 //print whole board
            }
            printf("\n");
        }
    printf("-------------------------------------------------\n");
    printf("|12||13||14||15||16||17||18||19||20||21||22||23|\n");
}

//check if starting is viable
int checkerStart(int startCol, char play, char noPlay){
    int i,j;

    if(startCol >= 0 && startCol <= 11){
        for(int i = 4; i >= 0; i--){
            if(board[i][startCol] == play){
                return i;
            }
            else if(board[i][startCol] == noPlay){
                return -1;
            }
        }
        return -1;
    }
    else if (startCol >= 12 && startCol <= 23){
        startCol = startCol - 12;
        for(int i = 7; i <= 11; i++){
            if(board[i][startCol] == play){
                return i;
            }
            else if(board[i][startCol] == noPlay){
                return -1;
            }
        }
        return -1;
    }

}

//check if destination is viable
int checkerEnd(int endCol, char play, char noPlay){
    int i,j;
    edible = 0;
    int spaces = 0;
    if(endCol >= 0 && endCol <= 11){
        if(board[4][endCol] == ' '){
            for( i = 4; i >= 0; i--){
                if(board[i][endCol] == ' '){
                    spaces++;
                }
                else if(board[i][endCol] == noPlay){
                    if(spaces > 3){
                        edible = 1;
                        return i;
                    }
                    else{
                        return -1;
                    }
                    
                }
                else{
                    return i+1;
                }
            }
            return 0;
        }
        else{
            return -1;
        }
    }
    else if (endCol >= 12 && endCol <= 23){
        endCol = endCol - 12;
        if(board[7][endCol] == ' '){
            for( i = 7; i <= 11; i++){
                if(board[i][endCol] == ' '){
                    spaces++;
                }
                else if(board[i][endCol] == noPlay){
                    if(spaces > 3){
                        edible = 1;
                        return i;
                    }
                    else{
                        return -1;
                    }
                    
                }
                else{
                    return i-1;
                }
            }
            return 11;
        }
        else{
            return -1;
        }
    }
}

//check how many player pieces are in their main board
void checkBoard(Player P1, Player P2){
    int i,j;
    P1Main = 0;
    P2Main = 0;
    for( i = 0; i < 12; i++){
        for( j = 0 ; j < 5; j++){
            if(board[j][i] == P1.piece){
                P1Main++;
            }
            
        }
    }

    for( i = 0; i < 12; i++){
        for( j = 7 ; j < 12; j++){
            if(board[j][i] == P2.piece){
                P2Main++;
            }
        }
    }  
}

//get players' move and move the piece
int getMove(Player P1, Player P2){
    int i,j;
    int start = 0;
    int end = 0;
    int flag = 0;
    int capture;
    char play = P1.piece;
    char noPlay = P2.piece;
    int dice; 

    //determine turn of player
    if(playerTurn == 1){
        printf("\nmove of %s", P1.Name);
    }
    else{
        printf("\nmove of %s", P2.Name);
        play = P2.piece;
        noPlay = P1.piece;
    }

    //check if any captured piece detected on bar
    for(int i = 0 ; i < 12; i++){
        if(board[5][i] == play){
            startCol = i;
            capture = 5;
            flag = 1;
        }
        if(board[6][i] == play){
            startCol = i + 12;
            capture = 6;
            flag = 1;
        }
    }

    //roll dice
    dice = DiceRandomizer(3);
    printf("\nYour Roll: %d", dice);

    //prompt starting move of player
    if(flag != 1){
        printf("\nInput column start: ");
        scanf("%d", &startCol);
        start = checkerStart(startCol, play, noPlay);
    }
    else{
        printf("\nDetected captured piece at column %d\n", startCol);
        start = capture;
    }
    
    //prompt ending move of player
    printf("Input column destination: ");
    scanf("%d", &endCol);
    end = checkerEnd(endCol, play, noPlay);
    if(start == -1 || end == -1||abs(endCol - startCol) != dice){
        printf("INVALID MOVE\n");
        return 0;
    }
    
    //change the pieces on the board
    if(flag == 1){
       board[start][startCol] = '-'; 
    }
    else{
        if(startCol > 11){
            board[start][startCol - 12] = ' ';
        }
        else{
            board[start][startCol] = ' ';
        }
        
    }
    
    if(endCol > 11){
        board[end][endCol - 12] = play;
    }
    else{
        board[end][endCol] = play;
    }

    //move captured piece to bar
    if(edible == 1){
        if(endCol > 11){
            board[6][endCol] = noPlay;
            }
            else{
                board[5][endCol] = noPlay;
            }
        }
    
    //reset turn after done
    if(playerTurn == 2){
        //Player1 action
        playerTurn = 1;
    }
    else{
        //Player2 action
        playerTurn++;
    }

    //start the late game
    if(P1Main == 15){
        P1Winning = 1;
    }
    if(P2Main == 15){
        P2Winning = 1;
    }

    //function for removing the pieces during late game
    if(P1Winning == 1){
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 13; j++){
                if(dice == 11 - startCol){
                board[i][startCol] = ' ';
                }
            }
        }
    }
    else if(P2Winning == 1){
        for(int i = 0; i < 12;i++){
            for(int j = 0; j < 13; j++){
                if(dice == 11 - startCol){
                    board[i][startCol] = ' ';       
                }
            }
        }
    }
    
    return 0;
}

//main function
int main(){

    Player P1, P2, PTemp; //player profiles
    int winner = 0; //initialize board with no winner
    
    P1.piece = 'X'; //Player 1 piece
    P2.piece = 'O'; //Player 2 piece
    PTemp.piece = ' ';//Blank piece
       
    //functions before game start
    getName(&P1, &P2);      //to get the players' Names
    determineOrder(&P1, &P2, &PTemp);   //to determine which player will go first
    chooseColor(&P1, &P2);  //let the player choose which color to play

    //main game start
    printf("\n");
    
    //to initialize starting board
    initializeBoard(board, P1, P2, PTemp);
    
    //main game loop
    while(winner == 0){
        checkBoard(P1, P2);
        PrintTable(board, P1, P2, PTemp);
        getMove(P1, P2);
        
        //determine the winner in late game
        if(P1Winning == 1 && P1Main == 0){
            winner++;
        }
        else if(P2Winning == 1 && P2Main == 0){
            winner++;
        }
    }
    //print the winner of the game
    if(winner == 1 && P1Main == 0){
        inputColor(P1);
        printf("\n\n\nWINNER IS %s", P1.Name);
    }
    else if(winner == 1 && P2Main == 0){
        inputColor(P2);
        printf("\n\n\nWINNER IS %s", P2.Name);
    }

    //end the game  
    return 0;
}