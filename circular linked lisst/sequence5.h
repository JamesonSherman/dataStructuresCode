// CSC 307 SP 2018 HW8
// ***FILE: sequence5.h 
// ***Revised sequence3.h, available at https://www.cs.colorado.edu/~main/chapter5/sequence3.h,
//    to implement the sequence class using two stacks
//    and make it a template class

#ifndef MAIN_SAVITCH_SEQUENCE5_H
#define MAIN_SAVITCH_SEQUENCE5_H
#include <cstdlib>  // Provides size_t
#include "stack4.h"
namespace main_savitch_7B
{
	template <typename Item>
    class sequence
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef std::size_t size_type;
        // CONSTRUCTOR
		sequence() {};
        // MODIFICATION MEMBER FUNCTIONS
        void start( );
        void advance( );
        void insert(const Item& entry);
        void attach(const Item& entry);
		void remove_current( );
        // CONSTANT MEMBER FUNCTIONS
		size_type size() const;
		bool is_item() const;
        Item current( ) const;
    private:
		stack<Item> stack1;
		stack<Item> stack2;	
    };
}
#include "sequence5.template"
#endif