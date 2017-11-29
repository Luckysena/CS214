
#include "Sorter.c"
char *strtok_new(char * string, char const * delimiter);
void getCurrentDir(void);
char * _sortingCol;
void processDir(void*);
void fileSorter(void* arguments);
Heap * outputHeap;
int numThreads;
pthread_t tid;
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
    printf("Error on input: sorting column not specified, terminating...\n");
    return 0;
  }

  if(_dirIn == NULL){                     //default behavior is current directory
    _dirIn = (char*)malloc(sizeof(char));
    strcpy(_dirIn,".");
  }

  if(_dirOut == NULL){                    //default is directory it was found in (dirIn)
    _dirOut = _dirIn;
  }
  DIR* dirIn = opendir(_dirIn);

  char * columnNames[28];
  for(i = 0; i<28;i++){
    columnNames[i] = (char *) malloc(sizeof(char)*250);
  }
  strcpy(columnNames[0],"color");
  strcpy(columnNames[1],"director_name");
  strcpy(columnNames[2],"num_critic_for_reviews");
  strcpy(columnNames[3],"duration");
  strcpy(columnNames[4],"director_facebook_likes");
  strcpy(columnNames[5],"actor_3_facebook_likes");
  strcpy(columnNames[6],"actor_2_name");
  strcpy(columnNames[7],"actor_1_facebook_likes");
  strcpy(columnNames[8],"gross");
  strcpy(columnNames[9],"genres");
  strcpy(columnNames[10],"actor_1_name");
  strcpy(columnNames[11],"movie_title");
  strcpy(columnNames[12],"num_voted_users");
  strcpy(columnNames[13],"cast_total_facebook_likes");
  strcpy(columnNames[14],"actor_3_name");
  strcpy(columnNames[15],"facenumber_in_poster");
  strcpy(columnNames[16],"plot_keywords");
  strcpy(columnNames[17],"movie_imdb_link");
  strcpy(columnNames[18],"num_user_for_reviews");
  strcpy(columnNames[19],"language");
  strcpy(columnNames[20],"country");
  strcpy(columnNames[21],"content_rating");
  strcpy(columnNames[22],"budget");
  strcpy(columnNames[23],"title_year");
  strcpy(columnNames[24],"actor_2_facebook_likes");
  strcpy(columnNames[25],"imdb_score");
  strcpy(columnNames[26],"aspect_ratio");
  strcpy(columnNames[27],"movie_facebook_likes");

  int sortingColumn;
  for(sortingColumn = 0; sortingColumn < 28; sortingColumn++){
    if(strcmp(columnNames[sortingColumn],_sortingCol) == 0){
      break;
    }
  }
  processdirInput values;
  values.dirName = dirIn;
  values._dirName = _dirIn;
  values.dirOut = _dirOut;

  outputHeap = Heap_create(100000);
  printf("[PID: %i]Original PID\n",getpid());
  printf("[TID: %u]Original thread id\n",pthread_self());
  pthread_create(&tid,0,processDir,(void*)&values);
  numThreads++;
  pthread_join(tid,NULL);

  //printf("Before output file creation, outputHeap size: %i\n",outputHeap->list->size);
  printf("Total number of created threads (excluding main): %i\n",numThreads);
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
  for(i=0; i < 28; i++){
    strcat(firstRow,columnNames[i]);
    strcat(firstRow,",");
  }
  fprintf(foutput, "%s", firstRow);
  char * bufferIn = (char*) malloc(sizeof(char)*9000);  // create buffer for output
  data * tempData;
  /*for (i = 0; i <(outputHeap->list->size) ; i++)
  {
    printf("[%i]%s\n",i,outputHeap->list->nodeList[i]->dataVal->durMin);
  }*/
  int listSize = outputHeap->list->size;
  for (i = 0; i <(listSize-1) ; i++)
  {
    tempData = Heap_remove(outputHeap,sortingColumn);
    //printf("Removed from heap: %s\n",tempData->durMin);
    memset(bufferIn,'\0',sizeof(bufferIn));
    strcat(bufferIn,tempData->color);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->dirName);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->critCount);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->durMin);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->dirFB);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act3FB);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act2Name);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act1FB);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->gross);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->genre);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act1Name);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->title);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->numVoted);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->totalFB);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act3Name);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->faceNum);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->keyWord);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->link);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->numReview);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->lang);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->country);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->rated);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->budget);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->year);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->act2FB);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->score);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->ratio);
    strcat(bufferIn,",");
    strcat(bufferIn,tempData->movieFB);
    fprintf(foutput, "%s\n",bufferIn); //output
  }

  fclose(foutput);

  return 0;
}

void processDir(void* arguments){

  processdirInput *args = arguments;
  DIR* dirName = args -> dirName;
  char* _dirName = args -> _dirName;
  char* dirOut = args -> dirOut;
  printf("[TID: %u]Thread created for directory: %s\n",pthread_self(),_dirName);


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
          //printf("[TID: %u]Thread created for directory: %s\n",pthread_self(),_dirName);
          numThreads++;
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
        //printf("[TID: %u]Thread created for csv file: %s\n",pthread_self(),filename);
        numThreads++;
        pthread_join(tid,NULL);
        /*int i;
        for(i = 0; i < outputHeap->list->size; i++){
          printf("After Sort, Values at %i, is: %s\n",i,outputHeap->list->nodeList[i]->dataVal->title);
        }*/
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
  printf("[TID: %u]Thread created for csv file: %s\n",pthread_self(),file);
  if((_file == NULL)){
    printf("[TID: %u]Error sorting file: %s, %s exiting...\n",pthread_self(),file, strerror(errno));
    return;
  }
  char * col_names[28];  // array which contains name of columns
  int init = 0;         // counter for rows
  data total[30000];     // array for data structs
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
              printf("[TID: %i]CSV format incorrect, terminating..\n",pthread_self());
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

  int i;
  //split(total,0,init-2,comp_ptr);  // sort the data
  for(i = 0; i < (init-1); i++){
    Heap_add(outputHeap,&(total[i]),comp_ptr);
  }

  pthread_detach(pthread_self());
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
