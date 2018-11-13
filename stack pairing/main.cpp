// CSC 307 SP 2018 HW9
// ADAPTED FROM the following file, available at
// [https://www.cs.colorado.edu/~main/chapter10/bagexam.cxx]:

// FILE: bagexam.cxx
// Written by: Michael Main (main@colorado.edu), Nov 8, 2000
// Non-interactive test program for the bag class
// with improved test for heap leaks.
//
// DESCRIPTION:
// Each function tests part of the bag class, returning some
// number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...


#include <iostream>   
#include "bag3pair.h"
using namespace std;
using namespace main_savitch_5;


// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 4;
const int POINTS[MANY_TESTS+1] = {
  20, // Total points for all tests.
    8,  // Test 1 points
    2,  // Test 2 points
    5,  // Test 3 points
    5   // Test 4 points
};
const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for bag class",
    "Testing insert",
    "Testing the copy constructor",
    "Testing + and +=",
    "Testing erase and erase_one functions"
};


// **************************************************************************
// bool correct(
//   const bag& test,
//   bag::size_type n,
//   bag::size_type count[ ],
//   int max
//   )
// **************************************************************************
bool correct(
    const bag& test,
    bag::size_type n,
    bag::size_type count[],
    int max
    )
{
    int i;
    bool answer = true;
    if (test.size( ) != n)
        answer = false;
    else
        for (i = 0; answer && (i <= max); i++)
            if (count[i] != test.count(i))
                answer = false;
	double prev = -1.0;
	for (node* cn = test.first(); cn != NULL; cn = cn->link())
	{
		if ((cn->data()).first <= 0)
			answer = false;
		if ((cn->data()).second <= prev)
			answer = false;
		prev = (cn->data()).second;
	}
    cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
    return answer;
}


