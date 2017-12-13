
#include "Sorter.c"
pthread_t tid[1000];
serverThreadParams serverParams[1000];
int numThreads = 0;
bool sessions[1000];
int sessionID;


int main(int argc, char **argv)
{
    //command line flag input
    if((argv[1] == NULL) || (argv[2] == NULL)){
      printf("Missing port input, terminating...\n");
      return -1;
    }
    else if(argc > 3){
      printf("Too many command arguments, terminating...\n");
      return -2;
    }
    char *portNum = argv[2];



    //socket creation for server
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;



    //getting server address info
    s = getaddrinfo(NULL, portNum, &hints, &result);
    if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(1);
    }



    //bind socket to server
    if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
        perror("bind()");
        exit(1);
    }

    printf("Server initialized\n");

    //initialize sessions to false
    int i = 0;
    for(i; i < 1000; i++){
      sessions[i] = false;
    }

    //initializing some needed data
    char request[100];
    sessionID = 1;
    int checkID;
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
    char * sortingCol =(char*)malloc(sizeof(char)*100);
    char * ack = "Acknowledged!";



    //spawn service thread and keep listening
    while(true){
      if (listen(sock_fd, 100) == 0) {
        int client_fd = accept(sock_fd,NULL,NULL);

        //wait for sessionID request
        memset(request,'\0',sizeof(char)*100);
        int len = read(client_fd, request, sizeof(request)-1);
        request[len] = '\0';
        if(len < 0) error("ERROR reading from socket\n");

        //printf("request from client was: %s\n",request);
        //if requesting a sessionID give one
        if(strcmp(request,"Requesting sessionID")==0){


          //send sessionID to client
          char ID[4];
          memset(ID,'\0',sizeof(char)*4);
          sprintf(ID,"%d",sessionID);
          //printf("Giving away sessionID: %s\n",ID);
          write(client_fd,ID,4);
          printf("New client, session ID: %i\n",sessionID);

          //update session list & pass as parameter
          sessions[sessionID-1] = true;
          sessionID++;
          continue;
        }


        //otherwise check if it is a valid sessionID/input

        else if(isNum(request)){
          checkID = atoi(request);
          //check if sessionID number is in the correct range
          if((checkID > 1000)||(checkID<1)){
            char* sessionIDFailure = "Invalid sessionID, terminating connection";
            write(client_fd, sessionIDFailure, strlen(sessionIDFailure));
            close(client_fd);
            continue;
          }
          //check if session is active
          if(sessions[checkID-1] == false){
            char* sessionIDFailure = "Invalid sessionID, terminating connection";
            write(client_fd, sessionIDFailure, strlen(sessionIDFailure));
            close(client_fd);
            continue;
          }
          //if error checks were passed
          char* successfulID = "What is your request";
          printf("[SID:%s]Client input valid, Acknowledging connection...\n",request);
          write(client_fd, successfulID, strlen(successfulID));
        }
        //invalid client input scenario
        else{
          char* sessionIDFailure = "Invalid client input, terminating connection";
          write(client_fd, sessionIDFailure, strlen(sessionIDFailure));
          close(client_fd);
          continue;
        }

        //read in type of request
        char requestType[100];
        memset(requestType,'\0',sizeof(char)*100);
        char* sortR = "Sort";
        char* dumpR = "Dump";
        len = read(client_fd, requestType, sizeof(requestType)-1);
        requestType[len] = '\0';
        printf("[SID:%s]Request is: %s\n",request,requestType);

        //check for error on input
        if((strcmp(requestType,sortR)!=0) && (strcmp(requestType,dumpR)!=0)){
          char* requestTypeFailure = "Invalid request type, terminating connection";
          write(client_fd, requestTypeFailure, strlen(requestTypeFailure));
          close(client_fd);
          continue;
        }

        //if its a sort we need the sortingCol
        if(strcmp(requestType,sortR)==0){
          //Acknowledged sort request
      		write(client_fd, ack, strlen(ack));
          memset(sortingCol,'\0',sizeof(char)*100);

      		//Read in sortingCol
      		read(client_fd,sortingCol,sizeof(char)*100);
      		printf("[SID:%s]Received sortingCol: %s\n",sessionID,sortingCol);

          //get the int value of it to send over
          int sortingColumn;
          for(sortingColumn = 0; sortingColumn < 28; sortingColumn++){
            if(strcmp(columnNames[sortingColumn],sortingCol) == 0){
              serverParams[checkID-1].sortingColumn = sortingColumn;
              break;
            }
          }
        }


        //parameters to pass for each client request
        serverParams[checkID-1].sessionID = request;
        serverParams[checkID-1].requestType = requestType;
        serverParams[checkID-1].client_fd = client_fd;


        //for sort requests create a heap
        if(strcmp(requestType,sortR) == 0){
          serverParams[checkID-1].heap = Heap_create(10000);
        }



        //thread creation for client connection
        pthread_create(&tid[numThreads],0,acceptService,(void*)&serverParams[checkID-1]);
        numThreads++;


        //might need to not join pthreads... memory issue and unneeded space usage?
        for(i = 0 ; i < numThreads; i++){
          pthread_join(tid[i],NULL);
        }

      }

      else{
        perror("listen()");
        exit(1);
      }
    }
    return 0;
}
