// CSC 307 SP 2018 HW12
// ADAPTED FROM Figure 12.9 in our textbook

#ifndef TABLE3_H
#define TABLE3_H

#include <cstdlib> // Provides size_t
#include <vector> // Provides the STL vector class
#include <cassert>
#include <iostream>
namespace main_savitch_12C
{
	template <class RecordType, size_t TABLE_SIZE, class HashkeyFunction>
	class table
	{
	public:
		// CONSTRUCTORS (no destructor needed, uses automatic copy constructor)
		table() { total_records = 0; }
		// MODIFICATION MEMBER FUNCTIONS
		void insert(const RecordType& entry);
		void remove(int key);
		// CONSTANT MEMBER FUNCTIONS
		void find(int key, bool& found, RecordType& result) const;
		bool is_present(int key) const;
		std::size_t size() const { return total_records; }
		void provide_stats(); //*** "additional member functions to provide statistics"
		void provide_table_info();
	private:
		std::vector<RecordType> data[TABLE_SIZE];
		std::size_t total_records;

		// *** store the numbers of items examined during successful searches to
		//     "calculate the average number of items examined during a successful search, 
		//     and the maximum number of items examined during a successful search."
		std::vector<int> numItemsExaminedInSuccessfulSearch; 

		// HELPER MEMBER FUNCTION
		std::size_t hash(int key) const { return (key % TABLE_SIZE); }
		HashkeyFunction hashkey;
	};

	template <class RecordType, size_t TABLE_SIZE, class HashkeyFunction>
	void table<RecordType, TABLE_SIZE, HashkeyFunction>::insert(const RecordType& entry)
	{
		assert(entry.key >= 0);
		std::vector<RecordType>& chain = data[hash(hashkey(entry))];
		typename std::vector<RecordType>::iterator it;
		bool found = false;
		int numItemsExamined = 0;
		for (it = chain.begin(); (it != chain.end()) && (!found); ++it)
		{
			++numItemsExamined;
			if ((*it).key == entry.key)
			{
				found = true;
			}
		}
		if (found)
		{
			*(--it) = entry;
			numItemsExaminedInSuccessfulSearch.push_back(numItemsExamined);
		}
		else
		{
			chain.push_back(entry);
			++total_records;
		}
	}

	template <class RecordType, size_t TABLE_SIZE, class HashkeyFunction>
	void table<RecordType, TABLE_SIZE, HashkeyFunction>::provide_table_info()
	{
		size_t total_length = 0;
		size_t max_length = 0;
		for (size_t i = 0; i < TABLE_SIZE; ++i)
		{
			total_length += data[i].size();
			if (data[i].size() > max_length)
			{
				max_length = data[i].size();
			}
		}
		std::cout << "\n************************************************\n";
		std::cout << "The table has " << total_records << " records.\n";
		std::cout << "The average length of lists is: " << ((double)total_length /(double)TABLE_SIZE) << std::endl;
		std::cout << "The maximum length of lists is: " << max_length << std::endl;
		std::cout << "\n************************************************\n";
	}
}
#include "table3.template" // Include the implementation
#endif
