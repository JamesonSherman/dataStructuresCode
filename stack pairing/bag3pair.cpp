#include "bag3pair.h"

namespace main_savitch_5
{
	bag::bag()
	{
		head_ptr = NULL;
		many_nodes = 0;
	}

	bag::bag(const bag & source)
	{
		node *tail_ptr;

		list_copy(source.head_ptr, head_ptr, tail_ptr);
		many_nodes = source.many_nodes;

	}

	bag::~bag()
	{
		list_clear(head_ptr);
		many_nodes = 0;
	}

	bag::size_type bag::erase(const value_type & target)
	{
		size_type answer = 0;
		node *target_ptr = head_ptr;
		node *prev = NULL;
		bool stop_search = false;
		while ((target_ptr != NULL) && (!stop_search))
		{
			if (target_ptr->data().second == target)
			{
				stop_search = true;
				answer = target_ptr->data().first;
				--many_nodes;
				if (target_ptr == head_ptr)
					list_head_remove(head_ptr);
				else
					list_remove(prev);
			}
			else if (target_ptr->data().second > target)
			{
				stop_search = true;
			}
			else
			{
				prev = target_ptr;
				target_ptr = target_ptr->link();
			}
		}
		return answer;
	}

	bool bag::erase_one(const value_type & target) // --------------------
	{
		node *target_ptr = head_ptr;
		node *prev_ptr = NULL;

		if (head_ptr == NULL)
			return false;

		//target_ptr = list_search(head_ptr, target);
		while (target_ptr->data().second != target && target_ptr->link() != NULL)
		{
			prev_ptr = target_ptr;
			target_ptr = target_ptr->link();
		}

		if (target_ptr->data().second != target)
			return false;

		if (target_ptr->data().first == 1)
		{
			if (target_ptr == head_ptr)
				list_head_remove(head_ptr);
			else list_remove(prev_ptr);
			--many_nodes;
			return true;
		}

		else
		{
			--(target_ptr->data().first);
			return true;
		}
	}

	void bag::insert(const value_type & entry) // ----------------------
	{
		node *precurs = NULL;
		node *curs = head_ptr;

				if (many_nodes == 0) 
				{
					list_head_insert(head_ptr, std::make_pair(1, entry)); 
					++many_nodes; 
					return;
				}

				if (many_nodes == 1)
				{
					if (entry > head_ptr->data().second)
					{
						list_insert(head_ptr, std::make_pair(1, entry));
						++many_nodes;
					}

					else if (entry < head_ptr->data().second)
					{
						list_head_insert(head_ptr, std::make_pair(1, entry));
						++many_nodes;
					}

					else
						++(head_ptr->data().first);

					return;
				}

				while (entry > curs->data().second && curs->link() != NULL)
				{
					precurs = curs;
					curs = curs->link();
				}

				if (entry > curs->data().second)
				{
					list_insert(curs, std::make_pair(1, entry));
					++many_nodes;
					
				}

				else if (entry < curs->data().second)
				{
					if (curs == head_ptr) 
					{
						list_head_insert(head_ptr, std::make_pair(1, entry));
					}
					else
					{
						list_insert(precurs, std::make_pair(1, entry));
					}
					++many_nodes;
					
				}

				else
				{
					++(curs->data().first);
					
				}
	}

	void bag::operator+=(const bag & addend) // --------------------
	{
				node *curs = addend.head_ptr;

				while (curs != NULL)
				{
					for (size_type i = 1; i <= curs->data().first; ++i)
					{
						insert(curs->data().second);
					}

					curs = curs->link();
				}
	}

	void bag::operator=(const bag & source)
	{
		node *tail_ptr;

		if (this == &source)
			return;

		list_clear(head_ptr);
		many_nodes = 0;

		list_copy(source.head_ptr, head_ptr, tail_ptr);
		many_nodes = source.many_nodes;
	}

	bag::size_type bag::count(const value_type & target) const // ---------------
	{
		node *targp;

		targp = list_search(head_ptr, target);
		
		if (targp != NULL) return (targp->data().first);

		else return 0;

	}

	bag operator+(const bag & b1, const bag & b2)
	{
		bag answer;

		answer += b1;
		answer += b2;

		return answer;

	}
}
/*
//////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                    Collaborators on this Assignment:                     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                                                                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              Micheal whitney - Implementation                            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              Jeremiah Scott - Implementation                             \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              cplusplus.com/reference/utility/pair - Pair Class Info      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                                                                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
