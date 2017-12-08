#include "Sorter.c"

// first arg is name of new dir
char* createChar(int charCount);

void createCSV(char * dirName, char** toCopy){
  //printf("creating csv\n");
  char * filename = malloc(strlen(dirName)+9);
  strcpy(filename,dirName);
  strcat(filename,"/");
  strcat(filename,createChar(4));
  strcat(filename,".csv");
  FILE *fp1;
  fp1 = fopen(filename,"w+");
  int i;


  //char string[10000];
  for(i = 0; i < 4000; i++){
    fprintf(fp1,"%s\n",toCopy[i]);
    //printf("%i\n",i);
  }
  fclose(fp1);
}


char* createChar(int charCount)
{       int i;
	if(charCount==0)
		return NULL;

	char* c = (char *) malloc(sizeof(char)*charCount);
	for( i = 0;i<charCount-1;i++)
	{
		c[i] = (char) (rand()%(122-97))+97;
	}
	c[charCount-1] = '\0';
 return c;
}

char * createDir(char* dirName, int avgNumofDir,char** toCopy)
{

if(strlen(dirName)<=26)
   {   int i;

	DIR *dir;
  struct dirent *dent;
  char* Newdir = dirName;
	dir = opendir(dirName);
	for ( i = 0; i <avgNumofDir ; ++i)
	{

	int changeDir =  (int) rand()%30 + 1;

	//if(changeDir % 2 == 0)
	//{
		//int avgNumofRows = (int) rand() %5444 +1;

		//createCSV(dirName,toCopy);
	//}

	if (changeDir == 1)
	{

		 Newdir = malloc(strlen(dirName)+2);
		if (Newdir != NULL)
			{
			close(dir);
			strcpy(Newdir,dirName);
			strcat(Newdir,"/");
			strcat(Newdir,createChar(4));
 			int succ = mkdir(Newdir, 0700);
 			if(succ != -1)
 				{
 					dir = opendir(Newdir);
 			}
 		}
 		else
 		{
 			exit(01);
 		}
	}
	if (changeDir == 15)
	{
		char * Newdir = malloc(strlen(dirName)+2);
		if (Newdir != NULL)
			{
			close(dir);
			strcpy(Newdir,dirName);
			strcat(Newdir,"/");
			strcat(Newdir,createChar(4));
 			return Newdir;
 		}

	}

	}
close(dir);
return Newdir;
}
}
  //first input is root dir
  //second input is average number of directorys
  //third is file to be copied
int main(int argc, char const* argv[]){
  int i;
  /*char string[1000];
  char* data[6000];
  FILE* fp;
  fp = fopen(argv[3],"r+");
  i = 0;
  while(fgets(string,10000,fp)!= NULL){
    data[i] = malloc(sizeof(string));
    strcpy(data[i],string);
    i++;
  }*/

char** data = NULL;


  struct stat st;
  	char* newDir = argv[1];
  if(stat(newDir,&st) != 0)
  {
  	int succ = mkdir(newDir, 0700);
  	if(succ == -1)
  		exit(01);
  }




  for ( i = 0; i < atoi(argv[2])/10; ++i)
  	{
  		char* nextDir = createDir(newDir,atoi(argv[2]),data);
  		if(nextDir != NULL)
  			{

  			newDir = malloc(strlen(nextDir));
  			strcpy(newDir,nextDir);
  			int succ = mkdir(newDir, 0700);
  		}
  		else
  			{

  				exit(01);
        }

      }
    }
