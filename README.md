Welcome to Minesweeper!

This program allows the user to play Minesweeper from their console window.
This is a simplistic rendition of the classic game, tracking user inputs to target and uncover/flag squares throughout the grid.

HOW TO PLAY
    TRAVERSING MENUS
    When booting up the game (can be done with  ./minesweeper  in your choice Terminal/CMD), the user is met with the Opening Screen as to which they can enter certain commands
        Easy     Medium     Hard     Help     Quit
    Difficulty Levels (Easy, Medium, Hard): Begin the game with () amount of bombs.
        Easy: 9x9 Grid with 10 Bombs
        Medium: 16x16 Grid with 40 Bombs
        Hard: 16x30 Grid with 99 Bombs
    Help: Prints out a Help Screen
    Quit: Quits out of the game

    PLAYING THE GAME
    The input sequence is as follows:
        (1) input  row column  or input  Help  or  Quit
        (2) input  U  F  R
        (3) Repeat from (1)
    Minesweeper is a game where a number of mines are scattered throughout the grid. It is your job touncover all the areas not covered by these mines. There are 4 kinds of squares.
        (1) Empty Squares. They are indicated by blank space and indicate that no mines are adjacent.
        (2) Number Squares. They indicate how many mines surround the square itself.
            Ex. If the number is a '3', there are 3 mines in the 3x3 space surrounding the square.
        (3) Mine Squares. Indicated by an 'M', these squares indicate that a mine is on the square itself
            Tip: if you see this, then you have lost a life...
        (4) Flagged Squares. Indicated by an 'F', these squares have been flagged by the player to indicate a  
            potential mine.
            Tip: cannot uncover a flagged square

DETAILS
This program was created with C++ through Visual Studio code using Ubuntu 20.04.
The main feature of the program coding-wise would be the basic recursive nature in uncovering the squares.
Compilation is simply g++ minesweeper.cpp -o 'your_file_executable_name' .
Running is './your_file_executable_name' .
