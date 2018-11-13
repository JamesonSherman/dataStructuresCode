#include "sorted_sequence.h"
#include <cstdlib>

typedef std::size_t size_type;
typedef double value_type;

main_savitch_3::sorted_sequence::sorted_sequence()
{
	used = 0;
	current_index = 0;
	//for (int i = 0; i < CAPACITY;i++) data[i] = 0;
}

void main_savitch_3::sorted_sequence::start()
{
	current_index = 0;
	return;
}

void main_savitch_3::sorted_sequence::advance()
{
	if (is_item())//((current_index + 1) < CAPACITY) && ((current_index + 1) < used))
	{
		current_index++;
	}
	return;
}

void main_savitch_3::sorted_sequence::insert(const value_type & entry)
{
	if (used < CAPACITY)
	{
		if (used == 0) 
		{
			data[current_index] = entry;
			used++;
			return;
		}
		else 
		{
			used++;
			data[used - 1] = entry;
			insert_sort();
			for (size_type i = 0; i < used; i++)
			{
				if (data[i] == entry)
				{
					current_index = i;
					break;
				}
			}
			return;
		}
	}
	else return;
}

void main_savitch_3::sorted_sequence::remove_current()
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
	/*if (current_index == used)
	{
		current_index--;
	}*/
	return;
}

size_type main_savitch_3::sorted_sequence::size() const
{
	return used;
}

bool main_savitch_3::sorted_sequence::is_item() const
{
	if (current_index < used) return true;
	else return false;
}

value_type main_savitch_3::sorted_sequence::current() const
{
	if (is_item()) return data[current_index];
	else return data[0];
}

void main_savitch_3::sorted_sequence::insert_sort()
{
	value_type alpha;
	value_type beta;
	bool ordered = false;
	bool moved = false;

	if (used > 1)
	{
		while (ordered != true)
		{
			moved = false;
			for (size_type i = 0; i < (used-1); i++)
			{
				if (data[i] > data[i + 1])
				{
					alpha = data[i];
					beta = data[i + 1];
					data[i] = beta;
					data[i + 1] = alpha;
					moved = true;
				}
			}
			if (moved == false) ordered = true;
		}
	}
	return;
}
