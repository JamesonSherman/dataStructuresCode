// CSC 307 SP 2018 HW9
// ***FILE: bag3pair.h 
// ***Adapted from bag3.h, available at https://www.cs.colorado.edu/~main/chapter5/bag3.h,
//    "so that the items of the bag are stored with a new technique" 
//	  as described in Chapter 5 programming exercise 19.


#ifndef MAIN_SAVITCH_BAG3_H
#define MAIN_SAVITCH_BAG3_H
#include <cstdlib>   // Provides size_t and NULL
#include "node1pair.h"   
namespace main_savitch_5
{
    class bag
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef node::item_type value_type;  //** node::item_type is double for this assignment.
        // CONSTRUCTORS and DESTRUCTOR
        bag( );
        bag(const bag& source);
		~bag( );
        // MODIFICATION MEMBER FUNCTIONS
        size_type erase(const value_type& target);
        bool erase_one(const value_type& target);
        void insert(const value_type& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);
        // CONSTANT MEMBER FUNCTIONS
        size_type size( ) const { return many_nodes; }
        size_type count(const value_type& target) const;
		node* first() const { return head_ptr; }
    private:
        node *head_ptr;       // List head pointer 
        size_type many_nodes; // Number of nodes on the list
    };

    // NONMEMBER FUNCTIONS for the bag class:    
    bag operator +(const bag& b1, const bag& b2);

}
#endif

