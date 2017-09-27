#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "Sorter.h"

bool compareInt(int A,int B)
{
	return A<B;
}
bool compareFloat(float A,float B)
{
	return A<B;
}
bool compareDateTime(time_t A,time_t B)
{
		return A<B;
}
bool compareString(char* A,char* B)
{
	int size1 = sizeof(A);
	int size2 =	sizeof(B);
	int counter=0;
	bool final=true;
	while(counter<size1 && counter<size2)
	{
		if((int)A[counter]==(int)B[counter])
		{
			counter++;
		}
		else if((int)A[counter]>(int)B[counter])
		{
			return false;
		}
		else
		{
		return true;
		}
	}
	return true;

}

void resize(data * ori) // resizes array if the original aribitrary size is too small
{

data * create=NULL;
create=(data*)realloc(ori,2*sizeof(ori));
while(create == ori);

ori=create;

}

void splitInt(const void* A, int left, int right)
{
	if (left < right)
	{
		int* array=(int*) A;
		int middle=left+(right-left)/2;
		splitInt(array,left,middle);
		splitInt(array,middle+1,right);
		mergeInt(array,left,middle,right);
	}

}
void mergeInt(const void * A,int left , int middle , int right) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	int * array=(int*) A;
	size1 = middle-left+1;
	size2 = right-middle;


	int *first = (int*) malloc(sizeof(int)*size1);
	int *second = (int*) malloc(sizeof(int)*size2);

	for (int i = 0; i < size1; ++i)
	{
		first[i] = array[left+i];
	}
	for (int j = 0; j < size2; ++j)
	{
		second[j] = array[middle+1+j];
	}

int iL = 0;
int iR = 0;
int iM = left;
while(iL < size1 && iR < size2)
{
	
	if(compareInt(first[iL],second[iR]))  
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
while(iR < size2)
{
	array[iM] = second[iR];
	iR++;
	iM++;
}

}
void splitString(const void* A, int left, int right)
{
	if (left < right)
	{
		String* array=(String*) A;
		int middle=left+(right-left)/2;
		splitString(array,left,middle);
		splitString(array,middle+1,right);
		mergeString(array,left,middle,right);
	}

}
void mergeString(const void * A,int left , int middle , int right) // Merges the two arrays together returns a combined array
{

	int size1,size2;
	
	String * array=(String*) A;
	size1 = middle-left+1;
	size2 = right-middle;

	String *first = (String*) malloc(sizeof(int)*size1);
	String *second = (String*) malloc(sizeof(int)*size2);

	for (int i = 0; i < size1; ++i)
	{
		first[i].data = array[left+i].data;
	}
	for (int j = 0; j < size2; ++j)
	{
		second[j].data = array[middle+1+j].data;
	}
int iL = 0;
int iR = 0;
int iM = left;
while(iL < size1 && iR < size2)
{
	if(compareString(first[iL].data,second[iR].data))  
	{
		array[iM].data = first[iL].data;
		iL++;
	}
	 else
	{
		array[iM].data = second[iR].data;
		iR++;
	}

iM++;
}
while(iL < size1)
{
	array[iM].data = first[iL].data;
	iL++;
	iM++;
}
while(iR < size2)
{
	array[iM].data = second[iR].data;
	iR++;
	iM++;
}

}
void splitFloat(const void* A, int left, int right)
{
	if (left < right)
	{
		float* array=(float*) A;
		int middle=left+(right-left)/2;
		splitInt(array,left,middle);
		splitInt(array,middle+1,right);
		mergeInt(array,left,middle,right);
	}

}
void mergeFloat(const void * A,int left , int middle , int right) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	float * array=(float*) A;
	size1 = middle-left+1;
	size2 = right-middle;


	float *first = (float*) malloc(sizeof(int)*size1);
	float *second = (float*) malloc(sizeof(int)*size2);

	for (int i = 0; i < size1; ++i)
	{
		first[i] = array[left+i];
	}
	for (int j = 0; j < size2; ++j)
	{
		second[j] = array[middle+1+j];
	}

int iL = 0;
int iR = 0;
int iM = left;
while(iL < size1 && iR < size2)
{
	
	if(compareFloat(first[iL],second[iR]))  
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
while(iR < size2)
{
	array[iM] = second[iR];
	iR++;
	iM++;
}

}
void splitDateTime(const void* A, int left, int right)
{
	if (left<right)
	{
		time_t * array=(time_t*) A;
		int middle=floor((left+1)/2);
		splitDateTime(array,left,middle);
		splitDateTime(array,middle+1,right);
		mergeDateTime(array,left,middle,right);
	}

}
void mergeDateTime(const void * A,int left , int middle , int right) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	time_t * array=(time_t*) A;
	size1 = middle-left+1;
	size2 = right-middle;

	time_t *first = (time_t*) malloc(sizeof(int)*size1);
	time_t *second = (time_t*) malloc(sizeof(int)*size2);

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
	
	if(compareDateTime(first[iL],second[iR]))  
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

/*
{
	void (*compare_ptr)(const void*,int,int);
	switch(ptr)
	{
		case  1 :
		{
	void (*compare_ptr)(const void*,int,int) = &splitInt;
		}
	break;
		case 2 :
		{
	void (*compare_ptr)(const void*,int,int) = &splitFloat;
		}	
	break;
		case 3:
		{
	void (*compare_ptr)(const void*,int,int) = &splitString;
	break;
		}
		case 4:
		{
	void (*compare_ptr)(const void*,int,int)= &splitDateTime;
		}
	break;
		default:
		{
	void (*compare_ptr)(const void*,int,int) = &splitInt;
		}
	break;

}
return compare_ptr;
}*/