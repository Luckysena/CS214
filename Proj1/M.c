#include "Sorter.c"
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
char *strtok_new(char * string, char const * delimiter);
char * _sortingCol;

int main(int argc, char const *argv[])
{

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
    _dirOut = _dirIn;
  }
  printf("input parameters are currently: colName: %s, dirInFlag: %s, dirOutFlag: %s\n",_sortingCol,_dirIn,_dirOut);

  DIR* dirIn = opendir(_dirIn);
  //DIR* dirOut = opendir(_dirOut);
  struct dirent* direntIn;
  //struct dirent* direntOut;

  // PID crap
  pid_t initialPID = getpid();
  pid_t childProcesses[256]; // might need to make larger, will see with testing.
  int totalProcesses = 1;
  printf("original pid: %d\n",initialPID);

  //calling this should recursively iterate through the entire filesystem
  processDir(dirIn, direntIn, _dirOut);
}

void processDir(DIR* dirName, struct dirent* direntName, char* dirOut){
  // will accept the current directory and run fileSorter() on any .csv found


  pid_t PID = getpid();    //debugging purposes, get current process PID

  while((direntName = readdir(dirName)) != NULL){    //for every entry in the directory

    //printf("[%d]Working with file: %s\n", PID,direntName->d_name);
    //process sub-directories recursively
    if(isFile(direntName->d_name) == 0) {
      if((strcmp(direntName->d_name,"..") != 0) && (strcmp(direntName->d_name,".") != 0)){  // and not current or prev dir
        printf("[%i]%s is not a regular file, forking...\n",getpid(),direntName->d_name);
        fork();   //fork a process to take care of it

        if(PID != getpid()){  //only child process will get this shit
          processDir(opendir(direntName->d_name),readdir(opendir(direntName->d_name)),dirOut);
          wait();  //prevent orphans
          break;
        }
        continue;  //to skip the current pointer value

      }
      else{
        continue;  //to skip . and ..
      }
    }

    if(isCSV(direntName->d_name)==0) {   //check for CSV files
      printf("[%i]%s is not a regular file, forking...\n",getpid(),direntName->d_name);
      fork();
      if(PID != getpid()){
        fileSorter(_sortingCol,direntName->d_name,dirOut);
        wait();   //placement of wait() is critical here to prevent orphans but also not double sort
        break;
      }
    }
  }
}

int isCSV(const char* str){
  if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv")){
    return 0;
  }
  else{
    return -1;
  }
}


int isFile(const char* name)
{
    DIR* directory = opendir(name);

    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}

void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}

void fileSorter(char* sortingCol, char* file, char* dirout){
  // This was our original main, should modify it to read from given file and output a file
  // need to implement a check for format!!!!!!!!!!!!!!!!!!!!!!

  printf("[%i]Sorting file: %s, with column: %s\n",getpid(),file,sortingCol);
  //need to check if it fits our format
  FILE* _file = fopen(file, "r");
  if((_file == NULL) || (ftell(_file)==-1)){
    printf("[%i]Error sorting file: %s, exiting...\n",getpid(),file);
    return;
  }
  char * col_names[28];  //array which contains name of columns
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

       // printf("%s\n",p);
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

              p = strtok_new(NULL, delimiter);


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
  printf("[%i]Creating file: %s\n",getpid(),outputName);
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
  for (i = 0; i <init-1 ; i++)
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

char *strtok_new(char * string, char const* delimiter)
{
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
void toString(data *total)
{
int i;
for (i = 0; i <28 ; i++)
  {
    printf("%s\n",total [i].color);
    printf("%s\n",total [i].dirName);
    printf("%s\n",total [i].critCount);
    printf("%s\n",total [i].durMin);
    printf("%s\n",total [i].dirFB);
    printf("%s\n",total [i].act3FB);
    printf("%s\n",total [i].act2Name);
    printf("%s\n",total [i].act1FB);
    printf("%s\n",total [i].gross);
    printf("%s\n",total [i].genre);
    printf("%s\n",total [i].act1Name);
    printf("%s\n",total [i].title);
    printf("%s\n",total [i].numVoted);
    printf("%s\n",total [i].totalFB);
    printf("%s\n",total [i].act3Name);
    printf("%s\n",total [i].faceNum);
    printf("%s\n",total [i].keyWord);
    printf("%s\n",total [i].link);
    printf("%s\n",total [i].numReview);
    printf("%s\n",total [i].lang);
    printf("%s\n",total [i].country);
    printf("%s\n",total [i].rated);
    printf("%s\n",total [i].budget);
    printf("%s\n",total [i].year);
    printf("%s\n",total [i].act2FB);
    printf("%s\n",total [i].score);
    printf("%s\n",total [i].ratio);
    printf("%s\n",total [i].movieFB);
  }
return;
}
