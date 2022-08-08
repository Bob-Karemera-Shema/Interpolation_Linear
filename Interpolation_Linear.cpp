// Interpolation_Linear.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <list>
#include <random>

using namespace std;

int comparison_counter;  //Global variable

int linearSearch(vector <int> data_set, int top, int bottom, int target)
{
	//Perform linear search
	//If target is found, return index
	//else return  -1
	for (int j = bottom; j < top; j++)
	{
		++comparison_counter;
		if (data_set[j] == target)
		{
			return j;
		}
		if (data_set[j] > target)
		{
			return -1;
		}
	}
}

int interpolationSearch(vector <int> data_set, int top, int bottom, int target)
{
	// If target is found, its index is returned
	// else perform linear search

	comparison_counter = 0;		//comparison set to zero everytime interpolation search is performed

	if (bottom == top)
	{
		++comparison_counter;
		if (data_set[bottom] == target)
		{
			return bottom;
		}
		return -1;
	}

	//Get predicted target using interpolation formula
	int predicted_target = (((top - bottom) * ((double)(target - data_set[bottom]) /
		(data_set[top] - data_set[bottom]))) + bottom);

	++comparison_counter;
	if (data_set[predicted_target] == target)
	{
		return predicted_target;
	}
	else if (data_set[predicted_target] < target)
	{
		bottom = predicted_target + 1;
	}
	else
	{
		top = predicted_target - 1;
	}

	predicted_target = linearSearch(data_set, top, bottom, target);

	return predicted_target;
}

int min(vector <int> comparisons)				//Function to get minimum value from a vector
{
	int min = 1;

	for (int j = 0; j < comparisons.size(); j++)
	{
		if (comparisons[j] < min)
		{
			min = comparisons[j];
		}
	}
	return min;
}

int mean(vector <int> comparisons)				//Function to get the mean of all values in a vector
{
	int sum = 0;

	for (int j = 0; j < comparisons.size(); j++) {
		sum += comparisons[j];
	}

	return sum / comparisons.size();
}

int max(vector <int> comparisons)				//Function to get maximum value from a vector
{
	int max = 1;

	for (int j = 0; j < comparisons.size(); j++) {
		if (comparisons[j] > max) {
			max = comparisons[j];
		}
	}
	return max;
}

int main()
{
	//Declare vectors to store best, average and worst cases for all vector sizes
	vector <int> bestCase;
	vector <int> averageCase;
	vector <int> worstCase;

	//Declare file holder for empirical data file
	ofstream dataFile;

	for (int n = 1; n <= 1024; n++)
	{
		vector <int> data_set;			//data vector for each iteration
		vector <int> comparisons;		//comparisons vector for each iteration
		int search_target;
		int top = n - 1;				//last element index in the data vector
		int bottom = 0;					//first element index in the data vector

		for (int i = 1; i <= n; i++)	//initialise data set
		{
			data_set.push_back(i);
		}

		for (int j = 1; j <= n; j++)	//test interpolation search with different search targets and data set sizes
		{
			search_target = j;
			int index = interpolationSearch(data_set, top, bottom, search_target);

			if (index != -1)
			{
				comparisons.push_back(comparison_counter);
			}
		}

		//add best,average and worst cases for each array size to their corresponding vectors
		bestCase.push_back(min(comparisons));
		averageCase.push_back(mean(comparisons));
		worstCase.push_back(max(comparisons));
	}

	//Write dempirical test data to designated file
	dataFile.open("Data.txt", ios::app);
	for (int i = 0; i < bestCase.size(); i++)
	{
		dataFile << i + 1 << "\t" << bestCase[i] << "\t" << averageCase[i] << "\t" << worstCase[i] << endl;
	}
	dataFile.close();	//Close access to test data file

	return 0;
	system("PAUSE");
}