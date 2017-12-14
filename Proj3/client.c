#include "Sorter.c"
void processDir(void* arguments);
char * _sortingCol;
pthread_t tid[1000];
processdirInput values[1000];
sortRequestInput inputVals[1000];
int c = 0;
int d = 0;

int main(int argc, char **argv){
  //command line arguments
  int i, result;
  char colFlag[10], dirInFlag[10], dirOutFlag[10], hflag[10], pflag[10];
  char * _dirIn = NULL;
  char * _dirOut = NULL;
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





  //open a connection with server for sessionID
  int s;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  s = getaddrinfo(host, port, &hints, &results);
  if (s != 0) {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
          exit(1);
  }
  if(connect(sock_fd, results->ai_addr, results->ai_addrlen) == -1){
                perror("connect");
                exit(2);
  }



  // need to get sessionID here and pass it along
  char *requestForID = "Requesting sessionID";
  write(sock_fd, requestForID, strlen(requestForID));
  char sessionID[10];
  int len = read(sock_fd, sessionID,9);
  sessionID[len] = "\0";

  printf("Connected to server with sessionID: %s\n",sessionID);
  close(sock_fd);

  //pthread parameters
  DIR* dirIn = opendir(_dirIn);
  processdirInput values;
  values.dirName = dirIn;
  values._dirName = _dirIn;
  values.sessionID = sessionID;
  values.port = port;
  values.host = host;



  //directory traversals
  pthread_create(&tid[c],0,processDir,(void*)&values);
  c++;
  
  for(i = 0; i<c; i++){
        pthread_join(tid[i],NULL);
  }

  //printf("pthreads are joined.. need to dump now\n");



  //need to restart connection here

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  s = getaddrinfo(host, port, &hints, &results);
  if (s != 0) {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
          exit(1);
  }
  if(connect(sock_fd, results->ai_addr, results->ai_addrlen) == -1){
                perror("connect");
                exit(2);
  }



  //sessionID for dumpRequest
  char tempbuff[100];
  write(sock_fd,sessionID,sizeof(char)*10);
  read(sock_fd,tempbuff,sizeof(char)*100);


  //send dumpRequest
  char* dumpRequest = "Dump";
  write(sock_fd,dumpRequest,strlen(dumpRequest));

  printf("[SID: %s] Sending dump request\n",sessionID);


  //column name creation
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





  //open a file to output dump
  char* outputName = (char*)malloc(sizeof(char)*1000);  //file output name
  memset(outputName,'\0',sizeof(char)*1000);
  strcat(outputName, "AllFiles-sorted-");
  strcat(outputName,_sortingCol);
  strcat(outputName,".csv");
  chdir(_dirOut);
  FILE* foutput;
  foutput = fopen(outputName,"w+");



  //first row creation
  char * firstRow = (char *)malloc(sizeof(char)*1000);
  memset(firstRow,'\0',sizeof(char)*1000);
  for(i=0; i < 28; i++){
    strcat(firstRow,columnNames[i]);
    strcat(firstRow,",");
  }
  fprintf(foutput, "%s\n", firstRow);



  //dump response
  char* ack = "Acknowledged";
  char buffer[9001];
  while(true){
    write(sock_fd,ack,strlen(ack));
    memset(buffer,'\0',sizeof(char)*9001);
    len = read(sock_fd,buffer,sizeof(char)*9000);
    if(len < 0) error("ERROR reading dump from socket\n");
    buffer[len] = '\0';
    //printf("Received: %s\n",buffer);
    //printf("\n");
    if(strcmp(buffer,"FinishedSend") == 0){
      break;
    }
    fprintf(foutput, "%s\n",buffer);

  }
  fclose(foutput);
  printf("File creation completed, closing connection!\n");
  close(sock_fd);
  return 0;
}




