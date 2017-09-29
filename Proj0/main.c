#include "testSorterV1.c"

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
}
// int is default any number not 2,3,4
// float is 2
// String is 3
// Datetime is 4
//C:\\MinGw\bin\main.exe
