// CSC 307 SP 2018 HW12
// ADAPTED FROM the following file, available at
// https://www.cs.colorado.edu/~main/chapter12/testtab2.cxx,
// to work with "a table class with STL vectors":

// FILE: testtab2.cxx
// An interactive test program for the second table ADT.

#include <cctype>      // Provides toupper
#include <cstdlib>     // Provides EXIT_SUCCESS and size_t
#include <iostream>    // Provides cin, cout
#include <string>
#include <random>
#include "table3.h"    // Provides the table class
using namespace std;
using namespace main_savitch_12C;

// Struct definition for the test_record_type, which has a key and a double.
struct test_record_type
{
    int key;
    double data;
};

struct hashkey 
{
	int operator()(const test_record_type& t)
	{
		return t.key;
	}
};

// PROTOTYPES for functions used by this test program:
void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// The next character has been read (skipping blanks and newline characters), 
// and this character has been returned.

test_record_type get_record( ); 
// Postcondition: The user has been prompted to enter data for a record. The
// key has been read, echoed to the screen, and returned by the function.
test_record_type get_record(int k, double d);

int get_key( );
// Postcondition: The user has been prompted to enter a key for a record. The
// items have been read, echoed to the screen, and returned by the function.

void get_data(table<test_record_type, 811, hashkey>& test, size_t numentries)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> udist(1, 10000000);
	for (size_t i = 0; i < numentries; ++i)
	{
		int k = udist(gen);
		double d = k / 100000.0;
		test.insert(get_record(k, d));
	}
}

int main( )
{
	table<test_record_type, 811, hashkey> test;   // A table that we'll perform tests on
    char choice;                     // A command character entered by the user
	bool found;                      // Value returned by find function
	test_record_type result;         // Value returned by find function

	int numentries;
	cout << "I have initialized an empty table.\n";
	cout << "Each record in the table has an integer key and a real number as data." << endl;
	cout << "How many records are to be added to this table initially? Enter a positive integer:  ";
	cin >> numentries;
	
	get_data(test, numentries);

	cout << "\n\nI added " << numentries << " records with (uniformly) randomly generated keys to an empty table." << endl;
	test.provide_table_info();

	cout << "\n===========================\n";
	cout << "According to my calculations, the load factor, "
		<< "the average number of items examined during a successful search, "
		<< "and the maximum number of items examined during a successful search "
		<< "for the current table are as follows:" << endl;
	cout << "===========================\n";
	test.provide_stats();

    do
    {
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'S': cout << "The table size is " << test.size( ) << endl;
                      break;
            case 'I': test.insert(get_record( ));
                      cout << "The record has been inserted." << endl;
                      break;
            case 'R': test.remove(get_key( ));
                      cout << "Remove has been called with that key." << endl;
                      break;     
            case '?': if (test.is_present(get_key( )))
                          cout << "That key is present." << endl;
                      else
                          cout << "That key is not present." << endl;
                      break;
            case 'F': test.find(get_key( ), found, result);
                      if (found)
                          cout << "The key's data is: " << result.data << endl;
                      else
                          cout << "That key is not present." << endl;
                      break;
            case 'Q': cout << "Ridicule is the best test of truth." << endl;
                      break;
            default:  cout << choice << " is invalid. Sorry." << endl;
        }
    }
    while ((choice != 'Q'));

	test.provide_table_info();

	cout << "\n===========================\n";
	cout << "According to my calculations, the load factor, "
		<< "the average number of items examined during a successful search, "
		<< "and the maximum number of items examined during a successful search "
		<< "for the current table are as follows:" << endl;
	cout << "===========================\n";
	test.provide_stats();

    return EXIT_SUCCESS;
}

void print_menu( )
// Library facilities used: iostream.h
{
    cout << endl; // Print blank line before the menu
    cout << "The following choices are available: " << endl;
    cout << " S   Print the result from the size( ) function" << endl;
    cout << " I   Insert a new record with the insert(...) function" << endl;
    cout << " R   Remove a record with the remove(...) function" << endl;
    cout << " ?   Check whether a particular key is present" << endl;
    cout << " F   Find the data associated with a specified key" << endl;
    cout << " Q   Quit this test program" << endl;
}

char get_user_command( )
// Library facilities used: iostream.h
{
    char command;

    cout << "Enter choice: ";
    cin >> command; // Input of characters skips blanks and newline character

    return command;
}

test_record_type get_record( )
// Library facilities used: iostream.h
{
    test_record_type result;
    
    cout << "Please enter a real number for a record's data: ";
    cin  >> result.data;
    cout << result.data << " has been read." << endl;
    result.key = get_key( );
    return result;
}

test_record_type get_record(int k, double d)
// Library facilities used: iostream.h
{
	test_record_type result{ k,d };
	return result;
}

int get_key( )
// Library facilities used: iostream.h
{
    int key;
    
    do
    {
        cout << "Please enter a non-negative integer for a key: ";
        cin  >> key;
    }
    while (key < 0);
    cout << key << " has been read." << endl;
    return key;
}
