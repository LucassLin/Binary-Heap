/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PriorityQueue.h
 * Author: Lcc
 *
 * Created on 2017年3月12日, 下午2:30
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "event.h"
#include <iostream>
#include <utility>
#include <stdexcept>
using namespace std;

 class BinaryHeap
 {
 public:
BinaryHeap();
BinaryHeap( int capacity );
~BinaryHeap();
BinaryHeap(const BinaryHeap &obj);
BinaryHeap& operator = (const BinaryHeap &other);

 bool isEmpty( );

 void incrementKey(int pos, int value);
 
 void decrementKey(int pos, int value);

 void insert(  event x );
 event deleteMin( );

 int get_size();
 
 int front();
 
  int get_capacity();
 
 void resize(int n);


 
 

 

 

 private:
 unsigned int capacity; // capacity of array
 event* array; // The heap array
 unsigned int size;  //size of array
 void percolateDown(unsigned int hole );
 };
 
 int BinaryHeap::front(){
     return (array[1].get_time());
 }
 
 int BinaryHeap::get_size()
 {
     return size;
 }
 
BinaryHeap::BinaryHeap()
{
	array = NULL;
	capacity = 0;
	size = 0;
}

 
BinaryHeap::BinaryHeap(const BinaryHeap &obj)
{
	*this = obj;
}

BinaryHeap& BinaryHeap::operator = (const BinaryHeap &other)
{
	if (this != &other)
	{
		delete []array;
	}
	size = other.size;
	capacity = other.capacity;
	array = new event[other.size];
	for (unsigned int i=0; i<size; i++)
		{
			array[i] = other.array[i];
		}
	return *this;
		
}



 
 

BinaryHeap::BinaryHeap(int capacity)
{
	this->capacity = capacity;
        array =  new event[capacity];
        size = 0;
}

BinaryHeap::~BinaryHeap()
{
    //delete []array;
    
}

bool BinaryHeap::isEmpty ()
{
    return (size == 0);
}

void BinaryHeap::resize(int n)
{
	
    event* newarray;

    newarray = new event[n];

    for (unsigned int i=1; i<size; i++)
    {
        newarray[i] = array[i];}
    delete[] array;
	capacity = n;
    array = newarray;
	cout << "resize the array" <<endl;

    
    

}


 void BinaryHeap::insert( event x )
 {
     
     if( capacity-5 <=size && size <= capacity - 1 )
     {    
         resize(2*capacity);
     }
     
 
// Percolate up
 int hole = ++size;
 event copy = x;

 array[ 0 ] = copy;
 for( ; x < (array[ hole / 2 ]); hole /= 2 ) {
 array[ hole ] = ( array[ hole / 2 ] );
 }
 array[ hole ] = ( array[ 0 ] );
 
 }


event BinaryHeap::deleteMin( )
{
         
         if(size == 0)
         {
             return event(0,0,0,1);
             cout << "can't" <<endl;
         }
         
else
{
    
        
 event  return_value = array[1];
 array[ 1 ] = ( array[ size-- ] );
 percolateDown( 1 );
 

 return return_value;
}

 }

void BinaryHeap::percolateDown(unsigned int hole )
 {
 unsigned int child;
 event tmp = ( array[ hole ] );

 for( ; hole * 2 <= capacity; hole = child )
 {
 child = hole * 2;
 if( child != capacity && (array[ child + 1 ]) < (array[ child ]) )
 ++child;
 ;
 if( (array[ child ]) < (tmp) )
 {array[ hole ] = ( array[ child ] );}
 else
 {break;}
 }
 array[ hole ] = ( tmp );

 }


void BinaryHeap::incrementKey(int pos, int value)
{
    
    array[pos].set_time(value);
    percolateDown(pos);
}

void BinaryHeap::decrementKey(int pos, int value)
{
array[pos].set_time(-value);
    
    
 event copy = array[pos];

 array[ 0 ] = copy;   
 for( ; array[pos] < (array[ pos / 2 ]); pos /= 2 ) {
 array[ pos ] = ( array[ pos / 2 ] );
 }
 array[ pos ] = ( array[ 0 ] );
}

#endif /* PRIORITYQUEUE_H */

