
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

    sessionID = 1;
    //spawn service thread and keep listening
    while(true){
      if (listen(sock_fd, 100) == 0) {
        int client_fd = accept(sock_fd,NULL,NULL);

        //wait for sessionID request
        char request[100];
        int len = read(client_fd, request, sizeof(request)-1);
        request[len] = '\0';
        if(len < 0) error("ERROR reading from socket\n");

        printf("request from client was: %s\n",request);
        //if requesting a sessionID give one
        if(strcmp(request,"Requesting sessionID")==0){


          //send sessionID to client
          char* ID = (char*)malloc(sizeof(char)*4);
          memset(ID,'\0',sizeof(*ID));
          sprintf(ID,"%d",sessionID);
          printf("Giving away SIG: %s\n",ID);
          write(client_fd,ID,sizeof(*ID));
          printf("New client, session ID: %i\n",sessionID);

          //update session list & pass as parameter
          sessions[sessionID-1] = true;
          sessionID++;
          continue;
        }


        //otherwise check if it is a valid sessionID/input
        else if(isNum(request)){
          int checkID = atoi(request);
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
          printf("Client input passed\n");
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
        char* requestType = (char*)malloc(sizeof(char)*100);
        char* sortR = "Sort";
        char* dumpR = "Dump";
        read(client_fd, requestType, sizeof(*requestType));
        printf("[SID: %i]Request is: %s\n",sessionID,requestType);

        //check for error on input
        if((strcmp(requestType,sortR)!=0) && (strcmp(requestType,dumpR)!=0)){
          char* requestTypeFailure = "Invalid request type, terminating connection";
          write(client_fd, requestTypeFailure, strlen(requestTypeFailure));
          close(client_fd);
          continue;
        }


        //parameters to pass for each client request
        serverParams[sessionID-1].sessionID = request;
        serverParams[sessionID-1].requestType = requestType;
        serverParams[sessionID-1].client_fd = client_fd;


        //for sort requests create a heap
        if(strcmp(requestType,sortR) == 0){
          serverParams[sessionID-1].heap = Heap_create(10000);
        }



        //thread creation for client connection
        pthread_create(&tid[numThreads],0,acceptService,(void*)&serverParams[sessionID]);
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
