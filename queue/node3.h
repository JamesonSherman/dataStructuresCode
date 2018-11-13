// CSC 307 SP 2018 HW10
// ***FILE: node3.h 
// ***Adapted from node2.h, available at http://www.cs.colorado.edu/~main/chapter8/node2.h,
//    to work with "the queue class using a circular linked list"
//    as described in Chapter 8 Programming Project 6.

// ***Note that this file does _not_ include list manipulation functions.

// ***Relevant comments from node2.h are below. 
// FILE: node2.h (part of the namespace main_savitch_6B)
// PROVIDES: A template class for a node in a linked list...
// The template parameter is the type of the data in each node.

//
// TYPEDEF for the node<Item> template class:
//   Each node of the list contains a piece of data and a pointer to the
//   next node. The type of the data (node<Item>::value_type) is the Item type
//   from the template parameter. The type may be any of the built-in C++ classes
//   (int, char, ...) or a class with a default constructor, an assignment
//   operator, and a test for equality (x == y).

// CONSTRUCTOR for the node<Item> class:
//   node(
//     const Item& init_data = Item(),
//     node* init_link = NULL
//   )
//     Postcondition: The node contains the specified data and link.
//     NOTE: The default value for the init_data is obtained from the default
//     constructor of the Item. In the ANSI/ISO standard, this notation
//     is also allowed for the built-in types, providing a default value of
//     zero. The init_link has a default value of NULL.
//
// NOTE about two versions of some functions:
//   The data function returns a reference to the data field of a node and
//   the link function returns a copy of the link field of a node.
//   Each of these functions comes in two versions: a const version and a
//   non-const version. If the function is activated by a const node, then the
//   compiler choses the const version (and the return value is const).
//   If the function is activated by a non-const node, then the compiler choses
//   the non-const version (and the return value will be non-const).
// EXAMPLES:
//    const node<int> *c;
//    c->link( ) activates the const version of link returning const node*
//    c->data( ) activates the const version of data returning const Item&
//    c->data( ) = 42; ... is forbidden
//    node<int> *p;
//    p->link( ) activates the non-const version of link returning node*
//    p->data( ) activates the non-const version of data returning Item&
//    p->data( ) = 42; ... actually changes the data in p's node
//
// MEMBER FUNCTIONS for the node<Item> class:
//   const Item& data( ) const <----- const version
//   and
//   Item& data( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is a reference to the  data from this node.
//
//   const node* link( ) const <----- const version
//   and
//   node* link( ) <----------------- non-const version
//   See the note (above) about the const version and non-const versions:
//     Postcondition: The return value is the link from this node.
//   
//   void set_data(const Item& new_data)
//     Postcondition: The node now contains the specified new data.
//   
//   void set_link(node* new_link)
//     Postcondition: The node now contains the specified new link.

#ifndef MAIN_SAVITCH_NODE3_H  
#define MAIN_SAVITCH_NODE3_H
#include <cstdlib>   // Provides NULL and size_t

namespace main_savitch_8D
{
    template <class Item>
    class node
    {
    public:
        // TYPEDEF
        typedef Item value_type;
        // CONSTRUCTOR
        node(const Item& init_data=Item( ), node* init_link=NULL)
            { data_field = init_data; link_field = init_link; }
        // MODIFICATION MEMBER FUNCTIONS
        Item& data( ) { return data_field; }
        node* link( ) { return link_field; }
        void set_data(const Item& new_data) { data_field = new_data; }
        void set_link(node* new_link) { link_field = new_link; }
        // CONST MEMBER FUNCTIONS
        const Item& data( ) const { return data_field; }
        const node* link( ) const { return link_field; }
    private:
        Item data_field;
        node *link_field;
    };
}
#endif
