#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "testSorterV1.h"
//enum _boolean {false, true};

bool compareString(String A,String B)
{
	int size1 = A.size;
	int size2 =	B.size;
	int counter=0;
	bool final=true;
	while(counter<size1 && counter<size2)
	{
		if((int)A.data[counter]==(int)B.data[counter])
		{
			counter++;
		}
		else if((int)A.data[counter]>(int)B.data[counter])
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
bool compare(data leftArr, data rightArr, int comp_ptr)
{

	switch(comp_ptr)
	{
		case 0:
			return compareString(leftArr.color,rightArr.color);
		break;
		case 1:
			return compareString(leftArr.dirName,rightArr.dirName);	
		break;
		case 2:
			return leftArr.critCount < rightArr.critCount;	
		break;
		case 3:
			return leftArr.durMin < rightArr.durMin;
		break;
		case 4:
			return leftArr.dirFB < rightArr.dirFB;
		break;
		case 5:
			return leftArr.act3FB < rightArr.act3FB;
		break;
		case 6:
			return compareString(leftArr.act2Name,rightArr.act2Name);
		break;
		case 7:
			return leftArr.act1FB < rightArr.act1FB;
		break;
		case 8:
			return leftArr.gross < rightArr.gross;
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
			return leftArr.numVoted < rightArr.numVoted;
		break;
		case 13:
			return leftArr.totalFB < rightArr.totalFB;
		break;
		case 14:
			return compareString(leftArr.act3Name,rightArr.act3Name);
		break;
		case 15:
			return leftArr.faceNum < rightArr.faceNum;
		break;
		case 16:
			return compareString(leftArr.keyWord,rightArr.keyWord);
		break;
		case 17:
			return compareString(leftArr.link,rightArr.link);
		break;
		case 18:
			return leftArr.numReview < rightArr.numReview;
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
			return leftArr.budget < rightArr.budget;
		break;
		case 23:
			return leftArr.year < rightArr.year;
		break;
		case 24:
			return leftArr.act2FB < rightArr.act2FB;
		break;
		case 25:
			return leftArr.score < rightArr.score;
		break;
		case 26:
			return leftArr.ratio < rightArr.ratio;
		break;
		case 27:
			return leftArr.movieFB < rightArr.movieFB; 
		break;
		default:
		return leftArr.critCount < rightArr.critCount;
		break;

	}

}
void mergeData(const void *A,int left , int middle , int right, int comp_ptr) // Merges the two arrays together returns a combined array
{
	int size1,size2;
	size1 = middle-left+1;
	data * array = (data*) A;
	size2 = right-middle;


	data *first = (data*) malloc(sizeof(data)*size1);
	data *second = (data*) malloc(sizeof(data)*size2);

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

}

void split(const void* array, int left, int right,int comp_ptr)
{

	if (left < right)
	{
		int middle=left+(right-left)/2;
		split(array,left,middle,comp_ptr);
		split(array,middle+1,right,comp_ptr);
		mergeData(array,left,middle,right,comp_ptr);
	}

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
		printf("%s\n",ori[i].genre);
		printf("%s\n",ori[i].act1Name);
		printf("%s\nr",ori[i].title);
		printf("%d\n",ori[i].numVoted);
		printf("%d\n",ori[i].totalFB);
		printf("%s\n",ori[i].act3Name);
		printf("%d\n",ori[i].faceNum);
		printf("%s\n",ori[i].keyWord);
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