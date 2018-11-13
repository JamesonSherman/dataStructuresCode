#include "sequence3.h"
#include <iostream>

typedef double value_type;
typedef std::size_t size_type;

main_savitch_5::sequence::sequence()
{
	node *head_ptr = NULL;
	node *tail_ptr = NULL;
	node *cursor = NULL;
	node *precursor = NULL;
	size_type many_nodes = 0;
}

main_savitch_5::sequence::sequence(const sequence & source)
{
	if (source.many_nodes == 0)
	{
		node *head_ptr = NULL;
		node *tail_ptr = NULL;
		node *cursor = NULL;
		node *precursor = NULL;
		size_type many_nodes = 0;
		return;
	}
	else if (source.head_ptr == source.cursor)
	{
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		many_nodes = source.many_nodes;
		return;
	}
	else
	{
		list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
		list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
		precursor->set_link(cursor);
		cursor = precursor->link();
		return;
	}
}

main_savitch_5::sequence::~sequence()
{
	list_clear(head_ptr);
	many_nodes = 0;
}

void main_savitch_5::sequence::start()
{
	precursor = NULL;
	cursor = head_ptr;

	return;
}

void main_savitch_5::sequence::advance()
{
	if (cursor != NULL)
	{
		precursor = cursor;
		cursor = cursor->link();
	}

	return;
}

void main_savitch_5::sequence::insert(const value_type & entry)
{
	if (precursor == NULL)
	{
		list_head_insert(head_ptr, entry);
		precursor = NULL;
		cursor = head_ptr;
		many_nodes++;
	}
	else
	{
		list_insert(precursor, entry);
		cursor = precursor->link();
		many_nodes++;
	}
	return;
	/*if (cursor == head_ptr)
	{
		list_head_insert(cursor, entry);
		std::cerr << "\nInsert " << entry << " at head.\n";
		many_nodes++;
		return;
	}
	else
	{
		list_insert(precursor, entry);
		std::cerr << "\nInsert " << entry << " at cursor.\n";
		if (precursor->link() != NULL)
			cursor = precursor->link();

		many_nodes++;
		return;
	}*/
	//if (cursor == head_ptr)
	//{
	//	list_head_insert(cursor, entry);
	//	//std::cerr << "\nInsert " << entry << " at head.\n";
	//	many_nodes++;
	//	return;
	//}
	//list_insert(precursor, entry);
	////std::cerr << "\nInsert " << entry << " after cursor " << many_nodes << ".\n";
	//many_nodes++;
	//return;
}

void main_savitch_5::sequence::attach(const value_type & entry)
{

	if (cursor == head_ptr)
	{
		if (cursor == NULL)
		{
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
		}
		else
		{
			list_insert(head_ptr, entry);
			if (head_ptr->link() != NULL)
				cursor = head_ptr->link();
			else cursor = head_ptr;
		}
		many_nodes++;
		return;
	}
	list_insert(cursor, entry);
	

	many_nodes++;
	return;

	/*if (head_ptr == NULL)
	{
		list_head_insert(head_ptr, entry);
		many_nodes++;
		std::cerr << "\nAttch " << entry << " at head.\n";
		return;
	}

	list_insert(cursor, entry);
	std::cerr << "\nAttch " << entry << " after cursor " << many_nodes << ".\n";
	precursor = cursor;
	cursor = cursor->link();
	many_nodes++;
	return;*/	
}

void main_savitch_5::sequence::operator=(const sequence & source)
{
	if (this == &source)
		return;

	node *tail_ptr;
	list_clear(head_ptr);
	many_nodes = 0;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
	start();
	return;
}

void main_savitch_5::sequence::remove_current()
{
	if (cursor == NULL)
		return;

	if (cursor == head_ptr)
	{
		list_head_remove(head_ptr);
		many_nodes--;
		return;
	}
	list_remove(cursor);
	many_nodes--;
}

value_type main_savitch_5::sequence::current() const
{
	if (!is_item())
		return 0;
	else
		return cursor->data();
}

// CONSTRUCTOR for the sequence class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.

