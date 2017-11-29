#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "Sorter.h"
enum _boolean {false, true};

bool compare(data leftArr, data rightArr, int comp_ptr)
{
	char c1 = leftArr.title[0];
	char c2 = rightArr.title[0];
	char * tmp1 = leftArr.title;
	char * tmp2 = rightArr.title;

	switch(comp_ptr)
	{
		case 0:
			return strcmp(leftArr.color,rightArr.color) < 0;
		break;
		case 1:
		{
			return strcmp(leftArr.dirName,rightArr.dirName)< 0;
		}
		break;
		case 2:
			return strcmp(leftArr.critCount,rightArr.critCount)< 0;
		break;
		case 3:
			return atoi(leftArr.durMin) <= atoi(rightArr.durMin);
		break;
		case 4:
			return strcmp(leftArr.dirFB,rightArr.dirFB) < 0;
		break;
		case 5:
			return atoi(leftArr.act3FB) <= atoi(rightArr.act3FB);
		break;
		case 6:
			return strcmp(leftArr.act2Name,rightArr.act2Name) < 0;
		break;
		case 7:
			return atoi(leftArr.act1FB) <= atoi(rightArr.act1FB);
		break;
		case 8:
			return atoi(leftArr.gross) <= atoi(rightArr.gross);
		break;
		case 9:
			return strcmp(leftArr.genre,rightArr.genre) < 0;
		break;
		case 10:
			return strcmp(leftArr.act1Name,rightArr.act1Name) < 0;
		break;
		case 11:

			if(c1 == '\"'){
				tmp1++;
			}
			if(c2 == '\"'){
				tmp2++;
			}
			return strcmp(tmp1,tmp2) < 0;
		break;
		case 12:
			return atoi(leftArr.numVoted) <= atoi(rightArr.numVoted);
		break;
		case 13:
			return atoi(leftArr.totalFB) <= atoi(rightArr.totalFB);
		break;
		case 14:
			return strcmp(leftArr.act3Name,rightArr.act3Name) < 0;
		break;
		case 15:
			return atoi(leftArr.faceNum) <= atoi(rightArr.faceNum);
		break;
		case 16:
			return strcmp(leftArr.keyWord,rightArr.keyWord) < 0;
		break;
		case 17:
			return strcmp(leftArr.link,rightArr.link) < 0;
		break;
		case 18:
			return atoi(leftArr.numReview) <= atoi(rightArr.numReview);
		break;
		case 19:
			return strcmp(leftArr.lang,rightArr.lang) < 0;
		break;
		case 20:
			return strcmp(leftArr.country,rightArr.country) < 0;
		break;
		case 21:
			return strcmp(leftArr.rated,rightArr.rated) < 0;
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
void mergeData(data *array,int left , int middle , int right, int comp_ptr){
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
return;
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
return;
}

ArrayList * ArrayList_create(int n){
	ArrayList *list = malloc(sizeof(*list));
	if(list == NULL){
		return NULL;
	}
	list->capacity = n;
	list->size = 0;
	list->dataVal = calloc(n,sizeof(data));
	if(list->dataVal == NULL){
		free(list);
		return NULL;
	}
	return list;
}
ArrayList * Arraylist_resize(ArrayList * list, int cap){
	ArrayList * newList = ArrayList_create((2*cap));
	int i;
	for(i = 0; i < cap; i++){
		(newList->dataVal)[i] = (list->dataVal)[i];
	}
	newList->size = cap;
	return newList;
}

ArrayList * ArrayList_add(ArrayList * list, data elem){
	if(elem.color == NULL){
		printf("Adding elem failed\n");
		return NULL;
	}
	list->dataVal[list->size] = elem;
	(list->size)++;
	if((list->capacity)==(list->size)){
		list = Arraylist_resize(list,(list->capacity));
	}
	return list;
}
