// CSC 307 SP 2018 HW5
// ADAPTED FROM the following file:
// FILE: sequence_exam2.cxx
// Written by: Michael Main (main@colorado.edu) - Oct 29, 1997
// Non-interactive test program for the sequence class using a dynamic array,
// with improved test for heap leaks.
//
// DESCRIPTION:
// Each function of this program tests part of the sequence class, returning
// some number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...

#include <iostream>    // Provides cout.
#include <cstdlib>     // Provides size_t.
#include "sequence2a.h" // Provides the Sequence class with double items.
using namespace std;
using namespace main_savitch_4;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 7;
const int POINTS[MANY_TESTS+1] = {
    20,  // Total points for all tests.
     3,  // Test 1 points
     3,  // Test 2 points
     3,  // Test 3 points
     2,  // Test 4 points
     3,  // Test 5 points
     3,  // Test 6 points
     3  // Test 7 points
};
const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for sequence class with a dynamic array",
    "Testing insert, attach, and add_to_front",
    "Testing remove_current and remove_from_front",
	"Testing add_to_end with adding/removing operations",
    "Testing make_last_current",
    "Testing the += operator",
    "Testing the + operator",
    "Testing the subscript operator"
};


// **************************************************************************
// bool test_basic(const sequence& test, size_t s, bool has_cursor)
//   Postcondition: A return value of true indicates:
//     a. test.size() is s, and
//     b. test.is_item() is has_cursor.
//   Otherwise the return value is false.
//   In either case, a description of the test result is printed to cout.
// **************************************************************************
bool test_basic(const sequence& test, size_t s, bool has_cursor)
{
    bool answer;

    cout << "Testing that size() returns " << s << " ... ";
    cout.flush( );
    answer = (test.size( ) == s);
    cout << (answer ? "Passed." : "Failed.") << endl;
    
    if (answer)
    {
        cout << "Testing that is_item() returns ";
        cout << (has_cursor ? "true" : "false") << " ... ";
        cout.flush( );
        answer = (test.is_item( ) == has_cursor);
        cout << (answer ? "Passed." : "Failed.") << endl;
    }

    return answer;
}


// **************************************************************************
// bool test_items(sequence& test, size_t s, size_t i, double items[])
//   The function determines if the test sequence has the correct items
//   Precondition: The size of the items array is at least s.
//   Postcondition: A return value of true indicates that test.current()
//   is equal to items[i], and after test.advance() the result of
//   test.current() is items[i+1], and so on through items[s-1].
//   At this point, one more advance takes the cursor off the sequence.
//   If any of this fails, the return value is false.
//   NOTE: The test sequence has been changed by advancing its cursor.
// **************************************************************************
bool test_items(sequence& test, size_t s, size_t i, double items[])
{
    bool answer = true;
    
    cout << "The cursor should be at item [" << i << "]" << " of the sequence\n";
    cout << "(counting the first item as [0]). I will advance the cursor\n";
    cout << "to the end of the sequence, checking that each item is correct...";
    cout.flush( );
    while ((i < s) && test.is_item( ) && (test.current( ) == items[i]))
    {
        i++;
        test.advance( );
    }

    if ((i != s) && !test.is_item( ))
    {   // The test.is_item( ) function returns false too soon.
        cout << "\n    Cursor fell off the sequence too soon." << endl;
        answer = false;
    }
    else if (i != s)
    {   // The test.current( ) function returned a wrong value.
        cout << "\n    The item [" << i << "] should be " << items[i] << ",\n";
        cout << "    but it was " << test.current( ) << " instead.\n";
        answer = false;
    }
    else if (test.is_item( ))
    {   // The test.is_item( ) function returns true after moving off the sequence.
        cout << "\n    The cursor was moved off the sequence,";
        cout << " but is_item still returns true." << endl;
        answer = false;
    }

    cout << (answer ? "Passed." : "Failed.") << endl;
    return answer;
}


