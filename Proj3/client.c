#include "Sorter.c"
char *strtok_new(char * string, char const * delimiter);
void getCurrentDir(void);
char * _sortingCol;
void processDir(void*);
void fileSorter(void* arguments);
Heap * outputHeap;
int numThreads;
pthread_t tid;

//Client variables -kumail
// We need a socket
//int sockfd;
// We need port number
int port;
// We need a sockaddr_in struct for
// creating server socket
struct sockaddr_in address;
// We need a hostent struct pointer to
// hold server info from gethostbyname()
struct hostent *server;

int main(int argc, char const *argv[]){
  int i, result, totalProcesses;
  char colFlag[10], dirInFlag[10], dirOutFlag[10], hflag[10], pflag[10];   //command line flags
  char * _dirIn = NULL;
  char * _dirOut = NULL; //pointers to names of args
  char * host = NULL;
  int port = 0;
  strcpy(colFlag,"-c");
  strcpy(dirInFlag,"-d");
  strcpy(dirOutFlag,"-o");
  strcpy(hflag,"-h");
  strcpy(pflag,"-p");

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

    result = strcmp(hflag,argv[i]);
    if(result == 0){
      host = argv[i+1];
    }

    result = strcmp(pflag, argv[i]);
    if(result == 0){
      port = atoi(argv[i+1]);
    }
  }

  if(_sortingCol == NULL){             //default behavior will be sort by crits
    printf("Error on input: sorting column not specified, terminating...\n");
    return 0;
  }

  if(host == NULL){             //default behavior will be sort by crits
    printf("Error on input: host not specified, terminating...\n");
    return 0;
  }

  if(port == 0){             //default behavior will be sort by crits
    printf("Error on input: port not specified, terminating...\n");
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
  //client things:
  server = gethostbyname(host);
  // Now we need to initialize sockaddr_in struct
	// before we do initialization, it's good to set buffer zeros
	// replace corresponding parts
	memset(&address, 0, sizeof(address));
	// .sin_family = AF_INET
	address.sin_family = AF_INET;
	// .sin_port = htons(portnumber)
	address.sin_port = htons(port);
	// replace corresponding parts
	// we do binary copy to initialize sockaddr_in address part
	// from hostent pointer
	bcopy((char*)server->h_addr,
			(char*)&address.sin_addr.s_addr,
			server->h_length);
  /*client things end*/

  pthread_create(&tid,0,processDir,(void*)&values);
  numThreads++;
  pthread_join(tid,NULL);

}

void processDir(void* arguments){
  processdirInput *args = arguments;
  DIR* dirName = args -> dirName;
  char* _dirName = args -> _dirName;
  char* dirOut = args -> dirOut;
 //printf("[TID: %u]Thread created for directory: %s\n",pthread_self(),_dirName);


  struct dirent* direntName;
  while((direntName = readdir(dirName)) != NULL){
    char * filename = (char*)malloc(sizeof(char)*1000);
    memset(filename,'\0',sizeof(filename));
    strcat(filename,_dirName);
    strcat(filename,"/");
    strcat(filename,direntName->d_name);


    //printf("[TID: %u]Working with %s\n",pthread_self(),filename);
    if(isFile(filename) == 0) {
      if((strcmp(direntName->d_name,"..") != 0) && (strcmp(direntName->d_name,".") != 0)){  // and not current or prev dir
          processdirInput values;
          values.dirName = opendir(filename);
          values._dirName = filename;
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

void fileSorter(void* arguments){
  sorterInput *args = arguments;
  char* sortingCol = args -> sortingCol;
  char* file = args -> file;
  char* dirout = args -> dirout;
  FILE* _file = fopen(file, "r");
 // printf("[TID: %u]Thread created for csv file: %s\n",pthread_self(),file);
  if((_file == NULL)){
    printf("[TID: %u]Error sorting file: %s, %s exiting...\n",pthread_self(),file, strerror(errno));
    return;
  }

  /****** STEP 1: Create Socket ******/
  // call socket(AF_INET, SOCK_STREAM, 0) to create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    //perror() report error message
    perror("sock");
    //exit your program
    exit(EXIT_FAILURE);
  }

  /****** STEP 2: Connection *******/
  // call connect(socketfd, (struct sockaddr*)&..., sizeof(...))
  if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0)
  {
    // perror() report error message
    perror("connect");
    // close socket
    close(sockfd);
    // exit your program
    exit(EXIT_FAILURE);
  }

  char sortrequest[256];
  strcat(sortrequest,"Sort");
  int n = write(sockfd, file, strlen(file));
   // check if message is sent successfully

  if (n <= 0)
  {
    // perror() again...
    perror("error writing to server");
  }

}
//end filesorter method

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

int isCSV(const char* str){
  if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv")){
    return 0;
  }
  else{
    return -1;
  }
}
