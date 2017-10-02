#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "Sorter.h"
enum _boolean {false, true};

bool compareString(char* A,char* B)
{
	int size1 = sizeof(A);
	int size2 =	sizeof(B);
	int counter=0;
	bool final=true;
	if(A == NULL )
	{
		return false;
	}
	if (B == NULL)
	{
		return true;
	}
	while(counter<size1 && counter<size2)
	{
		if((int)A[counter]==(int)B[counter])
		{
			counter++;
		}
		else if((int)A[counter]<(int)B[counter])
		{
			return true;
		}
		else
		{
		return false;
		}
	}
	return true;
}
bool compare(data leftArr, data rightArr, int comp_ptr)
{

	switch(comp_ptr)
	{
		case 0:
			return compareString(leftArr.color,rightArr.color);
		break;
		case 1:
		{
			return compareString(leftArr.dirName,rightArr.dirName);
		}
		break;
		case 2:
			return compareString(leftArr.critCount,rightArr.critCount);
		break;
		case 3:
			return atoi(leftArr.durMin) <= atoi(rightArr.durMin);
		break;
		case 4:
			return compareString(leftArr.dirFB,rightArr.dirFB);
		break;
		case 5:
			return atoi(leftArr.act3FB) <= atoi(rightArr.act3FB);
		break;
		case 6:
			return compareString(leftArr.act2Name,rightArr.act2Name);
		break;
		case 7:
			return atoi(leftArr.act1FB) <= atoi(rightArr.act1FB);
		break;
		case 8:
			return atoi(leftArr.gross) <= atoi(rightArr.gross);
		break;
		case 9:
			return compareString(leftArr.genre,rightArr.genre);
		break;
		case 10:
			return compareString(leftArr.act1Name,rightArr.act1Name);
		break;
		case 11:
			return compareString(leftArr.title,rightArr.title);
		break;
		case 12:
			return atoi(leftArr.numVoted) <= atoi(rightArr.numVoted);
		break;
		case 13:
			return atoi(leftArr.totalFB) <= atoi(rightArr.totalFB);
		break;
		case 14:
			return compareString(leftArr.act3Name,rightArr.act3Name);
		break;
		case 15:
			return atoi(leftArr.faceNum) <= atoi(rightArr.faceNum);
		break;
		case 16:
			return compareString(leftArr.keyWord,rightArr.keyWord);
		break;
		case 17:
			return compareString(leftArr.link,rightArr.link);
		break;
		case 18:
			return atoi(leftArr.numReview) <= atoi(rightArr.numReview);
		break;
		case 19:
			return compareString(leftArr.lang,rightArr.lang);
		break;
		case 20:
			return compareString(leftArr.country,rightArr.country);
		break;
		case 21:
			return compareString(leftArr.rated,rightArr.rated);
		break;
		case 22:
			return atoi(leftArr.budget) <= atoi(rightArr.budget);
		break;
		case 23:
			return atoi(leftArr.year) <= atoi(rightArr.year);
		break;
		case 24:
			return atoi(leftArr.act2FB) <= atoi(rightArr.act2FB);
		break;
		case 25:{
			char * endToken;
			char * endToken2;
			double left = strtol(leftArr.score,&endToken,10);
			double right = strtol(rightArr.score,&endToken,10);
			return left <= right;
		}
		break;
		case 26:{
				char * endToken;
			char * endToken2;
			double left = strtol(leftArr.ratio,&endToken,10);
			double right = strtol(rightArr.ratio,&endToken,10);
			return left <= right;
		}
		break;
		case 27:{
			 int left = atoi(leftArr.movieFB);
			 int right = atoi(rightArr.movieFB);
			return left < right;
		}
		break;
		default:
		return atoi(leftArr.critCount) < atoi(rightArr.critCount);
		break;

	}

}
void mergeData(data *array,int left , int middle , int right, int comp_ptr) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	size1 = middle-left+1;
	size2 = right-middle;

	data *first = (data*) malloc(sizeof(data)*size1);
	data *second = (data*) malloc(sizeof(data)*size2);
	int i;
	for (i = 0; i < size1; ++i)
	{
		first[i] = array[left+i];
	}
	int j;
	for (j = 0; j < size2; ++j)
	{
		second[j] = array[middle+1+j];
	}

int iL = 0;
int iR = 0;
int iM = left;

while(iL < size1 && iR < size2)
{

	if(compare(first[iL],second[iR],comp_ptr))
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
free(first);
free(second);
first = NULL;
second = NULL;

}

void split(data *array, int left, int right,int comp_ptr)
{

	if (left < right)
	{

		int middle=left+(right-left)/2;
		split(array,left,middle,comp_ptr);
		split(array,middle+1,right,comp_ptr);
		mergeData(array,left,middle,right,comp_ptr);
	}

}
