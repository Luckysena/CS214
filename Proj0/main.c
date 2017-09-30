#include "testSorterV1.c"
<<<<<<< HEAD
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

=======

int main(int argc, char const *argv[])
{
	FILE *fp;
	FILE *wf;

	fp=fopen("movie_metadata.csv","r");
	wf=fopen("movie_new_metadata.csv","ab+");
	int init=0;
	data* ori = (data*) malloc(sizeof(data)*4);
	
	char *token;
	int filled[28] =  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27} ;

	while(init<4)
	{
		char buffer[4000];
		char *token;
		fgets(buffer,4000,(FILE*) fp);	
		if(init != 0)
		{
			token = strtok(buffer, ",");
				token = strtok(NULL,",");
			ori[init-1].color.data = token;
				token = strtok(NULL,",");
			ori[init-1].dirName.data = token;
				token = strtok(NULL,",");
			ori[init-1].critCount = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].durMin = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].act3FB = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].dirFB = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].act2Name.data = token;
				token = strtok(NULL,",");
			ori[init-1].act1FB = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].gross = (float)atoi(token);
				token = strtok(NULL,",");
			ori[init-1].genre.data = token;
				token = strtok(NULL,",");
			ori[init-1].act1Name.data = token;
				token = strtok(NULL,",");
			ori[init-1].title.data = token;
				token = strtok(NULL,",");
			ori[init-1].numVoted = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].totalFB = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].act3Name.data = token;
				token = strtok(NULL,",");
			ori[init-1].faceNum = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].keyWord.data = token;
				token = strtok(NULL,",");
			ori[init-1].link.data = token;
				token = strtok(NULL,",");
			ori[init-1].numReview = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].lang.data = token;
				token = strtok(NULL,",");
			ori[init-1].country.data = token;
				token = strtok(NULL,",");
			ori[init-1].rated.data = token;
				token = strtok(NULL,",");
			ori[init-1].budget = (float)atoi(token);
				token = strtok(NULL,",");
			ori[init-1].year = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].act2FB = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].score = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].ratio = atoi(token);
				token = strtok(NULL,",");
			ori[init-1].comp_ptr = filled;
			ori[init-1].size = 27 ;
			printf("%d\n",ori[init-1].dirFB);
		}
		else
		{
			fputs(buffer,wf);
		}
			
		init++;
	}
	//toString(ori);
	fclose(fp);
	fclose(wf);
>>>>>>> 1b013e66ef69b6557a08631b1436e716dbc79cfc
}
// int is default any number not 2,3,4
// float is 2
// String is 3
// Datetime is 4
//C:\\MinGw\bin\main.exe
