#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "Sorter.h"
enum _boolean {false, true};




bool compareInt(int A,int B)    // ***** Didn't define bool anywhere? -M
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

void resizes(String * ori) // resizes array if the original aribitrary size is too small
{

String * create=NULL;
create=(String*)realloc(ori,2*sizeof(ori));
while(create == ori);

ori=create;

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
void printString(String *S)
{
	int size = sizeof(S)/sizeof(S[0]);
	 for (int i = 0; i < size; ++i)
	 {
	 	printf(",%s ",S[i].data);
	 }
	 printf("\n");
}
void toString(data *ori)
{
	int size = sizeof(ori)/sizeof(ori[0]);
	for (int i = 0; i <size ; ++i)
	{
		printf("%s\n",ori[i].color);
		printf("%s\n",ori[i].dirName);
		printf("%d\n",ori[i].critCount);
		printf("%s\n",ori[i].durMin);
		printf("%d\n",ori[i].dirFB);
		printf("%d\n",ori[i].act3FB);
		printf("%s\n",ori[i].act2Name);
		printf("%d\n",ori[i].act1FB);
		printf("%f\n",ori[i].gross);
		printString(ori[i].genre);
		printf("%s\n",ori[i].act1Name);
		printf("%s\nr",ori[i].title);
		printf("%d\n",ori[i].numVoted);
		printf("%d\n",ori[i].totalFB);
		printf("%s\n",ori[i].act3Name);
		printf("%d\n",ori[i].faceNum);
		printString(ori[i].keyWord);
		printf("%s\n",ori[i].link);
		printf("%d\n",ori[i].numReview);
		printf("%s\n",ori[i].lang);
		printf("%s\n",ori[i].country);
		printf("%s\n",ori[i].rated);
		printf("%f\n",ori[i].budget);
		printf("%d\n",ori[i].year);
		printf("%d\n",ori[i].act2FB);
		printf("%f\n",ori[i].score);
		printf("%f\n",ori[i].ratio);
		printf("%d\n",ori[i].movieFB);
	}

}
void split(const void* array, int left, int right,void (*Merge_ptr)(const void*,int,int,int))
{
printf("on subarray: \n");
int i;
for(i = left; i<=right; i++ ){
	printf("%c", array);
}
printf("\n");
	if (left < right)
	{
		int middle=left+(right-left)/2;
		split(array,left,middle,Merge_ptr);
		split(array,middle+1,right,Merge_ptr);
		Merge_ptr(array,left,middle,right);
	}

}
