#ifndef QUICKSORT_H_
#define QUICKSORT_H_

inline int partition_naive(int *A, int p, int r)
{
	int x = A[r];
	int i = p - 1;
	int j;
	for(j=0; j<r; j++)
	{
		if(A[j] <= x)
		{
			i = i + 1;
			int tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	int tmp = A[i+1];
	A[i+1] = A[r];
	A[r] = tmp;
	return i+1;
}

void quicksort_naive(int *A, int p, int r)
{
	if(p<r)
	{
		int q = partition_naive(A, p, r);
		quicksort_naive(A, p, q - 1);
		quicksort_naive(A, q + 1, p);
	}
}


#endif // QUICKSORT_H_