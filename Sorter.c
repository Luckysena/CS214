#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "Sorter.h"


void resize(data * ori) // resizes array if the original aribitrary size is too small
{

data * create=NULL;
create=(data*)realloc(ori,2*sizeof(ori));
while(create == ori);

ori=create;

}

void split(const void* A, int left, int right)
{
	if (left<right)
	{
		data *array=(data*)A;
		int middle=floor((left+1)/2);
		split(array,left,middle);
		split(array,middle+1,right);
		merge(array,left,middle,right);
	}

}
void merge(const void * A,int left , int middle , int right) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	data *array=(data*)A;
	size1 = middle-left+1;
	size2 = right-middle;

	data *first = (data*) malloc(sizeof(int)*size1);
	data *second = (data*) malloc(sizeof(int)*size2);

	for (int i = left; i < size1; ++i)
	{
		first[i] = array[i];
	}
	for (int j = middle+1; j < size2; ++j)
	{
		second[j] = array[j] ;
	}

int iL = 0;
int iR = 0;
int iM = left;

while(iL < size1 && size2 > iR )
{
	if (compare(first[iL],second[iR]))  
	{
		array[iM] = first[iL];
		iL++;
	}
	 else
	{
		array[iM] = second[iR];
		iR++;
	}

iM++;
}
while(iL < size1)
{
	array[iM] = first[iL];
	iL++;
	iM++;
}
while(size2 > iR)
{
	array[iM] = second[iR];
	iR++;
	iM++;
}

}
bool compare(data A, data B)
{

}