/*
* Name: Caleb Rollf, CS302 Data Structures
* Description: Definitions for the non-defined functions and constructors
* in the LL.h header file.
*/

#include "LL.h"
#include <iostream>

//deep copy constructor for LL
template <class type>
LL<type>::LL(const LL<type>& copy)
{ 
  if(!copy.isEmpty())               //following code executes if !empty
  {
    node *temp = new node;          //dynamically allocate a new node
    temp->next = nullptr;           //set to nullptr
    temp->prev = nullptr;           //set to nullptr
    this->head = temp;              //head points to temp
    this->tail = temp;              //tail points to temp
    
    node *copytemp = copy.head;     //set copytemp ptr to its head
    
    while(copytemp != nullptr)      //iterate until reaches the tail
    {
      temp->data = copytemp->data;  //set copy data to temp's data 

      if(copytemp->next != nullptr) //makes sure there is an existing node
      {                             //before initializing a new temp node
        temp->next = new node;      //intialize the next node
        temp->next->prev = temp;    //have next node's prev ptr point to temp
        temp = temp->next;          //iterate temp
      }
      else                          //otherwise,
      {
        temp->next = nullptr;       //temp->next points to null pointer
      }
      copytemp = copytemp->next;    //iterate copytemp
      
    }
    this->tail = temp;              //tail points to temp
  }
}

template <class type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs)
{
  if (this != &rhs)                 //executes if not equal to each other
  {
    if(!this->isEmpty())            //checks if lhs is not empty
    {
      while(!this->isEmpty()) { headRemove(); } //delete every element
    }
    
    node *temp = new node;          //dynamically allocate a new node
    temp->next = nullptr;           //set to nullptr
    temp->prev = nullptr;           //set to nullptr
    this->head = temp;              //head points to temp
    this->tail = temp;              //tail points to temp
    
    node *rhsPtr = rhs.head;        //set rhsPtr to its head


    while(rhsPtr != nullptr)        //iterate until reaches the tail
    {
      temp->data = rhsPtr->data;    //set rhs's data to temp's

      if(rhsPtr->next != nullptr)   //makes sure there is an existing node to copy
      {                             //before initializing a new temp node

        temp->next = new node;      //intialize next node
        temp->next->prev = temp;    //have next node's prev ptr point to temp
        temp = temp->next;          //iterate temp
      }
      else                          //otherwise,
      {
        temp->next = nullptr;       //temp->next points to null pointer
      }
       rhsPtr = rhsPtr->next;       //iterate rhsPtr
    }
    this->tail = temp;              //tail points to temp
  }
  return *this;
}

template <class type>
LL<type>::~LL()
{
    //create a nodeptr that points to the nodeptr head points to
    node *currentPtr = head;
    
    //continue until it reaches the tail
    while (currentPtr != nullptr)
    {
        //store the next pointer before deleting currentPtr
        node *nextPtr = currentPtr->next;
        //delete node
        delete currentPtr;
        //update head to next node
        head = nextPtr;
        //move to next node
        currentPtr = nextPtr;
    }
    //set head to nullptr
    head = nullptr;
}

template <class type>
void LL<type>::tailInsert(const type& data)
{
  node *temp = new node;        //dynamically allocate a new node
  temp->data = data;            //set temp's data to passed val
  temp->next = nullptr;         //is a nullpointer
  temp->prev = nullptr;         //is a nullpointer

  if(this->isEmpty())           //if empty, assigns head and tail to new node
  { head = temp; tail = temp; }  
  else                          //otherwise,
  {
    this->tail->next = temp;    //make tail point to new node
    temp->prev = this->tail;    //connect temp to tail
    this->tail = temp;          //tail popints to new node
  }
}

//this function should be used after using the remove function
template <class type>
void LL<type>::tailInsert(const iterator& s, const iterator& t)
{
  if(tail != nullptr)
  {
    node *temp = this->tail;    //new temp pointing to tail
  
    temp->next = s.current;     //tail->next points to the first node of the severed list
    s.current->prev = temp;     //s.current->prev points to tail
    tail = t.current;           //tail now points to end of severed list
  }
  else
  {
    head = s.current;
    tail = t.current;
  }

}

template <class type>
void LL<type>::tailInsert(const iterator& s)
{
  if(tail != nullptr)
  {
    node *temp = this->tail;    //new temp pointing to tail

    tail->next = s.current;     //tail->next points to the first node of the severed list
    s.current->prev = tail;     //s.current->prev points to tail
    tail = s.current;           //tail now points to end of severed list
  }
  else
  {
    head = tail = s.current;
  }
}

template <class type>
void LL<type>::remove(iterator& it)
{

  node *tempS = it.current;     //tempS points to the severed node
  node *tempA;
  if(tempS != head)
  {
    tempA = tempS->prev;      //tempA now points to node before cut-off
    tempA->next = nullptr;    //sever connection
    tempS->prev = nullptr;    //sever connection
    tail = tempA;             //tail now points to node before cut-off
  }
  else
  {
    head = nullptr;
    tail = nullptr;
  }
}

template <class type>
void LL<type>::headRemove()
{
  //create a nodeptr that points to the node head points to
    node *currentPtr = head;

    //executes if there is at least one node
    if(currentPtr != nullptr)
    {
        //makes head point to next in link
        head = currentPtr->next;
        //makes the head prev null
        if(head != nullptr) { head->prev = nullptr; }
        else                { tail = nullptr; }
        //deletes node
        delete currentPtr;
    }
}
