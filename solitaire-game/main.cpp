/*---------------------------------------------
* Name: Caleb Rollf,  Data Structures: Solitaire-ish
* Description: Making a Solitaire-Like game. It does not have a full 
* set of cards, nor is the deck random by default because it takes 
* in the a deck (init.txt) from a commandline argument. You make your
*  move by typing in the pile # you want to move, followed by the pile 
* you want to move it to. J, Q, K, and A do not exist in this program
* ---------------------------------------------*/

#include "LL.h"
#include "LL.cpp"
#include <iostream>
#include <fstream>

/*---------------------------------------------
* Description: User-defined datatype cardType
* will hold the value of the card and the suit
* --------------------------------------------*/
struct cardType
{
  int face;                 //card numbers from 2-10. 
  char suit;                //'C'lubs;  'H'earts;  'D'iamonds; 'S'pades;
};

//global variables
const int STACK_SIZE = 5;   //initialize and declare a const int of size 5
LL<cardType>::iterator nil; //iterator nil is a nullptr of cardType


/*---------------------------------------------
* Description: prints all of the stacks
* ---------------------------------------------*/
void print(LL<cardType>::iterator topOfPile[], LL<cardType> piles[])
{
  for(int i = 0; i <= STACK_SIZE - 1; i++)        //FOR LOOP iterates from 0 to 4 (5 times)
  {
    //create a temp iterator to traverse through nodes to conserve top of pile
    LL<cardType>::iterator temp = topOfPile[i];

    std::cout << (i + 1) << ": ";  //output pile #

    if(temp != piles[i].begin())
    {
      temp--;                     //move temp back one space.

      while(temp != nil)          //while LOOP until temp reaches a nullptr
      {
        std::cout << "__ ";                      
        temp--;                   //traversal
      }
      temp = topOfPile[i];        //reset temp iterator
    }
    
    while(temp != nil)
    {
      std::cout << (*temp).face   //outputs face card
        << (*temp).suit           //outputs suit
        << " ";                   
        temp++;
    }
    std::cout << std::endl;       //newline
  }
}


/*---------------------------------------------
* Description: checks is the the move the user entered is valid by returning true or false
* depending on conditions inside the function. errorMsg is a pass by refernce variable and 
* when the function is finished, if there is an error, it will be reassigned to the specific
* error text.
*---------------------------------------------*/
bool isValidMove(LL<cardType>::iterator topOfPile[], LL<cardType> piles[],int val1, int val2, std::string &errorMsg)
{
  
  //stack range needs to be validated first to avoid seg fault
  bool rangeValid = (val1 >= 0 && val1 <= 4) && (val2 >= 0 && val2 <= 4);
  
  //assign errorMsg if:

  //range is not valid
  if(!rangeValid)                {errorMsg = "Out of range";                           return false;}
  //from piles array is empty
  if(piles[val1].isEmpty())      {errorMsg = "Cannot move card from empty stack";      return false;}
  //to piles array is empty
  else if(piles[val2].isEmpty()) {errorMsg = "Cannot move card to an empty stack";     return false;}

  bool topcard1red = false;     //initially set to false; card is black
  bool bottomCard2red = false;  //initially set to false; card is black

  LL<cardType>::iterator toBottomCard = piles[val2].end();
  
  //checks if the the numbers are valid
  bool numValid = ((*toBottomCard).face - 1) == ((*topOfPile[val1]).face);

  topcard1red    = ((*topOfPile[val1]).suit == 'D' || (*topOfPile[val1]).suit == 'H' );  //if true, card is red
  bottomCard2red = ((*toBottomCard).suit    == 'D' || (*toBottomCard).suit    == 'H' );  //if true, card is red
                        
  if((topcard1red == bottomCard2red || !numValid)) {errorMsg = "Invalid move";                           return false;}
  
  return true;                  //returns true if all conditions are satisfied
}


/*---------------------------------------------
* Description: This function controls the entire 
* game and is called until the game is finished.
* ---------------------------------------------*/
void game(LL<cardType>::iterator topOfPile[], LL<cardType> piles[])
{
  int val1 = 0;                     //from pile
  int val2 = 0;                     //to pile
  std::string errorMsg = "";        //holds the error message
  LL<cardType>::iterator it1, it2;  //create iterators

  print(topOfPile, piles);          //print stacks
  std::cout << "Make your move: ";  //prompt user
  std::cin >> val1 >> val2;         //player enters move

  //displays the user entered values
  std::cout << val1 << " " << val2 << std::endl;

  val1 -= 1;                   //decrement val1 to be valid for determining correct stack
  val2 -= 1;                   //decrement val2 to be valid for determining correct stack

  //runs if the move is valid
  if(isValidMove(topOfPile, piles, val1, val2, errorMsg))
  {
    if(topOfPile[val1] != piles[val1].end())
    {
      it1 = topOfPile[val1];
      it2 = piles[val1].end();
      topOfPile[val1]--;
      piles[val1].remove(it1);
      
      piles[val2].tailInsert(it1, it2);
    }
    else 
    {
      it1 = topOfPile[val1];
      topOfPile[val1]--;
      piles[val1].remove(it1);
      piles[val2].tailInsert(it1); 
    }
  }
  //runs if the move isn't valud
  else
  {
    std::cout << errorMsg << std::endl;
  }
}


/*---------------------------------------------
* Description: this function will be called by main 
* and it will keep being called as a condition check 
* to determine if the game is still in progress
* ---------------------------------------------*/
bool gameInProgress(LL<cardType>::iterator topOfPile[], LL<cardType> piles[])
{
  for(int i = 0; i <= STACK_SIZE - 1; i++)  //FOR LOOP iterates 5 times (0-4)
  {
    if(topOfPile[i] != piles[i].begin())  
    {
      return true;
    }
  }
  return false;
}


/*---------------------------------------------
* Description: main function will accept the deck from 
* a command line argument and will load cardType card
* ---------------------------------------------*/
int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    return 1;
  }

  LL<cardType> piles[STACK_SIZE];               
  LL<cardType>::iterator topOfPile[STACK_SIZE];
  std::ifstream cardFile;

  cardFile.open(argv[1]);
    
  for(int i = 0; i <= STACK_SIZE - 1; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      cardType card;
      cardFile >> card.face >> card.suit;
      piles[i].tailInsert(card);
    }
    topOfPile[i] = piles[i].end();  
  }

  while(gameInProgress(topOfPile,piles))
  {
    game(topOfPile,piles);
  }
  print(topOfPile, piles);

  return 0;
}
