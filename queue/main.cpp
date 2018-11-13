// CSC 307 SP 2018 HW10
// ***Adapted from pal.cxx, available at http://www.cs.colorado.edu/~main/chapter8/pal.cxx,
//    to test "the queue class using a circular linked list"
//    as described in Chapter 8 Programming Project 6.

// ***Relevant comments from pal.cxx are below. 
// FILE: pal.cxx
// Program to test whether an input line is a palindrome. Spaces,
// punctuation, and the difference between upper- and lowercase are ignored.

#include <cassert>    // Provides assert
#include <cctype>     // Provides isalpha, toupper
#include <cstdlib>    // Provides EXIT_SUCCESS
#include <iostream>   // Provides cout, cin, peek
#include <string>
#include <stack>      // Provides the stack template class
#include "queue5.h"
using namespace std;
using main_savitch_8D::queue;


// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 3;
const int POINTS[MANY_TESTS + 1] = {
	20, // Total points for all tests.
	10,  // Test 1 points
	5,  // Test 2 points
	5  // Test 3 points
};
const char DESCRIPTION[MANY_TESTS + 1][256] = {
	"Testing whether an input line is a palindrome (See Figures 8.3 and 8.4)",
	"Testing push, pop, and front",
	"Testing the copy constructor, assignment, and size",
};

bool pal(string str)
{
	// adapted from Figure 8.3 in our textbook, a program to recognize palindromes
	queue<char> q; 
	stack<char> s;
	queue<char>::size_type mismatches = 0;  // Mismatches between queue and stack
	for (const auto& letter : str)
	{	
		if (isalpha(letter))
		{
			q.push(toupper(letter));
			s.push(toupper(letter));
		}
	}
	while ((!q.empty()) && (!s.empty()))
	{
		if (q.front() != s.top())
		{
			++mismatches;
		}
		q.pop();
		s.pop();
	}

	if (mismatches == 0)
	{
		cout << "That is a palindrome." << endl;
		return true;
	}
	else
	{
		cout << "That is not a palindrome." << endl;
		return false;
	}
}

bool correct(queue<int> test, queue<int>::size_type n, int items[], int ibegin)
{
	unsigned int i;
	bool answer = true;
	if (test.size() != n)
		answer = false;
	else
	{
		for (i = 0; answer && (i < n); i++)
		{
			if (items[i+ibegin] != test.front())
				answer = false;
			test.pop();
		}
	}
	cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
	return answer;
}

unsigned int test1()
{
	bool answer = true;
	string str1 = "Straw? No, too stupid a fad. I put soot on warts.";
	string str2 = "Able were you ere you saw Elba.";
	cout << "Testing if \"" << str1 << "\" is a palindrome." << endl; 
	if (!pal(str1))
	{
		answer = false;
	}
	cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
	if (!answer) return 0;
	
	cout << "Testing if \"" << str2 << "\" is a palindrome." << endl;
	if (pal(str2))
	{
		answer = false;
	}
	cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
	if (!answer) return 0;
	return POINTS[1];
}

unsigned int test2()
{
	const queue<int>::size_type TESTSIZE = 300;
	queue<int> test;
	int items1[2] = { 1, -1 };
	int items2[8] = { 1,2,3,4,5,6,7,8};
	int items3[TESTSIZE];

	cout << "Testing size for an empty queue.";
	cout << endl;
	if (!correct(test, 0, items1, 0)) return 0;

	cout << "Enqueueing 1 and then -1 then testing\n";
	cout << endl;
	test.push(1); test.push(-1);
	if (!correct(test, 2, items1, 0)) return 0;

	cout << "Dequeueing until empty then testing\n";
	cout << endl;
	test.pop(); test.pop();
	if (!correct(test, 0, items1,0)) return 0;

	cout << "Enqueueing 1, 2, ..., 8 then testing\n";
	cout << endl;
	for (int i = 1; i <= 8; ++i)
	{
		test.push(i);
		
	}
	if (!correct(test, 8, items2, 0)) return 0;

	queue<int> test2;
	cout << "Enqueueing 200 ints to an empty queue then testing\n";
	cout << endl;
	
	for (int i = 1; i <= 200; ++i)
	{
		int next = (rand() % TESTSIZE) + i;
		test2.push(next);
		items3[i-1] = next;

	}
	if (!correct(test2, 200, items3, 0)) return 0;

	cout << "Dequeueing 12 ints then testing\n";
	cout << endl;

	for (int i = 1; i <= 12; ++i)
	{
		test2.pop();
	}
	if (!correct(test2, 188, items3, 12)) return 0;


	cout << "Enqueueing 12 more ints then testing\n";
	cout << endl;

	for (int i = 201; i <= 212; ++i)
	{
		test2.push(i);
		items3[i - 1] = i;
	}
	if (!correct(test2, 200, items3, 12)) return 0;

	return POINTS[2];
}

unsigned int test3()
{
	queue<int> test;
	int items1[2] = { 1, -1 };
	int items2[8] = { 1,2,3,4,5,6,7,8 };

	cout << "Testing that copy constructor works for empty queue\n";
	cout << endl;
	queue<int> copy1(test);
	if (!correct(copy1, 0, items1, 0)) return 0;

	cout << "Enqueueing 1, 2, ..., 8 to an empty queue and testing that copy constructor and = work\n";
	cout << endl;
	for (int i = 1; i <= 8; ++i)
	{
		test.push(i);
	}
	if (!correct(copy1, 0, items1, 0)) return 0;

	queue<int> copy2(test);
	if (!correct(copy2, 8, items2, 0)) return 0;

	copy1 = copy2;
	if (!correct(copy1, 8, items2, 0)) return 0;

	cout << "Enqueueing 1 and -1 to an empty queue and testing that = works\n";
	cout << endl;
	queue<int> test1;
	test1.push(1); 
	test1.push(-1);
	copy2 = test1;
	if (!correct(copy2, 2, items1, 0)) return 0;
	if (!correct(copy1, 8, items2, 0)) return 0;
	return POINTS[2];
}

unsigned int run_a_test(unsigned int number, const char message[], unsigned int test_function(), unsigned int max)
{
	unsigned int result;

	cout << endl << "START OF TEST " << number << ":" << endl;
	cout << message << " (" << max << " points)." << endl;
	result = test_function();
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
int main( )
{
	unsigned int sum = 0;
	sum += run_a_test(1, DESCRIPTION[0], test1, POINTS[1]); 
	sum += run_a_test(2, DESCRIPTION[1], test2, POINTS[2]); 
	sum += run_a_test(3, DESCRIPTION[2], test3, POINTS[3]);
	
	cout << "You have " << sum << " points out of " << POINTS[0];
	cout << " points from this test program.\n";

    return EXIT_SUCCESS;    
}
