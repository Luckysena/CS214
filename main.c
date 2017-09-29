#include "testSorterV1.c"

int main(int argc, char const *argv[])
{
	FILE *fp;
	FILE *wf;

	fp=fopen("movie_metadata.csv","r");
	wf=fopen("movie_new_metadata.csv","ab+");
	int init=0;
	data* ori = (data*) malloc(sizeof(data)*4);
	char buffer[4000];
	char *token;

	int filled[28] =  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27} ;

	while(init<4)
	{
		fgets(buffer,4000,(FILE*) fp);	
		if(init != 0)
		{
			token = strtok(buffer, ",");
				token = strtok(NULL,",");
			ori[init].color.data = token;
				token = strtok(NULL,",");
			ori[init].dirName.data = token;
				token = strtok(NULL,",");
			ori[init].critCount = atoi(token);
				token = strtok(NULL,",");
			ori[init].durMin = atoi(token);
				token = strtok(NULL,",");
			ori[init].dirFB = atoi(token);
				token = strtok(NULL,",");
			ori[init].act3FB = atoi(token);
				token = strtok(NULL,",");
			ori[init].act2Name.data = token;
				token = strtok(NULL,",");
			ori[init].act1FB = atoi(token);
				token = strtok(NULL,",");
			ori[init].gross = (float)atoi(token);
				token = strtok(NULL,",");
			ori[init].genre.data = token;
				token = strtok(NULL,",");
			ori[init].act1Name.data = token;
				token = strtok(NULL,",");
			ori[init].title.data = token;
				token = strtok(NULL,",");
			ori[init].numVoted = atoi(token);
				token = strtok(NULL,",");
			ori[init].totalFB = atoi(token);
				token = strtok(NULL,",");
			ori[init].act3Name.data = token;
				token = strtok(NULL,",");
			ori[init].faceNum = atoi(token);
				token = strtok(NULL,",");
			ori[init].keyWord.data = token;
				token = strtok(NULL,",");
			ori[init].link.data = token;
				token = strtok(NULL,",");
			ori[init].numReview = atoi(token);
				token = strtok(NULL,",");
			ori[init].lang.data = token;
				token = strtok(NULL,",");
			ori[init].country.data = token;
				token = strtok(NULL,",");
			ori[init].rated.data = token;
				token = strtok(NULL,",");
			ori[init].budget = (float)atoi(token);
				token = strtok(NULL,",");
			ori[init].year = atoi(token);
				token = strtok(NULL,",");
			ori[init].act2FB = atoi(token);
				token = strtok(NULL,",");
			ori[init].score = atoi(token);
				token = strtok(NULL,",");
			ori[init].ratio = atoi(token);
				token = strtok(NULL,",");
			ori[init].comp_ptr = filled;
			ori[init].size = 27 ;
		}
		else
		{
			fputs(buffer,wf);
		}
		init++;
	}
	fclose(fp);
	fclose(wf);
}
// int is default any number not 2,3,4
// float is 2
// String is 3
// Datetime is 4
//C:\\MinGw\bin\main.exe
