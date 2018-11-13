// CSC 307 SP 2018 HW11
// ADAPTED FROM the following file, available at
// https://www.cs.colorado.edu/~main/chapter10/bintree.h:


// FILE: bintree.h (part of the namespace main_savitch_10)
// PROVIDES: A template class for a node in a binary tree and functions for 
// manipulating binary trees. The template parameter is the type of data in
// each node.
// 
// TYPEDEF for the binary_tree_node<Item> template class:
//   Each node of the tree contains a piece of data and pointers to its
//   children. The type of the data (binary_tree_node<Item>::value_type) is
//   the Item type from the template parameter. The type may be any of the C++
//   built-in types (int, char, etc.), or a class with a default constructor,
//   and an assignment operator.
//
// CONSTRUCTOR for the binary_tree_node<Item> class:
//   binary_tree_node(
//       const item& init_data = Item( ),
//       binary_tree_node<Item>* init_left = NULL,
//       binary_tree_node<Item>* init_right = NULL
//   )
//     Postcondition: The new node has its data equal to init_data,
//     and it's child pointers equal to init_left and init_right.
//
// MEMBER FUNCTIONS for the binary_tree_node<Item> class:
//   const item& data( ) const      <----- const version
//   and
//   Item& data( )                  <----- non-const version
//     Postcondition: The return value is a reference to the data from
//     this binary_tree_node.
//
//   const binary_tree_node* left( ) const  <----- const version
//   and
//   binary_tree_node* left( )              <----- non-const version
//   and
//   const binary_tree_node* right( ) const <----- const version
//   and
//   binary_tree_node* right( )             <----- non-const version
//     Postcondition: The return value is a pointer to the left or right child
//     (which will be NULL if there is no child).
//
//   void set_data(const Item& new_data)
//     Postcondition: The binary_tree_node now contains the specified new data.
//
//   void set_left(binary_tree_node* new_link)
//   and
//   void set_right(binary_tree_node* new_link)
//     Postcondition: The binary_tree_node now contains the specified new link
//     to a child.
//
//   bool is_leaf( )
//     Postcondition: The return value is true if the node is a leaf;
//     otherwise the return value is false.
//
//   template <class Item, class SizeType>
//   void print(const binary_tree_node<Item>* node_ptr, SizeType depth)
//     Precondition: node_ptr is a pointer to a node in a binary tree (or
//     node_ptr may be NULL to indicate the empty tree). If the pointer is
//     not NULL, then depth is the depth of the node pointed to by node_ptr.
//     Postcondition: If node_ptr is non-NULL, then the contents of *node_ptr
//     and all its descendants have been written to cout with the << operator,
//     using a backward in-order traversal. Each node is indented four times
//     its depth.


#ifndef BINTREE_H
#define BINTREE_H
#include <cstdlib>  // Provides NULL and size_t
#include <iomanip>    // Provides std::setw


namespace main_savitch_10
{

    template <class Item>
    class binary_tree_node
    {
    public:
	// TYPEDEF
	typedef Item value_type;
	// CONSTRUCTOR
	binary_tree_node(
	    const Item& init_data = Item( ),
	    binary_tree_node* init_left = NULL,
	    binary_tree_node* init_right = NULL
	)
	{ 
      	    data_field = init_data; 
	    left_field = init_left; 
	    right_field = init_right;
	}
	
	// MODIFICATION MEMBER FUNCTIONS
	Item& data( ) { return data_field; }
	binary_tree_node*& left( ) { return left_field; }
	binary_tree_node*& right( ) { return right_field; }
	void set_data(const Item& new_data) { data_field = new_data; }
	void set_left(binary_tree_node* new_left) { left_field = new_left; }
	void set_right(binary_tree_node* new_right) { right_field = new_right; }
	// CONST MEMBER FUNCTIONS
	const Item& data( ) const { return data_field; }
	const binary_tree_node* left( ) const { return left_field; }
	const binary_tree_node* right( ) const { return right_field; }
	bool is_leaf( ) const 
	    { return (left_field == NULL) && (right_field == NULL); }
    private:
	Item data_field;
	binary_tree_node *left_field;
	binary_tree_node *right_field;
    };

	template <class Item, class SizeType>
	void print(binary_tree_node<Item>* node_ptr, SizeType depth)
	{
		if (node_ptr != NULL)
		{
			print(node_ptr->right(), depth + 1);
			std::cout << std::setw(4 * depth) << ""; // Indent 4*depth spaces.
			std::cout << node_ptr->data() << std::endl;
			print(node_ptr->left(), depth + 1);
		}
	}
	
}
#endif
