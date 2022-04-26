// PROJEKT PRIR 2022
// DOLACZENIE BIBLIOTEK
#include <math.h>
#include <iostream>
#include "mpi.h"
#include <cstdlib>
using namespace std;
// SEKCJA MPI
int main(int argc, char *argv[])
{
	// wielkosc tablicy
	const int n = 10;
	int rank, size;
	int  i, j, k;
	int avg=0, sum=0;
	int values[n] = {0};
	// tablica do przechowywania liczb
	int maxvalue[2] = {0};
	int minvalue[2] = {0};
	int globalmaxvalue[2] = {0};
	int globalminvalue[2] = {0};

	MPI::Status status;
		// inicjalizacja MPI
        MPI::Init(argc, argv);
        size = MPI::COMM_WORLD.Get_size();
        rank = MPI::COMM_WORLD.Get_rank();

	// wypelnianie liczbami losowymi
	srand(rank+1);
	for (i = 0; i < n; i++)
	{
		values[i] = rand();
	}
	clock_t start = clock();
	maxvalue[0] = values[0];
	minvalue[0] = values[0];
	maxvalue[1] = rank;
	minvalue[1] = rank;
	// min, max dla kazdego z procesow
	for (k = 1; k < n; k++)
	{
		if (values[k] > maxvalue[0])
		{
			maxvalue[0] = values[k];
			int posmax = k;
			for ( int c = posmax; c < n - 1; c++) {
				values[k+1];
			}
		}
		if (values[k] < minvalue[0])
		{
			minvalue[0] = values[k];
			int posmin = k;
			for ( int c = posmin; c < n - 2; c++) {
				values[k+1];
			}
		}
	}
	// liczenie sumy i sredniej
   	for (int i = 0; i < n - 2; i++) {
   		sum = sum + values[i];
		avg = sum / n - 2;
   	}
	MPI::Finalize();
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Czas wykonania: %f\n", seconds);
	return 0;
}