// **************************************************************************
// int test1( )
//   Performs some basic tests of insert and the constant member
//   functions. Returns POINTS[1] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test1( )
{
    const bag::size_type TESTSIZE = 3000;
    bag test;
	bag b;
    bag::size_type items[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bag::size_type rand_items[50];
    char test_letter = 'A';
    bag::size_type i;
    int next;

    cout << test_letter++ << ". ";
    cout << "Testing size and count for an empty bag.";
    cout << endl;
    if (!correct(test, 0, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Adding the number 4 to the bag, and then testing\n";
    cout << "   size and count.";
    cout << endl;
    test.insert(4);
    items[4]++;
    if (!correct(test, 1, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting the number 2 into the bag.\n";
    cout << "   Then checking size and count.";
    cout << endl;
    test.insert(2);
    items[2]++;
    if (!correct(test, 2, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting the number 1 into the bag.\n";
    cout << "   Then checking size and count.";
    cout << endl;
    test.insert(1);
    items[1]++;
    if (!correct(test, 3, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting the number 3 into the bag.\n";
    cout << "   Then checking size and count.";
    cout << endl;
    test.insert(3);
    items[3]++;
    if (!correct(test, 4, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting another 2 into the bag.\n";
    cout << "   Then checking size and count.";
    cout << endl;
    test.insert(2);
    items[2]++;
    if (!correct(test, 4, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting the numbers 5, 6, and 7 into the bag.\n";
    cout << "   Then checking size and count.";
    cout << endl;
    test.insert(5);
    test.insert(6);
    test.insert(7);
    items[5]++;
    items[6]++;
    items[7]++;
    if (!correct(test, 7, items, 7)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting " << TESTSIZE << "+ random items between 0 and 49 into a new bag\n";
    cout << "   and then checking size and count.";
    cout << endl;
	for (i = 0; i < 50; i++) {
		rand_items[i] = 1; // (i < 8) ? items[i] : 0;
		b.insert(i);
	}
    for (i = 0; i < TESTSIZE; i++)
    {
        next = rand( ) % 50;
        rand_items[next]++;
        b.insert(next);
    }

	if (!correct(b, 50, rand_items, 49)) return 0;

    return POINTS[1];
}



// **************************************************************************
// int test2( )
//   Performs some tests of the copy constructor.
//   Returns POINTS[2] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test2( )
{
    bag test;
    bag::size_type items[4] = { 0, 0, 0, 0 };

    cout << "A. Testing that copy constructor works okay for empty bag...";
    cout << flush;
    bag copy1(test);
    if (!correct(copy1, 0, items, 3)) return 0;

    cout << "B. Testing copy constructor with 4-item bag...";
    cout << flush;
    test.insert(1);
    test.insert(1);
    test.insert(1);
    test.insert(1);
    bag copy2(test);
    test.insert(1); // Alter the original, but not the copy
    items[1] = 4; // Should be four 1's in the copy2.
    if (!correct(copy2, 1, items, 3)) return 0;

    return POINTS[2];
}


// **************************************************************************
// int test3( )
//   Performs some tests of the + and += operator.
//   Returns POINTS[3] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test3( )
{
	const bag::size_type TESTSIZE = 3000;
	bag test;
	bag b;
	bag::size_type items[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	bag::size_type rand_items[50];
	bag::size_type items2[50];
	char test_letter = 'A';
	bag::size_type i;
	int next;

	cout << test_letter++ << ". ";	
	cout << "Adding 4, 2, 2, 4, 1, 5, 2 to an empty bag, and then testing\n";
	cout << "   size and count.";
	cout << endl;
	test.insert(4); items[4]++;
	test.insert(2); items[2]++;
	test.insert(2); items[2]++;
	test.insert(4); items[4]++;
	test.insert(1); items[1]++;
	test.insert(5); items[5]++;
	test.insert(2); items[2]++;
	if (!correct(test, 4, items, 7)) return 0;

	cout << test_letter++ << ". ";
	cout << "Inserting " << TESTSIZE << "+ random items between 0 and 49 into a new bag\n";
	cout << "   and then checking size and count.";
	cout << endl;
	for (i = 0; i < 50; i++) {
		rand_items[i] = 1; // (i < 8) ? items[i] : 0;
		if (i < 8)
			items2[i] = items[i] + rand_items[i];
		else
			items2[i] = rand_items[i];

		b.insert(i);
	}
	for (i = 0; i < TESTSIZE; i++)
	{
		next = rand() % 50;
		rand_items[next]++;
		items2[next]++;
		b.insert(next);
	}
	if (!correct(b, 50, rand_items, 49)) return 0;

	cout << test_letter++ << ". ";
	cout << "adding two bags, A + B, and then checking size and count.";
	cout << endl;
	bag badd1 = test + b;
	
	if (!correct(badd1, 50, items2, 49)) return 0;

	cout << test_letter++ << ". ";
	cout << "adding two bags, B += A, and then checking size and count.";
	cout << endl;
	bag badd2 = b;
	badd2 += test;
	if (!correct(badd2, 50, items2, 49)) return 0;
    return POINTS[3];
}


// **************************************************************************
// int test4( )
//   Performs basic tests for the erase and erase_one functions.
//   Returns POINTS[4] if the tests are passed.
//   Otherwise returns 0.
// **************************************************************************
int test4( )
{
    bag test;
    bag::size_type count[16] = { 0,1,1,1,1,1,1,1,1,0,2,1,1,1,1,1};
    bag::size_type cempty[16]= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    cout << "Testing removal from empty bag (should have no effect) ...";
    cout << flush;
    if (test.erase_one(0))
    {
	cout << "Erase function incorrectly returned true." << endl;
	return 0;
    }
    if (!correct(test, 0, cempty, 15)) return 0;
        
    cout << "Inserting these: 8 6 10 1 7 10 15 3 13 2 5 11 14 4 12" << endl;
    test.insert( 8);
    test.insert( 6);
    test.insert(10);
    test.insert( 1);
    test.insert( 7);
    test.insert(10);
    test.insert(15);
    test.insert( 3);
    test.insert(13);
    test.insert( 2);
    test.insert( 5);
    test.insert(11);
    test.insert(14);
    test.insert( 4);
    test.insert(12);
    if (!correct(test, 14, count, 15)) return 0;

    cout << "Removing 0 (which is not in bag, so bag should be unchanged) ...";
    cout << flush;
    if (test.erase_one(0))
    {
	cout << "Erase function incorrectly returned true." << endl;
	return 0;
    }
    if (!correct(test, 14, count, 15)) return 0;

    cout << "Removing the 6 ..." << flush;
    if (!test.erase_one(6))
    {
	cout << "Erase function incorrectly returned false." << endl;
	return 0;
    }
    count[6] = 0;
    if (!correct(test, 13, count, 15)) return 0;

    cout << "Removing one 10 ..." << flush;
    test.erase_one(10);
    count[10]--;
    if (!correct(test, 13, count, 15)) return 0;

    cout << "Removing the 1 ..." << flush;
    test.erase_one(1);
    count[1]--;
    if (!correct(test, 12, count, 15)) return 0;

    cout << "Removing the 15 ..." << flush;
    test.erase_one(15);
    count[15]--;
    if (!correct(test, 11, count, 15)) return 0;

    cout << "Removing the 5 ..." << flush;
    test.erase_one(5);
    count[5]--;
    if (!correct(test, 10, count, 15)) return 0;

    cout << "Removing the 11 ..." << flush;
    test.erase_one(11);
    count[11]--;
    if (!correct(test, 9, count, 15)) return 0;

    cout << "Removing the 3 ..." << flush;
    test.erase_one(3);
    count[3]--;
    if (!correct(test, 8, count, 15)) return 0;

    cout << "Removing the 13 ..." << flush;
    test.erase_one(13);
    count[13]--;
    if (!correct(test, 7, count, 15)) return 0;

    cout << "Removing the 2 ..." << flush;
    test.erase_one(2);
    count[2]--;
    if (!correct(test, 6, count, 15)) return 0;

    cout << "Removing the 14 ..." << flush;
    test.erase_one(14);
    count[14]--;
    if (!correct(test, 5, count, 15)) return 0;

    cout << "Removing the 4 ..." << flush;
    test.erase_one(4);
    count[4]--;
    if (!correct(test, 4, count, 15)) return 0;

    cout << "Removing the 12 ..." << flush;
    test.erase_one(12);
    count[12]--;
    if (!correct(test, 3, count, 15)) return 0;

    cout << "Removing the 8 ..." << flush;
    test.erase_one(8);
    count[8]--;
    if (!correct(test, 2, count, 15)) return 0;

    cout << "Removing the 7 ..." << flush;
    test.erase_one(7);
    count[7]--;
    if (!correct(test, 1, count, 15)) return 0;

    cout << "Inserting more 10's ..." << flush;
    test.insert(10);
    test.insert(10);
    test.insert(10);

    cout << "Removing all 10's ..." << flush;
    test.erase(10);
    count[10] = 0;
    if (!correct(test, 0, count, 15)) return 0;
    return POINTS[4];
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

    sum += run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
    sum += run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
    sum += run_a_test(3, DESCRIPTION[3], test3, POINTS[3]);
    sum += run_a_test(4, DESCRIPTION[4], test4, POINTS[4]);

    cout << "If you submit this now, you will have\n";
    cout << sum << " points out of the ";
    cout << POINTS[0];
    cout << " points from this test program.\n";
    
	//system("pause");
    return EXIT_SUCCESS;

}

