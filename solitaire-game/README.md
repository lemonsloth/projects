# Mini "Solitaire" "Game"
### A simplified version of the classic card game Solitaire. (And also my first GitHub project!)

The main purpose of this project was to demonstrate my ability to implement Doubly Linked Lists and its functions, as well as operator overloading and templates. This was a school project and LL.h was created by faculty. However, the implementation of the Linked List (LL.cpp) and main.cpp was solely myself. I included LL.h in case you wanted to run it.

### Why is Solitaire and Game in Quotes?
This version of Solitaire does not include seven decks, a discard and draw pile, a foundation pile, nor is the deck random by default. The program receives a deck of card from a .txt commandline argument, in this case init.txt, and it's provided in the main files. This game also does not have jacks, queens, kings, and aces. Only cards 2-10. However, all of the other rules are the same. To move one pile to another, the suit color and rank must be the opposite color and the rank should be one lower. Whenever the top of the deck is face-down, its revealed! The win condition of this game is to reveal all of the cards in the five piles.

## How it Works

There are 4 files that are included in this repository to make it function: main.cpp, LL.cpp, LL.h, and init.txt. 

### LL.h
The header file LL.h defines the functions for the the LL and iterator classes and the node struct. The purpose of the iterator class is to help with traversing the doubly linked list. It uses increment, decrement, and comparisons operators to achieve this using operator overloading.

### LL.cpp

LL.cpp is the implemenation for the deep copy constructor, deconstructor, the overloaded function tailInsert, and various other functions. 

### main.cpp

The main file, main.cpp, is the implementation of the game itself and its rules. Main creates user-defined datatype, cardType, that holds the card rank and suit.
```
struct cardType
{
  int face;       //card numbers from 2-10. 
  char suit;      //'C'lubs;  'H'earts;  'D'iamonds; 'S'pades;
};
```

The main function will only run if it receives the correct amount of arguments from the command line. Then, it loads the piles from init.txt into an array of Linked Lists. Main will then keep calling a boolean function gameInProgress() that is used as a condition check to determine if the game is still in progress. Main will then call the game() function, prints the piles using print(), prompts the user to make its move, validates the move with isValidMove(), and then repeats until the game ends.

### init.txt

A text file that initializes the deck of cards to be put into the piles array.

## How to Run
```
g++ main.cpp
./a.out init.txt
```
