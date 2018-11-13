
#ifndef MAIN_SAVITCH_SEQUENCE_H
#define MAIN_SAVITCH_SEQUENCE_H
#include <cstdlib> 

namespace main_savitch_4
{
	class sequence
	{
	public:
		typedef double value_type;
		typedef std::size_t size_type;
		static const size_type DEFAULT_CAPACITY = 30;

		sequence(size_type initial_capacity = DEFAULT_CAPACITY);
		sequence(const sequence& source);
		~sequence();

		void resize(size_type new_capacity);
		void start();
		void advance();
		void insert(const value_type& entry);
		void attach(const value_type& entry);
		void remove_current();
		void operator =(const sequence& source);

		size_type size() const;
		bool is_item() const;
		value_type current() const;

		void add_to_front(const value_type& entry); // Precon: There is space to add another value or allocate space for one. Postcon: a number is added to the front of the array.
		void remove_from_front(); // Precon: there is something in position 0 to remove. Postcon: the data in position 0 is removed and the following information takes its place.
		void add_to_end(const value_type& entry); // Precon: there is space to add another value or allocate space for one. Postcon: a number is added to the end of the array.
		void make_last_current(); // Postcon: the last item is at current_index
		void operator+=(const sequence& s); // Postcon: data in "s" is appended to the end of the destination.
		value_type operator[] (size_type index) const; // Precon: index is less than the capacity of the data array. Postcon: Returns value at data[index].

	private:
		value_type* data;
		size_type used;
		size_type current_index;
		size_type capacity;
	};
	sequence operator+(const sequence& s1, const sequence& s2); // Postcon: s2's data appended to the end of s1's data.
}

#endif
