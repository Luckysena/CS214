#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "multiproc.h"
#include <sys/mman.h>

char * _sortingCol;
enum _boolean {false, true};
char origin[1024];
char origin2[1024];
    
int main(int argc, char **argv){ 
    int *countp = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
    *countp = 1;
    getcwd(origin,sizeof(origin));
    getcwd(origin2,sizeof(origin2));
//Following code will check for command line args and take them if given or set defaults
    int i, result;
    char colFlag[10], dirInFlag[10], dirOutFlag[10];   //command line flags
    char * _dirIn = NULL;
    char * _dirOut = NULL; //pointers to names of args
    strcpy(colFlag,"-c");
    strcpy(dirInFlag,"-d");
    strcpy(dirOutFlag,"-o");

    for(i = 0; i < argc; i++){
        result = strcmp(colFlag,argv[i]);    //compare arg to column name flag
        if(result == 0){                     //if equal, next arg must be the col name for sorting
            _sortingCol = argv[i+1];
        }

        result = strcmp(dirInFlag,argv[i]);
        if(result == 0){
          _dirIn = argv[i+1];
        }

        result = strcmp(dirOutFlag, argv[i]);
        if(result == 0){
            _dirOut = argv[i+1];
        } 
    }
    if(_sortingCol == NULL){             //default behavior will be sort by crits
        _sortingCol = (char*)malloc(25*sizeof(char));
        strcpy(_sortingCol,"num_critic_for_reviews");
    }

    if(_dirIn == NULL){                     //default behavior is current directory
        _dirIn = (char*)malloc(sizeof(char));
        strcpy(_dirIn,".");
    }
    if(_dirOut == NULL){                    //default is directory it was found in (dirIn)
        _dirOut = origin2;
    }
    char temp[1024];
    if(strcmp(_dirIn,".") != 0){
        temp[0] = '\0';
        strcat(temp,origin);
        strcat(temp,"/");
        strcat(temp,_dirIn);
        _dirIn = temp;
    }
    char temp2[1024];
    if(strcmp(_dirOut,origin2) != 0){
        temp2[0] = '\0';
        strcat(temp2,origin2);
        strcat(temp2,"/");
        strcat(temp2,_dirOut);
        _dirOut = temp2;
    }
    DIR* dirIn = opendir(_dirIn);
    int pid = getpid();
    printf("Initial PID: %d\n", pid);
    processDir(opendir(_dirIn),_dirIn,_dirOut,_sortingCol,countp);
    if(pid == getpid()){
	printf("Total Number Of Processes: %d\n",*countp);
    }else{exit(0);}

    return 0;
}
char *append(char *str, char ch){
    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1 ); 
    strcpy(str2, str);
    str2[len] = ch;
    str2[len + 1] = '\0';
    return str2;
}
int checkIfCSV(char *filename){
    char *temp = filename;
    int length = strlen(temp);

    if(temp[0] == '.' || temp[1] == '.'){return 0;}

    int i;
    char c = temp[0];
    int check = 0;
    for(i = 1; i < length; i++){
        if(temp[i] == '.'){
	    check = 1;
	    break;
        }
    }
    char *csv = (char *)malloc((length-i)*sizeof(char));   
    csv = "";
    if(check == 0){
        return 2; // 2 means another directory
    }else{
	int j;
        for(j = i; j < length; j++){csv = append(csv,temp[j]);}
    }
    if(strcmp(csv,".csv") == 0){return 1;} // 1 means CSV file
    return 0; // 0 means not a CSV file nor a directory
}
void processDir(DIR* dirName, char* _dirName ,char* dirOut, char* _sortingCol, int *counter){
  // will accept the current directory and run fileSorter() on any .csv found
  chdir(_dirName);
  pid_t PID = getpid();    //debugging purposes, get current process PID
  struct dirent* direntName;
  while((direntName = readdir(dirName)) != NULL){    //for every entry in the directory
    //process sub-directories recursively
    //printf("ENTRY: |%s|\n",direntName->d_name);
    if(isFile(direntName->d_name) == 0) {
      if((strcmp(direntName->d_name,"..") != 0) && (strcmp(direntName->d_name,".") != 0)){  // and not current or prev dir
        if(fork() == 0){  //child process
	  (*counter)++;
          printf("[%i]Process forked for directory: %s\n",getpid(),direntName->d_name);
          processDir(opendir(direntName->d_name),direntName->d_name,dirOut,_sortingCol,counter);
          break;
        }
        wait();  //prevent orphans
        continue;  //to skip the current pointer value
      }else{continue;}  //to skip . and ..
    }

    if((isCSV(direntName->d_name) == 0) && (strstr(direntName->d_name,"sorted") == NULL)) {   //check for CSV files + without "sorted"
      if(fork()==0){
        (*counter)++;
        printf("[%i]Process forked for csv file: %s\n",getpid(),direntName->d_name);
        fileSorter(_sortingCol,direntName->d_name,dirOut);
        break;
      }
      wait();
    }
  }
  return;
}

