
*/

#include <iostream>
#include <iomanip>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <ctime>
#include <cstdlib>

using namespace std;

void merge(unsigned int data[], size_t n1, size_t n2);
void mergesort(unsigned int data[], size_t n, unsigned int exit_point = 1);
void insertionsort(unsigned int data[], size_t n);
void print(unsigned int data[], size_t n);

//---------------------------------------------------------------
void merge(unsigned int data[], size_t n1, size_t n2)
{
	int *temp;
	size_t copied = 0;
	size_t copied1 = 0;
	size_t copied2 = 0;
	size_t i;

	temp = new int[n1 + n2];

	while ((copied1 < n1) && (copied2 < n2))
	{
		if (data[copied1] < (data + n1)[copied2])
		{
			temp[copied++] = data[copied1++];
		}
		else
		{
			temp[copied++] = (data + n1)[copied2++];
		}
	}

	while (copied1 < n1)
	{
		temp[copied++] = data[copied1++];
	}
	while (copied2 < n2)
	{
		temp[copied++] = (data + n1)[copied2++];
	}

	for (i = 0; i < n1 + n2; ++i)
	{
		data[i] = temp[i];
	}
	delete[]temp;
}

void mergesort(unsigned int data[], size_t n,unsigned int exit_point)
{
	size_t n1;
	size_t n2;

	if (n > exit_point)
	{
		n1 = n / 2;
		n2 = n - n1;

		mergesort(data, n1);
		mergesort((data + n1), n2);

		merge(data, n1, n2);
	}
}

void insertionsort(unsigned int data[], size_t n)
{
	size_t i, j;
	int next;

	for (i = 1; i < n; ++i)
	{
		next = data[i];
		j = i;
		while (j > 0 && next < data[j - 1])
		{
			data[j] = data[j - 1];
			--j;
		}
		data[j] = next;
	}
}

void print(unsigned int data[], size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}
//----------------------------------------------------------------
int main()
{
		const unsigned int ARRAY_SIZE = 1000;
		unsigned int numbers[ARRAY_SIZE];
		clock_t time0, time1, time_T, min_time0 = NULL, min_time1 = NULL;
		double min_timeT = 0.0, avg_merge = 0.0, avg_insert = 0.0;
		unsigned int min_iteration = 0;
		srand((unsigned)clock());
		
		for (unsigned int variance = ARRAY_SIZE; variance > 0; --variance)
		{
			time_T = 0;
			for (int i = 0; i < ARRAY_SIZE; ++i)
			{
				numbers[i] = rand() % 100;
			}

			time0 = clock();
			mergesort(numbers, ARRAY_SIZE, variance);

			avg_merge += static_cast<double>(clock() - time0) / CLOCKS_PER_SEC;
		
			time1 = clock();
			insertionsort(numbers, ARRAY_SIZE);

			
			avg_insert += static_cast<double>(clock() - time1) / CLOCKS_PER_SEC;
			
			if((clock() - time0)+(clock() - time1) < (clock() - min_timeT))
			{
				min_time0 = time0;
				min_time1 = time1;
				min_timeT = (clock() - time_T);
				min_iteration = ARRAY_SIZE - variance;
			}
		}



		cout << "\n**********************************************************************************************\n";
		cout << " Type of sorting used: " << "             |     " << "CPU Time:" << setw(5) << fixed << endl;
		cout << "\n**********************************************************************************************\n";
		cout << " Merge Sort " << "                       |     " << "Total CPU time for best-case merge sort: " << static_cast<double>(clock() - min_time0) / CLOCKS_PER_SEC << " seconds" << endl;
		cout << "\n**********************************************************************************************\n";
		cout << " Insertion Sort " << "                   |     " << "Total CPU time for best-case insertion sort: " << static_cast<double>(clock() - min_time1) / CLOCKS_PER_SEC << " seconds" << endl;
		cout << "\n**********************************************************************************************\n";
		cout << " Merge Sort " << "                       |     " << "Average CPU time for all merge sort cases: " << avg_merge << " seconds" << endl;
		cout << "\n**********************************************************************************************\n";
		cout << " Insertion Sort " << "                   |     " << "Average CPU time for all insertion sort cases: " << avg_insert << " seconds" << endl;
		cout << "\n**********************************************************************************************\n";

		cout << "According to these calculations, the optimal cutoff point for an array of " << ARRAY_SIZE << " elements of positive intergers" << endl;
		cout << "is after " << min_iteration << " iterations of merge sort with a total time of "<< static_cast<double>(min_timeT) / CLOCKS_PER_SEC << " seconds" << endl;

		return 0;
}

/*
//////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                    Collaborators on this Assignment:                     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                                                                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              Micheal whitney - Implementation                            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              Kaitlyn Butler - Implementation                             \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              James Sherman - Implementation                              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////              cplusplus.com - Reference                                   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////                                                                          \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

