#include "Sorter.c"
void processDir(void* arguments);
char * _sortingCol;
pthread_t tid;
int numThreads;

int main(int argc, char **argv)
{

  int i, result, totalProcesses;
  char colFlag[10], dirInFlag[10], dirOutFlag[10], hflag[10], pflag[10];   //command line flags
  char * _dirIn = NULL;
  char * _dirOut = NULL; //pointers to names of args
  char * host = NULL;
  char * port = NULL;
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
      port = argv[i+1];
    }
  }

  if(_sortingCol == NULL){
    printf("Error on input: sorting column not specified, terminating...\n");
    return 0;
  }

  if(host == NULL){
    printf("Error on input: host not specified, terminating...\n");
    return 0;
  }

  if(port == NULL){
    printf("Error on input: port not specified, terminating...\n");
    return 0;
  }

  if(_dirIn == NULL){
    _dirIn = (char*)malloc(sizeof(char));
    strcpy(_dirIn,".");
  }

  if(_dirOut == NULL){
    _dirOut = _dirIn;
  }

  DIR* dirIn = opendir(_dirIn);
  processdirInput values;
  values.dirName = dirIn;
  values._dirName = _dirIn;
  values.dirOut = _dirOut;
  values.host = host;
  values.port = port;

  numThreads = 1;
  pthread_create(&tid,0,processDir,(void*)&values);
  numThreads++;
  pthread_join(tid,NULL);
  return 0;

}

void sortRequest(void* arguments){
  sortRequestInput *args = arguments;
  char * sortingCol = args -> sortingCol;
  char * file = args -> file;
  char * host = args -> host;
  char * port = args -> port;
  FILE* _file = fopen(file, "r");
  printf("[TID: %u]Thread created for csv file: %s\n",pthread_self(),file);
  if((_file == NULL)){
    printf("[TID: %u]Error sorting file: %s, %s exiting...\n",pthread_self(),file, strerror(errno));
    return;
  }
  char * col_names[28];  // array which contains name of columns
  int init = 0;         // counter for rows
  data total[10000];     // array for data structs
  char string[1000];    // stdin string buffer

  while(fgets(string,1000,_file)!= NULL){
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

  // socket connections
	int s, n;
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hints, *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	s = getaddrinfo(host, port, &hints, &result);
	if (s != 0) {
	        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        	exit(1);
	}

	if(connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1){
                perror("connect");
                exit(2);
        }

	char *buffer = "Sort";

	n = write(sock_fd, buffer, strlen(buffer));
  if(n != -1){
    printf("[TID: %u]Sending sort request...\n",pthread_self());
  }
  else{
    printf("Error writing to socket\n");
  }

	char resp[1000];
	int len = read(sock_fd, resp, 999);
	resp[len] = '\0';
	printf("[TID: %u]%s\n", pthread_self(),resp);

  n = write(sock_fd,sortingCol,strlen(sortingCol));
  if(n != -1){
    printf("Sending sortingCol...\n");
  }
  else{
    printf("Error writing to socket\n");
  }

  len = read(sock_fd, resp, 999);
  resp[len] = '\0';
  printf("[TID: %u]%s\n",pthread_self(), resp);
  return;

}



void processDir(void* arguments){
  processdirInput *args = arguments;
  DIR* dirName = args -> dirName;
  char* _dirName = args -> _dirName;
  char* dirOut = args -> dirOut;
  char* host = args -> host;
  char* port = args -> port;
  printf("[TID: %u]Thread created for directory: %s\n",pthread_self(),_dirName);


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
          values.host = host;
          values.port = port;
          pthread_create(&tid,0,processDir,(void*)&values);
          numThreads++;
          //pthread_join(tid,NULL);
          continue;  //to skip the current pointer value
      }
      else{
        continue;  //to skip . and ..
      }
    }

    if(isCSV(direntName->d_name)==0) {   //check for CSV files
        sortRequestInput inputVals;
        inputVals.sortingCol= _sortingCol;
        inputVals.file = filename;
        inputVals.host = host;
        inputVals.port = port;
        pthread_create(&tid,0,sortRequest,(void*)&inputVals);
        numThreads++;
        //pthread_join(tid,NULL);

        continue;

    }
  }
}