void sortRequest(void* arguments){

  /*Will be opened by a thread and open a port to communicate with server*/
  sortRequestInput *args = arguments;
  char * sortingCol = args -> sortingCol;
  char * file = args -> file;
  char * sessionID = args -> sessionID;
  char * port = args -> port;
  char * host = args -> host;
  FILE* _file = fopen(file, "r");



  //File read-in
  if((_file == NULL)){
    printf("[SID: %s]Error sorting file: %s, %s exiting...\n",sessionID,file, strerror(errno));
    return;
  }
  char * col_names[28];  // array which contains name of columns
  int init = 0;         // counter for rows
  data total[10000];     // array for data structs
  char string[1000];    // stdin string buffer
  while(fgets(string,1000,_file)!= NULL){
      pthread_mutex_lock(&mutexC);
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
            //printf("%s\n",col_names[counter]);
            if((strcmp(col_names[counter],"")==0)){
              printf("[TID: %u]CSV format incorrect for file: %s, terminating..\n",pthread_self(),file);
              return;
            }
          }

        }
      pthread_mutex_unlock(&mutexC);
      init++;  //increment the row we're on
    }
  fclose(_file);



  //Socket creation
  printf("[SID: %s]File: %s, has been closed, opening socket...\n",sessionID,file);
  int s,n,i;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;


  //Get server information & connect
  s = getaddrinfo(host, port, &hints, &result);
  if (s != 0) {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
          exit(1);
  }
  if(connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1){
                perror("connect");
                exit(2);
  }



  //conduct service request with sessionID
	n = write(sock_fd, sessionID, sizeof(char)*10);
  if(n == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }


  //get response from service request
	char resp[1000];
	int len = read(sock_fd, resp, 999);
  if(len == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }


  //send sort request
  char* sortReq = "Sort";
  n = write(sock_fd, sortReq, strlen(sortReq));
  if(n == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }


  //response for sort request
  len = read(sock_fd, resp, 999);
  if(len == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }



  //send sortingCol
  n = write(sock_fd,sortingCol,sizeof(char)*100);
  if(n == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }



  //get response for sortingCol
  len = read(sock_fd, resp, 999);
  if(len == -1){
    printf("Error communicating sort request to server, terminating...\n");
    return;
  }


  char bufferIn[9000];
  //send file contents
  for (i = 0; i <(init-1); i++){
    memset(resp,'\0',sizeof(char)*1000);
    memset(bufferIn,'\0',sizeof(char)*9000);
    strcat(bufferIn,total[i].color);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].dirName);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].critCount);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].durMin);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].dirFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act3FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act2Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act1FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].gross);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].genre);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act1Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].title);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].numVoted);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].totalFB);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act3Name);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].faceNum);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].keyWord);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].link);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].numReview);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].lang);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].country);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].rated);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].budget);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].year);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].act2FB);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].score);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].ratio);
    strcat(bufferIn,",");
    strcat(bufferIn,total[i].movieFB);

    //write data to socket
    n = write(sock_fd, bufferIn, strlen(bufferIn));
    //printf("\n");
    //printf("Sending: %s\n",bufferIn);
    if(n == -1){
      printf("[SID: %s]Failed to write bufferIn line\n",sessionID);
      break;
    }

    //read back response
    len = read(sock_fd, resp, 999);
    resp[len] = '\0';

    if(strcmp(resp, "Accepted line") != 0){
      printf("[SID: %s]Failed to recieve bufferIn line by server\n",sessionID);
      break;
    }
  }



  //end of sort message
  char *endBuffer = "Finished";
  n = write(sock_fd, endBuffer, strlen(endBuffer));
  if(n == -1){
    printf("Error writing to socket\n");
  }
  close(sock_fd);
  return;
}

void processDir(void* arguments){
  processdirInput *args = arguments;
  DIR* dirName = args -> dirName;
  char* _dirName = args -> _dirName;
  char* sessionID = args -> sessionID;
  char* port = args -> port;
  char* host = args -> host;

  //printf("[TID: %u]Thread created for directory: %s\n",pthread_self(),_dirName);


  struct dirent* direntName;
  while((direntName = readdir(dirName)) != NULL){
    char * filename = (char*)malloc(sizeof(char)*1000);
    memset(filename,'\0',sizeof(*filename));
    strcat(filename,_dirName);
    strcat(filename,"/");
    strcat(filename,direntName->d_name);



    //printf("[TID: %u]Working with %s\n",pthread_self(),filename);
    if(isFile(filename) == 0) {
      if((strcmp(direntName->d_name,"..") != 0) && (strcmp(direntName->d_name,".") != 0)){  // and not current or prev dir
          //pthread_mutex_lock(&mutexA);
          values[c].dirName = opendir(filename);
          values[c]._dirName = filename;
          values[c].sessionID = sessionID;
          values[c].port = port;
          values[c].host = host;
          pthread_create(&tid[c],0,processDir,(void*)&values[c]);
          pthread_join(tid[c],NULL);
          c++;
          //pthread_mutex_unlock(&mutexA);
          continue;  //to skip the current pointer value
      }
      else{
        continue;  //to skip . and ..
      }
    }

    if(isCSV(direntName->d_name)==0) {   //check for CSV files
        //pthread_mutex_lock(&mutexB);
        inputVals[d].sortingCol= _sortingCol;
        inputVals[d].file = filename;
        inputVals[d].sessionID = sessionID;
        inputVals[d].host = host;
        inputVals[d].port = port;
        pthread_create(&tid[c],0,sortRequest,(void*)&inputVals[d]);
        pthread_join(tid[c],NULL);
        c++;
        d++;
        //pthread_mutex_unlock(&mutexB);
        continue;
    }

  }
  return;
}
