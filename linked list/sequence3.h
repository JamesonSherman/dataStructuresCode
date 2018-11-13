// FILE: sequence3.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_5)
// This is the header file for the project described in Section 5.4
// of "Data Structures and Other Objects Using C++"
// This is called "sequence3" because some students already implemented
// sequence1 (with a fixed array) and sequence2 (with a dynamic array).
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//

#ifndef MAIN_SAVITCH_SEQUENCE3_H
#define MAIN_SAVITCH_SEQUENCE3_H
#include <cstdlib>  // Provides size_t
#include<iostream>
#include "node1.h"  // Provides node class

namespace main_savitch_5
{
	class sequence
	{
	public:
		// TYPEDEFS and MEMBER CONSTANTS
		typedef double value_type;
		typedef std::size_t size_type;
		// CONSTRUCTORS and DESTRUCTOR
		sequence();
		sequence(const sequence& source);
		~sequence();
		// MODIFICATION MEMBER FUNCTIONS
		void start();
		void advance();
		void insert(const value_type& entry);
		void attach(const value_type& entry);
		void operator =(const sequence& source);
		void remove_current();
		// CONSTANT MEMBER FUNCTIONS
		size_type size() const { return many_nodes; }
		bool is_item() const 
		{ 
			//std::cerr << "\nChecking " << &cursor << "\n";
			return (cursor != NULL); 
		}
		value_type current() const;
	private:
		node *head_ptr;
		node *tail_ptr;
		node *cursor;
		node *precursor;
		size_type many_nodes;
	};
}

#endif
