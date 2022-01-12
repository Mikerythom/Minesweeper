#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

/* GLOBAL VARIABLES */
int numRows, numCols, diff;

void printMainScreen()
{

    cout << " _______________________________ " << endl;
    cout << "|                               |" << endl;
    cout << "|     Welcome to Minesweeper    |" << endl;
    cout << "|                               |" << endl;
    cout << "| Difficulties:                 |" << endl;
    cout << "|   Easy     (10 bombs)         |" << endl;
    cout << "|   Medium   (40 bombs)         |" << endl;
    cout << "|   Hard     (99 bombs)         |" << endl;
    cout << "|                               |" << endl;
    cout << "|   Help                 Quit   |" << endl;
    cout << "|_______________________________|" << endl;
    cout << endl;
    cout << "Please Choose a Difficulty" << endl << endl;
    cout << "Tip: Type  Help  for Controls" << endl;

}

void printHelpScreen()
{
    cout << " _______________________________ " << endl;
    cout << "|                               |" << endl;
    cout << "|          Help Screen          |" << endl;
    cout << "|                               |" << endl;
    cout << "| How to Play?                  |" << endl;
    cout << "| Minesweeper is a classic game |" << endl;
    cout << "| where a number of bombs are   |" << endl;
    cout << "| hidden within the grid. Your  |" << endl;
    cout << "| goal is to uncover all of the |" << endl;
    cout << "| safe squares while avoiding   |" << endl;
    cout << "| the mines!                    |" << endl;
    cout << "|                               |" << endl;
    cout << "| Choosing a Difficulty:        |" << endl;
    cout << "|   Inputs  Easy  Medium  Hard  |" << endl;
    cout << "| Selecting a Square:           |" << endl;
    cout << "|   Input   Row Column          |" << endl;
    cout << "| Uncover a Square:             |" << endl;
    cout << "|   Input   U                   |" << endl;
    cout << "| Flag a Square:                |" << endl;
    cout << "|   Input   F                   |" << endl;
    cout << "| Giving up:                    |" << endl;
    cout << "|   Input   Quit                |" << endl;
    cout << "|_______________________________|" << endl;
    cout << endl;

}

void printGameScreen(char** playerField, int numRows, int numCols, int lives)
{

    cout << "Lives: " << lives << endl;
    cout << "  ";
    if(diff==1){
        cout << "123456789" << endl;
    }
    else if(diff==2){
        cout << " 0        1      " << endl;
        cout << "   1234567890123456" << endl;
    }
    else if(diff==3){
        cout << " 0        1         2         3" << endl;
        cout << "   123456789012345678901234567890" << endl;
    }
    for(int i=0; i<numRows; i++){
        if(i<9 && (diff==2 || diff==3)){
            cout << i+1 << "  ";
        }
        else{
            cout << i+1 << " ";
        }
        for(int j=0; j<numCols; j++){
            cout << playerField[i][j];
        }
        cout << endl;
    }
    cout << endl;

}

void printWinScreen()
{

    cout << " _______________________________ " << endl;
    cout << "|                               |" << endl;
    cout << "|        CONGRATULATIONS        |" << endl;
    cout << "|           YOU  WON!           |" << endl;
    cout << "|        HERE'S A COOKIE        |" << endl;
    cout << " _______________________________ " << endl;

}

void printLoseScreen()
{

    cout << " _______________________________ " << endl;
    cout << "|                               |" << endl;
    cout << "|        Y O U   D I E D        |" << endl;
    cout << " _______________________________ " << endl;

}

void printByeScreen()
{

    cout << " _______________________________ " << endl;
    cout << "|                               |" << endl;
    cout << "|            GOODBYE            |" << endl;
    cout << " _______________________________ " << endl;

}

