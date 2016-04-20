#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>

using namespace std;

int comparisons = 0;
int exchanges = 0;

void bubblesort(int A[], int n)
{
	int i, j, temp;
	for (i = 1; i<n; i++) // number of passes
	{
		for (j = 0; j<n - 1; j++) // j varies from 0 to n-1
		{
			comparisons++;
			if (A[j] > A[j + 1]) // compare two successive numbers
			{
				temp = A[j]; // swap a[j] with a[j+1]
				A[j] = A[j + 1];
				A[j + 1] = temp;
				exchanges++;
			}
		}
	}
}

void InsertionSort(int A[], int n)
{
	int i, j, element;
	for (i = 1; i<n; i++)
	{
		element = A[i];
		// insert ith element in 0 to i-1 array
		j = i;
		while ((j>0) && (A[j - 1] > element))
			// compare if A[j-1] > element
		{
			A[j] = A[j - 1]; // shift elements
			j = j - 1;
			exchanges++;
			comparisons++;
		}
		A[j] = element; // place element at jth position
	}
}


#define max 20
void read(int A[max], int n)
{
	int i;
	for (i = 0; i<n; i++)
		cin >> A[i];
}


void display(int A[max], int n)
{
	int i;
	for (i = 0; i<n; i++)
		cout << A[i];
}

void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	
}

int partition(int a[], int left, int right, int pivotIndex)
{
	int pivot = a[pivotIndex];
	do
	{
		while (a[left] < pivot) left++;
		while (a[right] > pivot) right--;
		comparisons++;
		if (left < right && a[left] != a[right])
		{
			swap(a[left], a[right]);
			exchanges++;
		}
		else
		{
			return right;
		}
	} while (left < right);
	return right;
}
void quicksort(int a[], int left, int right)
{
	if (left < right)
	{
		int pivot = (left + right) / 2; // middle
		int pivotNew = partition(a, left, right, pivot);
		quicksort(a, left, pivotNew - 1);
		quicksort(a, pivotNew + 1, right);
	}
}

void shell_sort(int A[], int n)
{
	int temp, gap, i;
	int swapped;
	gap = n / 2;
	do
	{
		do
		{
			swapped = 0;
			for (i = 0; i<n - gap; i++) {
				comparisons++;
				if (A[i] > A[i + gap])
				{
					temp = A[i];
					A[i] = A[i + gap];
					A[i + gap] = temp;
					exchanges++;
					swapped = 1;
				}
			}
		} while (swapped == 1);
	} while ((gap = gap / 2) >= 1);
}

void merge(int A[], int low, int high, int mid)
{
	int i, j, k, C[10000];
	i = low; // index for first part
	j = mid + 1; // index for second part
	k = 0; //index for array c
	while ((i <= mid) && (j <= high))
		// merge arrays A & B in array C
	{
		comparisons++; exchanges++;
		if (A[i] < A[j])
			C[k] = A[i++];
		else
			C[k] = A[j++];
		k++;
	}
	while (i <= mid) {
		C[k++] = A[i++];
		exchanges++;
	}
	while (j <= high) {
		C[k++] = A[j++];
		exchanges++;
	}
	for (i = low, j = 0; i <= high; i++, j++) //???
		// copy array C contents back to array A
	{
		A[i] = C[j];
		exchanges++;
	}
}

void MergeSort(int A[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		MergeSort(A, low, mid);
		MergeSort(A, mid + 1, high);
		merge(A, low, high, mid);
	}
}

bool array_y(string red, int *& noms)   //reading in the text files into arrays
{
	ifstream thisfile;      //input file stream
	thisfile.open(red.c_str());     //c-style string, open the input file

	if (!thisfile.is_open())     //if the file fails to open
	{
		cout << "File not found" << red << endl;
		cout << "Incorrect location \n";
		cout << endl; //space
		return false;
	}
	string y;       //create a random string
	string x = " ";     //create a random string
	while (thisfile.peek() != EOF)
		//peek reads and returns the next character without extracting
		//while this is not equal to end of the file
	{
		thisfile >> y;      //read in string y
		x += y + " ";
	}
	thisfile.clear();
	thisfile.close();       //close the input file

	vector<string> vertical;        //a vector of string
	y = "";
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] == ' ')
		{
			vertical.push_back(y);
			y = "";
		}
		else
		{
			y += x[i];
		}
	}
	/*
	if (noms != NULL)        //making sure the memory is free
	{
		delete noms;
	}
	*/
	noms = new int[vertical.size()];
	for (int i = 0; i < vertical.size(); i++)
	{
		noms[i] = atoi(vertical[i].c_str());
	}
	return true;
}

int main()
{/*
	int a[] = { 5, 2, 4, 3, 1 };
	bubblesort(a, 5);
	for (int i = 0; i < 5; i++) {
		cout << a[i] << endl;
	}
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	int b[] = { 5, 2, 4, 3, 1 };
	InsertionSort(b, 5);
	for (int i = 0; i < 5; i++) {
		cout << b[i] << endl;
	}
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	int c[] = { 5, 2, 4, 3, 1 };
	quicksort(c, 0,4);
	for (int i = 0; i < 5; i++) {
		cout << c[i] << endl;
	}
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	int d[] = { 5, 2, 4, 3, 1 };
	shell_sort(d, 5);
	for (int i = 0; i < 5; i++) {
		cout << d[i] << endl;
	}
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	int e[] = { 5, 2, 4, 3, 1 };
	MergeSort(e, 0,4);
	for (int i = 0; i < 5; i++) {
		cout << e[i] << endl;
	}
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;
	*/
	//FEW UNIQUE
	cout << "FEW UNIQUE" << endl;
	int * a1;
	array_y("FewUnique.txt", a1);
	bubblesort(a1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("FewUnique.txt", a1);
	InsertionSort(a1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("FewUnique.txt", a1);
	quicksort(a1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("FewUnique.txt", a1);
	shell_sort(a1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("FewUnique.txt", a1);
	MergeSort(a1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;
	//RANDOM

	cout << "RANDOM" << endl;
	int * b1;
	array_y("Random.txt", b1);
	bubblesort(b1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Random.txt", b1);
	InsertionSort(b1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Random.txt", b1);
	quicksort(b1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Random.txt", b1);
	shell_sort(b1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Random.txt", b1);
	MergeSort(b1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	cout << "NEARLY SORTED" << endl;
	int * c1;
	array_y("NearlySorted.txt", c1);
	bubblesort(c1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("NearlySorted.txt", c1);
	InsertionSort(c1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("NearlySorted.txt", c1);
	quicksort(c1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("NearlySorted.txt", c1);
	shell_sort(c1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("NearlySorted.txt", c1);
	MergeSort(c1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	cout << "REVERSED" << endl;
	int * d1;
	array_y("Reversed.txt", d1);
	bubblesort(d1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Reversed.txt", d1);
	InsertionSort(d1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Reversed.txt", d1);
	quicksort(d1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Reversed.txt", d1);
	shell_sort(d1, 10000);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;

	array_y("Reversed.txt", d1);
	MergeSort(d1, 0, 9999);
	cout << exchanges << " " << comparisons << endl;
	exchanges = 0;
	comparisons = 0;


	system("pause");
}


