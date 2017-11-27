#include "Sorter.c"
char *strtok_new(char * string, char const * delimiter);
void getCurrentDir(void);
char * _sortingCol;
void processDir(void*);
void fileSorter(void* arguments);
Heap * outputHeap;
int main(int argc, char const *argv[])
{

  //Following code will check for command line args and take them if given or set defaults
  int i, result, totalProcesses;
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
  DIR* dirIn = opendir(_dirIn);


  // TID crap
  pthread_t tid;
  processdirInput values;
  values.dirName = dirIn;
  values._dirName = _dirIn;
  values.dirOut = _dirOut;

  outputHeap = Heap_create(10000);


  pthread_create(&tid,0,processDir,(void*)&values);
  pthread_join(tid,NULL);

  printf("Before output file creation, outputHeap size: %i\n",outputHeap->list->size);
  //output file creation
  char* outputName = (char*)malloc(sizeof(char)*1000);  //file output name
  memset(outputName,'\0',sizeof(outputName));
  strcat(outputName, "AllFiles-sorted-");
  strcat(outputName,_sortingCol);
  strcat(outputName,".csv");
  chdir(_dirOut);
  FILE* foutput;
  foutput = fopen(outputName,"w+");
  char * firstRow = (char *)malloc(sizeof(char)*1000);
  memset(firstRow,'\0',sizeof(firstRow));
  strcat(firstRow,"color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross	genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes,");
  fprintf(foutput, "%s\n", firstRow);
  free(firstRow);
  char * bufferIn = (char*) malloc(sizeof(char)*9000);  // create buffer for output
  /*for (i = 0; i <(outputHeap->size) ; i++)
  {
    if(outputHeap->list->nodeList[i].dataVal->color == NULL){
      printf("element %i is null\n",i);
    }
    memset(bufferIn,'\0',sizeof(bufferIn));
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->color);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->dirName);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->critCount);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->durMin);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->dirFB);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act3FB);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act2Name);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act1FB);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->gross);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->genre);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act1Name);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->title);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->numVoted);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->totalFB);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act3Name);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->faceNum);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->keyWord);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->link);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->numReview);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->lang);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->country);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->rated);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->budget);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->year);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->act2FB);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->score);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->ratio);
    strcat(bufferIn,",");
    strcat(bufferIn,outputHeap->list->nodeList[i].dataVal->movieFB);
    fprintf(foutput, "%s\n",bufferIn); //output
  }
  */
  fclose(foutput);

  return 0;
}

void processDir(void* arguments){

  processdirInput *args = arguments;
  DIR* dirName = args -> dirName;
  char* _dirName = args -> _dirName;
  char* dirOut = args -> dirOut;
  printf("[%i]Thread created for directory: %s\n",1,_dirName);
  pthread_t tid;

  struct dirent* direntName;
  while((direntName = readdir(dirName)) != NULL){    //for every entry in the directory
    if(isFile(direntName->d_name) == 0) {
      if((strcmp(direntName->d_name,"..") != 0) && (strcmp(direntName->d_name,".") != 0)){  // and not current or prev dir
          char* directoryName = (char*)malloc(sizeof(char)*1000);
          memset(directoryName,'\0',sizeof(directoryName));
          strcat(directoryName,_dirName);
          strcat(directoryName,"/");
          strcat(directoryName,direntName->d_name);
          processdirInput values;
          values.dirName = opendir(direntName->d_name);
          values._dirName = directoryName;
          values.dirOut = dirOut;
          pthread_create(&tid,0,processDir,(void*)&values);
          pthread_join(tid,NULL);
          continue;  //to skip the current pointer value
      }
      else{
        continue;  //to skip . and ..
      }
    }

    if(isCSV(direntName->d_name)==0) {   //check for CSV files
        char * filename = (char*)malloc(sizeof(char)*1000);
        memset(filename,'\0',sizeof(filename));
        strcat(filename,_dirName);
        strcat(filename,"/");
        strcat(filename,direntName->d_name);
        sorterInput sorterValues;
        sorterValues.sortingCol= _sortingCol;
        sorterValues.file = filename;
        sorterValues.dirout = dirOut;
        pthread_create(&tid,0,fileSorter,(void*)&sorterValues);
        pthread_join(tid,NULL);
        continue;

    }
  }
  pthread_exit(NULL);
}

int isCSV(const char* str){
  if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv")){
    return 0;
  }
  else{
    return -1;
  }
}


int isFile(const char* name){
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

void strip_ext(char *fname){
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}

void getCurrentDir(void){
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
    printf("Working directory: %s\n",directory);
    return;
}


void fileSorter(void* arguments){

  sorterInput *args = arguments;
  char* sortingCol = args -> sortingCol;
  char* file = args -> file;
  char* dirout = args -> dirout;
  FILE* _file = fopen(file, "r");
  printf("[%i]Thread created for csv file: %s\n",1,file);
  if((_file == NULL)){
    printf("[%i]Error sorting file: %s, %s exiting...\n",1,file, strerror(errno));
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

  if(comp_ptr == 28){   // this is the case where input doesn't match the col names list
    comp_ptr = 2; //defaults to num_critic_for_reviews
  }



  split(total,0,init-2,comp_ptr);  // sort the data
  int i;
  for(i = 0; i < (init-1); i++){
    outputHeap = Heap_add(outputHeap,&(total[i]),comp_ptr);
  }

  pthread_exit(NULL);
}

char *strtok_new(char * string, char const* delimiter)
{
   char * delim = (char*)malloc(sizeof(char)*25);
   memset(delim,'/0',sizeof(delim));
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
void toString(data *total){
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