int isCSV(const char* str){
  if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv")){
    return 0;
  }else{return -1;}
}

int isFile(const char* name){
    DIR* directory = opendir(name);
    if(directory != NULL){
     closedir(directory);
     return 0;
    }
    if(errno == ENOTDIR){return 1;}
    return -1;
}
void fileSorter(char* sortingCol, char* file, char* dirout){
  //printf("[%i]The directory we're in is: %s\n",getpid(),getCurrentDir());
  FILE* _file = fopen(file, "r");
  if((_file == NULL)){
    printf("[%i]Error sorting file |%s|: %s, exiting...\n",getpid(),file, strerror(errno));
    return;
  }
  char * col_names[28];  // array which contains name of columns
  int init = 0;         // counter for rows
  data total[10000];     // array for data structs
  char string[4000];    // stdin string buffer
  while(fgets(string,4000,_file)!= NULL)   // loop to go thru all of input
  {
      int type = 0;             // counter to assign proper struct attributes
      char delimiter[] = ",";   // delim char
      data read;                // placeholder data struct for filling
      char * p = strtok_new(string, delimiter);  // p will iterate through input string
      if(init != 0)             // first stdin is column names string
      {
      while(type<28)            // fill in struct attributes
      {
        switch(type)
        {
          case 0:
          {
            read.color = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.color,p);
                 else
               strcpy(read.color,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 1:
          {
             read.dirName = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.dirName,p);
                 else
              strcpy(read.dirName,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 2:
          {
             read.critCount= (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.critCount,p);
                 else
              strcpy(read.critCount,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 3:
          {
             read.durMin = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.durMin,p);
                 else
              strcpy(read.durMin,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 4:
          {
            read.dirFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.dirFB,p);
                 else
              strcpy(read.dirFB,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 5:
          {
              read.act3FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act3FB,p);
                 else
              strcpy(read.act3FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 6:
          {
             read.act2Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act2Name,p);
                 else
              strcpy(read.act2Name,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 7:
          {
               read.act1FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act1FB,p);
                 else
              strcpy(read.act1FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 8:
          {
               read.gross = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.gross,p);
                 else
              strcpy(read.gross,"0");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 9:
          {
               read.genre = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.genre,p);
                 else
              strcpy(read.genre,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 10:
          {
              read.act1Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act1Name,p);
                 else
              strcpy(read.act1Name,"");

              p = strtok_new(NULL, "exception");


          }
          break;
          case 11:
          { read.title= (char*) malloc(sizeof(char)*400);

             if(*p)
              strcpy(read.title,p);
                 else
              strcpy(read.title,"");

              p = strtok_new(NULL, delimiter);


          }
          break;
          case 12:
          {
              read.numVoted = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.numVoted,p);
                 else
              strcpy(read.numVoted,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 13:
          {
              read.totalFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.totalFB,p);
                 else
              strcpy(read.totalFB,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 14:
          {
              read.act3Name = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act3Name,p);
                 else
              strcpy(read.act3Name,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 15:
          {
            read.faceNum = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.faceNum,p);
                 else
              strcpy(read.faceNum,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 16:
          {
            read.keyWord = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.keyWord,p);
                 else
              strcpy(read.keyWord,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 17:
          {
             read.link = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.link,p);
                 else
              strcpy(read.link,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 18:
          {
             read.numReview = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.numReview,p);
                 else
              strcpy(read.numReview,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 19:
          {
            read.lang = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.lang,p);
                 else
              strcpy(read.lang,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 20:
          {
             read.country = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.country,p);
                 else
              strcpy(read.country,"");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 21:
          {
              read.rated = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.rated,p);
                 else
              strcpy(read.rated,"");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 22:
          {
            read.budget = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.budget,p);
                 else
              strcpy(read.budget,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 23:
          {
            read.year = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.year,p);
                 else
              strcpy(read.year,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 24:
          {
           read.act2FB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.act2FB,p);
                 else
              strcpy(read.act2FB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 25:
          {
            read.score = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.score,p);
                 else
              strcpy(read.score,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          case 26:
          {
            read.ratio = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.ratio,p);
                 else
              strcpy(read.ratio,"0");

              p = strtok_new(NULL, delimiter);

          }
          break;
          case 27:
          {
         read.movieFB = (char*) malloc(sizeof(char)*400);
             if(*p)
              strcpy(read.movieFB,p);
                 else
              strcpy(read.movieFB,"0");

              p = strtok_new(NULL, delimiter);
          }
          break;
          default:
          break;
        }
        type++;
      }

        total[init-1]=read;     // point the item in struct array to placeholder data struct
        }
        else
        {

          int counter = 0;       // counter for filling in name of columns row
          while(counter<28){     // loop to create an array of column names
            col_names[counter] = (char *) malloc(sizeof(char)*250);   // make space for the name
            memset(col_names[counter],'\0',sizeof(col_names[counter]));
            if(*p){              // if the pointer isnt empty, copy the string into array
              strcpy(col_names[counter],p);
            }
            else{
              strcpy(col_names[counter],"");
            }
            p = strtok_new(NULL,delimiter);
            counter++;
          }
          for(counter = 0; counter<28; counter++){
            if((strcmp(col_names[counter],"")==0)){
              printf("[%i]CSV format incorrect, terminating..\n",getpid());
              return;
            }
          }
        }
      init++;  //increment the row we're on
    }

  fclose(_file);
  // now we need to read the arg column name and set comp_ptr to it
  int comp_ptr = 0;
  for(comp_ptr; comp_ptr < 28; comp_ptr++){
    if(strcmp(col_names[comp_ptr], sortingCol)==0){
      break;  //break out of the loop once we reach the col name we need
    }
  }
  chdir(dirout);
  //file output creation
  char* outputName = (char*)malloc(sizeof(char)*1000);  //file output name
  memset(outputName,'\0',sizeof(outputName));
  strip_ext(file);
  strcat(outputName, file);
  strcat(outputName,"-sorted-");
  strcat(outputName,sortingCol);
  strcat(outputName,".csv");


  FILE* foutput;
  foutput = fopen(outputName,"w+");
  //printf("[%i]Creating file: %s\n",getpid(),outputName);
  int i;
  char * firstRow = (char *)malloc(sizeof(char)*1000);
  memset(firstRow,'\0',sizeof(firstRow));
  for(i = 0; i<28; i++){
    strcat(firstRow, col_names[i]);
    if(i != 27){
      strcat(firstRow, ",");
    }
    free(col_names[i]);      //free the memory used for col name array
  }

  fprintf(foutput, "%s\n", firstRow);
  free(firstRow);

  if(comp_ptr == 28){   // this is the case where input doesn't match the col names list
    comp_ptr = 2; //defaults to num_critic_for_reviews
  }
  split(total,0,init-2,comp_ptr);  // sort the data
  char * bufferIn = (char*) malloc(sizeof(char)*9000);  // create buffer for output
  for (i = 0; i < init-1 ; i++)
  {
    // copy the sorted information in row by row with commas
    memset(bufferIn,'\0',sizeof(bufferIn));
    strcat(bufferIn,total [i].color);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].dirName);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].critCount);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].durMin);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].dirFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act3FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act2Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act1FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].gross);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].genre);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act1Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].title);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].numVoted);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].totalFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act3Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].faceNum);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].keyWord);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].link);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].numReview);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].lang);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].country);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].rated);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].budget);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].year);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].act2FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].score);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].ratio);
    strcat(bufferIn,",");
    strcat(bufferIn,total [i].movieFB);
    fprintf(foutput, "%s\n",bufferIn); //output
  }
  fclose(foutput);
  return;
}
void strip_ext(char *fname){
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}
char *strtok_new(char * string, char const* delimiter){
   char * delim = (char*)malloc(sizeof(char)*25);
   memset(delim,'\0',sizeof(delim));
   strcpy(delim,"exception");

   static char *source = NULL;
   char *p, *riturn = 0;
   if(string != NULL)
   {
    source = string;
    }
   if(source == NULL)
    {
    return NULL;
   }
   if(strcmp(delimiter,delim)==0){

     if((p = strpbrk(source, "\"")) != NULL){
       if((p = strpbrk(source+1, "\"")) != NULL){
         p++;
         *p = 0;
         riturn = source;
         source = ++p;
         return riturn;
       }
     }

   }
   if((p = strpbrk (source, ",")) != NULL || (p = strpbrk (source, "\n")) != NULL)
    {
      *p  = 0;
      riturn = source;
      source = ++p;
    }
    if(riturn == NULL){
      riturn = source;
    }
return riturn;
}
bool compare(data leftArr, data rightArr, int comp_ptr){
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
void split(data *array, int left, int right,int comp_ptr){
	if (left < right)
	{
		int middle=left+(right-left)/2;
		split(array,left,middle,comp_ptr);
		split(array,middle+1,right,comp_ptr);
		mergeData(array,left,middle,right,comp_ptr);
	}
return;
}
char *getCurrentDir(void){
    char *currWorkDir, *token;
    char buffer[PATH_MAX + 1];
    char *directory;
    size_t length;

    currWorkDir = getcwd(buffer, PATH_MAX + 1 );
    token = strrchr(currWorkDir, '/');

    if( currWorkDir == NULL ){
        printf("Error"); /* You decide here */
        exit(1);
    }

    if (token == NULL) {
        printf("Error"); /* You decide here */
        exit(1);
    }

    length = strlen(token);
    directory = (char*)malloc(length);
    memcpy(directory, token+1, length);

    return directory;
}
