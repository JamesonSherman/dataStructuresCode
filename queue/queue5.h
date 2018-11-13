// CSC 307 SP 2018 HW10
// ***FILE: queue5.h 
// ***Adapted from queue4.h, available at http://www.cs.colorado.edu/~main/chapter8/queue4.h,
//    to work with "the queue class using a circular linked list"
//    as described in Chapter 8 Programming Project 6.

// ***Relevant comments from queue4.h are below. 
// FILE: queue4.h 
// TEMPLATE CLASS PROVIDED: queue<Item> (a queue of items)

// CONSTRUCTOR for the queue<Item> template class:
//   queue( )
//     Postcondition: The queue has been initialized as an empty queue.
//
// MODIFICATION MEMBER FUNCTIONS for the queue<Item> template class:
//   Item& front( ) 
//     Precondition: size( ) > 0
//     Postcondition: The return value is a reference to the item at
//     the front of the queue (and the queue is unaltered).
//
//   void pop( )
//     Precondition: size( ) > 0.
//     Postcondition: The front item of the queue has been removed.
//
//   void push(const Item& entry)
//     Postcondition: A new copy of entry has been inserted at the rear of the
//     queue.
//
// CONSTANT MEMBER FUNCTIONS for the queue<Item> template class:
//   bool empty( ) const
//     Postcondition: The return value is true if the queue is empty.
//
//   const Item& front( ) const
//     Precondition: size( ) > 0
//     Postcondition: The return value is a const reference to the item at
//     the front of the queue (and the queue is unaltered).
//
//   size_type size( ) const
//     Postcondition: The return value is the total number of items in the queue.
//
// VALUE SEMANTICS for the queue<Item> template class:
//   Assignments and the copy constructor may be used with queue<Item> objects.

#ifndef MAIN_SAVITCH_QUEUE5_H     // Prevent duplicate definition
#define MAIN_SAVITCH_QUEUE5_H
#include <cstdlib>   // Provides std::size_t
#include "node3.h"   // Node template class

namespace main_savitch_8D
{
    template <class Item>
    class queue
    {
    public:
        // TYPEDEFS 
        typedef std::size_t size_type;
        typedef Item value_type;
        // CONSTRUCTORS and DESTRUCTOR
        queue( );
		queue(const queue<Item>& source);
		~queue( );
        // MODIFICATION MEMBER FUNCTIONS
		Item& front( );
        void pop( );
        void push(const Item& entry);
		void operator =(const queue<Item>& source);
        // CONSTANT MEMBER FUNCTIONS
        bool empty( ) const { return (count == 0); }
		const Item& front( ) const;
		size_type size( ) const { return count; }
    private:
        node<Item> *rear_ptr; 
        size_type count;       // Total number of items in the queue
    };
}

#include "queue5.template" // Include the implementation
     
#endif
