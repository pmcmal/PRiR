// PROJEKT PRIR 2022
// DOLACZENIE BIBLIOTEK
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <math.h>
#include <unistd.h>
// OPENMP
using namespace std;
// WIELKOSC TABELI
int N = 10;
// ILOSC WATKOW DLA OPENMP
int watki = 32;

// SEKCJA TWORZENIA TABELI
int* createTable() {
  int* table = (int*)malloc(sizeof(int) * N);
  srand((unsigned) time(NULL));
	for (int i=0; i < N; i++) {
		// zakres losowania 1-1000
		table[i] = rand();
  }
  return table;
}

// SEKCJA WYKONANIA OPENMP
int openmp(int* table) {
	printf("\nLiczę dla openmp: \n");
	int posmax=0, posmin=0, avg=0, sum=0;
	#pragma omp parallel for num_threads(watki)
		for (int i = 1; i < N; i++) {
			int max = table[0]; // 1 element tablicy
			if(table[i]>max)
				{
				max=table[i];
				posmax=i;
			}
		}
		// usuwanie wartosci max
		for ( int c = posmax; c < N - 1; c++) {
			table[c]=table[c+1];
		}
		int min = table[0]; // 1 element tablicy
		for (int i = 1; i < N - 1; i++) {
			if(table[i]<min)
			{
				min=table[i];
				posmin=i;
			}
		}
		// usuwanie wartosci min
		for ( int c = posmin; c < N - 2; c++) {
			table[c]=table[c+1];
		}
		// liczenie sumy i sredniej
		for (int i = 0; i < N - 2; i++) {
			sum = sum + table[i];
			avg = sum / N-2;
		}
return 0;
}

// GLOWNA FUNKCJA
int main() {
	int wielkosc = 10000;
	printf("Liczę openMP: \n");
	for (int i=0; i < wielkosc; i++){
	  int* table = createTable();
	  clock_t start = clock();
	  printf("%d\n", openmp(table));
	  clock_t end = clock();
	  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	  printf("Czas wykonania: %f\n", seconds);
	}
	return 0;
}