// **************************************************************************
// bool correct(sequence& test, size_t s, size_t cursor_spot, double items[])
//   This function determines if the sequence (test) is "correct" according to
//   these requirements:
//   a. it has exactly s items.
//   b. the items (starting at the front) are equal to
//      items[0] ... items[s-1]
//   c. if cursor_spot < s, then test's cursor must be at
//      the location given by cursor_spot.
//   d. if cursor_spot >= s, then test must not have a cursor.
// NOTE: The function also moves the cursor off the sequence.
// **************************************************************************
bool correct(sequence& test, size_t size, size_t cursor_spot, double items[])
{
    bool has_cursor = (cursor_spot < size); 

    // Check the sequence's size and whether it has a cursor.
    if (!test_basic(test, size, has_cursor))
    {
        cout << "Basic test of size() or is_item() failed." << endl << endl;
        return false;
    }

    // If there is a cursor, check the items from cursor to end of the sequence.
    if (has_cursor && !test_items(test, size, cursor_spot, items))
    {
        cout << "Test of the sequence's items failed." << endl << endl;
        return false;
    }

    // Restart the cursor at the front of the sequence and test items again.
    cout << "I'll call start() and look at the items one more time..." << endl;
    test.start( );
    if (has_cursor && !test_items(test, size, 0, items))
    {
        cout << "Test of the sequence's items failed." << endl << endl;
        return false;
    }

    // If the code reaches here, then all tests have been passed.
    cout << "All tests passed for this sequence." << endl << endl;
    return true;
}