void uncover(char** field, char** playerField, int row, int col){

    /* STOPS WHEN ENCOUNTERING MINE */
    if(field[row][col]=='M'){
        return;
    }
    /* COPIES NUMBER OVER BUT STOPS */
    if(field[row][col]!=' '){
        playerField[row][col] = field[row][col];
        return;
    }
    /* ALREADY UNCOVERED TILE */
    if(playerField[row][col]==' '){
        return;
    }
    /* RECURSIVE CASE: REVEALING ALL ADJACENT EMPTY SPACES */
    playerField[row][col] = field[row][col];
    if(row-1>=0){
        if(col-1>=0){
            uncover(field, playerField, row-1, col-1);
        }
        uncover(field, playerField, row-1, col);
        if(col+1<numCols){
            uncover(field, playerField, row-1, col+1);
        }
    }
    if(col-1>=0){
        uncover(field, playerField, row, col-1);
    }
    if(col+1<numCols){
        uncover(field, playerField, row, col+1);
    }
    if(row+1<numRows){
        if(col-1>=0){
            uncover(field, playerField, row+1, col-1);
        }
        uncover(field, playerField, row+1, col);
        if(col+1<numCols){
            uncover(field, playerField, row+1, col+1);
        }
    }

}

bool isComplete(char** field, char** playerField)
{

    for(int i=0; i<numRows; i++){
        for(int j=0; j<numCols; j++){
            if((playerField[i][j]=='#' || playerField[i][j]=='F') && field[i][j]!='M'){
                return false;
            }
        }
    }
    return true;

}

