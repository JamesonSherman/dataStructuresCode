#include"sequence2a.h"
#include<algorithm>
#include<iostream>

typedef double value_type;
typedef std::size_t size_type;

main_savitch_4::sequence::sequence(size_type initial_capacity)
{
	data = new value_type[initial_capacity];
	used = 0;
	capacity = initial_capacity;
	current_index = 0;
	for (size_type i = 0; i < capacity; i++)
	{
		data[i] = 0;
	}
	return;
}

main_savitch_4::sequence::sequence(const sequence & source)
{
	value_type *temp;
	/*data = new value_type[source.capacity];
	used = source.used;
	capacity = source.capacity;
	current_index = 0;
	for (size_type i = 0; i < capacity; i++)
	{
		data[i] = source.data[i];
	}*/
	if (this == &source) return;

	if (capacity != source.capacity)
	{
		temp = new value_type[source.capacity];
		delete[] data;
		data = temp;
		capacity = source.capacity;
	}
	used = source.used;

	for (size_type i = 0; i < used; ++i)
	{
		data[i] = source.data[i];
	}
	current_index = source.current_index;
	return;
}

main_savitch_4::sequence::~sequence()
{
	delete[] data;
}

void main_savitch_4::sequence::resize(size_type new_capacity)
{
	value_type *temp;
	if (new_capacity == capacity)
	{
		return;
	}
	if (new_capacity < used)
	{
		new_capacity = used;
		//std::cout << "new size " << new_capacity << std::endl;
	}

	temp = new value_type[new_capacity];
	
	for (size_type i = 0; i < used;i++)
	{
		//std::cout << i << std::endl;
		temp[i] = data[i];
		//std::cout << i << " " << temp[i] << std::endl;
	}
	capacity = new_capacity;

	//std::copy(data, data + used, temp);
	delete[] data;
	data = temp;
	

	//if (new_capacity > used && new_capacity != capacity)
	//{
	//	value_type *temp = new value_type[new_capacity];
	//	for (size_type i = 0; i < std::min(capacity,new_capacity); i++)
	//	{
	//		temp[i] = data[i];
	//	}
	//	delete[] data;
	//	data = temp;
	//	capacity = new_capacity; // Updates Capacity
	//}

	return;
}

void main_savitch_4::sequence::start()
{
	current_index = 0;
	return;
}

void main_savitch_4::sequence::advance()
{
	if (current_index < used)
	{
		current_index++;
	}
	return;
}

void main_savitch_4::sequence::insert(const value_type & entry)
{
	size_type cur = current_index;
	if (used == (capacity))
	{
		resize(capacity + 1);
	}

	if (is_item())
	{
		for (cur = used; cur > current_index; --cur)
		{
			data[cur] = data[cur-1];
		}
		data[current_index] = entry;
	}
	else
	{
		if(used>0)
		{
			for (cur = used; cur > 0; --cur)
			{
				data[cur] = data[cur - 1];
			}
		}
		data[0] = entry;
	}

	used++;
	return;
}

void main_savitch_4::sequence::attach(const value_type & entry)
{
	size_type cur = current_index;
	if (used == (capacity))
	{
		resize(capacity + 1);
	}

	if (is_item())
	{
		for (cur = used; cur > current_index; --cur)
		{
			data[cur] = data[cur - 1];
		}
		current_index++;
		data[current_index] = entry;
	}
	else
	{
		data[used] = entry;
	}

	used++;
	return;
	/*size_type cur = current_index;
	if ((used + 1) >= capacity && used != 0)
	{
		resize(capacity + 1);
	}
	else if (!(is_item()))
	{
		data[used] = entry;
		used++;
	}
	else if (used != 0)
	{
		for (cur = current_index; cur < (used); cur++)
		{
			data[cur + 1] = data[cur];
		}
		used++;
		++current_index;
		data[current_index] = entry;
	}
	else
	{
		data[0] = entry;
		used++;
	}*/
}

void main_savitch_4::sequence::remove_current()
{
	size_type cur = current_index;

	if ((used > 0) && is_item())
	{
		for (cur = current_index; cur < (used - 1); cur++)
		{
			data[cur] = data[cur + 1];
		}
		used--;
	}
	return;
}

void main_savitch_4::sequence::operator=(const sequence & source)
{
	value_type *temp;
	if (this == &source) return;

	if (capacity != source.capacity)
	{
		temp = new value_type[source.capacity];
		delete[] data;
		data = temp;
		capacity = source.capacity;
	}
	used = source.used;
	std::copy(source.data, source.data + used, data);
	current_index = source.current_index;
	return;
}

size_type main_savitch_4::sequence::size() const
{
	return used;
}

bool main_savitch_4::sequence::is_item() const
{
	if (current_index < used) return true;
	else return false;
}

value_type main_savitch_4::sequence::current() const
{
	return data[current_index];
}

void main_savitch_4::sequence::add_to_front(const value_type & entry)
{
	if (used + 1 >= capacity)
		resize(capacity + 1);

	for (size_type cur = used; cur > 0; --cur)
	{
		data[cur] = data[cur - 1];
	}

	data[0] = entry;
	used++;
	current_index = 0;
	return;
}

void main_savitch_4::sequence::remove_from_front()
{
	if (used == 0) return;

	for (size_type i = 0; i < used; ++i)
	{
		data[i] = data[i + 1];
	}
	used--;
	current_index = 0;
	return;
}

void main_savitch_4::sequence::add_to_end(const value_type & entry)
{
	if (used + 1 >= capacity)
		resize(capacity + 1);
	data[used] = entry;
	current_index = used;
	++used;
	return;
}

void main_savitch_4::sequence::make_last_current()
{
	if (used < 1)
	{
		current_index = 0;
		return;
	}
	else
	{
		current_index = (used - 1);
		return;
	}
}

void main_savitch_4::sequence::operator+=(const sequence & s) // Append all of 's' onto the end of 'data'.
{
	if (s.used == 0) return;

	if (used + s.used > capacity) resize(s.used + used + 1); // Sets new capacity.

	for (size_type i = 0; i < s.used; ++i)
	{
		data[used + i] = s.data[i];
	}

	used += s.used;
	current_index = 0;
	return;
}

value_type main_savitch_4::sequence::operator[](size_type index) const
{
	return data[index];
}


main_savitch_4::sequence main_savitch_4::operator+(const sequence & s1, const sequence & s2)
{
	sequence sum;

	sum = s1;
	sum += s2;

	return sum;
}

// CONSTRUCTOR for the sequence class:
//   sequence(size_t initial_capacity = DEFAULT_CAPACITY)
//     Postcondition: The sequence has been initialized as an empty sequence.
//     The insert/attach functions will work efficiently (without allocating
//     new memory) until this capacity is reached.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void resize(size_type new_capacity)
//     Postcondition: The sequence's current capacity is changed to the 
//     new_capacity (but not less that the number of items already on the
//     list). The insert/attach functions will work efficiently (without
//     allocating new memory) until this new capacity is reached.
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
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
// DYNAMIC MEMORY USAGE by the List
//   If there is insufficient dynamic memory, then the following functions
//   throw a BAD_ALLOC exception: The constructors, insert, attach. 