// **************************************************************************
// int test1( )
//   Performs some basic tests of add_to_front
// **************************************************************************
int test1()
{
	sequence empty;                            // An empty sequence
	sequence test;                             // A sequence to add items to
	double items1[5] = {1,5,4,3,2 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence
	
										   // Test that the empty sequence is really empty
	cout << "Starting with an empty sequence." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;

	
	cout << "I am now using attach to put 20 into an empty sequence and then add_to_front to put 10." << endl;
	test.attach(20);
	test.add_to_front(10);
	if (!correct(test, 2, 0, items2)) return 0;

	cout << "I am now using insert to put 20 into an empty sequence and then add_to_front to put 10." << endl;
	test = empty;
	test.insert(20);
	test.add_to_front(10);
	if (!correct(test, 2, 0, items2)) return 0;

	cout << "I am now using add_to_front to put 2,3,4,5 in an empty sequence.\n";
	cout << "Then I move the cursor to the start and insert 1." << endl;
	test = empty;
	test.add_to_front(2);
	test.add_to_front(3);
	test.add_to_front(4);
	test.add_to_front(5);
	test.start();
	test.insert(1);
	if (!correct(test, 5, 0, items1)) return 0;

	cout << "I am now using attach to put 20, 30 in an empty sequence.\n";
	cout << "Then I use add_to_front to put 10. ";
	test = empty;
	test.attach(20);
	test.attach(30);
	test.add_to_front(10);
	if (!correct(test, 3, 0, items2)) return 0;

	cout << "I am now using add_to_front to put DEFAULT_CAPACITY+3, DEFAULT_CAPACITY+2, " << endl;
	cout << "DEFAULT_CAPACITY+1, ..., 2,1 in an empty sequence.\n";
	test = empty;
	for (size_t i = test.DEFAULT_CAPACITY+3; i > 0 ; --i)
	{
		test.add_to_front(i);
	}
	test.start();
	for (size_t i = 1; i <= test.size(); ++i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}
	
	// All tests have been passed
	cout << "All tests of this first function have been passed." << endl;
	return POINTS[1];
}


// **************************************************************************
// int test2( )
//   Performs some basic tests of remove_from_front
// **************************************************************************
int test2( )
{
    sequence test, empty;
	double items1[5] = { 1,5,4,3,2 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

    cout << "Using insert to put 3,4,5,1,2 in the sequence, and then using\n";
    cout << "remove_from_front";
    cout.flush( );
    test.insert(3);
    test.insert(4);
	test.insert(5);
	test.insert(1);
	test.insert(2);
	test.remove_from_front();
	if (!correct(test, 4, 0, items1)) return 0;

	test = empty;
	cout << "I am now using add_to_front to put DEFAULT_CAPACITY+3, DEFAULT_CAPACITY+2, " << endl;
	cout << "DEFAULT_CAPACITY+1, ..., 2,1 in an empty sequence.\n";
	test = empty;
	for (size_t i = test.DEFAULT_CAPACITY + 3; i > 0; --i)
	{
		test.add_to_front(i);
	}
	cout << "I am now using remove_from_front to remove 1,2,...,10.\n";
	unsigned int numremoved = 10;
	for (size_t i = 1; i <= numremoved; ++i)
	{
		test.remove_from_front();
	}
	for (size_t i = 1; i <= test.size(); ++i)
	{
		if ((!test.is_item()) || test.current() != (numremoved+i))
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}

    // All tests passed
    cout << "All tests of this second function have been passed." << endl;    
    return POINTS[2];
}


// **************************************************************************
// int test3( )
//   Performs basic tests for add_to_end
// **************************************************************************
int test3( )
{
	sequence empty;                            // An empty sequence
	sequence test;                             // A sequence to add items to
	double items1[5] = { 5,4,3,2, 1 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

											   // Test that the empty sequence is really empty
	cout << "Starting with an empty sequence." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;


	cout << "I am now using attach to put 20 into an empty sequence, add_to_front to put 10, and add_to_end to put 30." << endl;
	test.attach(20);
	test.add_to_front(10);
	test.add_to_end(30);
	if (!correct(test, 3, 2, items2)) return 0;

	cout << "I am now using insert to put 20 into an empty sequence, insert to put 10, and add_to_end to put 30." << endl;
	test = empty;
	test.insert(20);
	test.insert(10);
	test.add_to_end(30);
	if (!correct(test, 3, 2, items2)) return 0;

	cout << "I am now using add_to_front to put 2,3,4,5,6,7 in an empty sequence.\n";
	cout << "Then I call remove_from_front twice, and use add_to_end to put 1." << endl;
	test = empty;
	test.add_to_front(2);
	test.add_to_front(3);
	test.add_to_front(4);
	test.add_to_front(5);
	test.add_to_front(6);
	test.add_to_front(7);
	test.remove_from_front();
	test.remove_from_front();
	test.add_to_end(1);
	if (!correct(test, 5, 4, items1)) return 0;

	cout << "I am now using add_to_end to put DEFAULT_CAPACITY+3, DEFAULT_CAPACITY+2, " << endl;
	cout << "DEFAULT_CAPACITY+1, ..., 2,1 in an empty sequence.\n";
	test = empty;
	for (size_t i = test.DEFAULT_CAPACITY + 3; i > 0; --i)
	{
		test.add_to_end(i);
	}
	test.start();
	for (size_t i = test.DEFAULT_CAPACITY + 3; i > 0; --i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}

	// All tests have been passed
	cout << "All tests of this third function have been passed." << endl;
	return POINTS[3];
}


// **************************************************************************
// int test4( )
//   Performs some tests of make_last_current.
// **************************************************************************
int test4( )
{
	sequence empty;                            // An empty sequence
	sequence test;                             // A sequence to add items to
	double items1[5] = { 5,4,3,2, 1 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

											   // Test that the empty sequence is really empty
	cout << "Starting with an empty sequence." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;

	cout << "I am now using add_to_end to put 20 into an empty sequence, add_to_front to put 10, " << endl;;
	cout << "and call make_last_current." << endl;
	test.add_to_end(20);
	test.add_to_front(10);
	test.make_last_current();
	if (!correct(test, 2, 1, items2)) return 0;

	cout << "I am now using insert to put 0, 1, 2, 30, 20, 10 into an empty sequence, " << endl;;
	cout << "and repeat calling make_last_current and remove_current three times." << endl;
	test = empty;
	test.insert(0);
	test.insert(1);
	test.insert(2);
	test.insert(30);
	test.insert(20);
	test.insert(10);
	test.make_last_current();
	test.remove_current();
	test.make_last_current();
	test.remove_current();
	test.make_last_current();
	test.remove_current();
	if (!correct(test, 3, 3, items2)) return 0;

	cout << "I am now using add_to_front to put 2,3,4,5,6,7 in an empty sequence.\n";
	cout << "Then I call remove_from_front twice, and use add_to_end to put 1." << endl;
	test = empty;
	test.add_to_front(2);
	test.add_to_front(3);
	test.add_to_front(4);
	test.add_to_front(5);
	test.add_to_front(6);
	test.add_to_front(7);
	test.remove_from_front();
	test.remove_from_front();
	test.add_to_end(1);
	if (!correct(test, 5, 4, items1)) return 0;

	cout << "I am now using add_to_end to put DEFAULT_CAPACITY+3, DEFAULT_CAPACITY+2, ";
	cout << "DEFAULT_CAPACITY+1, ..., 2,1 in an empty sequence. I then repeat calling remove_from_front, ";
	cout << "make_last_current, and remove_current twice.\n";
	test = empty;
	for (size_t i = test.DEFAULT_CAPACITY + 3; i > 0; --i)
	{
		test.add_to_end(i);
	}
	test.remove_from_front();
	test.make_last_current();
	test.remove_current();
	test.remove_from_front();
	test.make_last_current();
	test.remove_current();
	
	test.start();
	for (size_t i = test.DEFAULT_CAPACITY + 1; i > 2; --i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}

	// All tests have been passed
	cout << "All tests of this fourth function have been passed." << endl;
	return POINTS[4];
}


// **************************************************************************
// int test5( )
//   Performs some tests of the += operator.
// **************************************************************************
int test5( )
{
	sequence empty;                            // An empty sequence
	sequence test;                             
	sequence s1;
	double items1[5] = { 5,4,3,2, 1 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

											   // Test that the empty sequence is really empty
	cout << "Starting with an empty sequence." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;

	cout << "I am using add_to_end to put 3,2 into an empty sequence, and add_to_front to put 4,5. " << endl;
	cout << "I then add the sequence (rhs) to an empty sequence (lhs)." << endl;
	s1.add_to_end(3);
	s1.add_to_end(2);
	s1.add_to_front(4);
	s1.add_to_front(5);
	test += s1;
	if (!correct(test, 4, 0, items1)) return 0;

	cout << "I am now adding an empty sequence (rhs) to the sequence (lhs)." << endl;
	s1 += empty;

	if (!correct(s1, 4, 0, items1)) return 0;


	cout << "I am now using attach to put 1,2,...,DEFAULT_CAPACITY in an empty sequence. ";
	cout << "I then use attach to put DEFAULT_CAPACITY+1, DEFAULT_CAPACITY+2, DEFAULT_CAPACITY+3 in an emtpy sequence. ";
	cout << "I add the shorter sequence (rhs) to the longer sequence (lhs)." << endl;
	test = empty;
	for (size_t i = 1; i <= test.DEFAULT_CAPACITY; ++i)
	{
		test.attach(i);
	}
	s1 = empty;
	for (size_t i = test.DEFAULT_CAPACITY +1; i < (test.DEFAULT_CAPACITY+4); ++i)
	{
		s1.attach(i);
	}
	test += s1;

	test.start();
	for (size_t i = 1; i < test.DEFAULT_CAPACITY + 4; ++i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}

	// All tests have been passed
	cout << "All tests of this fifth function have been passed." << endl;
	return POINTS[5];
} 


// **************************************************************************
// int test6( )
//   Performs some tests of the + operator.
// **************************************************************************
int test6( )
{
	sequence empty;                            // An empty sequence
	sequence test;
	sequence s1;
	sequence s2;
	double items1[5] = { 5,4,3,2, 1 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

											   // Test that the empty sequence is really empty
	cout << "Starting with an empty sequence." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;

	cout << "I am using add_to_end to put 3,2 into an empty sequence, and add_to_front to put 4,5. " << endl;
	cout << "I then add the sequence and an empty sequence, and call make_last_current." << endl;
	cout << "First, sequence + empty sequence: " << endl;;
	s1.add_to_end(3);
	s1.add_to_end(2);
	s1.add_to_front(4);
	s1.add_to_front(5);
	test = s1 + empty;
	test.make_last_current();
	if (!correct(test, 4, 3, items1)) return 0;

	cout << "Second, empty sequence + sequence: " << endl;;
	test = empty;
	test = empty + s1;
	test.make_last_current();
	if (!correct(test, 4, 3, items1)) return 0;


	cout << "I am now using attach to put 1,2,...,DEFAULT_CAPACITY in an empty sequence. ";
	cout << "I then use attach to put DEFAULT_CAPACITY+1, DEFAULT_CAPACITY+2, DEFAULT_CAPACITY+3 in an emtpy sequence. ";
	cout << "I add the two sequences." << endl;
	cout << "First, longer sequence + shorter sequence: ";
	s2 = empty;
	for (size_t i = 1; i <= test.DEFAULT_CAPACITY; ++i)
	{
		s2.attach(i);
	}
	s1 = empty;
	for (size_t i = test.DEFAULT_CAPACITY + 1; i < (test.DEFAULT_CAPACITY + 4); ++i)
	{
		s1.attach(i);
	}
	test = s2 + s1;;

	test.start();
	for (size_t i = 1; i < test.DEFAULT_CAPACITY + 4; ++i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}
	cout << "PASSED." << endl;
	cout << "Second, shorter sequence + longer sequence: ";
	test = empty;
	test = s1 + s2;

	test.start();
	for (size_t i = test.DEFAULT_CAPACITY+1; i < (test.DEFAULT_CAPACITY + 4); ++i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}
	for (size_t i = 1; i < test.DEFAULT_CAPACITY + 1; ++i)
	{
		if ((!test.is_item()) || test.current() != i)
		{
			cout << "    Test failed to find " << i << endl;
			return 0;
		}
		test.advance();
	}
	cout << "PASSED." << endl;

	// All tests have been passed
	cout << "All tests of this sixth function have been passed." << endl;
	return POINTS[6];
   
} 


// **************************************************************************
// int test7( )
//   Performs some basic tests of the [] operator.
// **************************************************************************
int test7( )
{
	sequence empty;                            // An empty sequence
	sequence test;
	sequence s1;
	sequence s2;
	double items1[5] = { 5,4,3,2, 1 };  // These 5 items are put in a sequence
	double items2[5] = { 10, 20, 30, 40, 50 }; // These are put in another sequence

	cout << "I am using attach to put 10, 20, 30, 40, 50 in an empty sequence." << endl;
	cout << "I use the subscript operator to access all items in this sequence." << endl;;
	test.attach(10);
	test.attach(20);
	test.attach(30);
	test.attach(40);
	test.attach(50);
	for (size_t i = 1; i < 6; ++i)
	{
		if (test[i-1] != 10*i)
		{
			cout << "    Test failed to access " << 10*i << " at current_index " << i-1 << endl;
			return 0;
		}
	}
	cout << "PASSED." << endl;

	cout << "I am using attach to put 1,2,...,DEFAULT_CAPACITY,DEFAULT_CAPACITY+1,DEFAULT_CAPACITY+2 in an empty sequence. ";
	cout << "I use the subscript operator to access all items in this sequence." << endl;
	test = empty;
	for (size_t i = 1; i <= test.DEFAULT_CAPACITY+2; ++i)
	{
		test.attach(i);
	}

	int ci = 0;
	test.start();
	while (test.is_item())
	{
		if (test[ci] != test.current())
		{
			cout << "    Test failed to find " << ci+1 <<  " at current_index " << ci  << endl;
			return 0;
		}
		test.advance(); 
		++ci;
	}
	cout << "PASSED." << endl;
	
	// All tests have been passed
	cout << "All tests of this seventh function have been passed." << endl;
	return POINTS[7];
}  

int run_a_test(int number, const char message[], int test_function( ), int max)
{
    int result;
    
    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;
    
    return result;
}


// **************************************************************************
// int main( )
//   The main program calls all tests and prints the sum of all points
//   earned from the tests.
// **************************************************************************
int main( )
{
    int sum = 0;
    
    
    cout << "Running " << DESCRIPTION[0] << endl;

    sum += run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
    sum += run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
    sum += run_a_test(3, DESCRIPTION[3], test3, POINTS[3]); 
    sum += run_a_test(4, DESCRIPTION[4], test4, POINTS[4]);
    sum += run_a_test(5, DESCRIPTION[5], test5, POINTS[5]);
    sum += run_a_test(6, DESCRIPTION[6], test6, POINTS[6]);
    sum += run_a_test(7, DESCRIPTION[7], test7, POINTS[7]);
	

    cout << "You have have " << (sum) << " points out of the " << (POINTS[0]);
    cout << " points from this test program.\n";
	
    return EXIT_SUCCESS;

}