int main(int argc, char* argv[])
{

    string input, temp, difficulty="invalid";
    while(!difficulty.compare("invalid")){
        printMainScreen();
        cin >> input;
        if(!input.compare("Help") || !input.compare("help")){
            printHelpScreen();
            cout << "Enter a key to continue..." << endl;
            cin >> temp;
        }
        else if(!input.compare("Quit") || !input.compare("quit")){
            printByeScreen();
            return 0;
        }
        else if(!input.compare("Easy") || !input.compare("easy") || !input.compare("Medium")\
            || !input.compare("medium") || !input.compare("Hard") || !input.compare("hard")){
            difficulty = input;
        }
        else{
            cout << "Invalid response..." << endl;
        }
    }

    /* NORMALIZING TO LOWERCASE */
    if(input[0] < 'a')
        input[0] += (char)32;
    
    /* SETTING UP THE GAME */
    char** field;
    char** playerField;
    if(!input.compare("easy")){
        numRows = 9;
        numCols = 9;
        field = new char*[9];
        playerField = new char*[9];
        for(int i=0; i<9; i++){
            field[i] = new char[9];
            playerField[i] = new char[9];
        }
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                field[i][j] = ' ';
                playerField[i][j] = '#';
            }
        }
        for(int i=0; i<10; i++){
            int randomNumber = rand()%81;
            /* ENSURING NO REPEATED MINES */
            if(field[randomNumber/9][randomNumber%9]=' '){
                field[randomNumber/9][randomNumber%9] = 'M';
            }
            else{
                i--;
            }
        }
        diff=1;
    }
    else if(!input.compare("medium")){
        numRows = 16;
        numCols = 16;
        field = new char*[16];
        playerField = new char*[16];
        for(int i=0; i<16; i++){
            field[i] = new char[16];
            playerField[i] = new char[16];
        }
        for(int i=0; i<16; i++){
            for(int j=0; j<16; j++){
                field[i][j] = ' ';
                playerField[i][j] = '#';
            }
        }
        for(int i=0; i<40; i++){
            int randomNumber = rand()%256;
            /* ENSURING NO REPEATED MINES */
            if(field[randomNumber/16][randomNumber%16]=' '){
                field[randomNumber/16][randomNumber%16] = 'M';
            }
            else{
                i--;
            }
        }
        diff=2;
    }
    else{
        numRows = 16;
        numCols = 30;
        field = new char*[16];
        playerField = new char*[16];
        for(int i=0; i<16; i++){
            field[i] = new char[30];
            playerField[i] = new char[30];
        }
        for(int i=0; i<16; i++){
            for(int j=0; j<30; j++){
                field[i][j] = ' ';
                playerField[i][j] = '#';
            }
        }
        for(int i=0; i<99; i++){
            int randomNumber = rand()%480;
            /* ENSURING NO REPEATED MINES */
            if(field[randomNumber/30][randomNumber%30]=' '){
                field[randomNumber/30][randomNumber%30] = 'M';
            }
            else{
                i--;
            }
        }
        diff=3;
    }
    /* COUNTING NEARBY MINES */
    for(int i=0; i<numRows; i++){
        for(int j=0; j<numCols; j++){
            if(field[i][j]=='M'){
                continue;
            }
            int counter=0;
            if(i-1>=0 && j-1>=0){ //topleft
                if(field[i-1][j-1]=='M'){
                    counter++;
                }
            }
            if(i-1>=0){ //top
                if(field[i-1][j]=='M'){
                    counter++;
                }
            }
            if(i-1>=0 && j+1<numCols){ //topright
                if(field[i-1][j+1]=='M'){
                    counter++;
                }
            }
            if(j-1>=0){ //left
                if(field[i][j-1]=='M'){
                    counter++;
                }
            }
            if(j+1<numCols){ //right
                if(field[i][j+1]=='M'){
                    counter++;
                }
            }
            if(i+1<numRows && j-1>=0){ //bottomleft
                if(field[i+1][j-1]=='M'){
                    counter++;
                }
            }
            if(i+1<numRows){ //bottom
                if(field[i+1][j]=='M'){
                    counter++;
                }
            }
            if(i+1<numRows && j+1<numCols){ //bottomright
                if(field[i+1][j+1]=='M'){
                    counter++;
                }
            }
            if(counter>0){
                field[i][j] = (char)counter+48;
            }
            else if(counter==0){
                field[i][j] = ' ';
            }
        }
    }
    int lives = 3;
    cout << "You will be given 3 lives. Make them count..." << endl;
    /* GAME LOGIC */
    while(lives>0){
        printGameScreen(playerField,numRows,numCols,lives);
        int chosenRow, chosenCol;
        char tempInput = NULL;
        cout << "Input:  Row Column" << endl;
        cin >> input;
        if(!input.compare("help") || !input.compare("Help")){
            printHelpScreen();
            cout << "Enter a key to continue..." << endl;
            cin >> temp;
            continue;
        }
        else if(!input.compare("Quit") || !input.compare("quit")){
            printByeScreen();
            return 0;
        }
        else if(input.length()>1){
            cout << "Invalid Response." << endl;
            continue;
        }
        stringstream split(input);
        split >> chosenRow;
        cin >> chosenCol;
        chosenRow--;
        chosenCol--;
        if(chosenRow<0 || chosenRow>=numRows){
            cout << "Please choose a valid row!" << endl;
            continue;
        }
        if(chosenCol<0 || chosenCol>=numCols){
            cout << "Please choose a valid column!" << endl;
            continue;
        }
        cout << "Choose: (U)ncover , (F)lag , (R)eselect" << endl;
        cin >> tempInput;
        switch(tempInput){
            case 'U':
                cout << "Chosen to Uncover Row: " << chosenRow+1 << " Column: " << chosenCol+1 << endl;
                if(playerField[chosenRow][chosenCol]!='#'){
                    if(playerField[chosenRow][chosenCol]=='F'){
                        cout << "Cannot uncover a flagged square." << endl;
                    }
                    else{
                        cout << "Cannot uncover an already uncovered square." << endl;
                    }
                }
                else if(field[chosenRow][chosenCol]=='M'){
                    cout << "BOOOOM! UH OH! You have hit a mine..." << endl;
                    playerField[chosenRow][chosenCol] = 'M';
                    lives--;
                }
                else{
                    uncover(field, playerField, chosenRow, chosenCol);
                }
                break;
            case 'F':
                cout << "Chosen to Flag Row: " << chosenRow+1 << " Column: " << chosenCol+1 << endl;
                if(playerField[chosenRow][chosenCol]=='F'){
                    cout << "You are unflagging this square." << endl;
                    playerField[chosenRow][chosenCol] = '#';
                }
                else if(playerField[chosenRow][chosenCol]=='#'){
                    playerField[chosenRow][chosenCol] = 'F';
                }
                else{
                    cout << "Cannot flag an uncovered square." << endl;
                }
                break;
            case 'R':
                cout << "Chosen to Reselect" << endl;
                break;
            default:
                cout << "Option is nonexistent, default to Reselect" << endl;
        }
        if(isComplete(field, playerField)){
            printGameScreen(playerField,numRows,numCols,lives);
            printWinScreen();
            return 0;
        }
    }
    printLoseScreen();

    return 0;
}