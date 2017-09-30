#include "testSorterV1.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{

	// 1) make array of data structs

	struct _data DataArray[5000];
	int DataArraySize = sizeof(DataArray)/sizeof(DataArray[0]);

	// 2) read each newline into a new data struct
	String s;
	fscanf(stdin, "%s", s.data);  //initial row removal
	int i;
	for(i = 0; i < DataArraySize; i++){    //iterate through all the newlines
	DataArray[i].critCount = malloc((sizeof(DataArray[0].critCount)));   // needs work: need to malloc for all the struct variables
	fscanf(stdin, "%s%*c %s%*c %d%*c %d%*c %d%*c %d%*c %s%*c %d%*c %f%*c %s%*c %s%*c %s%*c %s%*c %d%*c %d%*c %s%*c %d%*c %s%*c %s%*c %d%*c %s%*c %s%*c %s%*c %f%*c %d%*c %d%*c %f%*c %f%*c %d", DataArray[i].color, DataArray[i].dirName,
  // this will read the data in a formatted way to the struct itself. the %*c means it will tokenize with commas and ignore comma itself
	DataArray[i].critCount, DataArray[i].durMin, DataArray[i].dirFB, DataArray[i].act3FB,
	DataArray[i].act2Name, DataArray[i].act1FB, DataArray[i].gross, DataArray[i].genre,
	DataArray[i].act1Name, DataArray[i].title, DataArray[i].numVoted, DataArray[i].totalFB,
	DataArray[i].act3Name, DataArray[i].faceNum, DataArray[i].keyWord, DataArray[i].link,
	DataArray[i].numReview, DataArray[i].lang, DataArray[i].country, DataArray[i].rated,
	DataArray[i].budget, DataArray[i].year, DataArray[i].act2FB, DataArray[i].score,
	DataArray[i].ratio, DataArray[i].movieFB);

	// ISSUES: 1) need to figure out efficient malloc method for each struct attribute.
	//         2) not 100% sure how to move onto next row with stdin

}
	// 3) read input arg, and find it using comp ptr
	// 4) sort somehow..


	void (*Merge_ptr)(const void*,int,int,int) = &mergeData;



	return 0;

}
// int is default any number not 2,3,4
// float is 2
// String is 3
// Datetime is 4
//C:\\MinGw\bin\main.exe
